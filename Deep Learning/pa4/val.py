import numpy as np
import tensorflow as tf
from tensorflow import keras
from keras import layers

#Model as defined in the submitted dl_pa4.py python file
#We edit this file since we used sequential to define our model.
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

#load data for testing and validation purposes
#You must change the path passed into the np.load() function in order to load your training data.
testing_data = np.load('/content/drive/My Drive/Colab_Notebooks/pa4/videoframes_clips_valid.npy') 
testing_label = np.load('/content/drive/My Drive/Colab_Notebooks/pa4/joint_3d_clips_valid.npy')

#create our dataset by batching.
batch_size = 2
test_dataset = (
    tf.data.Dataset.from_tensor_slices((testing_data, testing_label)).batch(batch_size)
)

if __name__ == '__main__':
    # The following implementation is for students who construct model with tf.keras subclass model
    # Please adjust the following part accordingly if you adopt other implementation method.

    #create our model and do a prediction in order to initialize the model and build it
    model = DeepDynamicModel()
    model.predict(tf.ones(shape=[1, 8, 224, 224, 3]))

    #load the model weights from the trainined model
    #again please change the path in order to find the requisite file.
    model.load_weights('/content/drive/My Drive/Colab_Notebooks/pa4/model_weights')

    #the rest that follows is the val.py file provided by TA
    tmp_MPJPE = []
    tmp_loss = []
    for x, y in tqdm(test_dataset):
        predict = model.predict(x)
        
        loss = tf.math.reduce_sum(tf.losses.mean_squared_error(y, predict)) / batch_size
        
        MPJPE = tf.math.reduce_mean(tf.math.reduce_euclidean_norm((y - predict), axis=3)) * 1000
        tmp_MPJPE.append(MPJPE)
        tmp_loss.append(loss)
    testing_los = tf.reduce_mean(tmp_loss)
    test_MPJPE = tf.reduce_mean(tmp_MPJPE)
    print('MPJPE:', test_MPJPE.numpy())
