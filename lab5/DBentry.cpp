#include "DBentry.h"
#include <iostream>

// default constructor
DBentry:: DBentry() {}

// constructor
DBentry:: DBentry (string _name, unsigned int _IPaddress, bool _active) {
    this->name = _name;
    this->IPaddress = _IPaddress;
    this->active = _active;
}

// destructor
DBentry:: ~DBentry() {}

// set name
void DBentry:: setName(string _name) {
    this->name = _name;
}

// set IPaddress
void DBentry:: setIPaddress(unsigned int _IPaddress) {
    this->IPaddress = _IPaddress;
}

// set active
void DBentry:: setActive (bool _active) {
    this->active = _active;
}

// get name
string DBentry:: getName() const {
    return name;
}

// get IPaddress
unsigned int DBentry:: getIPaddress() const {
    return IPaddress;
}

// get active
bool DBentry:: getActive() const {
    return active;
}

// print entry
ostream& operator<< (ostream& out, const DBentry& rhs) {
    out << rhs.name << " : " << rhs.IPaddress << (rhs.active ? " : active" : " : inactive ") << endl;
}


