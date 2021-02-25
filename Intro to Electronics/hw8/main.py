#Code written by Saaif Ahmed
#IE HW 8 Problem 1/3 code
import math
vs = 2
vd = 0.675
r = 47
Is = 10**(-14)
n = 1
vtherm = 52/1000
ir1 = 0

count = 0
while count < 10:
    print(vd)
    vr = vs - vd
    ir1 = vr/r
    vd = n * vtherm * math.log(ir1/Is)

    count+=1
print("current:",ir1)
print("voltage: ",vd)
print("DC bias: ",vd/ir1)
print("gD: ", ir1/(n*vtherm))
print("rD: ", (n*vtherm)/ir1)