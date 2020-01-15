from PIL import Image as i
from check2_helper import make_square

im=i.new('RGB', (1000,360))
im1= i.open("1.jpg")
im2= i.open("2.jpg")
im3= i.open("3.jpg")
im4= i.open("4.jpg")
im5= i.open("5.jpg")
im6= i.open("6.jpg")

im1=im1.resize((256*im1.size[0]//im1.size[1],256))
im2=im2.resize((256*im2.size[0]//im2.size[1],256))
im3=im3.resize((256*im3.size[0]//im3.size[1],256))
im4=im4.resize((256*im4.size[0]//im4.size[1],256))
im5=im5.resize((256*im5.size[0]//im5.size[1],256))
im6=im6.resize((256*im6.size[0]//im6.size[1],256))

im.paste(im1,(31,20))
im.paste(im2,(41+im1.size[0],60))
im.paste(im3,(51+im1.size[0]+im2.size[0],20))
im.paste(im4,(61+im1.size[0]+im2.size[0]+im3.size[0],60))
im.paste(im5,(71+im1.size[0]+im2.size[0]+im3.size[0]+im4.size[0],20))
im.paste(im6,(81+im1.size[0]+im2.size[0]+im3.size[0]+im4.size[0]+im5.size[0],60))

im.show()