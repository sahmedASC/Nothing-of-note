def parse_line(line):
    x= line.split('/')
    if len(x)<=3:
        return None
    print(x)
    try: 
        a=int(x[len(x)-1])
        x.remove(str(a))
    except:
        return None
    try:
        b=int(x[len(x)-1])
        x.remove(str(b))
    except:
        return None
    try:
        c=int(x[len(x)-1])
        x.remove(str(c))
    except:
        return None
    string = ''
    for i in x:
        string= string + i +"/"
    string=string.rstrip('/')    
    return (c,b,a,string)
    
def get_line(fname,parno,lineno):
    file = open(fname, encoding='utf8')
    s= file.read()
    s= s.split('\n\n')
    line= s[parno-1]
    line=line.strip('\n')
    line = line.split('\n')
    return line[lineno-1]

fname= input("Please enter the file number ==> ").strip()
fname= fname+".txt"
parno = int(input("Please enter the paragraph number ==> ").strip())
lineno= int(input("Please enter the line number ==> ").strip())

print(get_line(fname,parno,lineno))

