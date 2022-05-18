import pathlib
import matplotlib.pyplot as plt
import numpy as np
import pickle
import random as r
import tensorflow as tf
#from plot import plot, visual
import pandas as pd
import math
import os
os.environ["KMP_DUPLICATE_LIB_OK"]="TRUE"

# read images
def load_images(path_list):
    number_samples = len(path_list)
    Images = []
    for each_path in path_list:
        img = plt.imread(each_path)
        # divided by 255.0
        img = img.reshape(784, 1) / 255.0
        '''
        In some cases data need to be preprocessed by subtracting the mean value of the data and divided by the 
        standard deviation to make the data follow the normal distribution.
        In this assignment, there will be no penalty if you don't do the process above.
        '''
        # add bias
        img = np.vstack((img, [1]))
        Images.append(img)
    data = tf.convert_to_tensor(np.array(Images).reshape(number_samples, 785), dtype=tf.float32)
    return data

#sigmoid function as determined in the report and derived in lecture.
def sigmoid(X, theta,k,index):
    denom = 0
    for i in range(len(k)):
        denom += math.exp(np.inner(X,theta[i]))

    numer = (math.exp(np.inner(X,theta[index])))/denom
    return numer

#loss function as determined in the report and derived in lecture.
def loss(X,theta,y):
    cost = 0
    for i in range(len(X)):
        for j in range(len(y[i])):
            cost += y[i][j] * math.log(sigmoid(X[i],theta,y[i],j))
    return (cost*-1)

#gradient for multi class logisitic regression. Builds the whole gradient matrix.
def gradient(X,y, theta):
    grad = np.zeros(np.shape(X[0]))
    new_theta = np.zeros(np.shape(theta))
    for j in range(len(y[0])):
        for i in range(len(X)):
            grad+= (y[i][j] - sigmoid(X[i],theta,y[i],j)) * X[i]
        new_theta[j] =grad*-1
    return new_theta

#Test the model learned parameters by making predictions with the sigmoid function
#chooses the maximum value of the individual class outputs of the sigmoid function
def test_model(X,y,theta):
    y_guess = [0,0,0,0,0]
    for i in range(len(X)):
        correct = np.where(y[i]==1)[0][0]
        guess = []
        for j in range(len(y[i])):
            g= (sigmoid(X[i],theta,y[i],j), j)
            guess.append(g)
        if max(guess)[1] != correct:
            y_guess[correct] +=1
    return y_guess


# load training & testing data
train_data_path = 'train_data' # Make sure folders and your python script are in the same directory. Otherwise, specify the full path name for each folder.
test_data_path = 'test_data' # Make sure folders and your python script are in the same directory. Otherwise, specify the full path name for each folder.
train_data_root = pathlib.Path(train_data_path)
test_data_root = pathlib.Path(test_data_path)

# list all training images paths，sort them to make the data and the label aligned
all_training_image_paths = list(train_data_root.glob('*'))
all_training_image_paths = sorted([str(path) for path in all_training_image_paths])

# list all testing images paths，sort them to make the data and the label aligned
all_testing_image_paths = list(test_data_root.glob('*'))
all_testing_image_paths = sorted([str(path) for path in all_testing_image_paths])

# load labels
training_labels = np.loadtxt('labels/train_label.txt', dtype = int) # Make sure folders and your python script are in the same directory. Otherwise, specify the full path name for each folder.
# convert 1-5 to 0-4 and build one hot vectors
training_labels = (tf.reshape(tf.one_hot(training_labels - 1 , 5, dtype=tf.float32), (-1, 5))).numpy()
testing_labels = np.loadtxt('labels/test_label.txt', dtype = int) # Make sure folders and your python script are in the same directory. Otherwise, specify the full path name for each folder.
testing_labels = (tf.reshape(tf.one_hot(testing_labels - 1 , 5, dtype=tf.float32), (-1, 5))).numpy()

# #--Block-- (Can uncomment block to load new data)
# # load images
# train_set = load_images(all_training_image_paths)
# test_set = load_images(all_testing_image_paths)
#
# #dump the training set
# filehandler1 = open("training_set.txt","wb")
# pickle.dump(train_set, filehandler1)
# filehandler1.close()
#
# #dump the testing set
# filehandler2 = open("testing_set.txt","wb")
# pickle.dump(test_set,filehandler2)
# filehandler2.close()
# #--Block--

#--Block-- (Pickle block so we don't need to convert data all the time and can just load pickle)
#comment these lines out if uncommenting above block to load new data
train_set = pickle.load( open( "training_set.txt", "rb" ) ).numpy()
test_set = pickle.load( open( "testing_set.txt", "rb" ) ).numpy()
#--Block--

#--Block-- (Set of our hyper parameters of traning the model)
theta = np.zeros((len(training_labels[0]),len(train_set[0])))
learning_rate=0.0001
iterations = 40
count = 0
y_count = [0,0,0,0,0]
for i in range(len(testing_labels)):
    k_to_1=np.where(testing_labels[i]==1)[0][0]
    y_count[k_to_1] +=1
#--Block--

#--Block--(Block that trains the model using gradient descent and gathers data)
loss_per_iter=[]
avg_acc = []
label_acc = []
x_axis = []
for i in range(len(testing_labels[0])):
    foo = []
    label_acc.append(foo)

while count<iterations:
    #collects data every 10 iterations
    if count%4 == 0:
        loss_per_iter.append( loss(train_set,theta,training_labels))
        iter_acc = test_model(test_set,testing_labels,theta)
        for i in range(len(iter_acc)):
            label_acc[i].append(iter_acc[i]/y_count[i])
        avg_acc.append(1-np.mean(np.divide(iter_acc,y_count)))
        print(count)
        x_axis.append(count)

    #updates theta matrix every iteration
    theta = theta - learning_rate*gradient(train_set,training_labels,theta)
    count +=1
#--Block--

#--Block--(Plotting all the data)
#need 1 plot for training loss per iteration
plot1 = plt.figure(1)
plt.plot(x_axis,loss_per_iter,color='r',label = "Training Loss")
plt.xlabel("Iteration")
plt.ylabel("Training Loss")
plt.title("Training Loss vs. Iteration")
plt.legend()
plt.show()

#need 1 plot for each classifier and it's accuracy/error
plot2 = plt.figure(2)
colors = ['r','g','b','c','m']
for i in range(len(label_acc)):
    plt.plot(x_axis,label_acc[i], color=colors[i],label = "Class: " +str(i+1))

plt.xlabel("Iteration")
plt.ylabel("Test Classifier Error")
plt.title("Test Classifier Error vs. Iteration")
plt.legend()
plt.show()

#need 1 plot for average traning accuracy per iteration
plot3 = plt.figure(3)
plt.plot(x_axis,avg_acc,color='g',label = "Average Accuracy")
plt.xlabel("Iteration")
plt.ylabel("Average Test Accuracy")
plt.title("Average Test Accuracy vs. Iteration")
plt.legend()
plt.show()
#--Block--

#--Block-- (Use to dump the theta matrix or W matrix of learned weights
filehandler = open("multiclass_parameters.txt","wb")
pickle.dump(theta, filehandler)
filehandler.close()
#--Block--

#--Block-- (Use the following block to plot Wk as an image for each digit)
theta =pickle.load( open( "multiclass_parameters.txt", "rb" ) )
for i in theta:
    img = i[0:784]
    img = img.reshape(28,28)
    plt.imshow(img)
    plt.colorbar()
    plt.show()

#--Block--