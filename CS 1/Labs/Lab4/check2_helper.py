from PIL import Image as i
def make_square(im):
    if im.size[0]>im.size[1]:
        imnew=im.crop((0,0,im.size[1],im.size[1]))
        print("width")
        return imnew
    elif im.size[1]>im.size[0]:
        imnew=im.crop((0,0,im.size[0],im.size[0]))
        print("height")
        return imnew        