#This was made by Saaif Ahmed '22 and this program takes in a phrase and turns it into a twitter hashtag
phrase = 'Things you wish you knew as a freshman'
phrase=phrase.title()
phrase=phrase.replace("T","#T")
phrase=phrase.replace(" ","")
print('The phrase \"Things you wish you knew as a freshman\"\nbecomes the hashtag ',"\"",phrase,"\"", sep="")
