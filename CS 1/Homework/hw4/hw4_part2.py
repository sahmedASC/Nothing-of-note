#This code was written by Saaif Ahmed '22
#The objective of this program is to find a zip code that the user is looking 
#for or something idrk get me out of here

import hw04_util
import math as m
zip_codes = hw04_util.read_zip_all()

def zip_by_location(zip_codes,location):
    #determine location by checking to see if the state and city is valid
    zips=[]
    for i in zip_codes:
        if i[3]==location[0] and i[4] == location[1]:
            zips.append(i[0])
    return zips

def location_by_zip(zip_codes, code):
    #determine if the zip code is valid
    for i in zip_codes:
        if code == i[0]:
            info=(i[1],i[2],i[3],i[4],i[5])
            return info
        else:
            info=[]
    return info

command = input("Command ('loc', 'zip', 'dist', 'end') => ")
print(command)
command = command.lower()
while command != "end":    
    
    if command == 'zip':
        city= input("Enter a city name to lookup => ")
        print(city)
        city= city.lower()
        city= city.title()
    
        state = input("Enter the state name to lookup => ")
        print(state)
        state = state.upper()
        
        location=(city,state)
        zips=zip_by_location(zip_codes,location)
        #this will run if the list is empty
        if len(zips)==0:
            print("No ZIP code found for ", city, ", ",state, sep="" )
        else:
            #Recreate a string from the list of zip codes to print out
            allzips = ""
            for i in zips:
                allzips= allzips + i +", "
            allzips=allzips.rstrip(", ")
            print("The following ZIP code(s) found for", city+", "+state+ ": "+allzips)
    
    elif command == "loc":
        code = input("Enter a ZIP code to lookup => ")
        print(code)
        info = location_by_zip(zip_codes,code)
        #will run if the zip is invlaid aka an empty list
        if len(info)==0:
            print("Invalid or unknown ZIP code")
        else:
            location="ZIP code "+code+" is in "+info[2]+", "+info[3]+", "+info[4]+" county,"
            print(location)
        
            longitude= abs(float(info[0]))
            latitude = abs(float(info[1]))
        #convert values to deg, min, sec
            deglong = int(longitude)
            minlong = int((longitude-deglong)*60)
            seclong = (longitude-deglong-minlong/60)*3600
            deglat = int(latitude)
            minlat = int((latitude-deglat)*60)
            seclat = (latitude-deglat-minlat/60)*3600
        #determine the direction
            if info[0] < 0:
                long = "S"
            else:
                long ="N"
            if info[1]< 0:
                    lat= "W"
            else:
                lat="E"
            print("\tcoordinates: ({0:03d}\xb0{1}'{2:.2f}\"".format(deglong,minlong,seclong),long,sep="",end="") 
            print(",{0:03d}\xb0{1}'{2:.2f}\"".format(deglat,minlat,seclat),lat,")",sep="")
    elif command == "dist":
        zip1= input("Enter the first ZIP code => ")
        print(zip1)
        zip2 = input("Enter the second ZIP code => ")
        print(zip2)
        
        location1 = location_by_zip(zip_codes,zip1)
        location2 = location_by_zip(zip_codes,zip2)
        #Again an empty list means invalid parameters
        if len(location1)==0 or len(location2)==0:
            print("The distance between", zip1, "and", zip2, "cannot be determined")
        else:
            #calculate distance using formula
            lat1= (float(location1[0])*m.pi)/180
            lat2= (float(location2[0])*m.pi)/180
            long1= (float(location1[1])*m.pi)/180
            long2= (float(location2[1])*m.pi)/180
        
            deltalat= lat2 - lat1
            deltalong= long2 - long1
            a= (m.sin(deltalat/2))**2 + m.cos(lat1)* m.cos(lat2) * (m.sin(deltalong/2))**2
            d= 2*(3959.191) * m.asin(a**0.5)
            if d == 0:
                print("The distance between", zip1, "and", zip2, "is", "0.00 miles")
            else:
                print("The distance between", zip1, "and", zip2, "is", round(d,2), "miles")
    else:
        print("Invalid command, ignoring")
    print("")
    command = input("Command ('loc', 'zip', 'dist', 'end') => ")
    print(command)
    command = command.lower()

print("")
print("Done")