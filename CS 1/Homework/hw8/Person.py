import math
class Person(object):
    def __init__(self,name,radius,home,x,y,dx,dy,current,rewards):
        #initial setup
        self.name = name
        self.radius = radius
        self.home = home
        self.x = float(x)
        self.y = float(y)
        self.dx = float(dx)
        self.dy = float(dy)
        self.current = current
        self.rewards = rewards
        self.points = 0
        self.m = True #a check for mobility called m. will change based on conditions
    def word(self):
        #This is a general output of the data of the individual formatted according
        #to guidelines
        string = "{} of {} in universe {}\n    at ({:.1f},{:.1f}) speed ({:.1f},{:.1f}) with {} rewards and {} points".format(self.name,self.home,self.current,self.x,self.y,self.dx,self.dy,len(self.rewards),self.points)
        return string
    def __str__(self):
        #this is a specific output of the data of the individual for specific areas of 
        #output
        string = "{} of {} in universe {}\n    at ({:.1f},{:.1f}) speed ({:.1f},{:.1f}) with {} rewards and {} points".format(self.name,self.home,self.current,self.x,self.y,self.dx,self.dy,len(self.rewards),self.points)
        string = string +"\nRewards:\n"
        for i in self.rewards:
            string= string + '    ' + i.name + '\n'
        string= string.rstrip('\n')
        return string    
    def move(self):
        #add the dx and dy to move
        self.x = self.x + self.dx
        self.y = self.y + self.dy
    def check(self):
        #if the speed is lower than ten the self.m value is false
        if abs(self.dx)<10 or abs(self.dy)<10:
            self.m=False        
    def border(self):
        #if it hits the border the self.m values is false
        if self.x<=0 or self.x>=1000 or self.y<=0 or self.y>=1000:
            self.m=False
        else:
            pass
    def pick(self,other,count):
        #the reward check. if the person and reward is in the same universe
        #you calculate the distance and remove the reward so no one else can get it
        #you also alter the value of dc and dy as according to guidelines
        if self.current == other.name:
            for i in other.rewards:
                if math.sqrt((self.x-i.x)**2+(self.y-i.y)**2) <= self.radius:
                    if i.name not in self.rewards:
                        self.rewards.append(i)
                        self.points = self.points + i.points
                        self.dx = self.dx - (len(self.rewards)%2)*(len(self.rewards)/6)*self.dx
                        self.dy = self.dy - ((len(self.rewards)+1)%2)*(len(self.rewards)/6)*self.dy
                        print("{} picked up \"{}\" at simulation step {}".format(self.name,i.name,count))
                        print(self.word())
                        print("")
                        other.rewards.remove(i)
    def collide(self,other,universe,count):
        #the collision check. if both people are in the same universe you check
        #the distance between them. If that is valid you check to see if they have
        #at least one item. if they do, you return the rewards to it's universe and 
        #then remove it from their list of rewards
        if self.current == other.current:
            if math.sqrt((self.x-other.x)**2+(self.y-other.y)**2) <= (self.radius+other.radius):
                if len(self.rewards)>0:
                    print("{} and {} crashed at simulation step {} in universe {}".format(self.name,other.name,count,self.current))
                    
                    for i in universe:
                        if i.name == self.rewards[0].uni:
                            i.rewards.append(self.rewards[0])
                            print("{} dropped \"{}\", reward returned to {} at ({},{})".format(self.name, self.rewards[0].name,i.name,self.rewards[0].x,self.rewards[0].y))
                    
                    self.points = self.points - self.rewards[0].points       
                    self.rewards.remove(self.rewards[0])
                    self.dx = -1*(self.dx + (len(self.rewards)%2)*(len(self.rewards)/6)*self.dx)
                    self.dy = -1*(self.dy + ((len(self.rewards)+1)%2)*(len(self.rewards)/6)*self.dy)                     
                if len(other.rewards)>0:
                    print("{} and {} crashed at simulation step {} in universe {}".format(other.name,self.name,count,other.current))
                    
                    for i in universe:
                        if i.name == other.rewards[0].uni:
                            i.rewards.append(other.rewards[0])
                            print("{} dropped \"{}\", reward returned to {} at ({},{})".format(other.name, other.rewards[0].name,i.name,other.rewards[0].x,other.rewards[0].y))
                    
                    other.points = other.points - other.rewards[0].points       
                    other.rewards.remove(other.rewards[0]) 
                    other.dx = -1*(other.dx + (len(other.rewards)%2)*(len(other.rewards)/6)*other.dx)
                    other.dy = -1*(other.dy + ((len(other.rewards)+1)%2)*(len(other.rewards)/6)*other.dy)
                
                print(self.word())
                print(other.word())
                print("")
                
    def portal(self,other,count):
        #portal check. same as rewards check. if the person gets close you change
        #its respective values.
        if self.current == other.name:
            for i in other.portal:
                if math.sqrt((self.x-i.from_x)**2+(self.y-i.from_y)**2) <= self.radius:
                    print("{} passed through a portal at simulation step {}".format(self.name,count))
                    self.x= i.to_x
                    self.y= i.to_y
                    self.current = i.to_name
                    print(self.word())