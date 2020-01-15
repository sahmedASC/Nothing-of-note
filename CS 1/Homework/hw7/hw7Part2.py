#This code was written by Saaif Ahmed '22
#The objective of this program is to find movies that people like and find
#what movies they might also like

import json

if __name__ == "__main__":
    #gather values for computation later on
    movies = json.loads(open("movies.json").read())
    ratings = json.loads(open("ratings.json").read())
    
    movie_copy = movies.copy()
    
    miniyear = input("Min year => ")
    print(miniyear)
    miniyear = int(miniyear)
    
    maxiyear = input("Max year => ")
    print(maxiyear)
    maxiyear = int(maxiyear)
    
    imdb = input("Weight for IMDB => ")
    print(imdb)
    w1 = float(imdb)
    
    twit = input("Weight for Twitter => ")
    print(twit)
    w2= float(twit)
    print("")
    
    #alter the movies file to inclue a combined rating for all valid entries
    for movie in movies:
        try:
            imdb = movies[movie]['rating']
            twitter = ratings[movie]
            if len(twitter) >= 3:
                avgtwit = sum(twitter)/len(twitter)
                combined = (w1* imdb + w2 *avgtwit)/(w1+w2)
                movie_copy[movie].update({'true_rate':combined})
            else:
                pass
        except:
            pass
    
    #go into loop for output
    while True:
        potential = []
        genre = input('What genre do you want to see? ')
        
        #break condition
        print(genre)
        if genre.lower() == 'stop':
            break
        print("")
        
        #Adds a movie if and only if all condition are met. timing. genre and 
        #ratings are check facotrs
        for i in movie_copy:
            if 'true_rate' in movie_copy[i]:
                if movie_copy[i]['movie_year'] > miniyear and movie_copy[i]['movie_year'] < maxiyear:
                    genres = movie_copy[i]['genre']
                    check = False
                    for j in genres:
                        if genre.title() == j.title():
                            check = True
                            break
                    if check:
                        x = (movie_copy[i]['true_rate'],movie_copy[i]['name'],movie_copy[i]['movie_year'])
                        potential.append(x)
                    else:
                        continue
                else:
                    continue
            else:
                continue
        
        #if no matches are found
        if len(potential) == 0:
            print("No {} movie found in {} through {}".format(genre.title(),miniyear,maxiyear))
        
        #gather and print the best and worst outputs
        else:
            potential.sort(reverse = True)
            x= potential[0]
            y= min(potential)            
            print("Best:")
            print("\tReleased in {}, {} has a rating of {:.2f}".format(x[2],x[1],x[0]))
            print("")
            print("Worst:")
            print("\tReleased in {}, {} has a rating of {:.2f}".format(y[2],y[1],y[0]))
        print("")
        check = False