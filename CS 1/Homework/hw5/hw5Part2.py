#This code was written by Saaif Ahmed '22
#This code builds off of part 1 by using simulating a wandering trainer
#Kinda like that one time where I tried to find Azelf in Pokemon Platinum
#but it kept moving
import random

def move_trainer():
    #Same functions as before except it does not print anything and returns
    #a tuple with the random values
    dire= ['N','E','S','W']
    choice= random.choice(dire)
    value= random.random()
    return (choice,value)

def throw_pokeball(num_false, num_true):
    #same function as part 1
    x= []
    i=0
    while i < num_false:
        x.append(False)
        i+=1
    i=0
    while i < num_true:
        x.append(True)
        i+=1
    y= random.choice(x)
    return y

grid= int(input("Enter the integer grid size => "))
print(grid)
prob = float(input("Enter a probability (0.0 - 1.0) => "))
if prob == 1.0 or prob == 0.0:
    print(int(prob))
else:
    print(prob)

#set the random seed
seed=11*grid
random.seed(seed)

#Set pre determined values that change with the simulation
false=3
true= 1
pos = (grid//2,grid//2)
turn = 0
seen= 0
caught= 0
while True:
    trainer= move_trainer()
    
    #These check to make sure that the trainer is in the boundary at all times
    if pos[0]==0 or pos[0]==(grid-1):
        print("Trainer left the field at turn {0}, location ".format(turn),"(",pos[0],", ",pos[1],").",sep ="")
        break
    if pos[1]==0 or pos[1]==(grid-1):
        print("Trainer left the field at turn {0}, location ".format(turn),"(",pos[0],", ",pos[1],").",sep ="")
        break
    
    #This is the movement system. Based on direction it will increase or
    #decrease row and column values
    turn+=1
    rows=pos[0]
    columns=pos[1]
    if trainer[0] == 'N':
        rows-=1
    elif trainer[0] == 'S':
        rows+=1
    elif trainer[0] == 'W':
        columns-=1      
    elif trainer[0] == 'E':
        columns+=1
    pos= (rows,columns)
    
    #This condition is hit when the random value is smaller than the determined
    #probability value. This is the catching system. It also records the number
    #caught and seen
    if trainer[1] <= prob:
        catch=throw_pokeball(false,true)
        print("Saw a pokemon at turn {0}, location ".format(turn), "(",pos[0],", ",pos[1],")",sep ="")
        seen +=1
        if catch == True:
            print("Caught it!")
            true +=1
            caught += 1
        else:
            print("Missed ...")
    
#output
print("{0} pokemon were seen, {1} of which were captured.".format(seen,caught))