from math import *

def bpopnext(bpop,fpop):
    bpop_n= (10*bpop)/(1+0.1*bpop)-0.05*bpop*fpop
    bpop_n= int(max(0,bpop_n))
    return bpop_n

def fpopnext(bpop,fpop):
    fpop_n= 0.4 * fpop + 0.02 * fpop * bpop
    fpop_n= int(max(0,fpop_n))
    return fpop_n

bpop= input("Nummber of bunnies ==> ")
print(bpop)

fpop= input("Nummber of foxes ==> ")
print(fpop)

print("Year 1:",bpop,fpop)

fpop=int(fpop)
bpop=int(bpop)

bpop_next= bpopnext(bpop,fpop)
fpop_next= fpopnext(bpop,fpop)
print("Year 2:",bpop_next,fpop_next)
bpop=bpop_next
fpop=fpop_next

bpop_next= bpopnext(bpop,fpop)
fpop_next= fpopnext(bpop,fpop)
print("Year 3:",bpop_next,fpop_next)
bpop=bpop_next
fpop=fpop_next

bpop_next= bpopnext(bpop,fpop)
fpop_next= fpopnext(bpop,fpop)
print("Year 4:",bpop_next,fpop_next)
bpop=bpop_next
fpop=fpop_next

bpop_next= bpopnext(bpop,fpop)
fpop_next= fpopnext(bpop,fpop)
print("Year 5:",bpop_next,fpop_next)
