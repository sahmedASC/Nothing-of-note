#This code was written by Saaif Ahmed '22
#The purpose of this program is to print a grid

import math as m

#Capturing of inputs
word1= input("Word => ")
print(word1)
columns= int(input("#columns => "))
print(int(columns))
rows= int(input("#rows => "))
print(int(rows))
print("Your word is:",word1)
print("")

#Begining of grids

#Grid A
print("(a)")
row_a="*** "*(columns-1)+"***" +"\n"
print(row_a*rows)

#Grid B
print("(b)")
midcolumn= round((columns/2)+0.1)
no_cs_column = columns-midcolumn
row_b="*** "*no_cs_column+"CS1"+ " ***"*no_cs_column

midrow= round((rows/2)+0.1)
no_cs_row= rows-midrow

print(row_a*no_cs_row,row_b,"\n",row_a*no_cs_row,"\n",end="",sep="")

#Grid C
print("(c)")
row_c_top="*** "*no_cs_column+" ^ "+" ***"*no_cs_column
row_c_bot="*** "*no_cs_column+" v "+" ***"*no_cs_column
row_c_slash1= "*** "*(no_cs_column-1)+" / " +" *** "+" \ "+" ***"*(no_cs_column-1)
row_c_slash2= "*** "*(no_cs_column-1)+" \ " +" *** "+" / "+" ***"*(no_cs_column-1)
row_c_cs="*** "*(no_cs_column-1)+" | " +" CS1 "+" | "+" ***"*(no_cs_column-1)+"\n"
row_c_lines="*** "*(no_cs_column-1)+" | " +" *** "+" | "+" ***"*(no_cs_column-1)+"\n"
row_c_main =row_c_lines*(no_cs_row-2)+row_c_cs+row_c_lines*(no_cs_row-2)

print(row_c_top)
print(row_c_slash1.rstrip())
print(row_c_main.rstrip(),sep="")
print(row_c_slash2.rstrip())
print(row_c_bot)
