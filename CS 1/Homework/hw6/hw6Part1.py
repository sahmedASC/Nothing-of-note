#This code was written by Saaif Ahmed '22
#Thee object of this program is to develop an autocorrect feature. Like the 
#ones on smartphones that totally work and don't cause any problems

def fix_words(dic,word,letters):
    #these are return values and lists for computation and check variables
    match = 'NO MATCH'
    found = 'FOUND'
    swap = 'SWAP'
    replace = 'REPLACE'
    drop = 'DROP'
    soldrop = []
    solswap = []
    solrep = []    
    tdrop = False
    tswap = False
    trep = False
    
    #simple check to see if the word already exists
    if word in dic:
        return (found,word)
    
    #drop test. delete one element at a time and re-check. re-instate the value
    #after checking
    s = list(word) #The words becomes a list for all computation
    
    length = len(s)
    for i in range(length):
        del s[i]
        test = "".join(s)
        if test in dic:
            tdrop = True
            soldrop.append(test)
        s= list(word)
    
    if tdrop:
        return (drop, min(soldrop))
    
    #swap check. First conditional to make sure no index error. Store the
    #original values first. swap them and check. reset the list after each time
    for j in range(len(s)):
        if j == (len(s)-1):
            break
        swap1 = s[j]
        swap2 = s[j+1]
        
        s[j] = swap2
        s[j+1] = swap1
        
        test = "".join(s)
        if test in dic:
            tswap = True
            solswap.append(test)
        s = list(word)
    
    if tswap:
        return (swap, min(solswap))
    
    #replace check. Run through each element of the list and replace with the
    #alphabet. check to see if it is in the dictionary. reset the value afterwards.
    for x in range(len(s)):
        primary = s[x]
        for y in letters:
            s[x] = y
            test = "".join(s)
            if test in dic:
                trep = True
                solrep.append(test)
            s[x] =primary
                
    if trep:
        return (replace, min(solrep))
                
    return (match,word)

dic = input("Dictionary file => ").strip()
print(dic)
file = input("Input file => ").strip()
print(file)

letters = [ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
'w', 'x', 'y', 'z' ]

words = set()
mistakes = []

#The dictionary becomes a set
for line in open(dic):
    word = line.strip().split('\n')
    words.add(word[0])

#The input words file becomes a list to maintain order
for i in open(file):
    test = i.strip().split('\n')
    mistakes.append(test[0])

#print loop
for word in mistakes:
    result = fix_words(words,word,letters)
    print("{:15} -> {:15} :{}".format(word,result[1],result[0]))

    
    