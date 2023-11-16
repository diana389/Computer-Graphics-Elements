#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

Mesh* object2D::CreateRectangle(
    const std::string& name,
    glm::vec3 center,
    float width,
    float height,
    glm::vec3 color,
    bool fill)
{

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(-width / 2.f , -height / 2.f , 0), color),
        VertexFormat(center + glm::vec3(width / 2.f, -height / 2.f , 0), color),
        VertexFormat(center + glm::vec3(width / 2.f , height / 2.f , 0), color),
        VertexFormat(center + glm::vec3(-width / 2.f , height / 2.f , 0), color)
    };

    Mesh* rect = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rect->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    rect->InitFromData(vertices, indices);
    return rect;
}

Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 center,
    float size,
    glm::vec3 color,
    bool fill)
{

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(-size / 2.f , -size / 2.f , 0), color),
        VertexFormat(center + glm::vec3(size / 2.f, -size / 2.f , 0), color),
        VertexFormat(center + glm::vec3(size / 2.f , size / 2.f , 0), color),
        VertexFormat(center + glm::vec3(-size / 2.f , size / 2.f , 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateHeart(
    const std::string& name,
    glm::vec3 center,
    float size,
    glm::vec3 color,
    bool fill)
{

    std::vector<VertexFormat> vertices;


    float x = size * (0);
    float y = size * (-15);
    vertices.emplace_back(glm::vec3(center.x + x, center.y + y, center.z), color);

    for (float t = 0.0f; t <= 3.0f * glm::pi<float>() / 4.0f; t += 0.01f) {
        float x = size * (16 * pow(sin(t), 3));
        float y = size * (13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t));

        vertices.emplace_back(glm::vec3(center.x + x, center.y + y, center.z), color);
    }

    for (float t = 5.0f * glm::pi<float>() / 4.0f; t <= 2 * glm::pi<float>(); t += 0.01f) {
        float x = size * (16 * pow(sin(t), 3));
        float y = size * (13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t));

        vertices.emplace_back(glm::vec3(center.x + x, center.y + y, center.z), color);
    }

    Mesh* heart = new Mesh(name);
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < vertices.size(); ++i) {
        indices.push_back(i);
    }

    if (!fill) {
        heart->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Fill the heart shape by using GL_TRIANGLE_FAN
        heart->SetDrawMode(GL_TRIANGLE_FAN);
    }

    heart->InitFromData(vertices, indices);
    return heart;

}

Mesh* object2D::CreateStar(
    const std::string& name,
    glm::vec3 center,
    float scale,
    glm::vec3 color,
    bool fill)
{

    Mesh* star = new Mesh(name);
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    float angleIncrement = 2 * glm::pi<float>() / 5;
    bool isOuterPoint = true;

    vertices.emplace_back(glm::vec3(center.x, center.y, center.z), color);

    for (int i = 0; i < 11; i++) {
        float radius = isOuterPoint ? (scale * 0.5) : (scale * 0.25);
        float angle = i * angleIncrement;

        float x = center.x + radius * glm::cos(angle);
        float y = center.y + radius * glm::sin(angle);
        vertices.emplace_back(glm::vec3(x, y, center.z), color);

        isOuterPoint = !isOuterPoint;
    }

    for (unsigned int i = 0; i < vertices.size(); ++i) {
        indices.push_back(i);
    }

    if (!fill) {
        star->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Fill the star shape by using GL_TRIANGLE_FAN
        star->SetDrawMode(GL_TRIANGLE_FAN);
    }

    star->InitFromData(vertices, indices);
    return star;
}

Mesh* object2D::CreateCannon(
    const std::string& name,
    glm::vec3 center,
    float size,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(0, size / 2.f, 1), color),
        VertexFormat(center + glm::vec3(-size / 4.f, 0, 1), color),
        VertexFormat(center + glm::vec3(size / 4.f, 0, 1), color),
        VertexFormat(center + glm::vec3(0, -size / 2.f, 1), color),
        VertexFormat(center + glm::vec3(-size / 4.f, 0, 1), color),
        VertexFormat(center + glm::vec3(size / 4.f, 0, 1), color),

        VertexFormat(center + glm::vec3(0, size / 8.f, 1), color),
        VertexFormat(center + glm::vec3(0, -size / 8.f, 1), color),
        VertexFormat(center + glm::vec3(size / 2.f, size / 8.f, 1), color),
        VertexFormat(center + glm::vec3(0, -size / 8.f, 1), color),
        VertexFormat(center + glm::vec3(size / 2.f, size / 8.f, 1), color),
        VertexFormat(center + glm::vec3(size / 2.f, -size / 8.f, 1), color)
    };

    Mesh* cannon = new Mesh(name);
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < vertices.size(); ++i) {
        indices.push_back(i);
    }

    if (!fill) {
       cannon->SetDrawMode(GL_LINE_LOOP);
    }
    else {
       cannon->SetDrawMode(GL_TRIANGLES);
    }

    cannon->InitFromData(vertices, indices);
    return cannon;
}

Mesh* object2D::CreateEnemy(
    const std::string& name,
    glm::vec3 center,
    float size,
    glm::vec3 outerColor,
    glm::vec3 innerColor,
    bool fill)
{
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    for (int i = 0; i < 6; i++) {
        float angle = glm::radians(60.0f * i);
        glm::vec3 vertexPosition = center + glm::vec3(size * cos(angle), size * sin(angle), 2);
        vertices.emplace_back(vertexPosition, outerColor);
        indices.push_back(i);
    }

    Mesh* hexagon = new Mesh(name);

    if (!fill) {
        hexagon->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Create triangles by connecting vertices
        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(2);
        indices.push_back(0);
        indices.push_back(2);
        indices.push_back(3);
        indices.push_back(0);
        indices.push_back(3);
        indices.push_back(4);
        indices.push_back(0);
        indices.push_back(4);
        indices.push_back(5);
    }

    for (int i = 0; i < 6; i++) {
        float angle = glm::radians(60.0f * i);
        glm::vec3 vertexPosition = center + glm::vec3((0.75f * size) * cos(angle), (0.75f * size) * sin(angle), 3);
        vertices.emplace_back(vertexPosition, innerColor);
        indices.push_back(i);
    }

    if (!fill) {
        hexagon->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Create triangles by connecting vertices
        indices.push_back(6);
        indices.push_back(7);
        indices.push_back(8);
        indices.push_back(6);
        indices.push_back(8);
        indices.push_back(9);
        indices.push_back(6);
        indices.push_back(9);
        indices.push_back(10);
        indices.push_back(6);
        indices.push_back(10);
        indices.push_back(11);
    }

    hexagon->InitFromData(vertices, indices);
    return hexagon;
}