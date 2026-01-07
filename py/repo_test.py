"""
A set of classes for performing a specific test within a git repo.
Base classes can be created for performing tool-specific tests.
Several generic test classes are included that could be used in any
type of repository.
"""

import datetime
import os
import pathlib
import queue
import re
import shutil
import subprocess
import sys
import tempfile
import threading
import time
from enum import Enum

from git import Repo
from mytypes import ResultType
from repo_test_suite import RepoTestSuite

##########################################################
# Useful static functions for manipulating and querying git repos
# These functions are independent of the repo_test classes.
##########################################################


def fetch_remote(repo, remote_name=None):
    """Fetch updates from the remote repository.
    This function may raise an Exception."""
    try:
        # Ensure the local repository is not in a detached HEAD state
        # TODO: provide a flat to check for detached state? No problems with fetch
        # if repo.head.is_detached:
        #     raise Exception("The repository is in a detached HEAD state.")
        if remote_name is not None:
            if remote_name not in repo.remotes:
                raise Exception(f"Remote {remote_name} not found in repository")
            remote = repo.remotes[remote_name]
        else:
            remote = repo.remotes.origin
        remote.fetch()
        return True
    except Exception as e:
        raise Exception(f"Error fetching updates from remote: {e}")


def get_unpushed_commits(repo, remote_name=None, remote_branch_name=None):
    """Get a list of unpushed commits in the local repository."""

    # Fetch the remote before doing the compare
    fetch_remote(repo, remote_name)

    # Get the remote branch reference
    if remote_name is None:
        remote_name = "origin"
    if remote_branch_name is None:
        remote_branch_name = repo.active_branch.name

    remote_branch = f"{remote_name}/{remote_branch_name}"

    # Commit is used instead of branch name since tags don't have branch names (but they have commits)
    # local_branch = repo.active_branch.name
    local_commit = repo.head.commit

    # Check for unpushed local commits
    # unpushed_commits = list(repo.iter_commits(f"{remote_branch}..{local_branch}"))
    unpushed_commits = list(repo.iter_commits(f"{remote_branch}..{local_commit}"))
    return unpushed_commits
    # if unpushed_commits:
    #     print(f"Local branch '{current_branch}' has unpushed commits:")
    #     for commit in unpushed_commits:
    #         print(f"  - {commit.hexsha[:7]}: {commit.message.strip()}")
    # else:
    #     print(f"No unpushed commits in local branch '{current_branch}'.")


def get_unpulled_commits(
    repo, remote_name=None, remote_branch_name=None, date_limit=None
):
    """Get a list of unpulled commits in the local repository."""
    # Fetch the remote before doing the compare
    fetch_remote(repo, remote_name)
    # Get the remote branch reference
    if remote_name is None:
        remote_name = "origin"
    if remote_branch_name is None:
        remote_branch_name = "main"
    # Create branch names
    remote_branch = f"{remote_name}/{remote_branch_name}"
    # Commit is used instead of branch name since tags don't have branch names (but they have commits)
    # local_branch = repo.active_branch.name
    local_commit = repo.head.commit
    # unpulled_commits = list(repo.iter_commits(f"{local_branch}..{remote_branch}"))
    unpulled_commits = list(repo.iter_commits(f"{local_commit}..{remote_branch}"))
    # Remove those commits that are after the date limit
    if date_limit is not None:
        unpulled_commits = [
            commit
            for commit in unpulled_commits
            if datetime.datetime.fromtimestamp(commit.committed_date) <= date_limit
        ]
    return unpulled_commits
    # if unpulled_commits:
    #     print(f"Remote branch '{remote_branch}' has unpulled commits:")
    #     for commit in unpulled_commits:
    #         print(f"  - {commit.hexsha[:7]}: {commit.message.strip()}")
    # else:
    #     print(f"No unpulled commits from remote branch '{remote_branch}'.")


def get_uncommitted_tracked_files(repo):
    """Get a list of uncommitted files in the local repository."""
    uncommitted_changes = repo.index.diff(None)
    modified_files = [
        item.a_path for item in uncommitted_changes if item.change_type == "M"
    ]
    return modified_files


def get_remote_tags():
    try:
        result = subprocess.run(
            ["git fetch --tags --force"], shell=True, capture_output=True, text=True
        )
        print(result.stdout)
    except subprocess.CalledProcessError as e:
        return False
    return True


def get_commit_file_contents(commit, file_path):
    try:
        file_content = (commit.tree / file_path).data_stream.read().decode("utf-8")
        if len(file_content) > 0:
            return file_content
    except KeyError:
        return None
    return None


#########################################################3
# Base repo test classes
#########################################################3


class RepoTestResult:
    """Class for indicating the result of a repo test"""

    def __init__(self, test, result=ResultType.SUCCESS, msg=None):
        self.test = test
        self.result = result
        self.msg = msg


class RepoTest:
    """Class for performing a test on files within a repository.
    Each instance of this class represents a _single_ test with a single
    executable. Multiple tests can be performed by creating multiple instances
    of this test class.
    This is intended as a super class for custom test modules.
    """

    def __init__(
        self,
        repo_test_suite,
        *,
        dir_path=".",
        abort_on_error=True,
        process_output_filename=None,
        timeout_seconds=0,
    ):
        """Initialize the test module with a repo object"""
        assert isinstance(repo_test_suite, RepoTestSuite)
        self.repo_test_suite = repo_test_suite
        self.abort_on_error = abort_on_error
        self.process_output_filename = process_output_filename
        # List of files that should be deleted after the test is done (i.e., log files)
        self.files_to_delete = []
        self.timeout_seconds = timeout_seconds
        self.dir_path = pathlib.Path(dir_path)

    def module_name(self):
        """returns a string indicating the name of the module. Used for logging."""
        return "BASE MODULE"

    def perform_test(self):
        """This function should be overridden by a subclass. It performs the test using
        the self.repo_test_suite object to obtain test-specific information."""
        return False

    def success_result(self, msg=None):
        return RepoTestResult(self, ResultType.SUCCESS, msg)

    def warning_result(self, msg=None):
        return RepoTestResult(self, ResultType.WARNING, msg)

    def error_result(self, msg=None):
        return RepoTestResult(self, ResultType.ERROR, msg)

    def read_stdout_to_queue_thread(proc, output_queue):
        while True:
            line = proc.stdout.readline()
            if line:
                output_queue.put(line.strip())
            else:
                break

    def execute_command(self, proc_cmd, process_output_filepath=None, print_dots=True):
        """Completes a sub-process command. and print to a file and stdout.
        Args:
            proc_cmd -- The string command to be executed.
            proc_wd -- The directory in which the command should be executed. Note that the execution directory
                can be anywhere and not necessarily within the repository. If this is None, the self.working_path
                will be used.
            print_to_stdout -- If True, the output of the command will be printed to stdout.
            print_message -- If True, messages will be printed to stdout about the command being executed.
            process_output_filepath -- The file path to which the output of the command should be written.
                This can be None if no output file is wanted.
        Returns: the sub-process return code
        """

        cmd_str = " ".join(proc_cmd)
        message = f"Executing the following command in directory {self.repo_test_suite.working_path}: {cmd_str} "
        self.repo_test_suite.print(message)

        if process_output_filepath is None:
            cm = tempfile.NamedTemporaryFile(delete=False, mode="w+t", encoding="utf-8")
            filename = cm.name
        else:
            cm = open(process_output_filepath, "w", encoding="utf-8")
            filename = process_output_filepath
            self.files_to_delete.append(process_output_filepath)

        self.repo_test_suite.print(f"Writing output to: {filename}")

        with cm as fp:
            fp.write(message + "\n")

            # Execute command
            assert self.dir_path.is_dir(), f"Directory does not exist: {self.dir_path}"
            start_time = time.time()
            proc = subprocess.Popen(
                proc_cmd,
                cwd=self.dir_path,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
                universal_newlines=True,
            )
            output_queue = queue.Queue()
            output_thread = threading.Thread(
                target=RepoTest.read_stdout_to_queue_thread, args=(proc, output_queue)
            )
            output_thread.start()

            last_dot_time = start_time
            while proc.poll() is None and output_thread.is_alive():
                try:
                    line = output_queue.get(timeout=1.0)
                    line = line + "\n"
                    if self.repo_test_suite.print_to_stdout:
                        pass
                        # sys.stdout.write(line)
                        # sys.stdout.flush()
                    if self.repo_test_suite.test_log_fp:
                        self.repo_test_suite.test_log_fp.write(line)
                        self.repo_test_suite.test_log_fp.flush()
                    if fp:
                        fp.write(line)
                        fp.flush()
                except queue.Empty:
                    # If the queue is empty, just move on: we waited for output and will try again
                    pass

                # Print a dot every 10 seconds to show progress
                if print_dots:
                    current_time = time.time()
                    if current_time - last_dot_time >= 5:
                        sys.stdout.write(".")
                        sys.stdout.flush()
                        last_dot_time = current_time

                if self.timeout_seconds > 0:
                    elapsed_time = time.time() - start_time
                    if elapsed_time > self.timeout_seconds:
                        # Timeout exceeded, terminate the process
                        self.repo_test_suite.print_error(
                            f"Process exceeded {self.timeout_seconds} seconds and was terminated."
                        )
                        proc.terminate()
                        return 1
            proc.communicate()
            print()
            return proc.returncode

    def cleanup(self):
        """Cleanup any files that were created by the test."""
        for file in self.files_to_delete:
            if os.path.exists(file):
                os.remove(file)

    def print_files(self, files, severity):
        MAX_NUM_PRINTED_FILES = 10
        assert severity in (ResultType.WARNING, ResultType.ERROR)
        print_fcn = (
            self.repo_test_suite.print_warning
            if severity == ResultType.WARNING
            else self.repo_test_suite.print_error
        )
        for file in files[:MAX_NUM_PRINTED_FILES]:
            print_fcn(f"  {file}")
        if len(files) > MAX_NUM_PRINTED_FILES:
            print_fcn(f"  ... and {len(files) - MAX_NUM_PRINTED_FILES} more files.")


#########################################################3
# Generic, non-repo test classes
#########################################################3


class FileExistsTest(RepoTest):
    """Checks to see if files exist in a repo directory. Note that this is a file system
    check and not a git check. The intent of this test is to see if the given file is
    created after executing some other command.

    This test also has the option of copying the files to a directory after the file check
    for later review.
    """

    def __init__(
        self,
        repo_test_suite,
        repo_file_list,
        abort_on_error=True,
        copy_dir=None,
        prepend_file_str=None,
        force_copy=True,
    ):
        """repo_file_list is a list of files that should exist in the repo directory.
        copy_dir : the directory to copy the file should the file exist
        prepend_file_str : a string to prepend to the file name when copying"""
        super().__init__(repo_test_suite, abort_on_error=abort_on_error)
        self.repo_file_list = repo_file_list
        self.copy_dir = copy_dir
        self.prepend_file_str = prepend_file_str
        self.force_copy = force_copy

    def module_name(self):
        name_str = "Files Exist: "
        return name_str + ", ".join(
            [
                str(s.relative_to(self.repo_test_suite.repo_root_path))
                for s in self.repo_file_list
            ]
        )

    def perform_test(self):
        success = True
        existing_files = []

        for repo_file in self.repo_file_list:
            file_path = self.repo_test_suite.working_path / repo_file
            if not os.path.exists(file_path):
                self.repo_test_suite.print_error(
                    f"File does not exist: {file_path.relative_to(self.repo_test_suite.repo_root_path)}"
                )
                success = False
            else:
                self.repo_test_suite.print(
                    f"File exists: {file_path.relative_to(self.repo_test_suite.repo_root_path)}"
                )
                existing_files.append(file_path)

        if self.copy_dir is not None:
            # Copy files to the copy directory
            if not os.path.exists(self.copy_dir):
                self.repo_test_suite.print_error(
                    f"Copy directory does not exist: {self.copy_dir}"
                )
            else:
                for orig_filepath in existing_files:
                    orig_filename = orig_filepath.name
                    if self.prepend_file_str is not None:
                        new_filename = f"{self.prepend_file_str}{orig_filename}"
                    else:
                        new_filename = orig_filename
                    new_file_path = pathlib.Path(self.copy_dir) / new_filename
                    try:
                        # see if target file already exists
                        if os.path.exists(new_file_path):
                            if self.force_copy:
                                os.remove(new_file_path)
                            else:
                                self.repo_test_suite.print_error(
                                    f"File already exists in copy directory: {new_file_path}"
                                )
                                continue
                        shutil.copy2(orig_filename, new_file_path)
                        self.repo_test_suite.print(
                            f"Copied {orig_filename} to {new_file_path}"
                        )
                    except Exception as e:
                        self.repo_test_suite.print_error(
                            f"Error copying file {orig_filename} to {new_file_path}: {e}"
                        )
        if success:
            return self.success_result()
        return self.error_result()


class FileRegexCheck(RepoTest):
    """Checks to see if a given file has a given regular expression match."""

    def __init__(
        self,
        repo_test_suite,
        filename,
        regex_str,
        module_name=None,
        error_msg=None,
        error_on_match=True,
        abort_on_error=True,
    ):
        """filename: name of file to check
         regex_str: regular expression string to match
         error_on_match: if True, an error will be thrown if the regex does match,
            otherwise an error is thrown if the regex does not match
        module_name: name to print for module (to override default)
        """
        super().__init__(repo_test_suite, abort_on_error=abort_on_error)
        self.filename = filename
        self.regex_str = regex_str
        self.error_on_match = error_on_match
        self.module_name_str = module_name
        self.error_msg = error_msg

    def module_name(self):
        if self.module_name_str is not None:
            return self.module_name_str
        return f"File Regex Check: {self.filename} - {self.regex_str} - Error on match: {self.error_on_match}"

    def perform_test(self):
        file_path = self.repo_test_suite.working_path / self.filename
        if not os.path.exists(file_path):
            self.repo_test_suite.print_error(f"File does not exist: {file_path}")
            return self.error_result()
        # Check to see if there is a match
        regex_match = False
        with open(file_path, "r") as file:
            file_contents = file.read()
            regex_match = re.search(self.regex_str, file_contents)
        if (
            regex_match
            and not self.error_on_match
            or not regex_match
            and self.error_on_match
        ):
            return self.success_result()
        if self.error_msg is not None:
            self.repo_test_suite.print_error(self.error_msg)
        return self.error_result()


class FileNotTrackedTest(RepoTest):
    """Checks to see if a given file is 'not tracked' in the repository.
    This is usually used to test for files that are created during the
    build and not meant for tracking in the repository.
    """

    def __init__(self, files_not_tracked_list):
        super().__init__()
        self.files_not_tracked_list = files_not_tracked_list

    def module_name(self):
        name_str = "Files Not Tracked: "
        for repo_file in self.files_not_tracked_list:
            name_str += f"{repo_file}, "
        return name_str[:-2]  # Remove the last two characters (', ')

    def perform_test(self):
        return_val = True
        test_dir = self.repo_test_suite.working_path
        tracked_dir_files = self.repo_test_suite.repo.git.ls_files(
            test_dir
        ).splitlines()
        # Get the filenames from the full path
        tracked_dir_filenames = [pathlib.Path(file).name for file in tracked_dir_files]
        # print(tracked_dir_filenames)
        for not_tracked_file in self.files_not_tracked_list:
            # file_path = repo_test_suite.working_path / repo_file
            # print("checking",not_tracked_file)
            # Check to make sure this file is not tracked
            if not_tracked_file in tracked_dir_filenames:
                self.repo_test_suite.print_error(
                    f"File should NOT be tracked in the repository: {not_tracked_file}"
                )
                # print(repo_test_suite.repo.untracked_files)
                return_val = False
        if return_val:
            return self.success_result()
        return self.error_result()


class FileTrackedTest(RepoTest):
    """Checks to see if a given file is 'not tracked' in the repository.
    This is usually used to test for files that are created during the
    build and not meant for tracking in the repository.
    """

    def __init__(self, repo_test_suite, files_tracked_list):
        super().__init__(repo_test_suite)
        for file in files_tracked_list:
            assert isinstance(file, pathlib.Path) and file.is_absolute()
        self.files_tracked_list = files_tracked_list

    def module_name(self):
        name_str = "Files Tracked: "
        return name_str + ", ".join(
            [
                str(s.relative_to(self.repo_test_suite.repo_root_path))
                for s in self.files_tracked_list
            ]
        )

    def perform_test(self):
        success = True
        test_dir = self.repo_test_suite.working_path
        tracked_dir_files = self.repo_test_suite.repo.git.ls_files(
            test_dir
        ).splitlines()
        tracked_dir_files = [
            self.repo_test_suite.repo_root_path / file for file in tracked_dir_files
        ]

        for tracked_file in self.files_tracked_list:
            if tracked_file not in tracked_dir_files:
                self.repo_test_suite.print_error(
                    f"File should be tracked in the repository: {tracked_file.relative_to(self.repo_test_suite.repo_root_path)}"
                )
                success = False
        if success:
            return self.success_result()
        return self.error_result()


class MakeTest(RepoTest):
    """Executes a Makefile rule in the repository."""

    def __init__(
        self,
        repo_test_suite,
        make_rule,
        *,
        dir_path=".",
        required_input_files=None,
        required_build_files=None,
        generate_output_file=True,
        make_output_filename=None,
        abort_on_error=True,
        timeout_seconds=60,
        copy_build_files_dir=None,
        copy_prefice_str=None,
    ):
        """- make_rule: the string makefile rule that is executed.
        - required_input_files: list of files that should exist before the make rule is executed.
        - required_build_files: list of files that should be created after the make rule is executed.
        - generate_output_file: if True, an output file will be generated with the make output.
        - make_output_filename: the name of the output file. If None, a default name will be generated.
        - copy_build_files_dir: the directory to copy the build files to after the make rule is executed
          (default is None in which case no files are copied)
        - copy_prefice_str: string to prepend to the copied file name
        """
        if generate_output_file and make_output_filename is None:
            # default makefile output filename
            make_output_filename = "make_" + make_rule.replace(" ", "_") + ".log"
        super().__init__(
            repo_test_suite,
            dir_path=dir_path,
            abort_on_error=abort_on_error,
            process_output_filename=make_output_filename,
            timeout_seconds=timeout_seconds,
        )
        self.make_rule = make_rule
        self.required_input_files = required_input_files
        self.required_build_files = required_build_files
        self.copy_build_files_dir = copy_build_files_dir
        self.copy_prefice_str = copy_prefice_str

    def module_name(self):
        """Generates custom module name string"""
        name_str = f"Makefile: 'make {self.make_rule}'"
        if self.required_input_files is not None and len(self.required_input_files) > 0:
            name_str += " required: "
            for required_file in self.required_input_files:
                name_str += f"{required_file}, "
            name_str = name_str[:-2]
        if self.required_build_files is not None and len(self.required_build_files) > 0:
            name_str += " ["
            for build_file in self.required_build_files:
                name_str += f"{build_file}, "
            name_str = name_str[:-2]
            name_str += "]"
        return name_str

    def perform_test(self):
        # Check to see if the required input files exist
        if self.required_input_files:
            for file in self.required_input_files:
                file_path = self.dir_path / file
                if not file_path.exists():
                    self.repo_test_suite.print_error(
                        f" Required file for Makefile rule '{self.make_rule}' does not exist: {file_path}"
                    )
                    return self.error_result()

        # Run the rule
        cmd = ["make", self.make_rule]
        # Get a temporary file for the make output using tempfile module
        make_return_val = self.execute_command(cmd)

        # Check to see if the make rule was successful
        if make_return_val != 0:
            return self.error_result()
        result = self.success_result()

        # Check to see if the required build files exist.
        missing_build_files = []
        if self.required_build_files:
            for file in self.required_build_files:
                file_path = self.dir_path / file
                if not file_path.exists():
                    missing_build_files.append(file_path)

        if missing_build_files:
            missing_files_str = ""
            for file in missing_build_files:
                missing_files_str += f"{file} "
            self.repo_test_suite.print_error(f"Missing build files:")
            self.print_files(missing_build_files, ResultType.ERROR)
            result = self.error_result()

        elif self.copy_build_files_dir is not None:  # all the files exist
            #  If the build files are to be copied, copy them to the copy directory
            for build_file in self.required_build_files:
                self.copy_build_file(self.repo_test_suite, build_file)
        return result

    def copy_build_file(self, repo_test_suite, build_file):
        """Copies the build file to the copy directory"""
        build_file_path = pathlib.Path(build_file)
        dest_filename = f"{build_file_path.name}"
        if self.copy_prefice_str is not None:
            dest_filename = f"{self.copy_prefice_str}_{dest_filename}"
        dest_path = pathlib.Path(self.copy_build_files_dir) / dest_filename
        repo_test_suite.print(f"Copying {build_file_path} to {dest_path}")
        try:
            shutil.copyfile(build_file_path, dest_path)
        except Exception as e:
            repo_test_suite.print(
                f"Error copying file {build_file_path} to {dest_path}"
            )
            repo_test_suite.print(f"Error: {e}")
            return False


class ExecsExistTest(RepoTest):
    """Determines whether an executable exists in the path (like unix)"""

    def __init__(self, executables, abort_on_error=True):
        super().__init__(abort_on_error=abort_on_error)
        self.executables = executables

    def module_name(self):
        name_str = "Executables Exist: "
        for executable in self.executables:
            name_str += f"{executable}, "
        return name_str[:-2]  # Remove the last two characters (', ')

    def perform_test(self):
        return_val = True
        for executable in self.executables:
            cmd = ["which", self.self.executable]
            which_val = self.execute_command(cmd)
            if which_val != 0:
                return_val = False
        if not return_val:
            return self.error_result()
        return self.success_result()


#########################################################3
# Git repo test classes
#########################################################3


class CheckForUntrackedFiles(RepoTest):
    """This tests the repo for any untracked files in the repository."""

    def __init__(self, repo_test_suite, ignore_ok=True):
        """ """
        super().__init__(repo_test_suite)
        self.ignore_ok = ignore_ok

    def module_name(self):
        return "Check for untracked git files"

    def perform_test(self):
        # TODO: look into using repo.untracked_files instead of git command

        untracked_files = self.repo_test_suite.repo.git.ls_files(
            "--others", "--exclude-standard"
        )
        if untracked_files:
            self.repo_test_suite.print_error("Untracked files found in repository:")
            files = untracked_files.splitlines()
            self.print_files(files, ResultType.WARNING)
            return self.warning_result()
        self.repo_test_suite.print("No untracked files found in repository")
        # return True
        return self.success_result()


class CheckForTag(RepoTest):
    """This tests to see if the given tag exists in the repository."""

    def __init__(self, tag_name):
        """ """
        super().__init__()
        self.tag_name = tag_name

    def module_name(self):
        return f"Check for tag '{self.tag_name}'"

    def perform_test(self):
        if self.tag_name in self.repo_test_suite.repo.tags:
            commit = self.repo_test_suite.repo.tags[self.tag_name].commit
            commit_date = datetime.datetime.fromtimestamp(
                commit.committed_date
            ).strftime("%Y-%m-%d %H:%M:%S")
            self.repo_test_suite.print(
                f"Tag '{self.tag_name}' found in repository (commit date: {commit_date})"
            )
            return self.success_result()
        self.repo_test_suite.print_error(f"Tag {self.tag_name} not found in repository")
        return self.warning_result()


class CheckForMaxRepoFiles(RepoTest):
    """Check to see if the repository has more than a given number of files."""

    def __init__(self, repo_test_suite, max_dir_files):
        """ """
        super().__init__(repo_test_suite)
        self.max_dir_files = max_dir_files

    def module_name(self):
        return "Check for max tracked repo files"

    def perform_test(self):
        tracked_files = self.repo_test_suite.repo.git.ls_files(
            self.repo_test_suite.relative_repo_path
        ).split("\n")
        n_tracked_files = len(tracked_files)
        self.repo_test_suite.print(
            f"{n_tracked_files} Tracked git files in {self.repo_test_suite.relative_repo_path}"
        )
        if n_tracked_files > self.max_dir_files:
            self.repo_test_suite.print_error(f"  Too many tracked files")
            return self.warning_result()
        return self.success_result()


class CheckForIgnoredFiles(RepoTest):
    """Checks to see if there are any ignored files in the repo directory.
    The intent is to make sure that these ignore files are removed through a clean
    operation. Returns true if there are no ignored files in the directory.
    """

    def __init__(self, repo_test_suite, check_path=None):
        """ """
        super().__init__(repo_test_suite)
        self.check_path = check_path

    def module_name(self):
        return "Check for ignored GIT files"

    def perform_test(self):
        if self.check_path is None:
            self.check_path = self.repo_test_suite.working_path
        # TODO: look into using repo.untracked_files instead of git command
        self.repo_test_suite.print(f"Checking for ignored files at {self.check_path}")
        ignored_files = self.repo_test_suite.repo.git.ls_files(
            self.check_path, "--others", "--ignored", "--exclude-standard"
        )
        if ignored_files:
            self.repo_test_suite.print_warning("Ignored files found in repository:")
            files = ignored_files.splitlines()
            self.print_files(files, ResultType.WARNING)
            return self.warning_result()
        self.repo_test_suite.print("No ignored files found in repository")
        # return True
        return self.success_result()


class CheckForUncommittedFiles(RepoTest):
    """Checks for uncommitted files in the repo directory."""

    def __init__(self, repo_test_suite):
        """ """
        super().__init__(repo_test_suite)

    def module_name(self):
        return "Check for uncommitted git files"

    def find_uncommitted_tracked_files(self, dir=None):
        """Static function that finds uncommitted files in the repo."""
        uncommitted_changes = self.repo_test_suite.repo.index.diff(None)
        modified_files = [
            item.a_path for item in uncommitted_changes if item.change_type == "M"
        ]
        return modified_files

    def perform_test(self):
        modified_files = self.find_uncommitted_tracked_files()
        if modified_files:
            self.repo_test_suite.print_warning("Uncommitted files found in repository:")
            self.print_files(modified_files, ResultType.WARNING)
            return self.warning_result()
        self.repo_test_suite.print("No uncommitted files found in repository")
        # return True
        return self.success_result()


class CheckNumberOfFiles(RepoTest):
    """Counts the number of files in the repo directory."""

    def __init__(self, max_files=sys.maxsize):
        """ """
        super().__init__()
        self.max_files = max_files

    def module_name(self):
        return "Count files in repo dir"

    def perform_test(self):
        uncommitted_files = self.repo_test_suite.repo.git.status("--suno")
        if uncommitted_files:
            self.repo_test_suite.print_error("Uncommitted files found in repository:")
            files = uncommitted_files.splitlines()
            for file in files:
                self.repo_test_suite.print_error(f"  {file}")
            # return False
            return self.warning_result()
        self.repo_test_suite.print("No uncommitted files found in repository")
        # return True
        return self.success_result()


class ListGitCommits(RepoTest):
    """Prints the commits of the given directory in the repo."""

    def __init__(self, check_path=None):
        """ """
        super().__init__()
        self.check_path = check_path

    def module_name(self):
        return "List Git Commits"

    def perform_test(self):
        if self.check_path is None:
            self.check_path = self.repo_test_suite.working_path
        relative_path = self.check_path.relative_to(self.repo_test_suite.repo_root_path)
        self.repo_test_suite.print(f"Checking for commits at {relative_path}")
        commits = list(self.repo_test_suite.repo.iter_commits(paths=relative_path))
        for commit in commits:
            commit_hash = commit.hexsha[:7]
            commit_message = commit.message.strip()
            commit_date = commit.committed_datetime.strftime("%Y-%m-%d %H:%M:%S")
            print(f"{commit_hash} - {commit_date} - {commit_message}")
        # return True
        return self.success_result()


class CheckRemoteOrigin(RepoTest):
    """Checks to see if the remote origin matches the local."""

    def __init__(self, repo_test_suite):
        """ """
        super().__init__(repo_test_suite)

    def module_name(self):
        return "Compare local repository to remote"

    def perform_test(self):
        try:
            # 1. Check for unpushed commits
            unpushed_commits = get_unpushed_commits(self.repo_test_suite.repo)
            if unpushed_commits:
                self.repo_test_suite.print_warning("Local branch has unpushed commits:")
                for commit in unpushed_commits:
                    self.repo_test_suite.print_warning(
                        f"  - {commit.hexsha[:7]}: {commit.message.strip()}"
                    )
                return self.warning_result()
            # 2. Check for unpulled commits
            unpulled_commits = get_unpulled_commits(self.repo_test_suite.repo)
            if unpulled_commits:
                self.repo_test_suite.print_warning("Local branch has unpulled commits:")
                for commit in unpulled_commits:
                    self.repo_test_suite.print_warning(
                        f"  - {commit.hexsha[:7]}: {commit.message.strip()}"
                    )
                return self.warning_result()
        except Exception as e:
            self.repo_test_suite.print_error(f"Error checking remote origin: {e}")
            return self.error_result()
        return self.success_result()


class CheckRemoteStarter(RepoTest):
    """Checks to see if a remote starter repository has been updated.
    Also checks to see if the local repository has been modified differently
    from this remote starter.
    """

    def __init__(
        self,
        repo_test_suite,
        remote_name,
        remote_branch=None,
        last_date_of_remote_commit=None,
    ):
        """
        remote_name: the name of the remote repository to check
        remote_branch: the branch of the remote repository to check (if None, defaults to 'main')
        last_date_of_remote_commit: the date of the last commit to check for updates (if None, defaults to currenttime)
          This parameter will only check to see if there are commits on the remote before or at this time.
        """
        super().__init__(repo_test_suite)
        self.remote_name = remote_name
        self.remote_branch = remote_branch
        if self.remote_branch is None:
            self.remote_branch = "main"
        self.last_date_of_remote_commit = last_date_of_remote_commit
        if self.last_date_of_remote_commit is None:
            self.last_date_of_remote_commit = datetime.datetime.now()

    def module_name(self):
        module_str = (
            f"Check for updates from remote: {self.remote_name}/{self.remote_branch}"
        )
        return module_str

    def perform_test(self):
        try:
            # 1. Check for unpulled commits from starter
            unpulled_commits = get_unpulled_commits(
                self.repo_test_suite.repo,
                self.remote_name,
                self.remote_branch,
                self.last_date_of_remote_commit,
            )
            if unpulled_commits:
                self.repo_test_suite.print_warning(
                    "Remote Branch has unpulled commits:"
                )
                for commit in unpulled_commits:
                    self.repo_test_suite.print_warning(
                        f"  - {commit.hexsha[:7]}: {commit.message.strip()}"
                    )
                return self.warning_result()
        except Exception as e:
            self.repo_test_suite.print_error(f"Error: {e}")
            return self.error_result()
        return self.success_result()
