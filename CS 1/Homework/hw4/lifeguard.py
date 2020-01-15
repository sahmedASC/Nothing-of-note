import math as m
def get_response_time(beach):
    theta2= (beach[5]*m.pi)/180
    #convert units like yards and mph to feet based units and second based units
    d1=beach[0]*3
    h=beach[2]*3
    v_sand= (beach[3]*5280)/3600
    
    #Create distance X based off of theta2
    x= d1*m.tan(theta2)
    
    #calculate L1 based on formula
    l1= ((x**2)+(d1**2))**0.5
    
    #calculate L2 based on formula
    l2= (((h-x)**2)+(beach[1]**2))**0.5
    
    #calculate T based on formula
    t= (l1+(beach[4]*l2))/v_sand    
    return t