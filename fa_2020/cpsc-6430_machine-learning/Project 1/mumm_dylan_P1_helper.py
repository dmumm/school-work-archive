# -------------------------------
# Dylan Mumm
# September 21, 2020
# CPSC 4430-001, Project 1 helper
# -------------------------------


import numpy as np
import matplotlib.pyplot as plt

# 
# READING INITIAL DATA AND FILES
# 

# opening user prompted training data set
'''
print("Input file name of training set formated as such...")
print("First line: integer number of lines of training data (m), tab, integer number of features(n)")
print("All other lines: values of input features, tab separated, followed by the value of the house (in order listed above)")
#inputName = input("File name: ")
#inputFile = open(inputName, "r")
'''
inputFile = open("REData.txt", "r")
# REPLACE ABOVE!!!!

# reading first line (rows and features)
rawFirstRow = inputFile.readline()
splitFirstRow = rawFirstRow.split()
numLines = int(splitFirstRow[0])
numFeatures = int(splitFirstRow[1])

# iterate, adding each row into string, until text file read all the way
nonRandomData = np.zeros([numLines, numFeatures+1])
for k in range(numLines):
    
    # take in whole rows as string
    aRawRow = inputFile.readline()
    
    # splitting between tabs
    aSplitRow = aRawRow.split()
    
    # converting each entry's columns to floats
    for j in range(7):
        nonRandomData[k, j] = float(aSplitRow[j])
        
# randomizing, making final complete data frame
def dataShuffle(dArray, r, c):
    newArray = np.zeros((r, c+1))
    A = np.arange(0, r)
    print(A)
    np.random.shuffle(A)
    print(A)
    for k in range(r):
        for j in range(c+1):
            newArray[A[k], j] = dArray[k, j]
    return newArray

completeData = dataShuffle(nonRandomData, numLines, numFeatures)

# dividing complete data set into training, CV, and testing sets for model 1

OGtrainingData = completeData[:248] # first 248 rows (3/5)
OGvalidationData = completeData[248:331] # in between 83 rows (4/5)
OGtestingData = completeData[331:414] # last 83 rows (5/5)

OGtrainingHeader = str(OGtrainingData.shape[0]) + "\t" + str(OGtrainingData.shape[1]-1)
np.savetxt("OG_Train.txt", OGtrainingData, fmt="%s", delimiter='\t', header=OGtrainingHeader, comments='')

OGvalidationHeader = str(OGvalidationData.shape[0]) + "\t" + str(OGvalidationData.shape[1]-1)
np.savetxt("OG_Valid.txt", OGvalidationData, fmt="%s", delimiter='\t', header=OGvalidationHeader, comments='')

OGtestingHeader = str(OGtestingData.shape[0]) + "\t" + str(OGtestingData.shape[1]-1)
np.savetxt("OG_Test.txt", OGtestingData, fmt="%s", delimiter='\t', header=OGtestingHeader, comments='')

# model 2

SQcompleteData = completeData.copy()
for k in range(SQcompleteData.shape[0]):
    for j in range(SQcompleteData.shape[1]-1):
        SQcompleteData[k, j] = pow(SQcompleteData[k, j], 2)

SQtrainingData = SQcompleteData[:248] # first 248 rows (3/5)
SQvalidationData = SQcompleteData[248:331] # in between 83 rows (4/5)
SQtestingData = SQcompleteData[331:414] # last 83 rows (5/5)

SQtrainingHeader = str(SQtrainingData.shape[0]) + "\t" + str(SQtrainingData.shape[1]-1)
np.savetxt("SQ_Train.txt", SQtrainingData, fmt="%s", delimiter='\t', header=SQtrainingHeader, comments='')

SQvalidationHeader = str(SQvalidationData.shape[0]) + "\t" + str(SQvalidationData.shape[1]-1)
np.savetxt("SQ_Valid.txt", SQvalidationData, fmt="%s", delimiter='\t', header=SQvalidationHeader, comments='')

SQtestingHeader = str(SQtestingData.shape[0]) + "\t" + str(SQtestingData.shape[1]-1)
np.savetxt("SQ_Test.txt", SQtestingData, fmt="%s", delimiter='\t', header=SQtestingHeader, comments='')

# model 3

BOcompleteData = np.zeros([numLines, (numFeatures*2) + 1])
for k in range(BOcompleteData.shape[0]):
    for j in range(0, (BOcompleteData.shape[1]//2)+1):
        BOcompleteData[k, j*2] = completeData[k, j].copy()
    for j in range(0, (BOcompleteData.shape[1]//2)):
        BOcompleteData[k, j*2+1] = SQcompleteData[k, j].copy()


BOtrainingData = BOcompleteData[:248] # first 248 rows (3/5)
BOvalidationData = BOcompleteData[248:331] # in between 83 rows (4/5)
BOtestingData = BOcompleteData[331:414] # last 83 rows (5/5)

BOtrainingHeader = str(BOtrainingData.shape[0]) + "\t" + str(BOtrainingData.shape[1]-1)
np.savetxt("BO_Train.txt", BOtrainingData, fmt="%s", delimiter='\t', header=BOtrainingHeader, comments='')

BOvalidationHeader = str(BOvalidationData.shape[0]) + "\t" + str(BOvalidationData.shape[1]-1)
np.savetxt("BO_Valid.txt", BOvalidationData, fmt="%s", delimiter='\t', header=BOvalidationHeader, comments='')

BOtestingHeader = str(BOtestingData.shape[0]) + "\t" + str(BOtestingData.shape[1]-1)
np.savetxt("BO_Test.txt", BOtestingData, fmt="%s", delimiter='\t', header=BOtestingHeader, comments='')