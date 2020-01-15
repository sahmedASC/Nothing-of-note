line = ""
count = 0
count2 = 0
for i in range(3):
    for j in range(3):
        count+=1
        line = line + str(i)+","+str(j) +" " + ((count//3)*" ")
        if count//3 == 1:
            count = 0
    count2+=1
    line= line + "\n" +((count2//3)*"\n")
    if count2//3 == 1:
        count2=0
line=line.rstrip()
print(line)

row =2
test=""
for i in range(9):
    test = test + str(i)+ "," + str(row) + " "
    
test= test.rstrip()
print(test)