import tensorflow as tf
from tensorflow import keras
from keras import layers
import numpy as np
import matplotlib.pyplot as plt
import math

# from google.colab import drive
# drive.mount('/content/drive')

#Our deep dynamic model used for learning the parameters.
#Consists of 5 convolutional layers, 2 pooling layers, 2 dense layers
#and 1 LSTM layer.
def DeepDynamicModel():
  model= keras.Sequential(
    [ layers.Lambda(lambda x: tf.divide(tf.cast(x,tf.float32),255.0)),
        layers.TimeDistributed(layers.Conv2D(16, 7, strides=(2, 2), activation='relu'), input_shape = (8, 224, 224, 3)),
        layers.TimeDistributed(layers.MaxPooling2D(pool_size=(2, 2))),
        layers.TimeDistributed(layers.Conv2D(16, 3, strides=(2, 2), activation='relu')),
     layers.TimeDistributed(layers.Conv2D(32, 3, 2, activation='relu')),
     layers.TimeDistributed(layers.Conv2D(64, 3, 2, activation='relu')),
     layers.TimeDistributed(layers.Conv2D(128, 3, 2, activation='relu')),
     layers.TimeDistributed(layers.MaxPooling2D(pool_size=(2, 2))),
     layers.TimeDistributed(layers.Flatten()),
     layers.LSTM(128, activation='relu',return_sequences=True),
     layers.TimeDistributed(layers.Dense(256, activation='relu')),
     layers.TimeDistributed(layers.Dense(51, activation= 'linear')),
     layers.Reshape((8, 17, 3))
    ])
  return model

#helper function used to calculate our proper metric that being MPJPE
#Passed into the model.fit() function for training and recording performance.
def MPJPE_error(y_true, y_pred):
  error = tf.math.reduce_euclidean_norm(y_pred - y_true, axis =-1)
  mean = tf.reduce_mean(error)
  return mean*1000


#load the data
#Note: adjust file accordingly in order to load the data from your given directory
#update path as needed
training_data = np.load('/content/drive/My Drive/Colab_Notebooks/pa4/videoframes_clips_train.npy')
training_labels = np.load('/content/drive/My Drive/Colab_Notebooks/pa4/joint_3d_clips_train.npy')
testing_data = np.load('/content/drive/My Drive/Colab_Notebooks/pa4/videoframes_clips_valid.npy')
testing_labels = np.load('/content/drive/My Drive/Colab_Notebooks/pa4/joint_3d_clips_valid.npy')

#Create our model and begin training
#setup up our batch size and learning rate and other hyper parameters
model2= DeepDynamicModel()
epochs = 5
batch_size = 80

model2.compile(optimizer=tf.keras.optimizers.Adam(learning_rate=1e-2, beta_1 = .75, beta_2 = .95),
               loss= keras.losses.MeanSquaredError(), metrics=['accuracy',MPJPE_error])
completed_model = model2.fit(training_data, training_labels, 
                             validation_data=(testing_data, testing_labels),batch_size=batch_size, epochs=epochs)

#Code block for plotting
n = np.arange(0, epochs)

plt.figure()
plt.plot(n, completed_model.history['loss'], label="train loss")
plt.plot(n, completed_model.history['val_loss'], label="validation loss")
plt.xlabel("Epochs")
plt.ylabel("Loss")
plt.title('Training and Testing Loss')
plt.legend()

plt.figure()
plt.plot(n, completed_model.history['accuracy'], label="train accuracy")
plt.plot(n, completed_model.history['val_accuracy'], label="validation accuracy")
plt.title('Training and Testing Accuracy')
plt.xlabel("Epochs")
plt.ylabel("Loss")
plt.legend()

plt.figure()
plt.plot(n,completed_model.history['val_MPJPE_error'])
plt.title('MPJPE Testing Results')
plt.xlabel("Epochs")
plt.ylabel("MPJPE")

plt.figure()
plt.plot(n,completed_model.history['MPJPE_error'])
plt.title('MPJPE Training Results')
plt.xlabel("Epochs")
plt.ylabel("MPJPE")
plt.show()
#################

#Save our model and in the designated destination with the required filename
# model2.summary()
model2.save('/content/drive/My Drive/Colab_Notebooks/pa4/model_weights')


#block used to get our explicityly last MPJPE value after training.
y_pred = model2.predict(testing_data)

error = tf.math.reduce_euclidean_norm(y_pred - testing_labels, axis =-1)
mean = tf.reduce_mean(error)
print('MPJPE is: ' + str(mean*1000))