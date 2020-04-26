//
//  main.cpp skeleton
//  lab3
//
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "shape.h"

// This is the shape array, to be dynamically allocated
shape** shapesArray;

// The number of shapes in the database, to be incremented 
// every time a shape is successfully created
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

// Command functions
void maxShapes (stringstream &line);
void create (stringstream &line);
void move (stringstream &line);
void rotate (stringstream &line);
void draw (stringstream &line);
void deleteShapes (stringstream &line);

// Error functions
void invalidCommand ();
void invalidArgument ();
void invalidShapeName ();
void shapeNameExists ();
void shapeNameNotFound (string name);
void invalidShapeType ();
void invalidValue ();
void tooManyArguments ();
void tooFewArguments ();
void shapeArrayIsFull ();

// Helper functions
int shapeIndex (string name);
void deleteAllShapes ();
void deleteOneShape (string name);
void drawAllShapes ();
bool shapeNameExists (string name);
bool reservedWord(string name);
bool invalidType (string type);
bool tooFewOrInvalid (stringstream &line);
bool invalidPosition (int pos);
bool invalidRotation (int angle);
bool tooManyArgs (stringstream &line);

int main() {

    string line;
    string command;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);   // Get a line from standard input

    while (!cin.eof()) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so the flags are cleared
        stringstream lineStream (line);

        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;
        
        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here

        // Check if the command is a member of valid
        bool validCommand = false;
        for (int i = 0; i < 7; i++)
        {
            if (command == keyWordsList[i])
            {
                validCommand = true;
            }
        }
        
        // If the command was found in the list, select the command specific function
        if (validCommand)
        {
            if (command == "maxShapes") maxShapes(lineStream);
            else if (command == "create") create(lineStream);
            else if (command == "move") move(lineStream);
            else if (command == "rotate") rotate(lineStream);
            else if (command == "draw") draw(lineStream);
            else if (command == "delete") deleteShapes(lineStream);
        } else
        {
            // If the command was invalid, output error message and proceed to next iteration
            invalidCommand();
        }

        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);   // Get the command line
        
    }  // End input loop until EOF.
    
    return 0;
}

// MaxShapes function
// Dynamically allocates memory for the shape 'database'
void maxShapes (stringstream &line)
{
    // Get the size of the array
    line >> max_shapes;
    // Allocate the array
    shapesArray = new shape*[max_shapes];
    // Output success message
    cout << "New database: max shapes is " << max_shapes << endl;
}

// Create function
// Creates a shape object that will be pointed at by a pointer element in the shapes array
void create (stringstream &line)
{
    string name, type;
    int x_location, y_location, x_size, y_size;
    
    // Get the name of the shape that is being created
    line >> name;
    // Check if there was a missing argument or an input was invalid
    if (tooFewOrInvalid(line)) return;
    // Check that the name is not a command or a shape name
    if (reservedWord(name)) return;
    // Check that a shape with this name has not already been created
    if (shapeNameExists(name)){
        shapeNameExists ();
        return;
    }
    
    // Get the type of shape
    line >> type;
    // Check if there was a missing argument or an input was invalid
    if (tooFewOrInvalid(line)) return;
    // Check that it is a valid shape name
    if (invalidType(type)) return;
    
    // Get the location along the x axis for the shape
    line >> x_location;
    // Check if there was a missing argument or an input was invalid
    if (tooFewOrInvalid(line)) return;
    // Check that the location is a positive number
    if (invalidPosition(x_location)) return;
    
    // Get the location along the y axis for the shape
    line >> y_location;
    // Check if there was a missing argument or an input was invalid
    if (tooFewOrInvalid(line)) return;
    // Check that the location is a positive number
    if (invalidPosition(y_location)) return;

    // Get the size of the shape in the x direction
    line >> x_size;
    // Check if there was a missing argument or an input was invalid
    if (tooFewOrInvalid(line)) return;
    // Check that the size is a positive number
    if (invalidPosition(x_size)) return;
    
    // Get the size of the shape in the y direction
    line >> y_size;
    // Check if there was a missing argument or an input was invalid
    if (tooFewOrInvalid(line)) return;
    // Check that the size is a positive number
    if (invalidPosition(y_size)) return;
    
    // Check that there are no left over arguments
    if (tooManyArgs(line)) return;

    // Check that the array is not full
    if (max_shapes == shapeCount)
    {
        shapeArrayIsFull();
        return;
    }
    
    // If all input are correct and valid, create a new shape
    shapesArray[shapeCount] = new shape(name, type, x_location, y_location, x_size, y_size);
    // Output success message
    cout << "Created  " << name << ": " << type << " " << x_location << " " << y_location << " " << x_size << " " << y_size << endl;
    // Increment shapeCount to ensure correct reflection of array size
    shapeCount++;
}

// Moves a shape from current y and y coordinates to new input coordinates
void move (stringstream &line)
{
    string name;
    int x_location, y_location;
    
    // Get the name of the shape to be moved
    line >> name;
    // Check if there was a missing argument or an input was invalid
    if (tooFewOrInvalid(line)) return;
    // Check that the name of the shape exists in the database
    if (!shapeNameExists(name))
    {
        shapeNameNotFound(name);
        return;
    }

    // Get the location along the x axis for the shape
    line >> x_location;
    // Check if there was a missing argument or an input was invalid
    if (tooFewOrInvalid(line)) return;
    // Check that the location is a positive number
    if (invalidPosition(x_location)) return;
    
    // Get the location along the y axis for the shape
    line >> y_location;
    // Check if there was a missing argument or an input was invalid
    if (tooFewOrInvalid(line)) return;
    // Check that the location is a positive number
    if (invalidPosition(y_location)) return;

    // Check that there are no left over arguments
    if (tooManyArgs(line)) return;
    // If all inputs are correct and valid, move the shape and set new location
    shapesArray[shapeIndex(name)]->setXlocation(x_location);
    shapesArray[shapeIndex(name)]->setYlocation(y_location);
    // Output success message
    cout << "Moved " << name << " to " << x_location << " " << y_location << endl;
}

// Rotates a shape by a given degree value
void rotate (stringstream &line)
{
    string name;
    int angle;
    
    // Get the name of the shape to be rotated
    line >> name;
    // Check if there was a missing argument or an input was invalid
    if (tooFewOrInvalid(line)) return;
    // Check if the shape exists in the database
    if (!shapeNameExists(name))
    {
        shapeNameNotFound(name);
        return;
    }
    
    // Get the angle
    line >> angle;
    // Check if there was a missing argument or an input was invalid
    if (tooFewOrInvalid(line)) return;
    // Check that the angle is between 0 and 360
    if (invalidRotation(angle)) return;
    
    // Check that there are no left over arguments
    if (tooManyArgs(line)) return;
    // If all inputs are correct and valid, rotate the shape and set the rotation value
    shapesArray[shapeIndex(name)]->setRotate(angle);
    // Output the success message
    cout << "Rotated " << name << " by " << angle << "degrees " << endl;
}

// "Draws" the shapes
// What it really does it output the shape and it's attributes
void draw (stringstream &line)
{
    string secondArg;
    
    // Get the second argument after draw has been entered
    // Can be all or a shape name
    line >> secondArg;
    // Check if there was a missing argument or an input was invalid
    if (tooFewOrInvalid(line)) return;
    // Check if the second argument is all
    if (secondArg == keyWordsList[0])
    {
        // Check if there any arguments left
        if (tooManyArgs(line)) return;
        // If all inputs are correct and valid, draw all shapes in the database
        else drawAllShapes();  
    } else
    {
        // Check that the shape name exists in the database
        if (!shapeNameExists(secondArg))
        {
            shapeNameNotFound(secondArg);
            return;
        } else
        {
            // Check if there are any arguments left
            if (tooManyArgs(line)) return;
            // Output success message
            cout << "Drew " << shapesArray[shapeIndex(secondArg)]->getName() << endl;
            // If all inputs are correct and valid, draw the shape
            shapesArray[shapeIndex(secondArg)]->draw();
        }
    }
}

// Deletes all shapes from the database
void deleteShapes (stringstream &line)
{
    string secondArg;

    // Get the second argument
    // Could be all or a shape name
    line >> secondArg;
    // Check if there was a missing argument or an input was invalid
    if (tooFewOrInvalid(line)) return;
    // Check if the second argument is all
    if (secondArg == keyWordsList[0])
    {
        // Check if there are any arguments left
        if (tooManyArgs(line)) return;
        // If all inputs are correct and valid, delete all shapes
        else deleteAllShapes();
    } else
    {
        // Check if the shape name exists in the database
        if (!shapeNameExists(secondArg))
        {
            shapeNameNotFound(secondArg);
            return;
        } else
        {
            // Check if there are any arguments left
            if (tooManyArgs(line))  return;
            // If all inputs are correct and valid, delete the given shape
            else deleteOneShape(secondArg);
        }
    }
}

// Error functions that are called when their respective conditions are present
void invalidCommand () { cout << "Error: invalid command" << endl; }
void invalidArgument () { cout << "Error: invalid argument" << endl; }
void invalidShapeName () { cout << "Error: invalid shape name" << endl; }
void shapeNameExists () { cout << "Error: shape name exists" << endl; }
void shapeNameNotFound (string name) { cout << "Error: shape " << name << " not found" << endl;}
void invalidShapeType () { cout << "Error: invalid shape type" << endl; }
void invalidValue () { cout << "Error: invalid value" << endl; }
void tooManyArguments () { cout << "Error: too many arguments" << endl; }
void tooFewArguments () { cout << "Error: too few arguments" << endl; }
void shapeArrayIsFull () { cout << "Error: shape array full" << endl; }

// Finds the shape's index in the database array
int shapeIndex (string name)
{
    for (int i=0; i < shapeCount; i++)
    {
        // If the ith element's name is the same as the given line, return the index
        if (shapesArray[i]->getName() == name)
        {
            return i;
        }
    }
    return -1;
}

// Deletes all shapes incrementally from the database
void deleteAllShapes ()
{
    for (int i=0; i < shapeCount; i++)
    {
        // Make sure the element is not a null pointer
        if (shapesArray[i] != NULL)
        {
            // Delete what the element is pointing to
            delete shapesArray[i];
            // Delete the element/the pointer
            shapesArray[i] = NULL;
            // Decrement the shapeCount to accurately reflect the size of the shape array
            shapeCount--;
        }
    }
    // Output success message
    cout << "Deleted: all shapes" << endl;
}

// Deletes only the shape passed in from the database
void deleteOneShape (string name)
{
    // Make sure the element is not a null pointer
    if (shapesArray[shapeIndex(name)] != NULL)
    {
        // Output success message
        // Must do before deletion
        cout << "Deleted shape " << shapesArray[shapeIndex(name)]->getName() << endl;
        // Delete what the element is pointing to
        delete shapesArray[shapeIndex(name)];
        // Delete the element/the pointer
        shapesArray[shapeIndex(name)] = NULL;
        // Decrement the shapeCount to accurately reflect the size of the shape array
        shapeCount--;
    }
}

// Draws all shapes in database
void drawAllShapes ()
{
    cout << "Drew all shapes" << endl;
    for (int i=0; i < shapeCount; i++)
    {
        shapesArray[i]->draw();
    }
}

// Check if the name already exists for one of the shapes in the database
bool shapeNameExists (string name)
{
    for (int i = 0; i < shapeCount; i++)
    {
        if (name == shapesArray[i]->getName()) return true;
    }
    return false;
}

// Check if the name is a member of one of the restricted lists
// Checks if it is all, a command or a reserved shape name
bool reservedWord (string name)
{
    for (int i = 0; i < 3; i++)
    {
        // Checks if it is a shape name
        if (name == shapeTypesList[i])
        {
            invalidShapeName();
            return true;
        }
    }
    
    for (int i = 0; i < 7; i++)
    {
        // Checks if it is a command/key word
        if (name == keyWordsList[i])
        {
            invalidShapeName();
            return true;
        }
    }
    return false;
}

// Checks if the type of shape inputted is allowed
bool invalidType (string type)
{
    for (int i = 0; i < 3; i++)
    {
        if (type == shapeTypesList[i]) return false;
    }
    invalidShapeType();
    return true;
}

// Checks if there was an end of file character inputted
// If not it returns an invalid argument, as that is the other reason line would fail
bool tooFewOrInvalid (stringstream &line)
{
    if (line.fail())
    {
        if (line.eof()) tooFewArguments();
        else invalidArgument();
            return true;
    }
    return false;
}

// Check if the inputted position is greater or equal to 0
bool invalidPosition (int pos)
{
    if (pos < 0)
    {
        invalidValue();
        return true;
    }
    else return false;
}

// Check that the given rotation is between 0 and 360
bool invalidRotation (int angle)
{
    if (angle < 0 || angle > 360)
    {
        invalidValue();
        return true;
    }
    else return false;
}

// Tries a test variable to receive input to determine if there is anything left in the stream
bool tooManyArgs(stringstream &line)
{
    string test;
    
    line >> test;
    if (!line.fail())
    {
         tooManyArguments();
         return true;
    }
    return false;
}

