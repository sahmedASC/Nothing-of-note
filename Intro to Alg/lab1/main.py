# Code written by Saaif Ahmed
# Lab 1 Intro to Algorithms S20

# Check 1
'''
1: get desired input number
2: check if the middle of the array is the desired number
    a: if yes accept
    b: if no then go to step 3
3:check if the guessed values is greater than the desired number
    a: if yes then begin looking at lower half of the array
    b: if no then begin looking at upper half of the array
4: construct new sub list from halfway point and then the upper or lower bound
5: repeat step 2

x = int(input())
nums = [...]
while True:
    guess = nums[len(nums)//2]
    if x == num:
        break
    else:
        if x > guess:
            nums= nums[len(nums)//2:len(nums)-1]
        else:
            nums= nums[0:len(nums)//2]
    if len(nums) == 1 and num[0] == x:
        break
    elif len(nums) == 1 and num[0] != x:
        break
'''

x = int(input("number: "))
#nums = [2,4,6,8,10]
nums = [1,2,3,4,5,6,6,6]
while True:
    guess = nums[len(nums) // 2]
    if x == guess:
        print('you did it')
        break
    else:
        if x > guess:
            nums = nums[len(nums) // 2:len(nums)]
        else:
            nums = nums[0:len(nums) // 2]
    if len(nums) == 1 and nums[0] == x:
        print("you did it")
        break

    elif len(nums) == 1 and nums[0] != x:
        print("you suck")
        break





