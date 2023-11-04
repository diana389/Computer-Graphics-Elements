#pragma once

#include <vector>
#include <string>

#include "core/engine.h"
#include "utils/gl_utils.h"
#include "components/simple_scene.h"

class GameObject {
public:
    // Constructors
    GameObject();
    GameObject(glm::vec2 center, glm::vec2 size, bool isDraggable, bool canPlaceObject, Mesh* mesh);

    glm::vec2 center;
    glm::vec2 size;
    bool isBeingDragged;
    bool isDraggable;
    bool canPlaceObject;
    bool isClicked;
    bool isClickable;
    bool isPlaced;
    Mesh* mesh;
};
