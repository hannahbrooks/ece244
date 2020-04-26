/*
 * This file was developed for the Fall 2018 instance of ECE244 at the University of Toronto.
 * Creator: Matthew J. P. Walker
 */


#include <galaxy-explorer/AsteroidsObserver.hpp>

void AsteroidsObserver::onAsteroidInRange(Asteroid asteroid) {
    // If you find an asteroid, add it to the list
    asteroid_list.insertAfter(asteroid_list.beforeEnd(), asteroid);
}

void AsteroidsObserver::onAsteroidUpdate(Asteroid asteroid) {
    // Get the head of the list
    AsteroidListItem* prev = asteroid_list.beforeBegin();
    // Get the start of the list to begin iteration
    AsteroidListItem* temp = asteroid_list.begin();
    
    while (temp != nullptr) {
        // Get rid of everything after prev and insert the new asteroid
        if (temp->getData().getID() == asteroid.getID()) {
            asteroid_list.eraseAfter(prev);
            asteroid_list.insertAfter(prev, asteroid);
            break;
        } else {
            // Go to the next asteroid
            temp = temp->getNext();
            prev = prev->getNext();
        }
    }
}

// Same as on update, but with just deletion
void AsteroidsObserver::onAsteroidOutOfRange(Asteroid asteroid) {
    AsteroidListItem* prev = asteroid_list.beforeBegin();
    AsteroidListItem* temp = asteroid_list.begin();
    
    while (temp != nullptr) {
        if (temp->getData().getID() == asteroid.getID()) {
            asteroid_list.eraseAfter(prev);
            break;
        } else {
            temp = temp->getNext();
            prev = prev->getNext();
        }
    }
}

// Same as out of range
void AsteroidsObserver::onAsteroidDestroy(Asteroid asteroid) {
    AsteroidListItem* prev = asteroid_list.beforeBegin();
    AsteroidListItem* temp = asteroid_list.begin();
    
    while (temp != nullptr) {
        if (temp->getData().getID() == asteroid.getID()) {
            asteroid_list.eraseAfter(prev);
            break;
        } else {
            temp = temp->getNext();
            prev = prev->getNext();
        }
    }
}
