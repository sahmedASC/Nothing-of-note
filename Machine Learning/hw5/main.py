import pandas as pd
import numpy as np
import openpyxl
import matplotlib.pyplot as plt
import random
from time import process_time
import sys

#l max function as described in the paper
def l_function(w,x,y):
    x = y * (np.inner(w,x))
    if (1- x)>0:
        return x
    else:
        return 0

#objective function as described in the paper
def objective(l,w,data,y):
    x=0
    for i in range(len(data)):
       x+= l_function(w,data[i],y[i])
    x= (x/len(data))
    x+= (l/2)*(np.linalg.norm(w))**2
    return x

#main function
def mysgdsvm(filename, k,iter):

    #parsing and intialization
    lam_reg = 0.5
    k=int(k)
    obj_error=[]

    df = pd.read_csv(filename, header=None)
    #parse the data
    d = len(df.columns)
    X = np.array(df.iloc[:,1:])
    y = np.array(df[[0]][0])
    N = X.shape[0]

    check = True
    if k == 1 or k == N:
        check = False
    k_percent = k/N

    w = np.zeros(d-1)

    #start of T iteration loop
    iteration=1
    while iteration<(iter+1):
        eta = 1/(lam_reg*iteration)

        #if choosing a mini batch
        if check:

            #create the subset A
            x_class1=[]
            x_class2=[]
            y_class1=[]
            y_class2=[]

            for i in range(len(y)):
                if y[i] == 1:
                    y_class1.append(y[i])
                    x_class1.append(X[i])
                else:
                    y_class2.append(y[i])
                    x_class2.append(X[i])

            choices = list(range(int(k_percent*len(x_class1))))
            random.shuffle(choices)
            k_size= int(k_percent*len(x_class1))

            training_class1 = np.array(x_class1)[choices[0:k_size],:]
            training_label1 = np.array(y_class1)[choices[0:k_size]]

            choices = list(range(int(k_percent*len(x_class2))))
            random.shuffle(choices)
            k_size= int(k_percent*len(x_class2))
            training_class2 = np.array(x_class2)[choices[0:k_size],:]
            training_label2 = np.array(y_class2)[choices[0:k_size]]
            true_x = np.concatenate((training_class1,training_class2))
            true_y = np.concatenate((training_label1,training_label2))

            #run the update
            for i in range(len(true_x)):
                if (true_y[i] * np.inner(w,true_x[i])) <1:
                    w = (1-(eta*lam_reg))*w + eta*true_y[i]*true_x[i]
                else:
                    w = (1-(eta*lam_reg))*w
            if (1 > (1/(np.sqrt(lam_reg)))/np.linalg.norm(w)):
                w=(1/(np.sqrt(lam_reg)))/np.linalg.norm(w)*w

        else:
            #full batch run
            if k == N:
                #run the update
                for i in range(len(X)):
                    if (y[i] * np.inner(w,X[i])) <1:
                        w = (1-(eta*lam_reg))*w + eta*y[i]*X[i]
                    else:
                        w = (1-(eta*lam_reg))*w
                if (1 > (1/(np.sqrt(lam_reg)))/(np.linalg.norm(w)+1/N)):
                    w=(1/(np.sqrt(lam_reg)))/np.linalg.norm(w)*w
            else:
                #stochastic k==1 run
                random_indices = np.random.choice(N, size=1, replace=False)
                true_x = X[random_indices, :]
                true_y = y[random_indices]

                #run the update
                if (true_y * np.inner(w,true_x)) <1:
                    w = (1-(eta*lam_reg))*w + eta*true_y*true_x
                else:
                    w = (1-(eta*lam_reg))*w
                if (1 > (1/(np.sqrt(lam_reg)))/np.linalg.norm(w)):
                    w=(1/(np.sqrt(lam_reg)))/np.linalg.norm(w)*w

        #calculate objective function
        obj_error.append(objective(lam_reg,w,X,y))
        iteration+=1

    return obj_error


# Press the green button in the gutter to run the script.
if __name__ == '__main__':

    #set up numruns loop
    counter = 0
    iter = 100
    errors=[]
    times = []
    iter_axis = list(range(iter))

    #run the sgdsvm based on the numruns save the time each time
    while counter <int(sys.argv[3]):
        start = process_time()
        errors.append( mysgdsvm(sys.argv[1],sys.argv[2],iter))
        counter +=1
        times.append(process_time()-start)

    #output the avg time the stdev of the time and notify a file was created
    np.savetxt("tmp.csv", errors, delimiter=",")
    print("The average time per run was: " +str(np.mean(times))+"s")
    print("The Standard Deviation of time per run was: " +str(np.std(times))+"s")
    print("File saved into tmp.csv")


    #below is plotting code

    # colors = ['r','g','b','c','m']
    # for i in range(len(errors)):
    #     plt.plot(iter_axis,errors[i], color=colors[i],label = "Run " +str(i))
    #
    # plt.xlabel("Iteration")
    # plt.ylabel("Objective Function Value")
    # plt.title("5 runs of k = "+sys.argv[2])
    # plt.legend()
    # plt.show()




