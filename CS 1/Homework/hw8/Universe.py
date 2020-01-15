class Universe(object):
    def __init__(self,rewards, name,portal):
        #setup
        self.rewards =rewards
        self.name = name
        self.portal = portal
    
    def __str__(self):
        #generate a string to print out when describing the universe
        string = "Universe: " +self.name + " ("+str(len(self.rewards))+ " rewards and "+ str(len(self.portal)) + " portals)\n"
        string = string + "Rewards:\n"
        if len(self.rewards) == 0:
            string = string + "None\n"
        else:
            for i in self.rewards:
                string = string+"at ("+str(i.x)+","+str(i.y)+ ")" + " for "+ str(i.points)+" points: "+i.name +"\n"
        string = string + "Portals:\n"
        if len(self.portal) == 0:
            string = string + "None\n"
        else:
            for i in self.portal:
                string = string + self.name + ":("+str(i.from_x)+","+str(i.from_y)+") -> "+ i.to_name + ":("+str(i.to_x)+","+str(i.to_y)+")"+"\n"
        string = string.rstrip("\n")
        return string
class Reward(object):
    #create a reward object to store values instead of an array
    def __init__(self,x,y,points,name,uni):
        self.x =x
        self.y = y
        self.points = points
        self.name = name
        self.uni= uni
class Portal(object):
    #create a portal object to store values instead of an array.
    def __init__(self,from_x,from_y,to_name,to_x,to_y):
        self.from_x= from_x
        self.from_y= from_y
        self.to_name= to_name
        self.to_x = to_x
        self.to_y= to_y
        