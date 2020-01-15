//
// Created by ahmeds7 on 1/23/2019.
//

#ifndef LAB2_ANIMAL_H
#define LAB2_ANIMAL_H
#include<string>


class animal {
public:
    animal(const std::string &name);

    std:string getName() const;
    float getWeight() const;
    bool getLand() const;
    bool getWater() const;
    bool getMeat() const;
    bool getPlant() ;

    void setWeight(float aweight);
    void setName(const std::string &name);
    void setWater(bool abool);
    void setLand(bool abool);
    void setMeat(bool abool);
    void setPlant(bool abool);

    bool isOmnitrix() const;
    bool isFroglike() const;



private:
    std::string name;
    float weight;
    bool land, water, meat, plant;

};


#endif //LAB2_ANIMAL_H
