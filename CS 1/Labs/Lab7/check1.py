def parse_line(line):
    x= line.split('/')
    if len(x)<=3:
        return None
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
    
    
line = "Here is some random text, like 5/4=3./12/3/4"
lines= "           Here is some spaces\n/12/32/4"
lines3= "Here is some random text, like 5/4=3./12/3/4as"

print(parse_line(lines))