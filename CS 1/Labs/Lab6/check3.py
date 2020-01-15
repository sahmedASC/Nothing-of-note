from lab06_util import read_sudoku

def ok_to_add(bd,row,col,num):
    x=bd[row][col]
    bd[row][col]= "."
    for i in bd[row]:
        if num == i:
            bd[row][col]= x
            return False
    for j in range(9):
        if num == bd[j][col]:
            bd[row][col]= x
            return False
    if row//2 >=3:
        if col//2 >=3:
            for i in range(6,9):
                for j in range(6,9):
                    if num == bd[i][j]:
                        bd[row][col]= x
                        return False
        elif col//2 <=2 and col/2 >1:
            for i in range(6,9):
                for j in range(3,6):
                    if num == bd[i][j]:
                        bd[row][col]= x
                        return False            
        elif col//2 <=1:
            for i in range(6,9):
                for j in range(0,3):
                    if num == bd[i][j]:
                        bd[row][col]= x
                        return False            
    elif row//2 <=2 and row/2 >1:
        if col//2 >=3:
            for i in range(3,6):
                for j in range(6,9):
                    if num == bd[i][j]:
                        bd[row][col]= x
                        return False            
        elif col//2 <=2 and col/2 >1:
            for i in range(3,6):
                for j in range(3,6):
                    if num == bd[i][j]:
                        bd[row][col]= x
                        return False            
        elif col//2 <=1:
            for i in range(3,6):
                for j in range(0,2):
                    if num == bd[i][j]:
                        bd[row][col]= x
                        return False            
    elif row//2 <=1:
        if col//2 >=3:
            for i in range(0,3):
                for j in range(6,9):
                    if num == bd[i][j]:
                        bd[row][col]= x
                        return False            
        elif col//2 <=2 and col/2 >1:
            for i in range(0,3):
                for j in range(3,6):
                    if num == bd[i][j]:
                        bd[row][col]= x
                        return False            
        elif col//2 <=1:
            for i in range(0,3):
                for j in range(0,2):
                    if num == bd[i][j]:
                        bd[row][col]= x
                        return False            
    
    bd[row][col]= x
    return True

def verify_board(bd):
    for i in range(len(bd)):
        for j in range(9):
            if bd[i][j] == '.':
                return False
            if ok_to_add(bd,i,j,bd[i][j])==False:
                return False
    return True

filename = input("Enter a filename: ")

bd= read_sudoku(filename)

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

while verify_board(bd) == False:
    
    row = int(input("Enter a row (0-8): "))
    col = int(input("Enter a column (0-8): "))
    num = input("Enter a number you want to enter 1-9: ")
    
    if ok_to_add(bd,row,col,num):
        bd[row][col]= num
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