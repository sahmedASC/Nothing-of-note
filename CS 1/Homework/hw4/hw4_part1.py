#This code was written by Saaif Ahmed '22 
#This program is a module that determines if someone is physically capable of 
#saving a human life on a beach, or mentally incappable of running in the right
#direction to save that person according to Red Cross standards.


from lifeguard import get_response_time

def get_optimal(beach, interval):
    #check every angle to see which is best
    angle_increment = (interval[1]-interval[0])/(interval[2]-1)
    actual_time = get_response_time(beach)
    case= [beach[0],beach[1],beach[2],beach[3],beach[4],interval[0]]
    
    mintime= get_response_time(case)
    optimal = case[5]
    #simple check system that will reassign the variable if the time is less
    i=interval[0]
    while i<= interval[1]:
        test = [beach[0],beach[1],beach[2],beach[3],beach[4],i]
        test_time= get_response_time(test)
        if test_time<mintime:
            mintime=test_time
            optimal = i
        i= float(i+angle_increment)
    diff=float(actual_time-mintime)
    return (mintime,optimal,diff)

def get_stats(beaches, interval):
    #use the angles to check to see how many pass or fail
    worthless=0
    coulda_been_better=0
    acceptable=0
    for i in beaches:
        time = get_response_time(i)
        if time > 120:
            #check to see if they could have made it with the best angle
            best_time = get_optimal(i,interval)
            if best_time[0]>120:
                 
                worthless+=1
            elif best_time[0] < 120:
                
                coulda_been_better +=1
        elif time< 120:
            acceptable +=1
    
    return (acceptable,coulda_been_better,worthless)
'''
if __name__ == "__main__":
    case = (8, 10, 50, 5, 2, 19.0987)
    theta1_values = (0.0, 90.0, 10)
    print("Optimal: {}".format(get_optimal(case, theta1_values)))
    results = [(8, 60, 40, 6, 1.2, 30.47),
     (8, 10, 50, 5, 2, 19.0987),
     (18, 40, 20, 3, 1.5, 48.123),
     (9, 10, 35, 5.5, 1.2, 45),
     (17, 90, 150, 7, 1.1, 87.5),
     (8, 12, 52, 6.5, 2.5, 29.0),
     (8.9, 100, 100, 2.4, 3, 0.0),
     (80, 52.5, 20, 4.5, 1.14, 78.55)
     ]
    statistics = get_stats(results, (0.0, 90.0, 1000))
    print("Rescued: {}; drowned and could save: {}; drowned and could not save: {}". \
    format(statistics[0], statistics[1], statistics[2]))'''
    