# Dylan Mumm
# CPSC 3600
# Project 1, Intro Python Assignment

import statistics
import json


class TestResultContainer:

    """Stores dictionary of lists and functions to append to them and run calculations"""

    stats = {
        "tp": [],
        "rtt": [],
        "s": [],
    }

    def append(self, key, entry):
        """Appends inputted entry into chosen key"""
        self.stats[key].append(entry)

    def average(self, key):
        """Returns average of chosen key"""
        return sum(self.stats[key]) / len(self.stats[key])

    def deviation(self, key):
        """Returns standard deviation of chosen key"""
        return statistics.stdev(self.stats[key])

    def write_to_json(self):
        """Dumps dictionary results into json file"""
        with open('results.json', 'w') as fp:
            json.dump(self.stats, fp)
