# Code written by Saaif Ahmed
# Lab 1 Intro to Algorithms S20

# Check 2
unsorted = [3, 5, 4, 6, 2, 8, 1]
max = 0
sum = 0
for i in range(len(unsorted)):
    sum = sum + unsorted[i]
    if unsorted[i] > max:
        max = unsorted[i]

sum_of_all = (max * (max+1))//2
print(sum_of_all - sum)

