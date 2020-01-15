import lab05_util as lab5
import webbrowser as web

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
    return (address,List[4])

restaurants= lab5.read_yelp('yelp.txt')

idfood=int(input("Enter a restaurant id: "))
if idfood>len(restaurants):
    print("Invalid ID")
if idfood<=len(restaurants):
    idfood-=1
    output=print_info(restaurants[idfood])
print("\nWhat would you like to do next\n1. Visit the homepage\n2. Show on Google Maps\n3. Show directions to this restaurant")
choice = int(input("Your choice (1-3)? ==> "))

address=""
for i in output[0]:
    #print(i)
    address= address +i +" "

if choice == 1:
    print(output[1])
    web.open(output[1])
if choice == 2:
    url="http://www.google.com/maps/place/"+address
    print(url)
    web.open(url)
if choice == 3:
    url = "http://www.google.com/maps/dir/110 8th Street Troy NY/"+address
    print(url)
    web.open(url)