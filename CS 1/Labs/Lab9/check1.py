from Date import Date

from Date import month_names

if __name__ == "__main__":
    dates = []
    
    for line in open('birthdays.txt'):
        line = line.split(' ')
        birth = Date(int(line[0]),int(line[1]),int(line[2]))
        dates.append(birth)
    earliest = Date(3000,12,31)
    for i in dates:
        if i < earliest:
            earliest=i
    print("earliest date",earliest)


    earliest = Date()
    for i in dates:
        x= i < earliest
        if x == False:
            earliest=i    
    print("latest", earliest)
    
    months=[]
    for i in dates:
        months.append(i.month)
    months.sort()
    
    print(month_names[max(set(months), key=months.count)])
    