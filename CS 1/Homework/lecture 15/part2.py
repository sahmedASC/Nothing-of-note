imdb_file = input("Data file name: ")
print(imdb_file)
prefix= input("Prefix: ")
print(prefix)


names = set()
lastname= []
for line in open(imdb_file, encoding = "ISO-8859-1"):
    words = line.strip().split('|')

    last = words[0].split(',')
    name = last[0].strip()
    names.add(name)
    
    pref=last[0]
    pref= pref.split(prefix)
    if pref[0] == '':
        lastname.append(pref[0])

print(len(names),"last names")

print(len(lastname), "start with", prefix)