#!/usr/bin/python3

import pathlib
import sys

import git
from mytypes import ResultType


class TermColor:
    """Terminal codes for printing in color"""

    PURPLE = "\033[95m"
    BLUE = "\033[94m"
    GREEN = "\033[92m"
    YELLOW = "\033[93m"
    RED = "\033[91m"
    END = "\033[0m"
    BOLD = "\033[1m"
    UNDERLINE = "\033[4m"


class RepoTestSuite:
    """This class is used to manage the execution of "tests" within a specific directories
    of a GitHub repository for the purpose of evaluating code within github repositories.

    A key function of this class is to manage the output of the test suite.
    There are two kinds of output generated during the test suite:
    - Command output: The actual output of commands executed as part of a test
    - Test summary: Text that summarizes the test status and results.
    There are three three output targets for this text:
    - stdout: The console output of the test suite.
    - summary log file: A file that contains the summary of the test output.
    - Command specific log files: Files for a specific test output to isolate the output from other tests

    repo: This is the git.Repo object that represents the local repository being tested.
          This class is not involved in preparing or changing the repository and an existing
          valid repository is assumed. The repository is used to find the repo directory
          (repo.working_tree_dir) and find individual files within the repo.
    tests_to_perform: A list of "repo_test" objects that represent a specific test to perform.
    working_dir: The directory in which the tests should be executed. Note that the execution
                 directory can be anywhere and not necessarily within the repository.
    log_dir: the directory where logs generated during the test will be generated.
            This can be None if no output file logging is wanted.
    summary_log_filename: The name of the file where a summary of the test output will be written.

    """

    def __init__(
        self,
        repo,
        test_name=None,
        working_dir=None,
        print_to_stdout=True,
        verbose=False,
        summary_log_filename=None,
        log_dir=None,
    ):
        # Reference to the Git repository
        self.repo = repo
        self.repo_root_path = pathlib.Path(repo.git.rev_parse("--show-toplevel"))

        # Directory where tests should be completed. This may be different from the script_path
        if working_dir is not None:
            self.working_path = pathlib.Path(working_dir)
        else:
            self.working_path = pathlib.Path(pathlib.Path.cwd())

        # Relative repo path
        self.relative_repo_path = self.working_path.relative_to(self.repo_root_path)

        # Directory of the logs
        self.log_dir = log_dir
        self.tests_to_perform = []  # list of test_module objects
        self.print_to_stdout = print_to_stdout
        self.verbose = verbose
        self.test_log_fp = None
        if summary_log_filename is not None:
            if self.log_dir is None:
                log_dir = pathlib.Path(".")
            else:
                log_dir = pathlib.Path(self.log_dir)
            summary_log_filepath = log_dir / summary_log_filename
            self.test_log_fp = open(summary_log_filepath, "w")
            if not self.test_log_fp:
                self.print_error(
                    "Error opening file for writing:", summary_log_filepath
                )
        self.test_name = test_name

        # Colors
        self.test_color = TermColor.BLUE
        self.success_color = TermColor.GREEN
        self.warning_color = TermColor.YELLOW
        self.error_color = TermColor.RED

        # Test result dictionary
        self.test_results = {}

    def add_test_module(self, test_module):
        """Add a test module to the test suite."""
        self.tests_to_perform.append(test_module)

    def print_color(self, color, *msg):
        """Print a message in color"""
        msg_str = " ".join(str(item) for item in msg)
        if self.test_log_fp is not None:
            # Don't print color codes to the log file, just plain message
            self.test_log_fp.write(msg_str + "\n")
        if color is not None:
            msg_str = color + msg_str + TermColor.END
        print(msg_str)

    def print_verbose(self, message):
        self.print(message, verbose_message=True)

    def print(self, message, verbose_message=False):
        """Prints a string to the appropriate locations."""
        # Print to std_out?
        if not verbose_message or self.verbose:
            if self.print_to_stdout:
                print(message)
            if self.test_log_fp is not None:
                self.test_log_fp.write(message + "\n")

    def print_error(self, message):
        """Prints a message using the 'error_color'"""
        self.print_color(self.error_color, message)

    def print_warning(self, message):
        """Prints a message using the 'warning_color'"""
        self.print_color(self.warning_color, message)

    def print_test_message(self, message):
        self.print_color(self.test_color, message)

    def print_test_title(self, message):
        print()
        self.print_test_message("#" * 80)
        self.print_test_message(message)
        self.print_test_message("#" * 80)
        print()

    def print_test_success(self, message):
        self.print_color(self.success_color, message)

    def test_cleanup(self):
        """Close the log file"""
        for test in self.tests_to_perform:
            test.cleanup()
        if self.test_log_fp:
            self.test_log_fp.close()

    def run_tests(self):
        """Run all the registered tests"""
        self.print_test_start_message()
        self.iterate_through_tests(self.tests_to_perform)
        # Wrap up
        self.test_cleanup()
        self.print_test_end_message()

    def print_test_start_message(self):
        """Start message at start of test"""
        self.print_test_title(f"Running test '{self.test_name}'")

    def print_test_summary(self):
        """Print a summary of the test results"""
        warnings = []
        errors = []
        success = []
        for test in self.test_results.keys():
            result = self.test_results[test]
            if result.result == ResultType.SUCCESS:
                success.append(result)
            elif result.result == ResultType.WARNING:
                warnings.append(result)
            else:
                errors.append(result)
        if not warnings and not errors:
            self.print_test_success("  No errors or warnings")

        if warnings:
            self.print_warning(f" {len(warnings)} Warnings")
            for warning in warnings:
                self.print_warning(f"  {warning.test.module_name()}")

        if errors:
            self.print_error(f" {len(errors)} Errors")
            for error in errors:
                self.print_error(f"  {error.test.module_name()}")

    def iterate_through_tests(self, list_of_tests, start_step=1):
        """Run list of tests. Return True if all tests pass, False otherwise"""
        set_result = ResultType.SUCCESS
        for idx, test in enumerate(list_of_tests):  # (but no setup or wrap-up):
            self.print_test_message(f"Step {idx+start_step}. {test.module_name()}")
            result_obj = self.execute_test_module(test)
            set_result = set_result.merge(result_obj.result)
        return set_result

    def execute_test_module(self, test_module):
        """Executes the 'perform_test' function of the tester_module and logs its result in the log file"""

        # Check to see if the test should proceed
        # if not self.proceed_with_tests:
        #     print("Skipping test",test_module.module_name(),"due to previous errors")
        #     return False

        module_name = test_module.module_name()
        result = test_module.perform_test()
        self.test_results[test_module] = result
        if result.result == ResultType.SUCCESS:
            self.print_test_success(f"Success: {module_name}\n")
        elif result.result == ResultType.WARNING:
            self.print_warning(f"Warning: {module_name}\n")
        else:
            self.print_error(f"Failed: {module_name}\n")
        return result

    @classmethod
    def exit_with_status(cls, status: ResultType):
        """Exit the program with a status code based on the test result"""
        if status == ResultType.WARNING:
            sys.exit(1)
        elif status == ResultType.ERROR:
            sys.exit(2)
        else:
            sys.exit(0)


# Static methods
def create_from_path(path=None):
    """Create a repo_test_suite object from a path. If no path is given,
    the current directory is used."""
    if path is None:
        path = pathlib.Path.cwd()
    repo = git.Repo(path, search_parent_directories=True)
    return RepoTestSuite(repo, path)
