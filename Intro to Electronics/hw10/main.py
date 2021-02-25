#IE HW 10 Prob 1 A

from matplotlib import pyplot as plt
import numpy as np

vgs = np.arange(0, 6.1, 0.1)

vg = 0
vds = 1
id = []
id2 = []
id3 = []
vtn = 2.5
kn = 0.1
while vg < 6:
    if vg< vtn:
        id.append(0)
    else:
        if vds < (vg- vtn):
            print("vgs triode", vg)
            current = kn * ((vg - vtn) * vds - vds ** 2 / 2);
            id.append( current)

        else:
            print("vgs saturation", vg)
            current = kn * (vg - vtn) ** (2) / 2
            id.append(current)
    vg+= 0.1

print("next set of values vd = 2.5")
vg = 0
vds = 2.5
while vg < 6:
    if vg< vtn:
        id2.append(0)
    else:
        if vds < (vg- vtn):
            print("vgs triode", vg)
            current = kn * ((vg - vtn) * vds - vds ** 2 / 2);
            id2.append( current)

        else:
            print("vgs saturation", vg)
            current = kn * (vg - vtn) ** (2) / 2
            id2.append(current)
    vg+= 0.1

print("next set of values vd = 2")
vg = 0
vds = 2
while vg < 6:
    if vg< vtn:
        id3.append(0)
    else:
        if vds < (vg- vtn):
            print("vgs triode", vg)
            current = kn * ((vg - vtn) * vds - vds ** 2 / 2);
            id3.append( current)

        else:
            print("vgs saturation", vg)
            current = kn * (vg - vtn) ** (2) / 2
            id3.append(current)
    vg+= 0.1

plt.plot(vgs,id)
plt.plot(vgs, id2)
plt.plot(vgs, id3)
plt.xlabel("VGS")
plt.ylabel("ID")
plt.title('ID-VGS')
plt.show()
