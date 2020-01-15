inputfile= input("Enter the scores file: ")
print(inputfile)
inputfile=inputfile.strip()

outputfile= input("Enter the output file: ")
print(outputfile)
outputfile=outputfile.strip()

nums=[]
for s in open(inputfile):
    s=s.replace("\n","")
    s= int(s)
    nums.append(s)
nums.sort()
#print(nums)

out = open(outputfile,"w")

pos=0

organized=[]
'''for j in nums:
    j = str(j)+ "\n"
    organized.append(j)
#print(organized)'''

for i in nums:
    out.write("{:2d}: {:3d}\n".format(pos,i))
    pos+=1
out.close()



