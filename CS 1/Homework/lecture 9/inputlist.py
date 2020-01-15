#this code was written by Saaif Ahmed '22

x=[]

while True:
    y=input("Enter a value (0 to end): ")
    print(y)
    y=int(y)
    x.append(y)
    if y == 0:
        break
x.remove(0)
maxi=max(x)
mini=min(x)
avg=sum(x)/len(x)
print("Min:",mini)

print("Max:",maxi)

print("Avg:",round(avg,1))
