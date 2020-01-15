x=input("Enter the first number: ")
print(x)
y=input("Enter the second number: ")
print(y)

x=float(x)
y=float(y)

average=(x+y)/2
if x>10 and y>10:
    print("Both are above 10.")
elif x<10 and y<10:
    print("Both are below 10.")
print("Average is",round(average,2))