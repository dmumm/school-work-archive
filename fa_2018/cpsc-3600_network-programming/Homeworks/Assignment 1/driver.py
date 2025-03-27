# Dylan Mumm
# CPSC 3600
# Project 1, Intro Python Assignment

from TestResultContainer import TestResultContainer


def isfloat(value):
    """Returns true if inputted value is a valid float"""
    try:
        float(value)
        return True
    except ValueError:
        return False

# Initializing dictionary and counter
results = TestResultContainer()
count = 0

# Main loop inside of try-except statement to catch Ctrl-C to stop collecting data
try:

    # Loops until broken via Ctrl-C
    while True:

        # Asks user for value, confirms validity, if valid appends to dictionary and breaks, if not, asks again
        while True:
            throughput = float(input("Throughput: "))
            if isfloat(throughput) and (throughput > 0):
                results.append("tp", throughput)
                break

        while True:
            rtt = float(input("RTT: "))
            if isfloat(rtt) and (rtt > 0):
                results.append("rtt", rtt)
                break

        while True:
            status = float(input("Connection Status: "))
            if isfloat(status) and (status > 0):
                results.append("s", status)
                break

        count += 1

except KeyboardInterrupt:

    # Dumps to JSON
    results.write_to_json()

    # Prints values, rounded to 3rd decimal point
    print("You have entered ", count, " test results.")
    print("The average and standard deviation of Throughput are ",
          round(results.average("tp"), 3), " and ", round(results.deviation("tp"), 3))

    print("The average and standard deviation of RTT are ",
          round(results.average("rtt"), 3), " and ", round(results.deviation("rtt"), 3))

    print("The average and standard deviation of Connection Status are ",
          round(results.average("s"), 3), " and ", round(results.deviation("s"), 3))
