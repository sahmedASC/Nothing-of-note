def add(m,n):
    if n == 0:
        return m
    else:
        return add(m,n-1)+1

def mult(b,a):
    if a==0:
        return 0
    if a == 1:
        return b
    if a == -1:
        return -1*b
    else:
        return add(mult(b,a-1),b)
    
def power(b,a):
    if a==1:
        return b
    if a==0:
        return 1
    if a ==-1:
        return 1/b
    else:
        return mult(power(b,a-1),b)
print(add(5,5))

print(mult(3,2))

print(power(2,4))
