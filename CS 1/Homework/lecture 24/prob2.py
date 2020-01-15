
points = [ (4,2), (1,-3), (-4, -6), (6,9), (3,8), (-5,2), (6,2) ]
b= filter(lambda x: x[1]+x[0]>0,points)
min_x = min(b)
print(min_x[0])