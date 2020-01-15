def timeskew(t1,t2,t3,t4,t5):
    avg=(t1+t2+t3+t4+t5)/5
    var=(t1-avg)**2+(t2-avg)**2+(t3-avg)**2+(t4-avg)**2+(t5-avg)**2
    var /= 5
    skew =(t1-avg)**3+(t2-avg)**3+(t3-avg)**3+(t4-avg)**3+(t5-avg)**3
    skew/= 5
    skew = skew/var**3**0.5
    return skew

def minmaxmean(t1,t2,t3,t4,t5,name):
    mini=min(t1,t2,t3,t4,t5)
    maxi=max(t1,t2,t3,t4,t5)
    avg=((t1+t2+t3+t4+t5)-(mini+maxi))/3
    print(name,"'s stats-- min: ", mini, ", max: ", maxi, ", avg: ", round(avg,1), 
          sep="")
    
name_1 = "Stan"
## The following are Stan's 5 latest running times for 3 miles

time1_1 = 34
time2_1 = 34
time3_1 = 35
time4_1 = 31
time5_1 = 29

name_2 = "Kyle"
## The following are Kyle's 5 latest running times for 3 miles

time1_2 = 30
time2_2 = 31
time3_2 = 29
time4_2 = 29
time5_2 = 28

name_3 = "Cartman"
## The following are Cartman's 5 latest running times for 3 miles
time1_3 = 36
time2_3 = 31
time3_3 = 32
time4_3 = 33
time5_3 = 33

name_4 = "Kenny"
## The following are Kenny's 5 latest running times for 3 miles
time1_4 = 33
time2_4 = 32
time3_4 = 34
time4_4 = 31
time5_4 = 35

name_5 = "Bebe"
## The following are Bebe's 5 latest running times for 3 miles
time1_5 = 27
time2_5 = 29
time3_5 = 29
time4_5 = 28
time5_5 = 30

skew1=timeskew(time1_1,time2_1,time3_1,time4_1,time5_1)
skew2=timeskew(time1_2,time2_2,time3_2,time4_2,time5_2)
skew3=timeskew(time1_3,time2_3,time3_3,time4_3,time5_3)
skew4=timeskew(time1_4,time2_4,time3_4,time4_4,time5_4)
skew5=timeskew(time1_5,time2_5,time3_5,time4_5,time5_5)
print ("{0}'s running times have a skew of {1:.2f}".format(name_1,skew1))
print ("{0}'s running times have a skew of {1:.2f}".format(name_2,skew2))
print ("{0}'s running times have a skew of {1:.2f}".format(name_3,skew3))
print ("{0}'s running times have a skew of {1:.2f}".format(name_4,skew4))
print ("{0}'s running times have a skew of {1:.2f}".format(name_5,skew5))

print("_____________________________________________")

minmaxmean(time1_1,time2_1,time3_1,time4_1,time5_1,name_1)
minmaxmean(time1_2,time2_2,time3_2,time4_2,time5_2,name_2)
minmaxmean(time1_3,time2_3,time3_3,time4_3,time5_3,name_3)
minmaxmean(time1_1,time2_4,time3_4,time4_4,time5_4,name_4)
minmaxmean(time1_5,time2_5,time3_5,time4_5,time5_5,name_5)
