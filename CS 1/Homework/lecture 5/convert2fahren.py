#This was made by Saaif Ahmed '22
#The objective of this program is to convert three degrees C to degrees F


c1=0
c2=32
c3=100
def convert2fahren(c):
    #This takes a degree C as an argument c and converts it to degree F
    f=(c*1.8)+32
    print(c, "->", f)
    return f
convert2fahren(c1)
convert2fahren(c2)
convert2fahren(c3)