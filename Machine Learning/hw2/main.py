import pandas as pd
import numpy as np
import openpyxl
import matplotlib.pyplot as plt
from time import process_time

#The cost function as defined in the homework
def linreg_cost(output, feature, theta):
    x=0
    for i in range(len(output)):
        x+=(output[i] - np.dot(feature[i],theta))**2
    x=x/(len(output))
    return x

#batch gradient descent update method by using matrices
#butter is just a placeholder term that came to mind
def update_theta_bgd(theta, lr, output,feature):
    butter = np.matmul(feature.transpose(),feature)
    butter = np.matmul(butter,theta.transpose())
    butter = butter - np.matmul(feature.transpose(),output.transpose())
    butter = (lr*2/len(output)) * butter
    butter = theta.transpose() - butter
    return butter.transpose()

#stochastic gradient descent. For 1 iteration
#uniformly randomly chooses an entry in the feature matrix
#to update theta
def update_theta_sgd(theta, lr, output, feature, k):
    i=0
    while i <k:
        index = np.random.randint(0,len(output),1)
        xn = feature[index]
        yn = output[index]
        test = (np.dot(theta, xn[0]) -yn)*xn[0]
        theta = theta - lr * test
        i+=1
    return theta

#Mini batch gradient descent. Uniformly randomly chooses 50
#samples of the whole dataset and performs gradient descent.
#Adapted to use the matrix methodology from batch gradient descent
def update_theta_mbgd(theta, lr, output, feature, k):
    index = []
    index.append(np.random.randint(0,len(output),k))
    features = feature[index,:]
    features = features[0]
    outputs = []
    for i in index:
        outputs.append(output[i])
    outputs = np.array(outputs)[0]
    butter = np.matmul(features.transpose(),features)
    butter = np.matmul(butter,theta.transpose())
    butter = butter - np.matmul(features.transpose(),outputs.transpose())
    butter = (lr*2/len(outputs)) * butter
    butter = theta.transpose() - butter

    return butter.transpose()


if __name__ == '__main__':
    #control for deciding which operation to run
    operation = float(input("input the number you are doing (1.1, 1.2, 1.3): "))

    #beginning of parsing. Reads in Excel file. Gets rid of Date and Time columns
    df = pd.read_excel('AirQualityUCI.xlsx')
    df = df.drop(['Date', 'Time'], axis=1)

    #inserts x^0 power column to the feature matrix
    df.insert(0,'col1',1)
    feature_matrix = np.array(df)

    #Preprocessing begins
    bad_index = []
    for i in range(len(feature_matrix)):
        count =0
        for j in range(len(feature_matrix[i])):
            if(feature_matrix[i][j] == -200):
                count +=1
        if count >=2:
            bad_index.append(i)
    #If a row has 2 or more -200 (bad sensors) in it remove that row
    feature_matrix = np.delete(feature_matrix,bad_index,0)

    #replacing the remaining -200 with 0
    for i in range(len(feature_matrix)):
        for j in range(len(feature_matrix[i])):
            if(feature_matrix[i][j] == -200):
                feature_matrix[i][j] =0

    #normalize the matrix by scaling by 1/1000
    #grab the benzene column and remove from feature matrix
    #make initial theta guess
    feature_matrix = 1/1000 * feature_matrix
    output_vector = feature_matrix[:,4]
    feature_matrix = np.delete(feature_matrix,4, axis=1)
    theta = np.random.default_rng(42).random((13))

    #Setup for plotting
    i=0
    iteration_index = []
    error =[]
    cpu = []

    #Run a number of iterations of Batch Gradient Descent
    if operation == 1.1:
        print("Running Problem 1 BGD")
        while i<100:
            t_start = process_time()
            theta = update_theta_bgd(theta,0.01,output_vector,feature_matrix)
            iteration_index.append(i)
            error.append(linreg_cost(output_vector,feature_matrix,theta))
            t_end = process_time()
            cpu.append(t_end-t_start)
            i+=1
        plt.title("Batch Gradient Descent")
        print("Finished P1 BGD")

    #Run a number of iterations of Stochastic Gradient Descent
    elif operation == 1.2:
        print("Running Problem 1 SGD")
        while i<100:
            t_start = process_time()
            theta = update_theta_sgd(theta,0.01,output_vector,feature_matrix, 1)
            iteration_index.append(i)
            error.append(linreg_cost(output_vector,feature_matrix,theta))
            t_end = process_time()
            cpu.append(t_end-t_start)
            i+=1
        plt.title("Stochastic Gradient Descent")
        print("Finished P1 SGD")

    #Run a number of iterations of Mini Batch Gradient Descent
    elif operation == 1.3:
        print("Running Problem 1 MBGD")
        while i<100:
            t_start = process_time()
            theta = update_theta_mbgd(theta,0.01,output_vector,feature_matrix,50)
            iteration_index.append(i)
            error.append(linreg_cost(output_vector,feature_matrix,theta))
            t_end = process_time()
            cpu.append(t_end-t_start)
            i+=1
        plt.title("Mini Batch Gradient Descent")
        print("Finished P1 SGD")

    #Finish plotting and output a graph
    #plt.xlabel("Iteration")
    plt.xlabel("CPU Time")
    plt.ylabel("Objective Error")
    #plt.plot(np.array(iteration_index), np.array(error), color ="green")
    plt.plot( np.array(cpu), np.array(error),color ="blue")
    plt.show()


