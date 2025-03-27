# -------------------------------
# Dylan Mumm
# October 4th, 2020
# CPSC 4430-001, Project 2
# -------------------------------

import numpy as np
import matplotlib.pyplot as plt
import math


# prompt for training set

def gradientDescent(x, y, theta, alpha, iterations):
    cost = np.zeros(iterations)
    for i in range(iterations):
        z = x @ (-theta.T)
        e = np.power(math.e , z)
        yhat = 1/(1+e)
    
        partialDerivative = (1/len(x))* (sum((yhat - y)*x))
        
        theta = theta - (alpha * partialDerivative)
        cost[i] = costFunction(x, y, theta)
        
    return theta, cost

def costFunction(x,y,theta):
    z = x @ (-theta.T)
    e = np.power(math.e , z)
    yhat = 1/(1 + e)
    
    j = ( (-y* (np.log(yhat)) ) - (1-y)* (np.log(1-yhat)) )
    
    return sum(j)/len(x)





print("Input file name of training set formated as such...")
print("First line: integer number of lines of training data (m), tab, integer number of features(n)")
print("All other lines: values of input features, tab separated, followed by if the capacitor passed QC and a 0.0 if it failed QC")
      
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
    
    # converting each entry's features to floats
    for j in range(numFeatures):
        trainingFeatures[k, j] = float(aSplitRow[j])
        
    # converting outcome to boolean
    trainingOutputs[k, 0] = float(aSplitRow[-1])
        

print("Training Set Weights:")
weights = np.zeros([1, trainingFeatures.shape[1]])
weights, cost = gradientDescent(trainingFeatures , trainingOutputs, weights, 0.3, 5000)
print(weights)

print("Final training J is:")
print(np.amin(cost))

# plotting training iterations
plt.plot(np.arange(5000), cost, 'r')  
plt.xlabel('Iterations')  
plt.ylabel('Costs')  
plt.title('Error vs Training iteration')
plt.show()

print("Input file name of testing set formated as such...")
print("First line: integer number of lines of training data (m), tab, integer number of features(n)")
print("All other lines: values of input features, tab separated, followed by if the capacitor passed QC and a 0.0 if it failed QC")
      
testFileName = input("File name: ")
testFile = open(testFileName, "r")

# reading first line (rows and features)
rawFirstRow = testFile.readline()
splitFirstRow = rawFirstRow.split()
numLines = int(splitFirstRow[0])
numFeatures = int(splitFirstRow[1])

# iterate, adding each row into string, until text file read all the way
testingFeatures = np.zeros([numLines, numFeatures])
testingOutputs  = np.zeros([numLines, 1])
for k in range(numLines):
    
    # take in whole rows as string
    aRawRow = testFile.readline()
    
    # splitting between tabs
    aSplitRow = aRawRow.split()
    
    # converting each entry's features to floats
    for j in range(numFeatures):
        testingFeatures[k, j] = float(aSplitRow[j])
        
    # converting outcome to boolean
    testingOutputs[k, 0] = float(aSplitRow[-1])


cost = np.zeros(5000)
for i in range(5000):
    cost[i] = costFunction(testingFeatures, testingOutputs, weights)
    
        
print("Testing J:")
print(np.amin(cost))

#  matrix

yhat = np.zeros([numLines, 1])
for k in range(numLines):
    for j in range(numFeatures):
        yhat[k, 0] = yhat[k, 0] + testingFeatures[k, j] * weights[0, j]

TP = 0
FP = 0
TN = 0
FN = 0

for i in range(len(yhat)): 
    if testingOutputs[i][0] == 1 and yhat[i][0] >= 0:
        TP += 1
    if yhat[i][0] >= 0 and testingOutputs[i][0] == 0:
        FP += 1
    if testingOutputs[i][0] == 0 and yhat[i][0] < 0:
        TN += 1
    if yhat[i][0] < 0 and testingOutputs[i][0] == 1:
        FN += 1
        
accuracy= (TP+TN)/(TP+TN+FP+FN)
precision = (TP)/(TP+FP)
recall = (TP)/(TP+FN)
F1= 2 * (1/((1/precision) + (1/recall)))
print('TP = {}, FP = {}, TN = {}, FN = {} \n accuracy = {}, Precision = {}, Recall = {}, F1 = {} '.format(TP,FP,TN,FN,accuracy,precision,recall, F1))


