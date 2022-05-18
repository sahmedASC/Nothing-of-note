import tensorflow as tf
import matplotlib.pyplot as plt
import numpy as np
from tensorflow.keras import layers
from tensorflow import keras
from tqdm import tqdm

#same funtion as in main dl_final.py
def generate_and_save_images(model, discriminator, test, start):
  decisions = []
  for point in tqdm(range(100)):
    noise = test[point + start - 1]
    pred = model(noise, training=False)
    decision = discriminator(pred)
    decisions.append(decision)
    plt.imshow(pred[0,:,:,0] * 127.5 + 127.5)
    plt.axis('off')
    plt.savefig('/content/drive/My Drive/Colab_Notebooks/pa_final/generated_images/image_{:04d}.png'.format(start+point))

#FID function. Not implemented 
def test_fid(model, train_images, test_images):

  return None

#IS function. Not implemented since loading images was not implemented.
def test_is(images, generated_images):

  return None

noise_dim = 100
gen_num = 1000

#add in your path for the saved model locations.
generator = keras.models.load_model('path/to/location')
discriminator = keras.models.load_model('path/to/location')

#can change seed with the below value. Be sure to adjust dimension of noise_dim accordingly
seed = tf.random.normal([gen_num, 1,1, noise_dim])  

generate_and_save_images(generator, discriminator, seed, 101)
