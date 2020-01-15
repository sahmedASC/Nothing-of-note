from tkinter import *
from ball import *
import random as r

def create():
    colorlist = ["blue","red","green","yellow","magenta", "orange"]
    rx = r.randint(10,390)
    ry = r.randint(10,390)
    rr = r.randint(10,15) 
    rc = colorlist[r.randint(0,len(colorlist)-1)]
    rdx = r.randint(-8,8)
    rdy = r.randint(-8,8)
    return [rx,ry,rr,rdx,rdy,rc]

class BallDraw(object):
    def __init__ (self, parent):
      
        ##=====DATA RELEVANT TO BALL===============
        x= create()
        self.b1= Ball(x[0],x[1],x[2],x[3],x[4],x[5])
        self.rx1 = x[0]
        self.ry1 = x[1]
        
        x = create()
        self.b2= Ball(x[0],x[1],x[2],x[3],x[4],x[5])
        self.rx2 = x[0]
        self.ry2 = x[1]
        
        x=create()
        self.b3= Ball(x[0],x[1],x[2],x[3],x[4],x[5])
        self.rx3 = x[0]
        self.ry3 = x[1]
        
        x=create()
        self.b4= Ball(x[0],x[1],x[2],x[3],x[4],x[5])
        self.rx4 = x[0]
        self.ry4 = x[1]
        
        x=create()
        self.b5= Ball(x[0],x[1],x[2],x[3],x[4],x[5])
        self.rx5 = x[0]
        self.ry5 = x[1]
        
        x=create()
        self.b6= Ball(x[0],x[1],x[2],x[3],x[4],x[5])
        self.rx6 = x[0]
        self.ry6 = x[1]
        
        x=create()
        self.b7= Ball(x[0],x[1],x[2],x[3],x[4],x[5])
        self.rx7 = x[0]
        self.ry7 = x[1]
        
        x=create()
        self.b8= Ball(x[0],x[1],x[2],x[3],x[4],x[5])
        self.rx8 = x[0]
        self.ry8 = x[1]
        
        x=create()
        self.b9= Ball(x[0],x[1],x[2],x[3],x[4],x[5])
        self.rx9 = x[0]
        self.ry9 = x[1]
        
        x=create()
        self.b0= Ball(x[0],x[1],x[2],x[3],x[4],x[5])
        self.rx0 = x[0]
        self.ry0 = x[1]        
        #========DATA NEEDED FOR ANIMATION=========
        #  Here is the time in milliseconds between consecutive instances
        #  of drawing the ball.  If this time is too small the ball will
        #  zip across the canvas in a blur.
        self.wait_time = 100

        #this will allow us to stop moving the ball when the program quits
        self.isstopped = False 

        self.maxx = 400 # canvas width, in pixels
        self.maxy = 400 # canvas height, in pixels

        #=============CREATE THE NEEDED GUI ELEMENTS===========
        ##  Create a frame, attach a canvas and 4 buttons to this frame
        ##  Buttons are used to cleanly exit the program;
        ##  to speed up or slow down the animation, and to restart 
        ##  the animation.
        ##  Canvas, like an image, is an object that we can draw objects on.
        ##  This canvas is called chart_1.  
        ##  Parent = root window, contains a frame
        ##  The frame contains the canvas and the 4 buttons.
        ##  We only care about the canvas in our animation
        self.parent = parent
        self.frame = Frame(parent)
        self.frame.pack()
        self.top_frame = Frame(self.frame)
        self.top_frame.pack(side=TOP)
        self.canvas = Canvas(self.top_frame, background="white", \
                             width=self.maxx, height=self.maxy )
        self.canvas.pack()
        self.bottom_frame = Frame(self.frame)
        self.bottom_frame.pack(side=BOTTOM)
        self.restart = Button(self.bottom_frame, text="Restart", command=self.restart)
        self.restart.pack(side=LEFT)
        self.slow = Button(self.bottom_frame, text="Slower", command=self.slower)
        self.slow.pack(side=LEFT)
        self.fast = Button(self.bottom_frame, text="Faster", command=self.faster)
        self.fast.pack(side=LEFT)
        self.quit = Button(self.bottom_frame, text="Quit", command=self.quit)
        self.quit.pack(side=RIGHT)

    def faster(self):
        if self.wait_time > 2:
            self.wait_time //= 2

    def slower(self):
        self.wait_time *= 2
            
    def restart(self):
        self.isstopped = False
        self.b1.x,self.b1.y = self.rx1,self.ry1
        self.b2.x,self.b2.y = self.rx2,self.ry2
        self.b3.x,self.b3.y = self.rx3,self.ry3
        self.b4.x,self.b4.y = self.rx4,self.ry4
        self.b5.x,self.b5.y = self.rx5,self.ry5
        self.b6.x,self.b6.y = self.rx6,self.ry6
        self.b7.x,self.b7.y = self.rx7,self.ry7
        self.b8.x,self.b8.y = self.rx8,self.ry8
        self.b9.x,self.b9.y = self.rx9,self.ry9
        self.b0.x,self.b0.y = self.rx0,self.ry0
        
        self.draw_ball()
        
    def quit(self):
        self.isstopped = True
        self.parent.destroy()
        
    def draw_ball(self):
        while True:
            #  Remove all the previously-drawn balls
            self.canvas.delete("all")
            
            # Draw an oval on the canvas within the bounding box
            bounding_box = self.b1.bounding_box() 
            self.canvas.create_oval(bounding_box, fill=self.b1.color)
            self.canvas.update()      # Actually refresh the drawing on the canvas.
            
            bounding_box = self.b2.bounding_box() 
            self.canvas.create_oval(bounding_box, fill=self.b2.color)
            self.canvas.update()
            
            bounding_box = self.b3.bounding_box() 
            self.canvas.create_oval(bounding_box, fill=self.b3.color)
            self.canvas.update()
            
            bounding_box = self.b4.bounding_box() 
            self.canvas.create_oval(bounding_box, fill=self.b4.color)
            self.canvas.update()
            
            bounding_box = self.b5.bounding_box() 
            self.canvas.create_oval(bounding_box, fill=self.b5.color)
            self.canvas.update()
            
            bounding_box = self.b6.bounding_box() 
            self.canvas.create_oval(bounding_box, fill=self.b6.color)
            self.canvas.update()
            
            bounding_box = self.b7.bounding_box() 
            self.canvas.create_oval(bounding_box, fill=self.b7.color)
            self.canvas.update()
            
            bounding_box = self.b8.bounding_box() 
            self.canvas.create_oval(bounding_box, fill=self.b8.color)
            self.canvas.update()
            
            bounding_box = self.b9.bounding_box() 
            self.canvas.create_oval(bounding_box, fill=self.b9.color)
            self.canvas.update()
            
            bounding_box = self.b0.bounding_box() 
            self.canvas.create_oval(bounding_box, fill=self.b0.color)
            self.canvas.update()            
        
            # Pause execution.  This allows the eye to catch up
            self.canvas.after(self.wait_time)
        
            self.b1.move()
            self.b2.move()
            self.b3.move()
            self.b4.move()
            self.b5.move()
            self.b6.move()
            self.b7.move()
            self.b8.move()            
            self.b9.move()
            self.b0.move()            
            
            self.b1.check_reverse(self.maxx,self.maxy)
            self.b2.check_reverse(self.maxx,self.maxy)
            self.b3.check_reverse(self.maxx,self.maxy)
            self.b4.check_reverse(self.maxx,self.maxy)
            self.b5.check_reverse(self.maxx,self.maxy)
            self.b6.check_reverse(self.maxx,self.maxy)
            self.b7.check_reverse(self.maxx,self.maxy)
            self.b8.check_reverse(self.maxx,self.maxy)
            self.b9.check_reverse(self.maxx,self.maxy)
            self.b0.check_reverse(self.maxx,self.maxy)
            
            if self.isstopped == True:
                break
            
        print("done")


if __name__ == "__main__":
    ##  We will create a root object, which will contain all 
    ##  our user interface elements
    ##
    root = Tk()
    root.title("Tkinter: Lab 11")

    ## Create a class to handle all our animation
    bd = BallDraw(root)

    ## Run the animation by continuously drawing the ball and then moving it
    bd.draw_ball()

    ## This is an infinite loop that allows the window to listen to
    ## "events", which are user inputs.  The only user event here is
    ## closing the window, which ends the program. 
    root.mainloop()