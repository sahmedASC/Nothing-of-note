file= input("enter that name B: ").strip()
f = open(file)
s = f.read()
s = s.split('|')
words = s[1]

def get_words(words):
    wordset= set()
    words = words.replace('.',' ').replace(',',' ').replace('(',' ').replace(')',' ').replace('"',' ')
    words = words.split(' ')
    for i in words:
        if len(i)>3:
            if i.isalpha():
                wordset.add(i)
    return wordset

print(get_words(words))
print(len(get_words(words)))

