import tensorflow as tf
import glob
import imageio
import matplotlib.pyplot as plt
import numpy as np
import os
import PIL
from tensorflow.keras import layers
from tensorflow import keras
import time
from tqdm import tqdm

#discriminator loss function for gradients
def disc_loss(real, fake):
  rloss = cross_entropy(tf.ones_like(real), real)
  floss = cross_entropy(tf.zeros_like(fake), fake)
  total = rloss + floss
  return total

#generator loss function for gradients
def gen_loss(fake):
  return cross_entropy(tf.ones_like(fake), fake)

#we define a tf function to use tf global variables
@tf.function
def training_step(images):
  #following algorithm create the noise 
  noise = tf.random.normal([1, 1, 100])

  with tf.GradientTape() as gen_tape, tf.GradientTape() as disc_tape:
    #define gradient with gradient tape
    genimages = generator(noise, training=True)
    real = discriminator(images, training=True)
    fake = discriminator(genimages, training=True)

    #compute loss
    gloss = gen_loss(fake)
    dloss = disc_loss(real, fake)

  #get gradients using the training variables
  gen_grad = gen_tape.gradient(gloss, generator.trainable_variables)
  disc_grad = disc_tape.gradient(dloss, discriminator.trainable_variables)

  #apply newly learned gradients
  generator_optimizer.apply_gradients(zip(gen_grad, generator.trainable_variables))
  discriminator_optimizer.apply_gradients(zip(disc_grad, discriminator.trainable_variables))

#Main training function
def train(dataset, epochs):

  #epochs is a hyper parameter for training purposes
  for epoch in tqdm(range(epochs)):
    start = time.time()
    i = 0
    #go through the mini batch for training
    for image_batch in tqdm(dataset):     
      training_step(image_batch)
      i+=1
    
    #Remove block if commented out checkpoints
    if (epoch + 1) % 15 == 0:
      checkpoint.save(file_prefix = checkpoint_prefix)
    ####################
    print('Epoch Time {} is {} seconds'.format(epoch+1, time.time()-start))

def generate_and_save_images(model, discriminator, test, start):
  decisions = []
  for point in tqdm(range(100)):
    noise = test[point + start - 1]
    #make a prediction
    pred = model(noise, training=False)
    decision = discriminator(pred)
    decisions.append(decision)
    #output the predction
    plt.imshow(pred[0,:,:,0] * 127.5 + 127.5)
    plt.axis('off')
    #save it
    plt.savefig('/content/drive/My Drive/Colab_Notebooks/pa_final/generated_images/image_{:04d}.png'.format(start+point))

#Data loading
real_images = np.load('/content/drive/My Drive/Colab_Notebooks/pa_final/images.npy')
attributes = np.load('/content/drive/My Drive/Colab_Notebooks/pa_final/attributes5.npy')

#hyper parameters to distinguish the data processing
BUFFER_SIZE = 50000
BATCH_SIZE = 1000

#shuffle the data and create batches
train_dataset = tf.data.Dataset.from_tensor_slices(real_images).shuffle(BUFFER_SIZE).batch(BATCH_SIZE)

#Create the generator as shown in the report
#layers are added sequentially use ReLU activation function
generator = tf.keras.Sequential([
    layers.Dense(4*4*1024, use_bias=False, input_shape=(1,100)),
    layers.BatchNormalization(),
    layers.LeakyReLU(),
    layers.Reshape((4,4,1024)),
    layers.Conv2DTranspose(1024, (4, 4), strides=(1,1), padding='same'),
    layers.BatchNormalization(),
    layers.ReLU(),
    layers.Conv2DTranspose(512, (5,5), strides=(2,2), padding='same'),
    layers.BatchNormalization(),
    layers.ReLU(),
    layers.Conv2DTranspose(256, (5,5), strides=(2,2), padding='same'),
    layers.BatchNormalization(),
    layers.ReLU(),
    layers.Conv2DTranspose(128, (5,5), strides=(2,2), padding='same'),
    layers.BatchNormalization(),
    layers.ReLU(),
    layers.Conv2DTranspose(3, (5,5), strides=(2,2), padding='same'),
    layers.BatchNormalization()
])

#Create the discriminator as shown in the report. Added in dropouts to prevent
#over fitting. Uses ReLU activation.
discriminator = tf.keras.Sequential([
  layers.Conv2D(64, (2,2), strides=(2,2), padding='same', input_shape=[64,64,3]),
  layers.ReLU(),
  layers.Dropout(.3),
  layers.Conv2D(128, (2,2), strides=(2,2), padding='same'),
  layers.ReLU(),
  layers.Dropout(.3),
  layers.Conv2D(256, (2,2), strides=(2,2), padding='same'),
  layers.ReLU(),
  layers.Dropout(.3),
  layers.Conv2D(512, (2,2), strides=(2,2), padding='same'),
  layers.ReLU(),
  layers.Dropout(.3),
  layers.Flatten(),
  layers.Dense(1, activation=('sigmoid')),
])

#define losses and optimizers of the model. Apply learning rates.
cross_entropy = tf.keras.losses.BinaryCrossentropy(from_logits=True)
generator_optimizer = tf.keras.optimizers.Adam(1e-4)
discriminator_optimizer = tf.keras.optimizers.Adam(1e-4)

#Tensorflow checkpoints. Aided in development can be removed
checkpoint_dir = '/content/drive/My Drive/Colab_Notebooks/pa_final/training_checkpoints'
checkpoint_prefix = os.path.join(checkpoint_dir, "ckpt")
checkpoint = tf.train.Checkpoint(generator_optimizer=generator_optimizer, discriminator_optimizer=discriminator_optimizer, generator=generator, discriminator=discriminator)
#if removing see the train() function.
###########################

# Hyper parameters
epochs = 20
noise_dim = 100
generate_num = 1000

#Seed for the training can be changed but change the noise_dim value
seed = tf.random.normal([generate_num, 1,1, noise_dim])
train(train_dataset, epochs)
generate_and_save_images(generator, discriminator, seed, 101)

#saving the model
#Must add own path when running.
generator.save('/content/drive/My Drive/Colab_Notebooks/pa_final/generator_model')
discriminator.save('/content/drive/My Drive/Colab_Notebooks/pa_final/discriminator_model')