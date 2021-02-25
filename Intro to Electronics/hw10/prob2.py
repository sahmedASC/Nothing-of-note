#IE HW 10 Prob 1 B

from matplotlib import pyplot as plt
import numpy as np

vds = np.arange(0, 6.1, 0.1)

vd = 0
vgs = 2.75
id = []
id2 = []
id3 = []
vtn = 2.5
kn = 0.1
while vd < 6:
    if vgs< vtn:
        id.append(0)
    else:
        if vd < (vgs- vtn):
            print("vds triode", vd)
            current = kn * ((vgs - vtn) * vd - vd ** 2 / 2);
            id.append( current)

        else:
            print("vds saturation", vd)
            current = kn * (vgs - vtn) ** (2) / 2
            id.append(current)
    vd+= 0.1

print("next set of values vgs = 3.0")

vd = 0
vgs = 3

while vd < 6:
    if vgs< vtn:
        id2.append(0)
    else:
        if vd < (vgs- vtn):
            print("vds triode", vd)
            current = kn * ((vgs - vtn) * vd - vd ** 2 / 2);
            id2.append( current)

        else:
            print("vds saturation", vd)
            current = kn * (vgs - vtn) ** (2) / 2
            id2.append(current)
    vd+= 0.1

print("next set of values vgs = 2.25")

vd = 0
vgs = 2.25
while vd < 6:
    if vgs< vtn:
        id3.append(0)
    else:
        if vd < (vgs- vtn):
            print("vds triode", vd)
            current = kn * ((vgs - vtn) * vd - vd ** 2 / 2);
            id3.append( current)

        else:
            print("vds saturation", vd)
            current = kn * (vgs - vtn) ** (2) / 2
            id3.append(current)
    vd+= 0.1

plt.plot(vds,id)
plt.plot(vds, id2)
plt.plot(vds, id3)
plt.xlabel("VDS")
plt.ylabel("ID")
plt.title('ID-VDS')
plt.show()