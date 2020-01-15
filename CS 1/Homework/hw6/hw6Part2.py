#This code was written by Saaif Ahmed '22
# The objective of this porgram is to determine how similar monsters in the
# Wizarding World of Harry Potter are from movie to movie. We compare sets of
#them. Too bad these movies are kinda trash and Harry Potter is a bad character
#can we do Naruto?

import textwrap

#create a dictionary by reading the file setting movie titles as keys and 
#the monsters as values in a set
data = dict()
for line in open('titles.txt'):
    line = line.strip().split('\n')
    for i in line:
        movie = i.strip().split('|')
        count = 1
        title = movie[0]
        data[title] = set()
        while count < len(movie):
            data[title].add(movie[count])
            count += 1

check = False
#initial statement of variable
while True:
    interest = input("Enter a title (stop to end) => ").strip()
    print(interest)
    
    #end condition
    if interest.lower() == 'stop':
        break
    print("")
    #this process determines the title that the user wants
    for i in data:
        keys = i.split(' ')
        try:
            #if the interest value is more than a single string we split it into
            #list and rejoin the string. Then we take the title, split it and 
            #rejoin as string. Lower both and check if the string is in title.
            checker = interest.split(' ')
            checker = "".join(checker)
            keys = "".join(keys)
            keys = keys.lower()
            if checker.lower() in keys:
                check = True
                name = i
                break
        except:
            #otherwise its a simple for loop string check process
            for j in keys:
                if interest.lower() == j.strip().lower():
                    check = True
                    name = i
                    break
            if check:
                break
    
    if check:
        #print the beasts in the title by accessing the key in the dictionary
        #and formating and printing it
        print("Found the following title:", name)
        beastslist = list(data[name])
        beastslist.sort()
        beast_title = ""
        for x in beastslist:
            beast_title = beast_title + x + ', '
        beast_title =beast_title.rstrip(', ')
        
        beast_title = 'Beasts in this title: '+beast_title
        lines = textwrap.wrap(beast_title)
        for line in lines:
            print(line)
        
        print("")
        
        #Find which titles contain beasts in common. test is a set test of
        #beasts. If the intersection returns a set longer than 0 it will
        #have to have something in common so add it to a list sort it and
        #print out the formatted string
        beast_list = data[name]
        common = []
        for i in data:
            test = data[i]
            if i != name:
                if len(test & beast_list)>0:
                    common.append(i)
        common.sort()
        
        beast_title = ""
        for x in common:
            beast_title = beast_title + x + ', '
        beast_title = beast_title.rstrip(', ')
        
        beast_title = 'Other titles containing beasts in common: ' + beast_title
        lines = textwrap.wrap(beast_title)
        for line in lines:
            print(line)
        
        print("")  
        
        # Find unique beasts by using set subtraction. Keep on substrating values
        # from sets and format and print what remains
        unique = data[name]
        for i in data:
            if i !=name:
                unique = unique - data[i]
        unique = list(unique)
        unique.sort()
        
        beast_title = ""
        for x in unique:
            beast_title = beast_title + x + ', '
        beast_title = beast_title.rstrip(', ')
        
        beast_title = 'Beasts appearing only in this title: ' + beast_title
        lines = textwrap.wrap(beast_title)
        for line in lines:
            print(line)        
        
    else:
        print('This title is not found!')
    print("")
    check = False