import pandas as pd
import numpy as np
import openpyxl
import matplotlib.pyplot as plt
import random
#
# #sigmoid function as described in lecture.
# def sigmoid(xi, theta):
#
#     x= 1/(1+np.exp(np.inner(-1*theta,xi)))
#     return x
#
# #logistic regression stochastic gradient descent as described in
# #lecture
# def sgrad(X,y,theta):
#     index = np.random.randint(0,len(y),1)
#     xi = X[index][0]
#     yi = y[index][0]
#     gradx =(sigmoid(xi,theta)-yi)*xi
#
#     return gradx
#
# #not used just for testing
# def loss(X,y,theta):
#     loss= 0
#     for xi, yi in zip(X,y):
#         loss += (yi *np.log(sigmoid(xi,theta)))+(1-yi)*(np.log(sigmoid(xi,theta)))
#     return loss*(-1/len(X))
#
# #makes a prediction using the sigmoid function
# #records number of correct predictions and returns
# #error rate
# def test_logreg(X,y,theta):
#     n_wrong = 0
#     for i in range(len(X)):
#
#         prob = sigmoid(X[i],theta)
#         answer = 0
#         if prob>=0.5:
#             answer = 1
#         if answer != y[i]:
#             n_wrong+=1
#
#     return float(n_wrong)/len(y)
#
#
# def logisiticRegression(filename, num_splits,train_percent):
#     #parse the data
#     df = pd.read_csv(filename, header=None)
#
#     d = len(df.columns)
#     X = np.array(df.iloc[:,:d-1])
#     y = np.array(df.iloc[:,d-1:])
#     N = X.shape[0]
#     error=[]
#     stdev=[]
#
#     iter = 0
#
#     alpha =0.05
#     i=0
#     particular_error=[]
#     for p in train_percent:
#         blah = []
#         particular_error.append(blah)
#
#     while iter<num_splits:
#         theta = np.zeros(d-1)
#
#         #create an 80-20 split
#         choices = list(range(N))
#         random.shuffle(choices)
#         eighty= int((N * 8)/10)
#
#         training = X[choices[0:eighty],:]
#         training_output = y[choices[0:eighty],:]
#
#         testing = X[choices[eighty:],:]
#         testing_output = y[choices[eighty:]]
#
#         index_to_store=0
#         #create the partial percent of the data to train
#         for p in train_percent:
#             choices = list(range(eighty))
#             random.shuffle(choices)
#             percent = int((eighty*p)/100)
#             training_p = training[choices[0:percent],:]
#             training_output_p = training_output[choices[0:percent],:]
#
#             #train the classifier using stochastic gradient descent
#             while i<1000:
#                 gradk = sgrad(training_p, training_output_p, theta)
#                 theta = theta - alpha*gradk
#                 i+=1
#             particular_error[index_to_store].append( test_logreg(testing,testing_output,theta))
#             index_to_store+=1
#         iter+=1
#     #gather mean and standard deviation of the error rates
#     for i in particular_error:
#
#         error.append(np.mean(i))
#         stdev.append(np.std(i))
#
#     #output results
#     print("Percents:")
#     print(train_percent)
#     print("Test Error Rate:")
#     print(error)
#     print("Standard Deviation:")
#     print(stdev)
#
#     return (error,stdev)
#
# #determines the mean and standard deviation for each feature
# def train_nbg(X,y):
#     y_0 = []
#     x_0=[]
#     x_1=[]
#     y_1=[]
#     for i in range(len(X)):
#         if y[i]== 0:
#             y_0.append(y[i])
#             x_0.append(X[i])
#         elif y[i]== 1:
#             y_1.append(y[i])
#             x_1.append(X[i])
#     mu0 = np.mean(x_0,axis=0)
#     mu1= np.mean(x_1,axis=0)
#     sigma0 = np.std(x_0,axis=0)
#     sigma1 = np.std(x_1,axis=0)
#
#     x= [mu0,sigma0,mu1,sigma1]
#     return x
#
# #Calculates the gaussian likelihood with a given mean and standard deviation
# def gaussian(mu, sigma,feature,X):
#     x = (1/((1/len(X))+sigma*np.sqrt(2*np.pi)))*np.exp(-0.5 * ((feature-mu)/((1/len(X))+sigma))**2)
#     return x
#
# def test_nbg(X,y,values):
#     #derive the P(y) of each classifier
#     py1=0
#     py0 = 0
#     for i in y:
#         if i == 0:
#             py0+=1
#         elif i == 1:
#             py1+=1
#     py1= py1/len(y)
#     py0 = py0/len(y)
#
#     nwrong = 0
#     #for a given test run
#     for i in range(len(X)):
#         chance1=1
#         chance0=1
#
#         #multilply all the conditional probabilities together
#         for j in range(len(X[i])):
#             chance1 *= gaussian(values[2][j],values[3][j],X[i][j],X)
#             chance0 *= gaussian(values[0][j],values[1][j],X[i][j],X)
#         #end with multiplying by P(y) of a given classifier
#         chance1*=py1
#         chance0*=py0
#
#         #determine output and record results
#         if(chance1>chance0):
#             answer = 1
#         else:
#             answer=0
#         if answer!= y[i]:
#             nwrong+=1
#     #return error rate
#     return nwrong/len(X)
#
# def naiveBayesGaussian(filename, num_splits, train_percent):
#     df = pd.read_csv(filename, header=None)
#
#     #parse the data
#     d = len(df.columns)
#     X = np.array(df.iloc[:,:d-1])
#     y = np.array(df.iloc[:,d-1:])
#     N = X.shape[0]
#     error=[]
#     stdev=[]
#     iter = 0
#
#     particular_error=[]
#     for p in train_percent:
#         blah = []
#         particular_error.append(blah)
#
#     #Do a given number of iterations
#     while iter<num_splits:
#
#         #create an 80-20 split
#         choices = list(range(N))
#         random.shuffle(choices)
#         eighty= int((N * 8)/10)
#
#         training = X[choices[0:eighty],:]
#         training_output = y[choices[0:eighty],:]
#
#         testing = X[choices[eighty:],:]
#         testing_output = y[choices[eighty:]]
#
#         index_to_store=0
#
#         for p in train_percent:
#             #create the partial percent of the data to train
#             choices = list(range(eighty))
#             random.shuffle(choices)
#             percent = int((eighty*p)/100)
#             training_p = training[choices[0:percent],:]
#             training_output_p = training_output[choices[0:percent],:]
#
#             #train the classifier
#             trained = train_nbg(training_p,training_output_p)
#
#             #calculate the error
#             particular_error[index_to_store].append( test_nbg(testing,testing_output,trained))
#             index_to_store+=1
#         iter+=1
#
#     #gather mean and standard deviation of the error rates
#     for i in particular_error:
#
#         error.append(np.mean(i))
#         stdev.append(np.std(i))
#
#     #output results
#     print("Percents:")
#     print(train_percent)
#     print("Test Error Rate:")
#     print(error)
#     print("Standard Deviation:")
#     print(stdev)
#
#     return (error,stdev)
#
# if __name__ == '__main__':
#     x = [0,0]
#
#     #Edit below if needed vvvvvv
#     x[0] = logisiticRegression("spambase.csv",100,[5,10,15,20,25,30])
#     x[1]= naiveBayesGaussian("spambase.csv",100,[5,10,15,20,25,30])
#     #Edit above if needed^^^^^^^
#
#     plt.errorbar([5,10,15,20,25,30],x[0][0],x[0][1], color='r', label='log_reg')
#     plt.errorbar([5,10,15,20,25,30],x[1][0],x[1][1], color='b', label='naive_bayes')
#     plt.xlabel("Train Percent")
#     plt.ylabel("Test Error Rate")
#     plt.title("Logistice Regression vs. Naive Bayes")
#     plt.legend()
#     plt.show()

x1 = np.array([0,1])
x2 = np.array([-1,1])
y1=-1
y2=1
theta = np.array([-0.1,0])

new = theta - 0.1*((np.inner(theta,x1)-y1)+(np.inner(theta,x2)-y2)+theta)
print(new)

loss = 0.5 * ((np.inner(new,x1)-y1)**2 +(np.inner(new,x2)-y2)**2) + 0.5 * (np.linalg.norm(new))**2

print(loss)