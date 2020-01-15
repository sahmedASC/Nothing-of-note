#include <iostream>
#include "Point2D.h"
#include "Rectangle.h"


int main() {
    //std::cout << "Hello, World!" << std::endl;
    Point2D a(1.14,1.14);
    Point2D b(6.14,6.14);
    Point2D c(1.0,1.0);
    Point2D d(2.0,2.0);
    Point2D outside(10.0,10.0);
    Point2D inside(1.5,1.5);
    Point2D test1(4,4);
    Point2D test2(5,4);
    Point2D test3(1.5,1.5);


    Rectangle rec1(a,b);
    Rectangle rec2(c,d);
    print_rectangle(rec1);
    print_rectangle(rec2);

    std::cout<< rec2.is_point_within(inside)<<std::endl;
    std::cout<< rec1.is_point_within(outside)<<std::endl;

    if(rec2.is_point_within(inside)){
        rec2.add_point(inside);
        std::cout<<"new point for this rectangle"<<std::endl;
        print_rectangle(rec2);
    }
    rec1.add_point(test1);
    rec1.add_point(test2);
    rec1.add_point(test3);
    std::cout<<"points in both"<<std::endl;
    std::vector<Point2D> x=points_in_both(rec1,rec2);
    for (int i=0;i<x.size();i++){
        std::cout<< x[i].x()<<','<<x[i].y()<<std::endl;
    }



    return 0;
}