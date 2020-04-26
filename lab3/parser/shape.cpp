//
//  shape.cpp skeleton
//  lab3
//
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

#include "shape.h"

// ECE244 Student: 
// Write the implementation (and only the implementation) of the shape
// class below

// Constructor with all fields passed as arguments
shape::shape (string n, string t, int x_loc, int y_loc, int x_sz, int y_sz)
{
    name = n;
    type = t;
    x_location = x_loc;
    y_location = y_loc;
    x_size = x_sz;
    y_size = y_sz;
}

// Returns the name of the shape
string shape::getName ()
{
    return name;
}

// Returns the type
string shape::getType ()
{
    return type;
}

// Returns the location of the shape on the x-axis
int shape::getXlocation ()
{
    return x_location;
}

// Returns the location of the shape on the y-axis
int shape::getYlocation ()
{
    return y_location;
}

// Returns the size of the shape in the x-dimension
int shape:: getXsize ()
{
    return x_size;
}

// Returns the size of the shape in the y-dimension
int shape::getYsize ()
{
    return y_size;
}

// Sets the type (see globals.h)
// No error checking done inside the method
// The calling program must ensure the type is correct
void shape::setType(string t)
{
    type = t;
}

// Sets the name of the shape
void shape::setName(string n)
{
    name = n;
}

// Sets the location of the shape on the x-axis
void shape::setXlocation(int x_loc)
{
    x_location = x_loc;
}

// Sets the location of the shape on the y-axis
void shape::setYlocation (int y_loc)
{
    y_location = y_loc;
}

// Sets the size of the shape in the x-dimension
void shape::setXsize (int x_sz)
{
    x_size = x_sz;
}

// Sets the size of the shape in the y-dimension
void shape::setYsize (int y_sz)
{
    y_size = y_sz;
}

// Sets the rotation of the shape
void shape::setRotate (int angle)
{
    rotation = angle;
}

// Draws a shape
// For this assignment it only prints the information of the shape
void shape::draw ()
{
    cout << name << ": " << type << " " << x_location << " " << y_location << " " << x_size << " " << y_size << endl;
} 
