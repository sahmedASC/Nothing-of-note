import lab05_util as lab5

def print_info(List):
    print(List[0])
    address= List[3]
    address= address.split("+")
    street= address[0]
    state= address[1]
    for i in address:
        print("\t",i)
    scores=List[6]
    length = len(List[6])
    if length<3:
        avg= sum(List[6])/len(List[6])
    else:
        scoresmax=max(scores)
        scoresmin=min(scores)
        total= sum(List[6])
        total-=scoresmax
        total-=scoresmin
        avg= total/(length-2)
    if avg<2:
        print("This restaurant is rated bad, based on {0:} reviews".format(len(List[6])))
    elif avg<3 and avg>=2:
        print("This restaurant is rated average, based on {0:} reviews".format(len(List[6])))
    elif avg<4 and avg>=3:
        print("This restaurant is rated above average, based on {0:} reviews".format(len(List[6])))
    elif avg<5 and avg>=4:
        print("This restaurant is rated very good, based on {0:} reviews".format(len(List[6])))
    return None

restaurants= lab5.read_yelp('yelp.txt')

idfood=int(input("Enter a restaurant id: "))
if idfood>len(restaurants):
    print("Invalid ID")
if idfood<=len(restaurants):
    idfood-=1
    print_info(restaurants[idfood])