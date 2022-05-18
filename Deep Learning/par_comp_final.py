import matplotlib.pyplot as plt
import numpy as np
import pickle
import random as r
import tensorflow as tf
from tensorflow import keras
from keras import layers
from google.colab import drive
import math
drive.mount('/content/gdrive')

training_labels = np.loadtxt('/content/gdrive/My Drive/Colab_Notebooks/pc_final/labels/train_label.txt', dtype = int) # Make sure folders and your python script are in the same directory. Otherwise, specify the full path name for each folder.
# convert 1-5 to 0-4 and build one hot vectors
training_labels = np.array( (tf.reshape(tf.one_hot(training_labels - 1 , 5, dtype=tf.float32), (-1, 5))))
testing_labels = np.loadtxt('/content/gdrive/My Drive/Colab_Notebooks/pc_final/labels/test_label.txt', dtype = int) # Make sure folders and your python script are in the same directory. Otherwise, specify the full path name for each folder.
testing_labels = np.array((tf.reshape(tf.one_hot(testing_labels - 1 , 5, dtype=tf.float32), (-1, 5))))

train_set = np.array(pickle.load( open( "/content/gdrive/My Drive/Colab_Notebooks/pc_final/training_set.txt", "rb" ) ))
test_set = np.array(pickle.load( open( "/content/gdrive/My Drive/Colab_Notebooks/pc_final/testing_set.txt", "rb" ) ))

model = keras.Sequential(
    [
     layers.Dense(5, activation = 'softmax')
    ])

epochs = 20
batch_size = 80

model.compile(optimizer=tf.keras.optimizers.Adam(learning_rate=1e-3, beta_1 = .75, beta_2 = .95),
               loss= keras.losses.MeanSquaredError(), metrics=['accuracy'])
completed_model = model.fit(train_set, training_labels, 
                             validation_data=(test_set, testing_labels),batch_size=batch_size, epochs=epochs)