#This code was written by Saaif Ahmed '22
#The objective of this program is run a number of simulations of a trainer
#achieving his goals and dreams of catching them all. Then gathering data on
#that.
import random

def move_trainer():
    #same as part 2
    dire= ['N','E','S','W']
    choice= random.choice(dire)
    value= random.random()
    return (choice,value)

def throw_pokeball(num_false, num_true):
    #same as part 2
    x= []
    i=0
    while i < num_false:
        x.append(False)
        i+=1
    i=0
    while i < num_true:
        x.append(True)
        i+=1
    i=0
    y= random.choice(x)
    return y

def run_one_simulation(grid, prob, count_grid):
    #essentially the main body program of part 2
    #I moved the boundary checks to the while loop condition
    #I pass in the "score board" array to alter the values in it
    false=3
    true= 1
    rows= grid//2
    columns = rows
    turn = 0

    while rows != 0 and rows != (grid-1) and columns != 0 and columns != (grid-1):
        turn+=1
        trainer= move_trainer()
        
        #The movement block of code
        if trainer[0] == 'N':
            rows-=1
        elif trainer[0] == 'S':
            rows+=1
        elif trainer[0] == 'W':
            columns-=1      
        elif trainer[0] == 'E':
            columns+=1 
        
        #If a pokemon is encountered and caught we increase that index in 
        #count_grid by 1 and the opposite if missed
        if trainer[1] <= prob:
            catch=throw_pokeball(false,true)
            if catch == True:
                count_grid[rows][columns] += 1
                true +=1
            else:
                count_grid[rows][columns] -= 1
                
    return turn

grid= int(input("Enter the integer grid size => "))
print(grid)
prob = float(input("Enter a probability (0.0 - 1.0) => "))
if prob == 1.0 or prob == 0.0:
    print(int(prob))
else:
    print(prob)

iterate= int(input("Enter the number of simulations to run => "))
print(iterate)
print("")

seed=11*grid
random.seed(seed)

#develop count_grid
count_grid = []
for i in range(grid):
    count_grid.append( [0]*grid )

#Create a list of turn values for computation down the line
turns = []
for start in range(iterate):
    t = run_one_simulation(grid,prob,count_grid)
    turns.append(t)

#Print out the list because it is required
for x in range(grid):
    for y in range(grid):
        print("{:5d}".format(count_grid[x][y]), end="")
    print("")

#simple calculation of the average, max, and min turns. Also what simulation had
#the min and max turns respectively
average = sum(turns)/len(turns)
maxturn= max(turns)
indexmax= turns.index(maxturn) +1
minturn = min(turns)
indexmin= turns.index(minturn) +1

#Create a really long list with all the values to do the rest of the
#calculations like the best and worst missed versus caught values
total_data= []
for row in range(len(count_grid)):
    for column in range(len(count_grid)):
        total_data.append(count_grid[row][column])

best = max(total_data)
worst = min(total_data)

print("Average number of turns in a simulation was {0:.2f}".format(average))
print("Maximum number of turns was {0} in simulation {1}".format(maxturn, indexmax))
print("Minimum number of turns was {0} in simulation {1}".format(minturn, indexmin))
print("Best net missed pokemon versus caught pokemon is", best)
print("Worst net missed pokemon versus caught pokemon is", worst)