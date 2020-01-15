import lab05_util as lab5

def print_info(List):
    print(List[0])
    address= List[3]
    address= address.split("+")
    street= address[0]
    state= address[1]
    for i in address:
        print("\t",i)
    avg= sum(List[6])/len(List[6])
    print("Average score: {0:.2f}".format(avg),"\n")
    return None
restaurants= lab5.read_yelp('yelp.txt')
print_info(restaurants[0])
print_info(restaurants[4])
print_info(restaurants[42])


