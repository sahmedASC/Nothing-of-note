#This code was written by Saaif Ahmed
#The objective of this code is to play a game of darts.
import math as m
def is_board_valid(config):
    ''' this nest will only return true if the board is valid.
    otherwise it will return false. Conditions are based on the pdf'''
    check = False
    if min(config) > 0:
        if config[2] > config[1]:
            if (config[4] - config[3]) > config[2]:
                if (config[6] - config[5]) > config[4]:
                    if config[6] < config[0]:
                        check = True
                        return check
                    else:
                        return check
                else:
                    return check
            else:
                return check
        else:
            return check
    else:
        return check

def get_score(config, pos):
    ''' Determine where the dart landed and the corresponding code '''
    
    '''determine if the dart lands on a wire based on the angle'''
    segment_wire= (pos[1]-81)%18
    
    '''Shift the entire board 279 degrees to get it to line up with the 
    x-axis such that the board is 1-20 counter clockwise. Divide it by 18 to 
    determine the segment it is in. 20-(that value) gives a distance from 20
     which when we take a % of it returns the specific score value of 
     the segment'''
    score = (20-int((pos[1]+279)/18))%20
    
    ''' There is one case where this method returns 0 instead of the proper 
    score and for that we just analyze the angle between a range of values'''
    if 81<pos[1] and pos[1]<99:
        score = 20  
    '''Check to see if it landed in the direct center'''
    if pos[0] == 0:
        return 50
    
    #Check to see if it landed outside the board
    elif pos[0]> config[6]:
        return 0
    elif segment_wire == 0:
        return 0
    
    #This section checks if the dart landed on the double/triple wires
    elif pos[0] == config[4] or pos[0] == (config[4]-config[3]):
        return 0
    elif pos[0] == config[6] or pos[0] == (config[6]-config[5]):
        return 0
    
    #This sections checks to see if it landed in the bullseye inner or outer.
    elif pos[0] < (config[1]/2):
        return 50
    elif pos[0] > (config[1]/2) and pos[0] < (config[2]/2):
        return 25
    
    #determine if the dart landed on the bullseye wires
    elif pos[0] == (config[1]/2) or pos[0] == (config[2]/2):
        return 0
    
    #triple or double the score if the radius is the appropriate distance
    elif pos[0]<config[4] and pos[0]>(config[4]-config[3]):
        score = score * 3
        return round(score)
    elif pos[0]<config[6] and pos[0]>(config[6]-config[5]):
        score = score * 2
        return round(score)
    return round(score)
   
#This section gathers inputs for the computation later on
print("Please enter dart board parameters below.")
board_diam = input("Board diameter => ")
print(board_diam)
board_diam = float(board_diam)

in_diam = input("Inner bull's eye diameter => ")
print(in_diam)
in_diam = float(in_diam)

out_diam = input("Outer bull's eye diameter => ")
print(out_diam)
out_diam = float(out_diam)

trip_width = input("Triple ring width => ")
print(trip_width)
trip_width = float(trip_width)

trip_dist = input("Distance from the center to the outside edge of the triple ring => ")
print(trip_dist)
trip_dist = float(trip_dist)

doub_width = input("Double ring width => ")
print(doub_width)
doub_width = float(doub_width)

doub_dist = input("Distance from the center to the outside edge of the double ring => ")
print(doub_dist)
doub_dist = float(doub_dist)

rad = input("Enter the radial coordinate (r) of the point where the dart landed => ")
print(rad)
rad = float(rad)

phi = input("Enter the angular coordinate (phi) of the point where the dart landed => ")
print(phi)
phi = float(phi)

#Create the position tuple based on the radius and angle
pos=(rad,phi)

#This is the seven tuple config of the board that we pass through the functions
config=(board_diam,in_diam,out_diam,trip_width,trip_dist,doub_width,doub_dist)

#Final output
valid=is_board_valid(config)
score= get_score(config,pos)

if valid==False:
    print("Invalid dartboard parameter(s) specified.")
if valid:
    print("This throw scored ",score,".",sep="")