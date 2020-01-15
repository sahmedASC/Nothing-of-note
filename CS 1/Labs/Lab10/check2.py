import random
import time
def closest1(x):
    '''
    >>> closest1([ 4.3, 1, 11.8, 17.4, 86, 5.4, ])
    (4.3, 5.4)
    
    >>> closest1([ 15.1, -12.1, 5.4, 11.8, 17.4, 4.3, 6.9 ])
    (4.3, 5.4)
    
    >>> closest1([])
    (None, None)
    >>> closest1([2,2,3,4,5,6,7,8,9])
    (2, 2)
    
    >>> closest1([1.1,2.1,4.1,5.6])
    (1.1, 2.1)
    '''    
    values = set()
    if len(x)<2:
        return None, None
    else:
        for i in x:
            for j in x:
                a = x.index(i)
                x=x[::-1]
                b= len(x)-1- x.index(j)
                if i-j == 0:
                    #print('equal to zero')
                    if a != b:
                        #print("not index")
                        return(i,j)
                else:
                    dist = abs(j-i)
                    values.add((dist,i,j))
        #print(min(values))
        return min(values)[1], min(values)[2]
    
    
def closest2(x):
    '''
    >>> closest2([ 4.3, 1, 11.8, 17.4, 86, 5.4, ])
    (4.3, 5.4)
    
    >>> closest2([ 15.1, -12.1, 5.4, 11.8, 17.4, 4.3, 6.9 ])
    (4.3, 5.4)
    
    >>> closest2([])
    (None, None)
    >>> closest2([2,2,3,4,5,6,7,8,9])
    (2, 2)
    
    >>> closest2([1.1,2.1,4.1,5.6])
    (1.1, 2.1)
    ''' 
    if len(x)<2:
        return None, None    
    y= x.copy()
    y.sort()
    values = set()
    for i in range(len(y)-1):
        b=(abs(y[i+1]-y[i]),y[i],y[i+1])
        values.add(b)
    return min(values)[1], min(values)[2]    

if __name__ == "__main__":
    #list1= [ 8, 5.4, 11.8, 17.4, 4.3, 1, ]
    b=[]
    for i in range(10000):
        x=random.uniform(0.0,1000.0)
        b.append(x)
    #s1 = time.time()
    #(x,y) = closest1(b)
    #t1 = time.time() - s1
    #print("Ver 1: ({},{}); time {:.3f} seconds".format(x,y,t1))

    s2 = time.time()
    (x,y) = closest2(b)
    t2 = time.time() - s2
    print("Ver 2: ({},{}); time {:.3f} seconds".format(x,y,t2))    
    