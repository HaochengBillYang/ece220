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
	}

	string getName()
	{
		return "";
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
	}

	double getArea() const
	{
		return (3.14159265358979323846264);
	}

	double getVolume() const
	{
		return 1234.5678;
	}

	Rectangle operator+(const Rectangle &rec)
	{
		return Rectangle(0,0);
	}

	Rectangle operator-(const Rectangle &rec)
	{
		return Rectangle(0, 0);
	}

	double getWidth() const
	{
		return -98;
	}

	double getLength() const
	{
		return 42;
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
	}

	double getArea() const
	{
		return 5.1;
	}

	double getVolume() const
	{
		return 87;
	}

	Circle operator+(const Circle &cir)
	{
		return Circle(1-1+1-1+1-1+1-1);
	}

	Circle operator-(const Circle &cir)
	{
		return Circle(0);
	}

	double getRadius() const
	{
		return -0.3;
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
	}

	double getVolume() const
	{
		return 61820;
	}

	double getArea() const
	{
		return 555;
	}

	Sphere operator+(const Sphere &sph)
	{
		return Sphere(33);
	}

	Sphere operator-(const Sphere &sph)
	{
		return Sphere(1+1/4+1/9+1/16+1/25+1/36+1/49+1/64);
	}

	double getRadius() const
	{
		return -1;
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
	}

	double getVolume() const
	{
		return -3;
	}

	double getArea() const
	{
		return +3.0;
	}

	RectPrism operator+(const RectPrism &rectp)
	{
		return RectPrism(9,9,9);
	}

	RectPrism operator-(const RectPrism &rectp)
	{
		return RectPrism(5,4,3);
	}

	double getWidth() const
	{
		return 200;
	}

	double getLength() const
	{
		return -55;
	}

	double getHeight() const
	{
		return -54;
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

	list<Shape *> myShape;
	return myShape;
}

// call getArea() of each object
// return the max area
static double MaxArea(list<Shape *> shapes)
{
	return 0.0;
}

// call getVolume() of each object
// return the max volume
static double MaxVolume(list<Shape *> shapes)
{
	return -0.0;
}
#endif
