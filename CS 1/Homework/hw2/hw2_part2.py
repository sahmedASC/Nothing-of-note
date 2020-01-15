#This code was written by Saaif Ahmed '22
#The objective of this program is to determine how fast you go on a track
from track import get_number_of_tracks
from track import get_track


def calculate_curve(track,speed):
    '''Both functions calculate the length by couting the letters, and dividing
    by 4
    Speed is converted to miles per . Time is simply distance/speed'''
    track=track.lower()
    length=track.count("b")+track.count("e")+track.count("n")+track.count("d")
    length/=4
    speed/=3600
    time=length/speed
    return (length,time)

def calculate_straight(track,speed):
    '''Both functions calculate the length by couting the letters, and dividing 
    by 4
    Speed is converted to miles per . Time is simply distance/speed'''    
    track=track.lower()
    length=track.count("s") +track.count("t")+track.count("r")+track.count("a")
    length=length+track.count("i")+track.count("g")+track.count("h")
    length/=4
    speed/=3600
    time=length/speed
    return (length,time)


num_tracks=get_number_of_tracks()

#Gather User data for calculations
print("Select a track between 1 and ",num_tracks," => ",sep="",end="")
track=int(input())
print(track)

curvespeed=input("Speed on curved segments (MPH) => ")
print(curvespeed)
curvespeed=float(curvespeed)

straightspeed=input("Speed on straight segments (MPH) => ")
print(straightspeed)
straightspeed=float(straightspeed)

#Define the track being used
track=get_track(track)

#Store the outputs of the defined functions into variable for later calculations
straight=calculate_straight(track,straightspeed)
curve=calculate_curve(track, curvespeed)

#Use the function outputs to compute total time and total length
totaltime=straight[1]+curve[1]
length=straight[0]+curve[0]

#Determine the average speed based on lengths of track parts.
#if there is no straight segment the average speed is just the curve speed and 
#vice versa
if straight[0]==0:
    avgspeed=curvespeed
elif curve[0]==0:
    avgspeed=straightspeed
else:
    avgspeed=(length/totaltime)*3600

#Conditionals for the final response section
if avgspeed<60:
    response="Kind of slow."
elif 60<=avgspeed<120:
    response="Getting there."
elif avgspeed>=120:
    response="Wow, quite the car!"

#output formatted using the .format() method
print("")
print("Track:\n",track,sep="")
print("is {0:.2f} miles long. You raced it in {1:.2f} seconds at an average speed of {2:.2f} MPH".format(length,totaltime,avgspeed))
print(response)