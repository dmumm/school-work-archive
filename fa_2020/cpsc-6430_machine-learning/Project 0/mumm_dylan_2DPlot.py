# -------------------------------
# Dylan Mumm
# August 30, 2020
# CPSC 4430-001, Project 0
# -------------------------------

# 
# READING DATA
# 

import numpy as np
import matplotlib.pyplot as plt

# opening file
irisFile = open("IrisData.txt", "r")
numRows = 150

# 150 x 5 array
data = np.zeros([numRows, 5])

# iterate, adding each row into string, until text file read all the way
for k in range(numRows):
    
    # take in whole rows as string
    aRawRow = irisFile.readline()
    #print(aRawRow)
    
    # splitting between tabs
    aSplitRow = aRawRow.split("\t")
    
    # converting first 4 columns to floats
    for j in range(4):
        data[k, j] = float(aSplitRow[j])
    if aSplitRow[4] == "setosa\n": data[k, 4] = 0
    if aSplitRow[4] == "versicolor\n": data[k, 4] = 1
    if aSplitRow[4] == "virginica\n": data[k, 4] = 2

#print(data)

# finished reading data
irisFile.close()

#
# PLOTTING
#

for k in range(numRows):
    
    # iterating through data, adding each row to scatterplot, color coded by color type
    # showing relationship between petal and sepal length
    if data[k, 4] == 0:
        plt.scatter(data[k, 0], data[k, 2], color = "purple", label = "Setosa")
    elif data[k, 4] == 1:
        plt.scatter(data[k, 0], data[k, 2], color = "pink", label = "Versicolor")
    elif data[k, 4] == 2:
        plt.scatter(data[k, 0], data[k, 2], color = "blue", label = "Virginica")
        
# labels
plt.xlabel("Sepal Length")
plt.ylabel("Petal Length")
plt.title("Sepal vs Petal Length for Varieties of Iris Flowers")

# making plot
plt.savefig("mumm_dylan_MyPlot.png", bbox_inches = "tight")
plt.show()