from PIL import Image as i
from check2_helper import make_square

im=i.new('RGB', (512,512))
im1= i.open("im.jpg")
im2= i.open("ca.jpg")
im3= i.open("hk.jpg")
im4= i.open("hw.jpg")

im1=make_square(im1)
im2=make_square(im2)
im3=make_square(im3)
im4=make_square(im4)

im1=im1.resize((256,256))
im2=im2.resize((256,256))
im3=im3.resize((256,256))
im4=im4.resize((256,256))

im.paste(im1,(0,0))
im.paste(im2,(256,0))
im.paste(im3,(0,256))
im.paste(im4,(256,256))

im.show()