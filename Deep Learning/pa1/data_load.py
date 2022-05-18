import pathlib
import matplotlib.pyplot as plt
import numpy as np
import pickle
import random as r
import tensorflow as tf
#from plot import plot, visual
import pandas as pd

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

# load training & testing data
train_data_path = 'train_data_2' # Make sure folders and your python script are in the same directory. Otherwise, specify the full path name for each folder.
test_data_path = 'test_data_2' # Make sure folders and your python script are in the same directory. Otherwise, specify the full path name for each folder.
train_data_root = pathlib.Path(train_data_path)
test_data_root = pathlib.Path(test_data_path)

# list all training images paths，sort them to make the data and the label aligned
all_training_image_paths = list(train_data_root.glob('*'))
all_training_image_paths = sorted([str(path) for path in all_training_image_paths])

# list all testing images paths，sort them to make the data and the label aligned
all_testing_image_paths = list(test_data_root.glob('*'))
all_testing_image_paths = sorted([str(path) for path in all_testing_image_paths])

# load labels
training_labels = np.loadtxt('labels_2/train_label.txt', dtype = int) # Make sure folders and your python script are in the same directory. Otherwise, specify the full path name for each folder.
# convert 0-9 and build one hot vectors
training_labels = tf.reshape(tf.one_hot(training_labels , 10, dtype=tf.float32), (-1, 10))
testing_labels = np.loadtxt('labels_2/test_label.txt', dtype = int) # Make sure folders and your python script are in the same directory. Otherwise, specify the full path name for each folder.
testing_labels = tf.reshape(tf.one_hot(testing_labels  , 10, dtype=tf.float32), (-1, 10))


#--Block-- (Can uncomment block to load new data)
# load images
train_set = load_images(all_training_image_paths)
test_set = load_images(all_testing_image_paths)

#dump the training set
filehandler1 = open("training_set_2.txt","wb")
pickle.dump(train_set, filehandler1)
filehandler1.close()

#dump the testing set
filehandler2 = open("testing_set_2.txt","wb")
pickle.dump(test_set,filehandler2)
filehandler2.close()
#--Block--

print("hello")