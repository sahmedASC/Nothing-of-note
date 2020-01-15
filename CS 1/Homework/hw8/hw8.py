#This code was written by Saaif Ahmed '22
#WOOOOOOO last homework. Now it is time for the final
#The objective of this program was to run a simulation of people moving through
#universes and running functions if certain things occurred. The winnning person
#is crowned Pokemon/Rick and Morty master of all RPI. 

from Universe import *
from Person import *
import json

#get the input file and read it
input_file = input("Input file => ").strip()
print(input_file)

data = json.loads(open(input_file).read())

#create lists for each universe objects and people objects
universes = []
peeps = []
for i in data:
    rewards = []
    portals = []
    for j in i['rewards']:
        if len(j) == 0:
            break
        else:
            r= Reward(j[0],j[1],j[2],j[3],i['universe_name'])
            rewards.append(r)
    for j in i['portals']:
        if len(j) == 0:
            break
        else:
            p = Portal(j[0],j[1],j[2],j[3],j[4])
            portals.append(p)
    for k in i['individuals']:
        people = Person(k[0],k[1],i['universe_name'],k[2],k[3],k[4],k[5],i['universe_name'],[])
        peeps.append(people)
    
    x= Universe(rewards,i['universe_name'],portals)
    universes.append(x)

#first set of output and formatting  
print("All universes")
print("-"*40)
if len(universes) == 1:
    for i in universes:
        print(str(i))
        print("")        
else:
    for i in universes:
        print(str(i),end="\n\n")    
print("All individuals")
print("-"*40)
for i in peeps:
    print(i.word())

print("")
print("Start simulation")
print("-"*40)

#beginning the simulation first check to see if any individual has invalid
#starting values
count = 0
lost= [] #lost is a list of people that have lost already so they are no repeats
for i in peeps:
    i.check()
    if i.m==False:
        print("{} stopped at simulation step {} at location ({:.1f},{:.1f})".format(i.name,count,i.x,i.y))
        print("")
        lost.append(i)
        peeps.remove(i)
        continue
for i in peeps:
    i.border()
    if i.m==False:
        print("{} stopped at simulation step {} at location ({:.1f},{:.1f})".format(i.name,count,i.x,i.y))
        print("")
        lost.append(i)
        peeps.remove(i)
        continue        
#go into loop
while count<100:
    #this follows the path within the homework: increment, move, border check,
    # reward check, collision check, portal check.
    count+=1
    for i in peeps:
        if i not in lost:
            i.move()
            i.border()
            if i.m==False:
                print("{} stopped at simulation step {} at location ({:.1f},{:.1f})".format(i.name,count,i.x,i.y))
                print("")
                lost.append(i)
                peeps.remove(i)
                continue
                
            i.check()
            if i.m==False:
                print("{} stopped at simulation step {} at location ({:.1f},{:.1f})".format(i.name,count,i.x,i.y))
                print("")
                lost.append(i)
                peeps.remove(i)
    
    #another break condition
    if len(peeps)==0:
        break
    
    #the reward check segment of loop
    for i in peeps:
        if i not in lost:
            for j in universes:
                i.pick(j,count)
    
    #check to see if movement has been slown to a lose condition after getting 
    #an item
    for i in peeps:
        i.check()
        if i.m==False:
            print("{} stopped at simulation step {} at location ({:.1f},{:.1f})".format(i.name,count,i.x,i.y))
            print("")
            lost.append(i)
            peeps.remove(i)                
        else:
            continue
    
    #break condition
    if len(peeps)==0:
        break
    
    #collision segment of loop
    for i in range(len(peeps)):
        for j in range(i+1,len(peeps)):
            peeps[i].collide(peeps[j],universes,count)
    
    #portal segment of loop
    for i in peeps:
        if i not in lost:
            for j in universes:
                i.portal(j,count)       

#further output
print("")
print("-"*40)
print("Simulation stopped at step {}\n{} individuals still moving".format(count,len(peeps)))
print("Winners:")

#determine the max score and print who ever has the equivalent of the max score.
maxi = 0
for i in lost:
    if i.points > maxi:
        maxi = i.points
win = []
for i in lost:
    if i.points == maxi:
        win.append(i)

for i in win:
    print(str(i))
    print("")