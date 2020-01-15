'''
Template program for Lecture 20 exercises.
'''

def linear_search( x, L ):
    try:
        y = L.index(x)
        return y
    except:
        for i in range(len(L)-1):
            if x < L[i]:
                return 0
            elif x>L[i] and x < L[i+1]:
                return i+1
            elif x >L[len(L)-1]:
                return len(L)


if __name__ == "__main__":
    #  Get the name of the file containing data
    fname = input('Enter the name of the data file => ')
    print(fname)

    #  Open and read the data values
    in_file = open(fname,'r')
    values = []
    for line in in_file:
        v = float(line)
        values.append(v)

    #  Search for each value requested by the user until -1 is entered
    x = 0
    while x != -1:
        x = float(input("Enter a value to search for ==> "))
        print(x)
        if x != -1:
            loc = linear_search(x, values )
            print(loc)