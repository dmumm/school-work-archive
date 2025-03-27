# -------------------------------
# Dylan Mumm
# September 21, 2020
# CPSC 4430-001, Project 1
# -------------------------------

import numpy as np
import matplotlib.pyplot as plt

# prompt for training set

print("Input file name of training set formated as such...")
print("First line: integer number of lines of training data (m), tab, integer number of features(n)")
print("All other lines: values of input features, tab separated, followed by the value of the house (in order listed above)")
trainFileName = input("File name: ")
trainFile = open(trainFileName, "r")

# reading first line (rows and features)
rawFirstRow = trainFile.readline()
splitFirstRow = rawFirstRow.split()
numLines = int(splitFirstRow[0])
numFeatures = int(splitFirstRow[1])

# iterate, adding each row into string, until text file read all the way
trainingFeatures = np.zeros([numLines, numFeatures])
trainingOutputs  = np.zeros([numLines, 1])
for k in range(numLines):
    
    # take in whole rows as string
    aRawRow = trainFile.readline()
    
    # splitting between tabs
    aSplitRow = aRawRow.split()
    
    # converting each entry's columns to floats
    for j in range(numFeatures):
        trainingFeatures[k, j] = float(aSplitRow[j])
    trainingOutputs[k, 0] = float(aSplitRow[-1])
        
weights = np.dot(np.linalg.pinv(np.dot(trainingFeatures.T, trainingFeatures)), 
                 np.dot(trainingFeatures.T, trainingOutputs))

print("Training Set Weights:")
for row in weights:
    for col in row:
        print("%.4f" % (col,))
      
# calculating hypothesis outputs
yhat = np.zeros([numLines, 1])
for k in range(numLines):
    for j in range(numFeatures):
        yhat[k, 0] = yhat[k, 0] + trainingFeatures[k, j] * weights[j, 0]
        
print("Training J:")

# calculating J
sqError = np.power(yhat - trainingOutputs, 2)
testJ = np.sum(sqError) / (2 * numLines)
print(testJ)
        
# prompt for validation set

print("Input file name of validation or test set formated as such...")
print("First line: integer number of lines of validation data (m), tab, integer number of features(n)")
print("All other lines: values of input features, tab separated, followed by the value of the house (in order listed above)")
validFileName = input("File name: ")
validFile = open(validFileName, "r")

# reading first line (rows and features)
rawFirstRow = validFile.readline()
splitFirstRow = rawFirstRow.split()
numLines = int(splitFirstRow[0])
numFeatures = int(splitFirstRow[1])

# iterate, adding each row into string, until text file read all the way
validationFeatures = np.zeros([numLines, numFeatures])
validationOutputs  = np.zeros([numLines, 1])
for k in range(numLines):
    
    # take in whole rows as string
    aRawRow = validFile.readline()
    
    # splitting between tabs
    aSplitRow = aRawRow.split()
    
    # converting each entry's columns to floats
    for j in range(numFeatures):
        validationFeatures[k, j] = float(aSplitRow[j])
    validationOutputs[k, 0] = float(aSplitRow[-1])
    
# calculating hypothesis outputs
yhat = np.zeros([numLines, 1])
for k in range(numLines):
    for j in range(numFeatures):
        yhat[k, 0] = yhat[k, 0] + validationFeatures[k, j] * weights[j, 0]
        
print("J:")

# calculating J

sqError = np.power(yhat - validationOutputs, 2)
validJ = np.sum(sqError) / (2 * numLines)
print(validJ)

# calculating r^2

denomInner = pow(validationOutputs - np.mean(validationOutputs), 2)
denom = np.sum(denomInner) / (2 * numLines)

rSquare = 1 - (validJ / denom)
rSquareAdjust = 1 - (((1 - rSquare) * (numLines - 1)) / (numLines - numFeatures - 1))

print("Adjusted R-Square:")
print(rSquareAdjust)

