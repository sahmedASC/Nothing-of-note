#This program was written by Saaif Ahmed '22
#The objective of this program is to begin to structure a random trainer's
#movement and pokeballs. What is this some Nuzlocke jawn?
import random

def move_trainer():
    #Picks a random direction and determines a random value
    dire= ['N','E','S','W']
    choice= random.choice(dire)
    value= random.random()
    print("Directions:",dire)
    print("Selected",choice+",","value {0:.2f}".format(value))
    return None

def throw_pokeball(num_false, num_true):
    #creates a list of a number of false and true values
    x= []
    i=0
    while i < num_false:
        x.append(False)
        i+=1
    i=0
    while i < num_true:
        x.append(True)
        i+=1
    print("Booleans:", x)
    y= random.choice(x)
    print("Selected",y)
    return y

#This section gathers the inputs
grid= int(input("Enter the integer grid size => "))
print(grid)

false= int(input("Enter the integer number of Falses => "))
print(false)

true= int(input("Enter the integer number of Trues => "))
print(true)

#Set the random seed for control
seed=grid*11
random.seed(seed)
print("Setting seed to", seed)

#General output
move_trainer()
move_trainer()
move_trainer()
move_trainer()
move_trainer()

throw_pokeball(false,true)
throw_pokeball(false,true)
throw_pokeball(false,true)
throw_pokeball(false,true)
throw_pokeball(false,true)