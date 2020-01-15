hd = input("Enter Dale's height: ")
print(hd)
hd=int(hd)


he = input("Enter Erin's height: ")
print(he)
he=int(he)


hs = input("Enter Sam's height: ")
print(hs)
hs=int(hs)

if hd>he and he>hs:
    print("Dale")
    print("Erin")
    print("Sam")
elif hd> hs and hs>he:
    print("Dale")
    print("Sam")
    print("Erin")
elif hs>hd and hd>he:
    print("Sam")
    print("Dale")
    print("Erin")
elif hs>he and he>hd:
    print("Sam")
    print("Erin")
    print("Dale")
elif he>hd and hd>hs:
    print("Erin")
    print("Dale")
    print("Sam")
else:
    print("Erin")
    print("Sam")
    print("Dale")

