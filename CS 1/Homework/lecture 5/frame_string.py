#This was made by Saaif Ahmed '22
#The purpose of this program is to draw a fram around a string

def frame_string(string):
    x=len(string)
    print("*"*(x+6))
    print("**",string,"**")
    print("*"*(x+6))
    
frame_string("Spanish Inquisition")
print("")
frame_string("Ni")