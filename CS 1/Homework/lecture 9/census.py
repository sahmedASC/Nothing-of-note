#This was written by Saaif Ahmed '22
census = [ 340, 589, 959, 1372, 1918, 2428, 3097, 3880, 4382, 5082, \
            5997, 7268, 9113, 10385, 12588, 13479, 14830, 16782, \
            8236, 17558, 17990, 18976, 19378 ]

i=0
total_difference=0
while i<len(census)-1:
    percent_difference= ((census[i+1]-census[i])/census[i])*100
    total_difference+=percent_difference
    i+=1
avg=total_difference/(i)
print("Average = {0:.1f}%".format(avg))
    