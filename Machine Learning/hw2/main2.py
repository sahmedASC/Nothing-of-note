import pandas as pd
import numpy as np
import openpyxl
import matplotlib.pyplot as plt
from time import process_time
import math


#The cost function of log regression as defined in the homework
def logreg_cost(feature, output, theta, lam):
    x = 0
    for i in range(len(output)):
        x+= math.log(1+math.exp(-1*output[i]*np.dot(feature[i],theta)))
    x = x/len(output)
    x+= (lam/2)*(np.linalg.norm(theta)**2)
    return x

#The batch gradient descent using the derived
#gradient of the loss equation in the homework
def logreg_bgd(feature, output, theta, lr ,lam):
    for i in range(len(theta)):
        sum = 0
        for j in range(len(output)):
            a = math.exp(-1*output[j] * np.dot(feature[j],theta))
            c = -1*output[j]*feature[j][i]
            sum+= (a*c)/(a+1)
        sum = sum/len(output)
        sum = sum + (lam)*theta[i] * (1/len(output))
        theta[i] = theta[i] - (lr/len(output))*sum
    return theta

#stochastic gradient descent. Same derivative but
#chooses 1 sample of the data set randomly
def logreg_sgd(feature, output, theta, lr, lam):
    index = np.random.randint(0,len(output))
    for i in range(len(theta)):
        sum = 0
        a = math.exp(-1*output[index] * np.dot(feature[index],theta))
        c = -1*output[index]*feature[index][i]
        sum+= (a*c)/(a+1)
        sum = sum/len(output)
        sum = sum + lam*theta[i] * (1/len(output))
        theta[i] = theta[i] - lr*sum
    return theta

#uniformly chooses 50 random components to make a subset
#of the whole dataset and runs batch gradient descent on that subset
def logreg_mbgd(feature, output, theta, lr, lam, k):
    index = []
    index.append(np.random.randint(0,len(output),k))
    features = feature[index,:]
    features = features[0]
    outputs = []
    for i in index[0]:
        outputs.append(output[i])
    for i in range(len(theta)):
        sum = 0
        for j in range(len(outputs)):
            a = math.exp(-1*outputs[j] * np.dot(features[j],theta))
            c = -1*output[j]*features[j][i]
            sum+= (a*c)/(a+1)
        sum = sum/50
        sum = sum + (lam)*theta[i] * (1/50)
        theta[i] = theta[i] - (lr/50)*sum
    return theta

if __name__ == '__main__':
    #parsing begins
    #deletes columns that are consistently 0
    #and adds in a colume of 1 to represent x^0
    df = pd.read_csv('ionosphere.csv', header=None)
    df = df.drop(df.columns[[1]], axis=1)
    df.insert(0,'col1',1)

    #does the mapping of b -> -1
    # and g -> 1
    feature_matrix = np.array(df)
    output_vector = feature_matrix[:,34]
    feature_matrix = np.delete(feature_matrix,34, axis=1)
    for i in range(len(output_vector)):
        if output_vector[i] == 'b':
            output_vector[i] = -1
        elif output_vector[i] == 'g':
            output_vector[i] = 1

    #initial theta guess and running of iterations
    theta = np.random.default_rng(42).random((34))
    i = 0
    iteration_index = []
    error =[]
    cpu = []
    t_start = process_time()
    while i < 5000:
        if(i %250 == 0):
            print(i)
            iteration_index.append(i)
            error.append(logreg_cost(feature_matrix,output_vector,theta,0.01))
            t_end = process_time()
            cpu.append(t_end-t_start)
            t_start = process_time()
        #theta = logreg_bgd(feature_matrix,output_vector,theta,1,0.01)
        #theta = logreg_sgd(feature_matrix,output_vector,theta,1,0.01)
        theta = logreg_mbgd(feature_matrix,output_vector,theta,1,0.01,50)

        i+=1

    #plot set up and output
    plt.title("Mini Batch Gradient Descent")
    #plt.xlabel("Iteration")
    plt.xlabel("CPU Time")
    plt.ylabel("Objective Error")
    #plt.plot(np.array(iteration_index), np.array(error), color ="green")
    plt.plot( np.array(cpu), np.array(error),color ="blue")
    plt.show()