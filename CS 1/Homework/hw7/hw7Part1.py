#This code was written by Saaif Ahmed '22
#The objective of the program is to build upon the autocorrect program from hw6
#by adding new methods for corrections and organizing them by frequency.

def found_word(word, dic):
    #check to see if the word is in the dictionary
    if word in dic:
        return True
    else:
        return False
def drop_word(word, dic, solution):
    s = list(word) #The words becomes a list for all computation
    
    #drop a letter, check, and restate the variable if nothing checks
    length = len(s)
    for i in range(length):
        del s[i]
        test = "".join(s)
        if test in dic:
            solution.add(test)
        s= list(word)
    
    return solution

def insert(word, dic, solution):
    letters = [ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
    'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z' ]
    
    #insert letters at every index, and restate the variable at loop's end
    s = list(word)
    length= len(s)+1
    for i in range(length):
        for j in letters:
            s.insert(i,j)
            test = "".join(s)
            if test in dic:
                solution.add(test)
            s= list(word)
    return solution

def swap(word, dic, solution):
    #same functionality as hw6. Store original values, swap, and re-state var
    
    s = list(word)
    for j in range(len(s)):
        if j == (len(s)-1):
            break
        swap1 = s[j]
        swap2 = s[j+1]
        
        s[j] = swap2
        s[j+1] = swap1
        
        test = "".join(s)
        if test in dic:
            solution.add(test)
        s = list(word)
    return solution

def replace(word, dic, solution, keyboard):
    #same functionality as hw6 but instead of running through a list of 
    #alphabet you run through a list given by the keyboard dictionary
    s= list(word)
    for x in range(len(s)):
        primary = s[x]
        letters = keyboard[primary]
        for y in letters:
            s[x] = y
            test = "".join(s)
            if test in dic:
                trep = True
                solution.add(test)
            s[x] =primary
    return solution

def top3(dic, solution):
    #Store the highest frequencies with it's respective word and retunr the tuple
    freq= []
    for i in solution:
        freq.append((dic[i],i))
    freq.sort(reverse = True)
    return freq
    
#gather input for computation
dic = input("Dictionary file => ").strip()
print(dic)
file = input("Input file => ").strip()
print(file)
keyboard_file = input("Keyboard file => ").strip()
print(keyboard_file)

#set up initial storage containers
words = dict()
keyboard = dict()
mistakes = []

#varibale that will hold the solutions for the test cases
solution = set()

#create a dicitonary where words are keys and frequencies are values
for line in open(dic):
    word = line.strip().split(',')
    words[word[0]] = word[1]

#The input words file becomes a list to maintain order
for i in open(file):
    test = i.strip().split('\n')
    mistakes.append(test[0])

#The keyboard becomes a dict where the first letter of each line is a key
#and the resulting "replacing" letters are the values
for i in open(keyboard_file):
    letters = i.strip().split(' ')
    keyboard[letters[0]] = list()
    count = 1
    while count< len(letters):
        keyboard[letters[0]].append(letters[count])
        count +=1

#main code running for every word in input file
for i in mistakes:
    #if the word is found print and continue
    result= found_word(i, words)
    if result:
        print("{:15} -> {:15} :{}".format(i,i,'FOUND'))
        continue
    else:
        #create a set with all the solutions
        solution = drop_word(i, words, solution)
        solution = insert(i, words, solution)
        solution = swap(i, words, solution)
        solution = replace(i, words, solution, keyboard)
    
    #if no match was found print and continue
    if len(solution) ==0:
        print("{:15} -> {:15} :{}".format(i,i,'NO MATCH'))
        solution = set()
        continue
    else:
        #print the resulting matches
        solution = list(solution)
        
        count = 1
        matches=top3(words,solution)
        top = 0
        for x in matches:
            print("{:15} -> {:15} :{}".format(i,x[1],'MATCH '+str(count)))
            if count == 3:
                break
            count +=1
            
    solution = set()
        