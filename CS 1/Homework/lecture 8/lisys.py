values = [ 14, 10, 8, 19, 7, 13 ]

x= int(input("Enter a value: "))
print(x)
values.append(x)

y=int(input("Enter another value: "))
print(y)
values.insert(2,y)

print(values[3], values[-1])
print("Difference:",(max(values)-min(values)))
print("Average:",round(sum(values)/len(values),1))
values = sorted(values)
middle=round(len(values)/2)
print("Median:",(values[middle-1]+values[middle])/2 )

