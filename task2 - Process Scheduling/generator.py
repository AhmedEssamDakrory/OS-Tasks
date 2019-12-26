import numpy as np 
import sys

# getting input file from user
print("Please Enter the Name of the Input File: ")
print(">>> ", end = " ")
inputFileName = input()

# reading parameters from the input file
param = open(inputFileName, "r")

if param.mode == 'r':
   	contents = param.readlines()

processNo = int(contents[0])
arrivalMu = float(contents[1].split()[0])
arrivalSigma = float(contents[1].split()[1])
burstMu = float(contents[2].split()[0])
burstSigma = float(contents[2].split()[1])
priorityLamda = float(contents[3])

# generating numbers
arrivalTime = np.random.normal(loc=arrivalMu, scale=arrivalSigma, size=processNo).astype(int)
burstTime = np.random.normal(loc=burstMu, scale=burstSigma, size=processNo).astype(int)
priority = np.random.poisson(lam=priorityLamda, size=processNo).astype(int)

# getting output file name from user
print("Please Enter the Name of the Output File:")
print(">>> ", end = " ")
outputFileName = input()

# saving processes parameters in output file
output = open(outputFileName, "w+")

output.write("%d\n" % processNo)
for i in range(processNo):
    output.write("%d %d %d\n" % (arrivalTime[i], burstTime[i], priority[i]))

print("file %s generated sucessfully!" % outputFileName)