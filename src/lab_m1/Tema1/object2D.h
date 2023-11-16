#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{
    Mesh* CreateRectangle(const std::string& name, glm::vec3 center, float width, float height, glm::vec3 color, bool fill = false);
    Mesh* CreateSquare(const std::string &name, glm::vec3 center, float size, glm::vec3 color, bool fill = false);
    Mesh* CreateHeart(const std::string& name, glm::vec3 center, float size, glm::vec3 color, bool fill = false);
    Mesh* CreateStar(const std::string& name, glm::vec3 center, float scale, glm::vec3 color, bool fill = false);
    Mesh* CreateCannon(const std::string& name, glm::vec3 center, float size, glm::vec3 color, bool fill = false);
    Mesh* CreateEnemy(const std::string& name, glm::vec3 center, float size, glm::vec3 outerColor, glm::vec3 innerColor, bool fill = false);
}
