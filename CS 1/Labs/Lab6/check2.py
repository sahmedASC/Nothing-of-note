bd = [ [ '1', '.', '.', '.', '2', '.', '.', '3', '7'],
       [ '.', '6', '.', '.', '.', '5', '1', '4', '.'],
       [ '.', '5', '.', '.', '.', '.', '.', '2', '9'],
       [ '.', '.', '.', '9', '.', '.', '4', '.', '.'],
       [ '.', '.', '4', '1', '.', '3', '7', '.', '.'],
       [ '.', '.', '1', '.', '.', '4', '.', '.', '.'],
       [ '4', '3', '.', '.', '.', '.', '.', '1', '.'],
       [ '.', '1', '7', '5', '.', '.', '.', '8', '.'],
       [ '2', '8', '.', '.', '4', '.', '.', '.', '6'] ]


def ok_to_add(bd,row,col,num):
    #column
    #x=bd[row][col]
    bd[row][col]= "."
    for i in bd[row]:
        if num == i:
            return False
    for j in range(9):
        if num == bd[j][col]:
            return False
    if row//2 >=3:
        print("7,8,9")
        if col//2 >=3:
            for i in range(6,9):
                for j in range(6,9):
                    if num == bd[i][j]:
                        return False
        elif col//2 <=2 and col/2 >1:
            for i in range(6,9):
                for j in range(3,6):
                    if num == bd[i][j]:
                        return False            
        elif col//2 <=1:
            for i in range(6,9):
                for j in range(0,3):
                    if num == bd[i][j]:
                        return False            
    elif row//2 <=2 and row/2 >1:
        if col//2 >=3:
            for i in range(3,6):
                for j in range(6,9):
                    if num == bd[i][j]:
                        return False            
        elif col//2 <=2 and col/2 >1:
            for i in range(3,6):
                for j in range(3,6):
                    if num == bd[i][j]:
                        return False            
        elif col//2 <=1:
            for i in range(3,6):
                for j in range(0,2):
                    if num == bd[i][j]:
                        return False            
    elif row//2 <=1:
        if col//2 >=3:
            for i in range(0,3):
                for j in range(6,9):
                    if num == bd[i][j]:
                        return False            
        elif col//2 <=2 and col/2 >1:
            for i in range(0,3):
                for j in range(3,6):
                    if num == bd[i][j]:
                        return False            
        elif col//2 <=1:
            for i in range(0,3):
                for j in range(0,2):
                    if num == bd[i][j]:
                        return False            
    
    return True

row = int(input("Enter a row (0-8): "))
col = int(input("Enter a column (0-8): "))
num = input("Enter a number you want to enter 1-9: ")

if ok_to_add(bd,row,col,num):
    bd[row][col]= str(num)
else:
    print("Invalid try again")

board = "-"*25+"\n" +"| "

count=0
count2=0
for x in range(len(bd)):
    for y in range(len(bd[0])):
        count+=1
        board= board+ bd[x][y]+ " " + ((count//3)*"| ")
        if count//3==1:
            count=0
    count2+=1
    
    board=board+"\n"
    
    if count2%3==0:
        board = board + "-"*25 + "\n" + "| "
        count2=0
    else:
        board=board + "| "
board = board.rstrip("| ")
print(board)