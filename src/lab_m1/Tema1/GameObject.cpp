#include "GameObject.h"

// Default constructor
GameObject::GameObject() {
    this->center = glm::vec2(0, 0);     
    this->size = glm::vec2(1, 1);
    this->isDraggable = false;
    this->canPlaceObject = false;
    this->mesh = NULL;
    this->isBeingDragged = false;
    this->isClicked = false;
    this->isClickable = false;
    this->isPlaced = false;
}

// Constructor to initialize the class members
GameObject::GameObject(glm::vec2 center, glm::vec2 size, bool isDraggable, bool canPlaceObject, Mesh* mesh) {
    this->center = center;           
    this->size = size;
    this->isDraggable = isDraggable;
    this->canPlaceObject = canPlaceObject;
    this->mesh = mesh;
    this->isBeingDragged = false;
    this->isClicked = false;
    this->isClickable = false;
    this->isPlaced = false;
}
