first= input("Please enter you first name: ")
len_first=len(first)

last= input("Please enter your last name: ")
len_last=len(last) +1

hello= "Hello,"
len_hello=len(hello)

maximum= max(len_first,len_last,len_hello)

distance_first=maximum-len_first
distance_last=maximum-len_last
distance_hello=maximum-len_hello
'''
max_distance=max(distance_first,distance_last,distance_hello)
'''

print("*"*(maximum+6))
print("** ", hello," "*(distance_hello)," **",sep="")
print("** ", first," "*(distance_first)," **", sep="")
print("** ", last,"!"," "*(distance_last)," **", sep="")
print("*"*(maximum+6))

    