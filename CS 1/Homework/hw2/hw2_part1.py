#This code was written by Saaif Ahmed '22. 
#A penny for a Gum Ball Mickey

import math as m

def find_volume_sphere(radius):
    '''given a radius find the volume of a sphere'''
    pi=m.pi
    vol=(4/3)*pi*radius**3
    return vol


def find_volume_cube(side):
    '''find a volume of a cube given a side'''
    return side**3

#gather user input for operations
rad_gum=input("Enter the gum ball radius (in.) => ")
print(rad_gum)
rad_gum=float(rad_gum)

sales=input("Enter the weekly sales => ")
print(sales)
sales=float(sales)


#determine target sales by 1.25*sales
goal_sales=m.ceil(1.25*sales)

#Take the cubic root of the target sales and ceiling it
#then use it to determine the side length as diameter*gumballs_per_side 
gum_per_side= m.ceil((goal_sales)**(1/3))
side=gum_per_side*(2*rad_gum)

#call functions defined at the beginning and store the return into variables
volume=find_volume_cube(side)
sphere=find_volume_sphere(rad_gum)

total_gum=gum_per_side**3
extra_gum=total_gum-goal_sales

#Determine the volume taken up by the gum balls for target sales and if
#the machine was completely filled
volume_gum=sphere*goal_sales
total_vol_gum=sphere*total_gum

#outputs formatted using .format() method
print("")
print("The machine needs to hold",gum_per_side,"gum balls along each edge.")
print("Total edge length is {0:.2f} inches.".format(side))
print("Target sales were {0:}, but the machine will hold {1:} extra gum balls.".format(goal_sales,extra_gum))
print("Wasted space is {0:.2f} cubic inches with the target number of gum balls,".format(volume-volume_gum))
print("or {0:.2f} cubic inches if you fill up the machine.".format(volume-total_vol_gum))