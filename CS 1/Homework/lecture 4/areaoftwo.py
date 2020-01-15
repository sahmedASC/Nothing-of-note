#This was made by Saaif Ahmed '22 and this program outputs the area of a circle
#radius of either 5 or 32
# a(r)=pi*r**2
import math
real_pi= math.pi
area1= real_pi*5**2
area2= real_pi*math.pow(32,2)
area2= round(area2,2)
print("Area 1 = {0:.2f}".format(area1))
print("Area 2 =", area2)
