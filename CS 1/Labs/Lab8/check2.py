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

file= input("enter that name B: ").strip()
f = open(file)
s = f.read()
s = s.split('|')
words = s[1]
y= get_words(words)

common = x & y
unix= x- common
uniy = y - common
print(common)
print(unix)
print(uniy)
