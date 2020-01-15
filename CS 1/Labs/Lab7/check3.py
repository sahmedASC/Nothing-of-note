def parse_line(line):
    x= line.split('/')
    if len(x)<=3:
        return None
    try: 
        a=int(x[len(x)-1])
        del x[len(x)-1]
    except:
        return None
    try:
        b=int(x[len(x)-1])
        del x[len(x)-1]
    except:
        return None
    try:
        c=int(x[len(x)-1])
        del x[len(x)-1]
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

check1=False

x= get_line(fname,parno,lineno)
if x != None:
    check1= True
    y= parse_line(x)
    if y != None:
        f_out = open("program.py","w")
        check = False
while check1:
    if y != None:
        f_out.write(y[3]+"\n")
        fname=str(y[0])+".txt"
        x=get_line(fname,y[1],y[2])
        
    else:
        break
    if x == None:
        break
    
    y=parse_line(x)
    if y == None:
        check = True
        break
    if y[3] == '':
        continue    
    if y[3] == 'END':
        check = True
        break
    

if check:
    f_out.close()
    exec(open("program.py").read())
    