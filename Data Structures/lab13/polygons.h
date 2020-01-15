#ifndef _POLYGONS_H_
#define _POLYGONS_H_

#include <iostream>
#include <cmath>
#include <cassert>
#include <vector>
#include <string>
#include "utilities.h"

// epsilon values used in comparing the edge lengths & angles between
// edges note that these values are dependent on the precision of
// the coordinates and the overall scale of the objects
#define DISTANCE_EPSILON 0.0001
#define ANGLE_EPSILON 0.1

class Polygon {
public:
	Polygon(std::string name, std::vector<Point> points) {
		if (points.size() < 3) {
			throw 1;
		}
		verts_ = points;
		name_ = name;
	}
	virtual ~Polygon() {}
	int NumVerts() { return verts_.size(); }
	std::vector<Point> getPoints() { return verts_; }
	std::string getName() { return name_; }
	virtual bool HasAllEqualSides() {
		bool ret = true;
		for (unsigned int i = 0; i + 2 < verts_.size(); i++) {
			if(!EqualSides(DistanceBetween(verts_[i], verts_[i+1]), \
				DistanceBetween(verts_[i+1], verts_[i+2]))) {
				ret = false;
				break;
			}
		} 
		return ret;
	}
protected:
	std::vector<Point> verts_;
	std::string name_;
};

class Quadrilateral : public Polygon {
public:
	Quadrilateral(std::string name, std::vector<Point> points) : Polygon(name, points) {
		if (points.size() != 4) {
			throw 1;
		}
	}
};

class Rectangle : public Quadrilateral {
public:
	Rectangle(std::string name, std::vector<Point> points) : Quadrilateral(name, points) {
		Vector a(points[0], points[1]);
		Vector b(points[2], points[3]);
		Vector c(points[1], points[2]);
		Vector d(points[0], points[3]);
		//check equal length opposite sides
		if (fabs(a.Length() - b.Length()) > DISTANCE_EPSILON || \
			fabs(c.Length() - d.Length()) > DISTANCE_EPSILON) {
			throw 1;
		}
		//check parallel opposite sides
		if (!Parallel(a, b) || !Parallel(c, d)) {
			throw 1;
		}
		//check 90 degrees on all four corners
		if (!RightAngle(Angle(points[0], points[1], points[2])) || \
			!RightAngle(Angle(points[1], points[2], points[3])) || \
			!RightAngle(Angle(points[2], points[3], points[0]))) {
			throw 1;
		}
	}
};

class Square : public Rectangle {
public:
	Square(std::string name, std::vector<Point> points) : Rectangle(name, points) {
		Vector a(points[0], points[1]);
		Vector b(points[2], points[3]);
		Vector c(points[1], points[2]);
		Vector d(points[0], points[3]);
		//check all sides equal length
		if (fabs(a.Length() - b.Length()) > DISTANCE_EPSILON || \
			fabs(b.Length() - c.Length()) > DISTANCE_EPSILON || \
			fabs(c.Length() - d.Length()) > DISTANCE_EPSILON || \
			fabs(d.Length() - a.Length()) > DISTANCE_EPSILON) {
			throw 1;
		}
	}
	bool HasAllEqualSides() { return true; }
};

class Triangle : public Polygon {
public:
	Triangle(std::string name, std::vector<Point> points) : Polygon(name, points) {
		if (points.size() != 3) {
			throw 1;
		}
	}
};

class IsoscelesTriangle : virtual public Triangle {
public:
	IsoscelesTriangle(std::string name, std::vector<Point> points) : Triangle(name, points) {
		//check at least two sides are equal
		if (!(\
			EqualSides(DistanceBetween(points[0], points[1]), DistanceBetween(points[1], points[2])) || \
			EqualSides(DistanceBetween(points[1], points[2]), DistanceBetween(points[2], points[0])) ||
			EqualSides(DistanceBetween(points[0], points[1]), DistanceBetween(points[2], points[0])) )) {
			throw 1;
		}
	}
};
class RightTriangle : public virtual  Triangle{
    RightTriangle(std::string name, std::vector<Point> points): Triangle(name, points) {
        if(! (RightAngle(Angle(points[0], points[1], points[2])) or RightAngle(Angle(points[1], points[2],points[0]))
        or RightAngle(Angle(points[0], points[2],points[1])))){
            throw 1;
        }

    }
};
class IsoscelesRightTriangle : public IsoscelesTriangle, public RightTriangle{
    RightTriangle(std::string nme, std::vector<Point> points): IsoscelesTriangle(name, points), RightTriangle(name, points) {}

};
class EquilateralTriangle : public IsoscelesTriangle {
public:
	EquilateralTriangle(std::string name, std::vector<Point> points) : IsoscelesTriangle(name, points),Triangle(name, points) {
		//check all sides are equal
		if (!(\
			EqualSides(DistanceBetween(points[0], points[1]), DistanceBetween(points[1], points[2])) && \
			EqualSides(DistanceBetween(points[1], points[2]), DistanceBetween(points[2], points[0])) &&
			EqualSides(DistanceBetween(points[0], points[1]), DistanceBetween(points[2], points[0])) )) {
			throw 1;
		}
	}
	bool HasAllEqualSides() { return true; }
};


#endif