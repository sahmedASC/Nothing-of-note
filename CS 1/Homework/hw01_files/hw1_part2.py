#This was written by Saaif Ahmed '22
#The purpose of this program is to fix a constitution text file, find the average
#number of characters per line, count the number of articles and sections, and
#find the number of times a word that the user inputs appears in the constituion.
import constitution as c
from constitution import substring

#Here I store the constitution.py text into a variable called og_doc
og_doc = c.get_all_text()
og_doc = og_doc.replace("@"," ")
og_doc = og_doc.replace("#","\n\n")
fixed_og_doc = og_doc.replace("^","\n")

#Re-assign the og_doc value for computation
og_doc = c.get_all_text()

#Calculate the average # of characters per line
#Count entire length of the constitution.py divided by the number of line breaks
lines1 = og_doc.count("#")*2
lines2 = og_doc.count("^")
lines = lines1+lines2
char_og_doc = len(og_doc)

avg_char_line= round((char_og_doc/lines)-1)

#Count the number of times Article appears in the document
articles= (og_doc.count("Article.")) + (og_doc.count("Article@"))

#Count the number of times Section appears in the document
sections= (og_doc.count("Section."))

#Indices of desired terms and positions in Article 1
#Begin by defining the article 1 string
article1= substring(fixed_og_doc, fixed_og_doc.find("Article. I.\n\n")+len("Article. I.\n\n"),fixed_og_doc.find("Article. II")-(fixed_og_doc.find("Article. I.\n\n")+len("Article. I.\n\n")))
articlebegin= fixed_og_doc.find("Article. I.\n\n")+len("Article. I.\n\n")
article_end= fixed_og_doc.find("Article. II")

article_first= substring(article1,0,1)
article_last=substring(fixed_og_doc,article_end-3,1)
articleword= substring(article1,0,article1.find(" "))
articlewordend= substring(article1,article1.rfind(" ")+1,(article1.rfind("\n\n"))-(article1.rfind(" ")+1))
#Return information about Article 1

print(avg_char_line*"*")
print(fixed_og_doc)
print(avg_char_line*"*","\n")
print("There are",articles,"articles and",sections,"sections in the United States Constitution\n")

#Print the indices of desired terms and positions in Article 1
print("Text of Article I starts at position ", articlebegin, " (character ","\'",article_first,"\')", " with the word \"",articleword,"\"",sep="")
print("Text of Article I ends at position ", article_end-3, " (character ","\'",article_last,"\')", " with the word \"",articlewordend,"\"","\n",sep="")

#take input from the user and run the count check for the number of times the 
#word appears
userword= input("Enter the word to count in the Constitution => ")
print(userword)
og_doc=og_doc.lower()
usernumber= og_doc.count(userword.lower())
print("Word ","\"",userword.upper(),"\""," appears ", usernumber, " times (without regard to case) in the text of the United States Constitution", sep="")
