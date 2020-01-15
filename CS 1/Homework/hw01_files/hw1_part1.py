#This code was written by Saaif Ahmed '22
#The objective of this program is to determine how long it will take for a 
#lifegaurd to save someone based on certain values and distances.
import math as m

#This part takes the input from the user according to format
d1= input("Enter the shortest distance from the lifeguard to water, d1 (yards) => ")
print(d1)
d1=float(d1)

d2= input("Enter the shortest distance from the swimmer to the shore, d2 (feet) => ")
print(d2)
d2=float(d2)

h=input("Enter the lateral displacement between the lifeguard and the swimmer, h (yards) => ")
print(h)
h=float(h)

v_sand= input("Enter the lifeguard's running speed on sand, v_sand (MPH) => ")
print(v_sand)
v_sand=float(v_sand)

n= input("Enter the lifeguard's swimming slowdown factor, n => ")
print(n)
n=float(n)

theta1=input("Enter the direction of lifeguard's running on sand, theta1 (degrees) => ")
print(theta1)

theta1=float(theta1)

#Create theta2 so I don't have to reassign theta 1
theta2= (theta1*m.pi)/180

#convert units like yards and mph to feet based units and second based units
d1=d1*3
h=h*3
v_sand= (v_sand*5280)/3600

#Create distance X based off of theta2
x= d1*m.tan(theta2)

#calculate L1 based on formula
l1= ((x**2)+(d1**2))**0.5

#calculate L2 based on formula
l2= (((h-x)**2)+(d2**2))**0.5

#calculate T based on formula
t= (l1+(n*l2))/v_sand

#Output
print("If the lifeguard starts by running in the direction with theta1 of",round(theta1)
      ,"degrees,\nthey will reach the swimmer in",round(t,1),"seconds")