#This code was written by Saaif Ahmed '22
#The objective of the program is to simulate a Pikachu running around in the
#wild encountering pokemon and defeating them all until his reign of terror is 
#stopped.

def move_pokemon(pos,direction,steps):
    '''This function uses an image coordinate system to move the pokemon.
    I seperate the tuple into individual elements and increase/decrease them
    based on the direction inputted. We lower it to account for up/lower case'''
    direction=direction.lower()
    rows=pos[0]
    columns=pos[1]
    if direction == "n":
        rows-=steps
        if rows < 0:
            rows=0
    elif direction == "s":
        rows+=steps
        if rows > 150:
            rows = 150
    elif direction == "w":
        columns-=steps
        if columns < 0:
            columns=0        
    elif direction == "e":
        columns+=steps
        if columns > 150:
            columns = 150
    pos=(rows,columns)
    return pos

#This section gathers all the inputs for computation down the line
turn = input("How many turns? => ")
print(turn)
turn = float(turn)

name = input("What is the name of your pikachu? => ")
print(name)

poketurn = input("How often do we see a Pokemon (turns)? => ")
print(poketurn)
poketurn=float(poketurn)

#default starting position and step count
pos=(75, 75)
steps=5

#list that will hold the record of win to loss
record=[]

#variables for the loop
i=0
pokecount=0

#begin the loop and the rest of the program
print("")
print("Starting simulation, turn 1 ",name," at (75, 75)",sep="")
while i<turn:
    #gets a direction input and then adjusts the position
    print("What direction does ",name," walk? => ",sep="",end="")
    direction=input("")
    print(direction)
    pos= move_pokemon(pos,direction,steps)
    pokecount+=1
    i+=1
    
    #this is the battle system. Check to see what type of pokemon is encountered
    #and then adjust the position based on the type. Append the result to record
    if pokecount == poketurn:
        print("Turn ", i,", ", name, " at ", pos, sep="")
        encounter= input("What type of pokemon do you meet (W)ater, (G)round? => ")
        print(encounter)
        encounter=encounter.lower()
        if encounter == 'w':
            pos = move_pokemon(pos,direction,1)
            print(name, "wins and moves to", pos)
            record.append('Win')
        elif encounter == "g":
            pos =  move_pokemon(pos,direction,-10)
            print(name, "runs away to", pos)
            record.append('Lose')
        else:
            record.append("No Pokemon")
        pokecount=0
#Final output with the final record and position
print(name," ends up at ", pos, ", Record: ",record, sep="")
        