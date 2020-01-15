def get_words(words):
    wordset= set()
    words = words.replace('.',' ').replace(',',' ').replace('(',' ').replace(')',' ').replace('"',' ')
    words = words.split(' ')
    for i in words:
        i=i.lower()
        if len(i)>3:
            if i.isalpha():
                wordset.add(i)
    return wordset

file= input("enter that name B: ").strip()
f = open(file)
s = f.read()
s = s.split('|')
words = s[1] 
x= get_words(words)
f.close()

similar = []
for club in open('allclubs.txt'):
    club = club.split('|')
    if club[0] != s[0]:
        words = club[1]
        test = get_words(words)
        common = x & test
        similar.append((len(common),club[0]))
similar.sort()
similar.sort(reverse = True)

for i in range(5):
    print(similar[i])