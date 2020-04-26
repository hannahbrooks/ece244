#include <galaxy-explorer/AsteroidList.hpp>


AsteroidListItem::AsteroidListItem() {
	this->next = nullptr;
	this->data = nullptr;
}

AsteroidListItem::AsteroidListItem(Asteroid a) {
	this->next = nullptr;
        this->data = new Asteroid(a);
}

AsteroidListItem::~AsteroidListItem() {
    // Delete the asteroid itself
    if (this->data != nullptr) {
        delete this->data;
    }
}

// Creating a new list and assigning the value of head to a null pointer
AsteroidList::AsteroidList() {
    head.setNext(nullptr);
}

AsteroidList::AsteroidList(const AsteroidList& src) {
    // The functions in this class are listed in a suggested order of implementation,
    // except for this one and the destructor (because you should put all your constructors together)
    
    // Get a pointer to the beginning of the list
    const AsteroidListItem* srcTemp = src.begin();
    // Get a pointer to the new item
    AsteroidListItem* newItem;
    AsteroidListItem* last = nullptr;
    
    while (srcTemp != nullptr) {
        // Create an instance of that new node with whatever source's current node has
        newItem = new AsteroidListItem(srcTemp->getData());
        // Case for the first node in the list
        if (last == nullptr) head.setNext(newItem);
        else last-> setNext(newItem); // Add the node to the list
        srcTemp = srcTemp->getNext();
        // Iterate to the next node
        last = newItem;
        // Adjust the end  
    }
}

AsteroidList::~AsteroidList() {
    // The functions in this class are listed in a suggested order of implementation,
    // except for this one and the copy constructor (because you should put all your constructors together).
    AsteroidListItem* temp;
    // Traverse the list and delete each node in the list
    while (head.hasNext()) {
        temp = head.getNext();
        head.setNext(temp->getNext());
        delete temp;
    }
    head.setNext(nullptr);
}

// Add an asteroid node to the front of a list
void AsteroidList::pushFront(Asteroid e) {
    AsteroidListItem* eToAddToList = new AsteroidListItem(e);
    
    // Take whatever the new asteroid is pointing to and make it the first
    // asteroid in the list
    eToAddToList->setNext(head.getNext());
    // Set head's next to the new asteroid
    head.setNext(eToAddToList);
}

Asteroid& AsteroidList::front() {
    // Get a pointer to head
    AsteroidListItem* headPtr = beforeBegin();
    // If the list is empty, return head's data. If not return next's data
    if (headPtr->hasNext()) headPtr = headPtr->getNext();
    return headPtr->getData();
}          

const Asteroid& AsteroidList::front() const {
    // Same as above but with const type
    const AsteroidListItem* headPtr = beforeBegin();
    // if the list is empty, return head's data, if not return next's data
    if (headPtr->hasNext()) headPtr = headPtr->getNext();
    return headPtr->getData();
}

bool AsteroidList::isEmpty() const {
    // Return true if head has no next. If it does, return false.
    return !head.hasNext();
}

int AsteroidList::size() const {
    int count = 0;
    // Get a pointer to head
    const AsteroidListItem* curr = beforeBegin();
    
    // Traverse each node and increment count
    while (curr->hasNext()) {
        curr = curr->getNext();
        count++;
    }
    return count;
}

AsteroidListItem* AsteroidList::beforeBegin() {
    // Get the address of head (a pointer to head)
    AsteroidListItem* headPtr = &head;
    return headPtr;
}

const AsteroidListItem* AsteroidList::beforeBegin() const {
    // Same as above but with const type
    const AsteroidListItem* headPtr = &head;
    return headPtr;
}

AsteroidListItem* AsteroidList::begin() {
    // Get a pointer to head and then return it's next (even if it is null)
    AsteroidListItem* firstAsteroid = beforeBegin();
    return firstAsteroid->getNext();
}

const AsteroidListItem* AsteroidList::begin() const {
    // Same as above but with const type
    const AsteroidListItem* firstAsteroid = beforeBegin();
    return firstAsteroid->getNext();
}

AsteroidListItem* AsteroidList::beforeEnd() {
    // Get a pointer to head
    AsteroidListItem* temp = beforeBegin();
    // Traverse the list until you get to the end, then return it
    while (temp->hasNext()) {
        temp = temp->getNext();
    }
    return temp;
}

const AsteroidListItem* AsteroidList::beforeEnd() const {
    // Same as above but with const type
    const AsteroidListItem* temp = beforeBegin();
    while (temp->hasNext()) {
        temp = temp->getNext();
    }
    return temp;
}

// Return end which is a pointer to NULL
AsteroidListItem* AsteroidList::end() {
    return nullptr;
}

// Same as above but with const type
const AsteroidListItem* AsteroidList::end() const {
    return nullptr;
}

AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, Asteroid e) {
    // Make e into an asteroid list item
    AsteroidListItem* eToAddToList = new AsteroidListItem(e);
    
    // Point e to prev's next and then point prev to e
    eToAddToList->setNext(prev->getNext());
    prev->setNext(eToAddToList);
    
    return eToAddToList;
}

AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, const AsteroidList& others) {
    // Make a new list with others
    AsteroidList* othersToAdd = new AsteroidList(others);
    // Get pointer to the beginning and the end of others
    AsteroidListItem* first = othersToAdd->begin();
    AsteroidListItem* end = othersToAdd->beforeEnd();
    
    // Point others' end to prev's next and then point prev to the beginning of others
    end->setNext(prev->getNext());
    prev->setNext(first);
}

AsteroidListItem* AsteroidList::eraseAfter(AsteroidListItem* prev) {
    // Get the node right after prev
    AsteroidListItem* temp = prev->getNext();
    // Set prev's next to the node after it.
    prev->setNext(temp->getNext());
    
    // Delete prev's old next
    delete temp;
    return prev;
}

void AsteroidList::clear() {
    AsteroidListItem* temp;
    
    // Traverse the list until head points to nothing
    while(head.hasNext()) {
        // Delete the node after and shift
        temp = head.getNext();
        head.setNext(temp->getNext());
        delete temp;
    }
    // Make sure that head will be pointing to nothing
    head.setNext(nullptr);
}

AsteroidList& AsteroidList::operator=(const AsteroidList& src) {
    // Get rid of everything in the current list
    this->clear();
    
    // Get the beginning of the list and a pointer to any item
    const AsteroidListItem* srcTemp = src.begin();
    AsteroidListItem* newItem;
    AsteroidListItem* last = nullptr;
    
    // Traverse the list and copy each node
    while(srcTemp != nullptr) {
        // Make an instance of each new asteroid item
        newItem = new AsteroidListItem(srcTemp->getData());
        // Case for the first node in the list
        if (last == nullptr) head.setNext(newItem);
        else last->setNext(newItem); // Add the node to the list
        // Iterate to the next node
        srcTemp = srcTemp->getNext();
        // Adjust the end
        last = newItem;
    }
    return (*this);
}