#Code written by Saaif Ahmed
#IE HW 8 Problem 2 code
import math
vs = 2.0
vd = 0.5
r = 200
Is = 10**(-14)
n = 1
vtherm = 26/1000


count = 0
while count < 10:
    print(vd)
    #vr = vs - vd
    vr = vs - (vd + vd)
    ir1 = vr/r
    #vd = n * vtherm * math.log((ir1/2)/Is)
    vd = n * vtherm * math.log(ir1/Is)
    count+=1
print("current:",ir1)
print("voltage: ",vd)
print("DC bias: ",vd/ir1)
print("gD: ", ir1/(n*vtherm))
print("rD: ", (n*vtherm)/ir1)