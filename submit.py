import argparse
import pathlib
import sys

import git

ROOT_PATH = pathlib.Path(__file__).parent.resolve()

sys.path.insert(0, str(ROOT_PATH / "py"))

from test_suite_427 import TestSuite427
from repo_test import FileNotEmptyTest

choices = [
    "lab1",
    "lab2",
    "lab3",
    "lab4_m1",
    "lab4_m2",
    "lab4_m3",
    "lab5_m1",
    "lab5_m2",
    "lab5_m3",
    "lab5_m4",
    "lab6_m1",
    "lab6_m2",
    "lab7",
    "lab8",
]

parser = argparse.ArgumentParser(description="Submit lab assignments")
parser.add_argument("lab", choices=choices, help="The lab to submit")
args = parser.parse_args()


repo = git.Repo(ROOT_PATH)

test_suite = TestSuite427(
    repo, lab_name=args.lab + "_submission", submit=True, max_repo_files=None
)

# One lifelong learning file per lab, checked at the lab's final milestone
lifelong_learning_files = {
    "lab1": "lab1.txt",
    "lab2": "lab2.txt",
    "lab3": "lab3.txt",
    "lab4_m3": "lab4.txt",
    "lab5_m4": "lab5.txt",
    "lab6_m2": "lab6.txt",
    "lab7": "lab7.txt",
    "lab8": "lab8.txt",
}

if args.lab in lifelong_learning_files:
    test_suite.add_repo_test(
        FileNotEmptyTest(
            test_suite, [f"lifelong_learning/{lifelong_learning_files[args.lab]}"]
        )
    )


test_suite.run_tests()
