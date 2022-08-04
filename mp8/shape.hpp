#ifndef SHAPE_H_
#define SHAPE_H_

#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <list>
#include <fstream>
#include <iomanip>

using namespace std;

// Base class
// Please implement Shape's member functions
// constructor, getName()
class Shape
{
public:
	// Base class' constructor should be called in derived classes'
	// constructor to initizlize Shape's private variable
	Shape(string name)
	{
		name_ = name;
	}

	string getName()
	{
		return name_;
	}

	virtual double getArea() const = 0;
	virtual double getVolume() const = 0;

private:
	string name_;
};

// Rectangle
// Please implement the member functions of Rectangle:
// constructor, getArea(), getVolume(), operator+, operator-

template <class T>
class Rectangle : public Shape
{
public:
	Rectangle(double width = 0, double length = 0) : Shape("Rectangle")
	{
		width_ = width;
		length_ = length;
	}

	double getArea() const
	{
		return (width_*length_);
	}

	double getVolume() const
	{
		return 0;
	}

	Rectangle operator+(const Rectangle &rec)
	{
		return Rectangle(width_+rec.width_, length_+rec.length_);
	}

	Rectangle operator-(const Rectangle &rec)
	{
		return Rectangle(max(0.0, width_-rec.width_), max(0.0, length_-rec.length_));
	}

	double getWidth() const
	{
		return width_;
	}

	double getLength() const
	{
		return length_;
	}

private:
	double width_;
	double length_;
};

// Circle
// Please implement the member functions of Circle:
// constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Circle : public Shape
{
public:
	Circle(double radius) : Shape("Circle")
	{
		radius_ = radius;
	}

	double getArea() const
	{
		return radius_*radius_*3.1415926535897932384626;
	}

	double getVolume() const
	{
		return 0;
	}

	Circle operator+(const Circle &cir)
	{
		return Circle(radius_+cir.radius_);
	}

	Circle operator-(const Circle &cir)
	{
		return Circle(max(0.0, radius_-cir.radius_));
	}

	double getRadius() const
	{
		return radius_;
	}

private:
	double radius_;
};

// Sphere
// Please implement the member functions of Sphere:
// constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Sphere : public Shape
{
public:
	Sphere(double radius) : Shape("Sphere")
	{
		radius_ = radius;
	}

	double getVolume() const
	{
		return (4.0/3)*3.1415926535897932384626*radius_*radius_*radius_;
	}

	double getArea() const
	{
		return 4.0*3.1415926535897932384626*radius_*radius_;
	}

	Sphere operator+(const Sphere &sph)
	{
		return Sphere(radius_+sph.radius_);
	}

	Sphere operator-(const Sphere &sph)
	{
		return Sphere(max(0.0, radius_-sph.radius_));
	}

	double getRadius() const
	{
		return radius_;
	}

private:
	double radius_;
};

// Rectprism
// Please implement the member functions of RectPrism:
// constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
class RectPrism : public Shape
{
public:
	RectPrism(double width, double length, double height) : Shape("RectPrism")
	{
		width_ = width;
		length_ = length;
		height_ = height;
	}

	double getVolume() const
	{
		return width_*length_*height_;
	}

	double getArea() const
	{
		return 2*(width_*length_+length_*height_+width_*height_);
	}

	RectPrism operator+(const RectPrism &rectp)
	{
		return RectPrism(width_+rectp.width_, length_+rectp.length_, height_+rectp.height_);
	}

	RectPrism operator-(const RectPrism &rectp)
	{
		return RectPrism(max(0.0, width_-rectp.width_), max(0.0, length_-rectp.length_), max(0.0, height_-rectp.height_));
	}

	double getWidth() const
	{
		return width_;
	}

	double getLength() const
	{
		return length_;
	}

	double getHeight() const
	{
		return height_;
	}

private:
	double length_;
	double width_;
	double height_;
};

// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects
static list<Shape *> CreateShapes(char *file_name)
{
	//@@Insert your code here
	int shapes;
	string name;
	double arg1, arg2, arg3;
	ifstream filestream ("test1.txt", std::ifstream::in);
	filestream >> shapes;
    list<Shape *> myShape;
	for(int i=0; i<shapes; i++)
	{
		filestream >> name;
		if(name=="Circle"){
			filestream >> arg1;
			myShape.insert(myShape.end(), new Circle(arg1));
		}
		else if(name=="Rectangle"){
			filestream >> arg1 >> arg2;
			myShape.insert(myShape.end(), new Rectangle<double>(arg1,arg2));
		}
		else if(name=="Sphere"){
			filestream >> arg1;
			myShape.insert(myShape.end(), new Sphere(arg1));
		}
		else if(name=="RectPrism"){
			filestream >> arg1 >> arg2 >> arg3;
			myShape.insert(myShape.end(), new RectPrism(arg1,arg2,arg3));
		}
	}	
	filestream.close();
	return myShape;
}

// call getArea() of each object
// return the max area
static double MaxArea(list<Shape *> shapes)
{	
	double flag;
	for (list<Shape *>::iterator it = shapes.begin(); it != shapes.end(); it++) {
    	if ((*it)->getArea() > flag){
			flag = (*it)->getArea();
		}
	}
	return flag;
}

// call getVolume() of each object
// return the max volume
static double MaxVolume(list<Shape *> shapes)
{
	double flag;
	for (list<Shape *>::iterator it = shapes.begin(); it != shapes.end(); it++) {
    	if ((*it)->getVolume() > flag){
			flag = (*it)->getVolume();
		}
	}
	return flag;
}
#endif
