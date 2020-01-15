co2_levels = [ 320.03, 322.16, 328.07, 333.91, 341.47, \
               348.92, 357.29, 363.77, 371.51, 382.47, 392.95 ]
avg=sum(co2_levels)/len(co2_levels)
items=len(co2_levels)
num=0
index=0
for i in co2_levels:
    if co2_levels[index] > avg:
        num+=1
    index+=1
print("Average:",round(avg,2))
print("Num above average:",num)