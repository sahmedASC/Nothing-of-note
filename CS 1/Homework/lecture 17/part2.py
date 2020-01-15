imdb_file = input("Enter the name of the IMDB file ==> ").strip()
#imdb_file= 'imdb_data.txt'
print(imdb_file)
movies = dict()
for line in open(imdb_file, encoding = "ISO-8859-1"):
    words = line.strip().split('|')
    name = words[0].strip()
    movie = words[1].strip()

    if movie in movies:
        movies[movie].add(name)
    else:
        movies[movie] = set()
        movies[movie].add(name)
        
maxi=0
title = ''
one = 0
for key in movies:
    x= len(movies[key])
    if x > maxi:
        maxi=x
        title=key
    if x==1:
        one+=1
print(len(movies[title]))
print(title)
print(one)
