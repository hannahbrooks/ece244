#include "TreeDB.h"
#include "DBentry.h"
#include "TreeNode.h"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

// declarations for command functions
void handleInsert (stringstream &line, TreeDB& database);
void handleFind (stringstream &line, TreeDB& database);
void handleRemove (stringstream &line, TreeDB& database);
void handlePrintProbes (stringstream &line, TreeDB& database);
void handleRemoveAll (TreeDB& database);
void handleUpdateStatus (stringstream &line, TreeDB& database);

int main() {

    TreeDB database;
    string line;
    string command;

    // prompt for input
    cout << "> ";
    getline(cin, line);

    while (!cin.eof()) {
        
        stringstream lineStream (line);
	
	// read in first command
        lineStream >> command;

	// go to assigned function depending on command
        if (command == "insert") handleInsert (lineStream, database);
        else if (command == "find") handleFind(lineStream, database);
        else if (command == "remove") handleRemove(lineStream, database);
        else if (command == "printall") cout << database;
        else if (command == "printprobes") handlePrintProbes(lineStream, database);
        else if (command == "removeall") handleRemoveAll(database);
        else if (command == "countactive") database.countActive();
        else if (command == "updatestatus") handleUpdateStatus(lineStream, database);
        else cout << "Error: invalid command" << endl;
        
        cout << "> ";
        getline(cin, line);
    }

    return 0;
}

void handleInsert (stringstream &line, TreeDB& database) {
    string name;
    unsigned int IPaddress;
    string status;
    
    // read in values
    line >> name;
    line >> IPaddress;
    line >> status;

    // create a temporary DBentry and attempt insertion
    DBentry* temp = new DBentry(name, IPaddress, status == "active");

    // print appropriate message
    if (database.insert(temp)) cout << "Success" << endl;
    else {
        cout << "Error: entry already exists" << endl;
        delete temp;
    }
    
}

void handleFind (stringstream &line, TreeDB& database) {
    string name;
    line >> name;

    // if the name can be found, print the name, if not print error
    if (database.find(name) != NULL) cout << *(database.find(name));
    else cout << "Error: entry does not exist" << endl;
}

void handleRemove (stringstream &line, TreeDB& database) {
    string name;
    line >> name;
    
    // if the name exists, remove it, if not print error
    if (database.find(name) != NULL) {
        database.remove(name);
        cout << "Success" << endl;
    }
    else cout << "Error: entry does not exist" << endl;
}

void handlePrintProbes (stringstream &line, TreeDB& database) {
    string name;
    line >> name;

    // if the name exists, print its probes, if not print error
    if (database.find(name) != NULL)
        database.printProbes();
    else cout << "Error: entry does not exist" << endl;
}

void handleRemoveAll (TreeDB& database) {
    // clear the tree and print success message
    database.clear();
    cout << "Success" << endl;
}

void handleUpdateStatus (stringstream &line, TreeDB& database) {
    string name;
    string status;
    line >> name;
    line >> status;

    // if the name exists, set its status to the appropriate value
    // if not print error
    if (database.find(name) != NULL) {
        (database.find(name))->setActive(status == "active");
        cout << "Success" << endl;
    }
    else cout << "Error: entry does not exist" << endl;
}
