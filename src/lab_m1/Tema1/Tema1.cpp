#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    // initialize variables
    glm::vec3 corner = glm::vec3(0, 0, 0);

    // RECTANGLE
    Mesh* rect = object2D::CreateRectangle("rect", corner, 100, 400, jordyBlue, true);
    AddMeshToList(rect);

    // GREEN SQUARES
    Mesh* square = object2D::CreateSquare("square", corner, 100, lightGreen, true);
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
        {
            std::string name = "square" + std::to_string(j) + std::to_string(i);
            AddMeshToList(square);
            obj = Square(glm::vec2(200 + 150 * i, 100 + 150 * j), glm::vec2(100, 100), square);
            gameObjects[name] = obj;
            // AddToMap(glm::vec2(200 + 150 * i, 100 + 150 * j), glm::vec2(100, 100), name, square);
        }

    // RED HEARTS
    Mesh* heart = object2D::CreateHeart("heart", corner, 3, red, true);
    for (int i = 0; i < lives; i++)
    {
        std::string name = "heart" + std::to_string(i);
		AddMeshToList(heart);
        obj = GameObject(glm::vec2(950 + 125 * i, 650), glm::vec2(100, 100), heart);
        gameObjects[name] = obj;
        // AddToMap(glm::vec2(950 + 125 * i, 650), glm::vec2(100, 100), name, heart);
	}

    // CANNON OUTLINE
    Mesh* cannon_outline = object2D::CreateSquare("cannon_outline", corner, 150, white, false);
	AddMeshToList(cannon_outline);

    // PINK STAR
    Mesh* star = object2D::CreateStar("star", glm::vec3(0, 0, 5), 60, lavanderPink, true);
    AddMeshToList(star);
    obj = Star(glm::vec2(900, 300), glm::vec2(100, 100), star);
    gameObjects["star"] = obj;
    // AddToMap(glm::vec2(900, 300), glm::vec2(100, 100), "star", star);

    // CANNONS TO PICK
    // orange cannon
    Mesh* orange_cannon = object2D::CreateCannon("orange_cannon", corner, 100, orange, true);
    AddMeshToList(orange_cannon);
    obj = Cannon(glm::vec2(100, 625), glm::vec2(100, 100), orange_cannon, orange);
    gameObjects["orange_cannon"] = obj;
    // AddToMap(glm::vec2(100, 625), glm::vec2(100, 100), "orange_cannon", orange_cannon);

    // blue cannon
    Mesh* blue_cannon = object2D::CreateCannon("blue_cannon", corner, 100, blue, true);
    AddMeshToList(blue_cannon);
    obj = Cannon(glm::vec2(300, 625), glm::vec2(100, 100), blue_cannon, blue);
    gameObjects["blue_cannon"] = obj;
    // AddToMap(glm::vec2(300, 625), glm::vec2(100, 100), "blue_cannon", blue_cannon);

    // yellow cannon
    Mesh* yellow_cannon = object2D::CreateCannon("yellow_cannon", corner, 100, yellow, true);
    AddMeshToList(yellow_cannon);
    obj = Cannon(glm::vec2(500, 625), glm::vec2(100, 100), yellow_cannon, yellow);
    gameObjects["yellow_cannon"] = obj;
    // AddToMap(glm::vec2(500, 625), glm::vec2(100, 100), "yellow_cannon", yellow_cannon);

    // purple cannon
    Mesh* purple_cannon = object2D::CreateCannon("purple_cannon", corner, 100, purple, true);
    AddMeshToList(purple_cannon);
    obj = Cannon(glm::vec2(700, 625), glm::vec2(100, 100), purple_cannon, purple);
    gameObjects["purple_cannon"] = obj;
    // AddToMap(glm::vec2(700, 625), glm::vec2(100, 100), "purple_cannon", purple_cannon);

    // GREY STARS
    Mesh* star_grey = object2D::CreateStar("star_grey", glm::vec3(0, 0, 0), 40, lightGray, true);
    AddMeshToList(star_grey);
    for (int i = 0; i < starsCollected; i++)
    {
        obj = GameObject(glm::vec2(900 + 50 * i, 525), glm::vec2(40, 40), meshes["star_grey"]);
        gameObjects["star_grey" + std::to_string(i)] = obj;
    }

    // LAUNCHED STARS
    Mesh* snow_star = object2D::CreateStar("snow_star", glm::vec3(0, 0, 4), 40, snow, true);
    AddMeshToList(snow_star);

    // ENEMIES
    // purple enemy
    Mesh* enemy_purple = object2D::CreateEnemy("enemy_purple", corner, 50, purple, coolGray, true);
    AddMeshToList(enemy_purple);

    // blue enemy
    Mesh* enemy_blue = object2D::CreateEnemy("enemy_blue", corner, 50, blue, jordyBlue, true);
    AddMeshToList(enemy_blue);

    // yellow enemy
    Mesh* enemy_yellow = object2D::CreateEnemy("enemy_yellow", corner, 50, yellow, lightGreen, true);
    AddMeshToList(enemy_yellow);

    // orange enemy
    Mesh* enemy_orange = object2D::CreateEnemy("enemy_orange", corner, 50, orange, hunyadiYellow, true);
    AddMeshToList(enemy_orange);
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(46.0/255, 40.0/255, 42.0/255, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);

    // render permanent objects

    // RECTANGLE
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(75, 250);

    RenderMesh2D(meshes["rect"], shaders["VertexColor"], modelMatrix);

    // CANNON OUTLINE
    for (int i = 0; i < 4; i++)
	    {
		    modelMatrix = glm::mat3(1);
		    modelMatrix *= transform2D::Translate(125 + 200 * i, 625);

		    RenderMesh2D(meshes["cannon_outline"], shaders["VertexColor"], modelMatrix);
	    }

    // GREY STARS
    // array of positions for the grey stars
    glm::vec2 starPositions[] = {
        glm::vec2(75, 525),
        glm::vec2(275, 525),
        glm::vec2(325, 525),
        glm::vec2(475, 525),
        glm::vec2(525, 525),
        glm::vec2(675, 525),
        glm::vec2(725, 525),
        glm::vec2(775, 525)
    };

    // render grey stars
    for (int i = 0; i < 8; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(starPositions[i].x, starPositions[i].y);

		RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);
    }
}

//void Tema1::RenderPermanentObjects()
//{
//    GameObject obj;
//
//    // rectangle
//    modelMatrix = glm::mat3(1);
//    modelMatrix *= transform2D::Translate(75, 250);
//
//    modelMatrix *= transform2D::Scale(1, 4);
//    RenderMesh2D(meshes["rect"], shaders["VertexColor"], modelMatrix);
//
//    // green squares
//    for (int i = 0; i < 3; i++)
//        for (int j = 0; j < 3; j++)
//        {
//            std::string name = "square" + std::to_string(i) + std::to_string(j);
//            obj = gameObjects[name];
//
//            modelMatrix = glm::mat3(1);
//            modelMatrix *= transform2D::Translate(obj.center.x,obj.center.y);
//
//            RenderMesh2D(meshes[name], shaders["VertexColor"], modelMatrix);
//        }
//
//    // cannon outline
//    for (int i = 0; i < 4; i++)
//    {
//        modelMatrix = glm::mat3(1);
//        modelMatrix *= transform2D::Translate(125 + 200 * i, 625);
//
//        RenderMesh2D(meshes["cannon_outline"], shaders["VertexColor"], modelMatrix);
//    }
//
//    // yellow star
//    obj = gameObjects["star"];
//
//    modelMatrix = glm::mat3(1);
//    modelMatrix *= transform2D::Translate(obj.center.x, obj.center.y);
//
//    if(!obj.isClicked)
//		RenderMesh2D(obj.mesh, shaders["VertexColor"], modelMatrix);
//
//    // cannons_to_pick
//    // orange cannon
//    modelMatrix = glm::mat3(1);
//    modelMatrix *= transform2D::Translate(100, 625);
//
//    RenderMesh2D(meshes["orange_cannon"], shaders["VertexColor"], modelMatrix);
//
//    // blue cannon
//    modelMatrix = glm::mat3(1);
//    modelMatrix *= transform2D::Translate(300, 625);
//
//    RenderMesh2D(meshes["blue_cannon"], shaders["VertexColor"], modelMatrix);
//
//    // yellow cannon
//    modelMatrix = glm::mat3(1);
//    modelMatrix *= transform2D::Translate(500, 625);
//
//    RenderMesh2D(meshes["yellow_cannon"], shaders["VertexColor"], modelMatrix);
//
//
//    // purple cannon
//    modelMatrix = glm::mat3(1);
//    modelMatrix *= transform2D::Translate(700, 625);
//
//    RenderMesh2D(meshes["purple_cannon"], shaders["VertexColor"], modelMatrix);
//
//    // grey stars
//
//    // orange cannon
//    modelMatrix = glm::mat3(1);
//    modelMatrix *= transform2D::Translate(75, 525);
//
//    RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);
//
//    // blue cannon
//    modelMatrix = glm::mat3(1);
//    modelMatrix *= transform2D::Translate(275, 525);
//
//    RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);
//
//    modelMatrix = glm::mat3(1);
//    modelMatrix *= transform2D::Translate(325, 525);
//
//    RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);
//
//    // yellow cannon
//    modelMatrix = glm::mat3(1);
//    modelMatrix *= transform2D::Translate(475, 525);
//
//    RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);
//
//    modelMatrix = glm::mat3(1);
//    modelMatrix *= transform2D::Translate(525, 525);
//
//    RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);
//
//    // purple cannon
//    modelMatrix = glm::mat3(1);
//    modelMatrix *= transform2D::Translate(675, 525);
//
//    RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);
//
//    modelMatrix = glm::mat3(1);
//    modelMatrix *= transform2D::Translate(725, 525);
//
//    RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);
//
//    modelMatrix = glm::mat3(1);
//    modelMatrix *= transform2D::Translate(775, 525);
//
//    RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);
//    // red hearts
//    for (int i = 0; i < lives; i++)
//    {
//        modelMatrix = glm::mat3(1);
//        modelMatrix *= transform2D::Translate(950 + 125 * i, 650);
//
//        RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
//    }
//
//    // enemy
//    modelMatrix = glm::mat3(1);
//    modelMatrix *= transform2D::Translate(1000, 100);
//
//    RenderMesh2D(meshes["enemy_purple"], shaders["VertexColor"], modelMatrix);
//
//    // enemy2
//    modelMatrix = glm::mat3(1);
//    modelMatrix *= transform2D::Translate(1000, 300);
//
//    RenderMesh2D(meshes["enemy_blue"], shaders["VertexColor"], modelMatrix);
//
//    // cannon
//    obj = gameObjects["cannon"];
//    modelMatrix = glm::mat3(1);
//    modelMatrix *= transform2D::Translate(obj.center.x, obj.center.y);
//
//    if (!obj.isClicked)
//        RenderMesh2D(obj.mesh, shaders["VertexColor"], modelMatrix);
//}

bool Tema1::CheckCollision(glm::vec2 center1, glm::vec2 size1, glm::vec2 center2, glm::vec2 size2)
{
	float x1 = center1.x;
	float y1 = center1.y;
	float x2 = center2.x;
	float y2 = center2.y;

	float dist = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));

	float r1 = size1.x / 2.f;
	float r2 = size2.x / 2.f;
    float r3 = size1.y / 2.f;
    float r4 = size2.y / 2.f;

	if (dist <= r1 + r2 && dist <= r3 + r4)
		return true;
	else
		return false;
}


void Tema1::Update(float deltaTimeSeconds)
{
    std::vector<std::string> objectsToRemove;

    for (auto& pair : gameObjects) 
    {
        const std::string& objName = pair.first;
        GameObject& obj = pair.second;

        modelMatrix = glm::mat3(1);

        if (objName.compare(0, 5, "enemy") == 0)
        {
            obj.center.x -= 20 * deltaTimeSeconds;
        }

        if (objName.compare(0, 9, "snow_star") == 0)
        {
			obj.center.x += 100 * deltaTimeSeconds;
            angularStep -= 2 * deltaTimeSeconds;

            modelMatrix *= transform2D::Translate(obj.center.x, obj.center.y);
            modelMatrix *= transform2D::Rotate(angularStep);
            modelMatrix *= transform2D::Translate(-obj.center.x, -obj.center.y);

            for (auto& pair2 : gameObjects)
            {
				const std::string& objName2 = pair2.first;
				GameObject& obj2 = pair2.second;

                if (objName2.compare(0, 5, "enemy") == 0)
                {
                    if (CheckCollision(obj.center, obj.size, obj2.center, obj2.size))
                    {
						objectsToRemove.push_back(objName);
                        obj2.strength--;

                        if (obj2.strength == 0)
							objectsToRemove.push_back(objName2);

						break;
					}
				}
			}
		}

        if (obj.center.x < 0 || obj.center.x > 1270) {
            objectsToRemove.push_back(objName);
            std::cout << "lives: " << lives << std::endl;
            gameObjects.erase("heart" + std::to_string(--lives));
        }

        modelMatrix *= transform2D::Translate(obj.center.x, obj.center.y);

		RenderMesh2D(obj.mesh, shaders["VertexColor"], modelMatrix);

    }

    // Remove the objects outside of the loop
    for (const std::string& objname : objectsToRemove) 
        gameObjects.erase(objname);

    if (!line0.cannons.empty() && !line0.enemies.empty() && !(time % 250)) {
        auto pair = line0.cannons.begin();
        const std::string& objName = pair->first;
        GameObject& obj = pair->second;

        GameObject snow_star = GameObject(glm::vec2(obj.center.x + 50, obj.center.y), glm::vec2(50, 50), meshes["snow_star"]);
        gameObjects["snow_star" + std::to_string(starsLaunched++)] = snow_star;
    }

    if (!line1.cannons.empty() && !line1.enemies.empty() && !(time % 250))
    {
		auto pair = line1.cannons.begin();
		const std::string& objName = pair->first;
		GameObject& obj = pair->second;

		GameObject snow_star = GameObject(glm::vec2(obj.center.x + 50, obj.center.y), glm::vec2(50, 50), meshes["snow_star"]);
		gameObjects["snow_star" + std::to_string(starsLaunched++)] = snow_star;
	}

    if (!line2.cannons.empty() && !line2.enemies.empty() && !(time % 250))
    {
        auto pair = line2.cannons.begin();
        const std::string& objName = pair->first;
        GameObject& obj = pair->second;

        GameObject snow_star = GameObject(glm::vec2(obj.center.x + 50, obj.center.y), glm::vec2(50, 50), meshes["snow_star"]);
        gameObjects["snow_star" + std::to_string(starsLaunched++)] = snow_star;
    }

    time++;

    if (!(time % 500))
    {
        int y = 100 + rand() % 400;
        int x = 100 + rand() % 1000;
        // AddToMap(glm::vec2(x, y), glm::vec2(100, 100), "star" + std::to_string(starsCount++), meshes["star"]);
        obj = Star(glm::vec2(x, y), glm::vec2(100, 100), meshes["star"]);
        gameObjects["star" + std::to_string(starsCount++)] = obj;
    }

    if (!(time % 600))
    {
        // random enemy
        int color = rand() % 4;
        int row = rand() % 3;
        std::string name;

        switch (color) {
        case 0:
            name = "enemy_orange" + std::to_string(enemyID++);
            // AddToMap(glm::vec2(1270, 100 + 150 * row), glm::vec2(100, 100), name, meshes["enemy_orange"]);
            obj = Enemy(glm::vec2(1270, 100 + 150 * row), glm::vec2(100, 100), meshes["enemy_orange"], orange);
            gameObjects[name] = obj;
            break;
        case 1:
            name = "enemy_blue" + std::to_string(enemyID++);
            // AddToMap(glm::vec2(1270, 100 + 150 * row), glm::vec2(100, 100), name, meshes["enemy_blue"]);
            obj = Enemy(glm::vec2(1270, 100 + 150 * row), glm::vec2(100, 100), meshes["enemy_blue"], blue);
            gameObjects[name] = obj;
            break;
        case 2:
            name = "enemy_yellow" + std::to_string(enemyID++);
            // AddToMap(glm::vec2(1270, 100 + 150 * row), glm::vec2(100, 100), name, meshes["enemy_yellow"]);
            obj = Enemy(glm::vec2(1270, 100 + 150 * row), glm::vec2(100, 100), meshes["enemy_yellow"], yellow);
            gameObjects[name] = obj;
            break;
        case 3:
            name = "enemy_purple" + std::to_string(enemyID++);
            // AddToMap(glm::vec2(1270, 100 + 150 * row), glm::vec2(100, 100), name, meshes["enemy_purple"]);
            obj = Enemy(glm::vec2(1270, 100 + 150 * row), glm::vec2(100, 100), meshes["enemy_purple"], purple);
            gameObjects[name] = obj;
            break;
        }

        switch (row) {
        case 0:
            line0.enemies[name] = gameObjects[name];
            break;
        case 1:
            line1.enemies[name] = gameObjects[name];
			break;
        case 2:
            line2.enemies[name] = gameObjects[name];
            break;
        }

        printLines();
    }
}

//void Tema1::AddToMap(glm::vec2 center, glm::vec2 size,const std::string& name, Mesh* mesh)
//{
//    if (mesh == nullptr)
//        throw std::runtime_error("Mesh is null");
//
//    GameObject obj;
//
//    if(mesh == meshes["orange_cannon"] || mesh == meshes["blue_cannon"] || mesh == meshes["yellow_cannon"] || mesh == meshes["purple_cannon"])
//        obj = Cannon(center, size, mesh);
//    
//    if (mesh == meshes["star"])
//        obj = Star(center, size, mesh);
//
//    if (mesh == meshes["enemy_orange"] || mesh == meshes["enemy_blue"] || mesh == meshes["enemy_yellow"] || mesh == meshes["enemy_purple"])
//		obj = Enemy(center, size, mesh);
//
//    if(mesh == meshes["square"])
//		obj = Square(center, size, mesh);
//
//    if(mesh == meshes["heart"])
//		obj = GameObject(center, size, mesh);
//
//    if(mesh == meshes["star_grey"])
//        obj = GameObject(center, size, mesh);
//
//    gameObjects[name] = obj;
// }

void Tema1::printLines()
{
    std::cout << "First line: ";
    std::cout << "Cannons: ";
    for (auto& pair : line0.cannons)
		std::cout << pair.first << " ";

    std::cout << "Enemies: ";
	for (auto& pair : line0.enemies)
        std::cout<< pair.first << " ";

    std::cout << std::endl;

    std::cout << "Second line: ";
    std::cout << "Cannons: ";
    for (auto& pair : line1.cannons)
        std::cout << pair.first << " ";

    std::cout << "Enemies: ";
    for (auto& pair : line1.enemies)
		std::cout << pair.first << " ";

    std::cout << std::endl;

	std::cout << "Third line: ";
	std::cout << "Cannons: ";
	for (auto& pair : line2.cannons)
		std::cout << pair.first << " ";

	std::cout << "Enemies: ";
	for (auto& pair : line2.enemies)
		std::cout << pair.first << " ";

	std::cout << std::endl;
}


void Tema1::FrameEnd()
{
}


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    // Add key press event
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    mouseY = window->GetResolution().y - mouseY;

    // Add mouse move event
    for (auto& pair : gameObjects) {
        const std::string& objName = pair.first;
        GameObject& obj = pair.second;

        if (obj.isBeingDragged) {
            // Update the position of the object based on the mouse cursor and offset
            obj.center.x += mouseX - obj.center.x;
            obj.center.y += mouseY - obj.center.y;
        }
    }
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    mouseY = window->GetResolution().y - mouseY;
    std::cout<< "Mouse clicked at " << mouseX << ", " << mouseY << endl;

    // Add mouse button press event
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {

        for (auto& pair : gameObjects) {
            const std::string& objName = pair.first;
            GameObject& obj = pair.second;

            // std::cout << "Object " << objName << " is at " << obj.center.x << ", " << obj.center.y << " with size " << obj.size.x << ", " << obj.size.y << endl;

            if (mouseX >= (obj.center.x - obj.size.x / 2.f) && mouseX <= (obj.center.x + obj.size.x / 2.f) && mouseY >= (obj.center.y - obj.size.y / 2.f) && mouseY <= (obj.center.y + obj.size.y / 2.f))
            {
                if (obj.isClickable)
                {
                    // obj.isClicked = true;

                    if(obj.mesh == meshes["star"])
                    {
                        // AddToMap(glm::vec2(900 + 50 * starsCollected, 525), glm::vec2(40, 40), "star_grey" + std::to_string(starsCollected++), meshes["star_grey"]);
                        obj = GameObject(glm::vec2(900 + 50 * starsCollected, 525), glm::vec2(40, 40), meshes["star_grey"]);
                        gameObjects["star_grey" + std::to_string(starsCollected++)] = obj;
                        std::cout << "Collected " << starsCollected << " stars" << endl;
                    }

                    gameObjects.erase(objName);

                    return;
                }

                if (!obj.isDraggable)
                    continue;


                // AddToMap(obj.center, obj.size, objName + std::to_string(cannonID++), obj.mesh);
                obj = Cannon(obj.center, obj.size, obj.mesh, obj.color);
                gameObjects[objName + std::to_string(cannonID++)] = obj;

                obj.isBeingDragged = true;
                std::cout << "Object " << objName << " is being dragged" << endl;

                return;
            }
        }

        
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    mouseY = window->GetResolution().y - mouseY;

    std::cout << "Mouse released at " << mouseX << ", " << mouseY << endl;

    // Add mouse button release event
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        for (auto& pair : gameObjects) {
            const std::string& objName = pair.first;
            GameObject& obj = pair.second;

            if (obj.isBeingDragged) {
                obj.isBeingDragged = false;
                std::cout << "Object " << objName << " is no longer being dragged" << endl;

                bool collision = false;

                for (auto& pair2 : gameObjects) {
                    const std::string& objName2 = pair2.first;
                    GameObject& obj2 = pair2.second;

                    if (objName2 != objName && obj2.canPlaceObject) {
                        if (CheckCollision(obj.center, obj.size, obj2.center, obj2.size)) {
							std::cout << "Collision between " << objName << " and " << objName2 << endl;
                            obj.center = obj2.center;
                            obj.isDraggable = false;
                            obj.isClickable = true;
                            collision = true;

                            if(objName2.compare(0, 7, "square0") == 0)
                                line0.cannons[objName] = gameObjects[objName];
                            else if (objName2.compare(0, 7, "square1") == 0)
                                line1.cannons[objName] = gameObjects[objName];
							else if (objName2.compare(0, 7, "square2") == 0)
                                line2.cannons[objName] = gameObjects[objName];

                            printLines();

                            if (obj.mesh == meshes["orange_cannon"])
                            {
                                if (starsCollected < 1)
                                    return;
                                else
                                {
                                    gameObjects.erase("star_grey" + std::to_string(--starsCollected));
                                }
                            }

                            if (obj.mesh == meshes["blue_cannon"])
                            {
                                if (starsCollected < 2)
                                    return;
                                else
                                {
                                    gameObjects.erase("star_grey" + std::to_string(--starsCollected));
                                    gameObjects.erase("star_grey" + std::to_string(--starsCollected));
                                }
                            }

                            if (obj.mesh == meshes["yellow_cannon"])
                            {
                                if (starsCollected < 2)
                                    return;
                                else
                                {
                                    gameObjects.erase("star_grey" + std::to_string(--starsCollected));
                                    gameObjects.erase("star_grey" + std::to_string(--starsCollected));
                                }
                            }

                            if (obj.mesh == meshes["purple_cannon"])
                            {
                                if (starsCollected < 3)
                                    return;
                                else
                                {
                                    gameObjects.erase("star_grey" + std::to_string(--starsCollected));
                                    gameObjects.erase("star_grey" + std::to_string(--starsCollected));
                                    gameObjects.erase("star_grey" + std::to_string(--starsCollected));
                                }
                            }

                            break;
						}
					}
                }

                if (collision == false)
                {
                    // obj.isClicked = true;
                    gameObjects.erase(objName);
                }

                return;
            }
        }
    }
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
