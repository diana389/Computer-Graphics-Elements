#pragma once

#include <vector>
#include <string>

#include "core/engine.h"
#include "utils/gl_utils.h"
#include "components/simple_scene.h"

	struct GameObject {
		glm::vec2 center;
		glm::vec2 size;
		bool isBeingDragged;
		bool isDraggable;
		bool canPlaceObject;
		bool isClicked; // fara
		bool isClickable;
		bool isPlaced; // fara
		Mesh* mesh;
	};
