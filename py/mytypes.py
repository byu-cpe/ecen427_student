from enum import Enum


class ResultType(Enum):
    SUCCESS = 1
    WARNING = 2
    ERROR = 3

    def merge(self, other: "ResultType") -> "ResultType":
        """Return the more severe of the two statuses."""
        return self if self.value >= other.value else other
