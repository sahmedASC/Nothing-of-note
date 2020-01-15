from PIL import Image as i

im=i.new('RGB', (512,512))
im1= i.open("inc3.png")
im2= i.open("1.jpg")
im3= i.open("hk.jpg")
im4= i.open("hw.jpg")

im1=im1.resize((256,256))
im2=im2.resize((256,256))
im3=im3.resize((256,256))
im4=im4.resize((256,256))

im.paste(im1,(0,0))
im.paste(im2,(256,0))
im.paste(im3,(0,256))
im.paste(im4,(256,256))

im.show()
