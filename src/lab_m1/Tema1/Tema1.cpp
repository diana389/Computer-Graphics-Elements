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

    // CANNONS TO PICK
    // orange cannon
    Mesh* cannon_orange = object2D::CreateCannon("cannon_orange", corner, 100, orange, true);
    AddMeshToList(cannon_orange);
    obj = Cannon(glm::vec2(100, 625), glm::vec2(100, 100), cannon_orange, orange);
    gameObjects["cannon_orange"] = obj;
    // AddToMap(glm::vec2(100, 625), glm::vec2(100, 100), "cannon_orange", cannon_orange);

    // blue cannon
    Mesh* cannon_blue = object2D::CreateCannon("cannon_blue", corner, 100, blue, true);
    AddMeshToList(cannon_blue);
    obj = Cannon(glm::vec2(300, 625), glm::vec2(100, 100), cannon_blue, blue);
    gameObjects["cannon_blue"] = obj;
    // AddToMap(glm::vec2(300, 625), glm::vec2(100, 100), "cannon_blue", cannon_blue);

    // yellow cannon
    Mesh* cannon_yellow = object2D::CreateCannon("cannon_yellow", corner, 100, yellow, true);
    AddMeshToList(cannon_yellow);
    obj = Cannon(glm::vec2(500, 625), glm::vec2(100, 100), cannon_yellow, yellow);
    gameObjects["cannon_yellow"] = obj;
    // AddToMap(glm::vec2(500, 625), glm::vec2(100, 100), "cannon_yellow", cannon_yellow);

    // purple cannon
    Mesh* cannon_purple = object2D::CreateCannon("cannon_purple", corner, 100, purple, true);
    AddMeshToList(cannon_purple);
    obj = Cannon(glm::vec2(700, 625), glm::vec2(100, 100), cannon_purple, purple);
    gameObjects["cannon_purple"] = obj;
    // AddToMap(glm::vec2(700, 625), glm::vec2(100, 100), "cannon_purple", cannon_purple);

    // GREY STARS
    Mesh* star_grey = object2D::CreateStar("star_grey", glm::vec3(0, 0, 0), 40, lightGray, true);
    AddMeshToList(star_grey);
    for (int i = 0; i < starsCollected; i++)
    {
        obj = GameObject(glm::vec2(900 + 50 * i, 525), glm::vec2(40, 40), meshes["star_grey"]);
        gameObjects["star_grey" + std::to_string(i)] = obj;
    }

    // LAUNCHED STARS
    Mesh* launched_star_orange = object2D::CreateStar("launched_star_orange", glm::vec3(0, 0, 4), 40, orange, true);
    AddMeshToList(launched_star_orange);

    Mesh* launched_star_blue = object2D::CreateStar("launched_star_blue", glm::vec3(0, 0, 4), 40, blue, true);
    AddMeshToList(launched_star_blue);

    Mesh* launched_star_yellow = object2D::CreateStar("launched_star_yellow", glm::vec3(0, 0, 4), 40, yellow, true);
    AddMeshToList(launched_star_yellow);

    Mesh* launched_star_purple = object2D::CreateStar("launched_star_purple", glm::vec3(0, 0, 4), 40, purple, true);
    AddMeshToList(launched_star_purple);

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

void Tema1::Shoot()
{
    obj.center = glm::vec2(500, 500);
    obj.color = snow;

    if (time % 200)
        return;

    for(int i = 0; i < 3; i++)
    {
        if (lines[i].cannons.empty() || lines[i].enemies.empty())
            continue;

            for (auto& pair_cannon : lines[i].cannons)
            {
                const std::string& objName_cannon = pair_cannon.first;
                GameObject& obj_cannon = pair_cannon.second;

                for (auto& pair_enemy : lines[i].enemies)
                {
                    const std::string& objName_enemy = pair_enemy.first;
                    GameObject& obj_enemy = pair_enemy.second;

                    if (obj_cannon.color == obj_enemy.color)
                    {
                        std::cout << "Cannon " << objName_cannon << " is shooting at " << objName_enemy << std::endl;
                        LaunchedStar launched_star;

                        printLines();

                        if (obj_cannon.color == orange)
                            launched_star = LaunchedStar(glm::vec2(obj_cannon.center.x + 50, obj_cannon.center.y), glm::vec2(50, 50), meshes["launched_star_orange"], obj_cannon.color);

                        if (obj_cannon.color == blue)
                            launched_star = LaunchedStar(glm::vec2(obj_cannon.center.x + 50, obj_cannon.center.y), glm::vec2(50, 50), meshes["launched_star_blue"], obj_cannon.color);

                        if (obj_cannon.color == yellow)
                            launched_star = LaunchedStar(glm::vec2(obj_cannon.center.x + 50, obj_cannon.center.y), glm::vec2(50, 50), meshes["launched_star_yellow"], obj_cannon.color);

                        if (obj_cannon.color == purple)
                            launched_star = LaunchedStar(glm::vec2(obj_cannon.center.x + 50, obj_cannon.center.y), glm::vec2(50, 50), meshes["launched_star_purple"], obj_cannon.color);

                        gameObjects["launched_star" + std::to_string(starsLaunched++)] = launched_star;

                        std::cout << "Launched star " << "launched_star " << launched_star.color << " from " << objName_cannon << " " << obj.color << std::endl;

                        break;
                    }
                }
            }
    }
}

void Tema1::GenerateStars()
{
    if (!(time % 200))
    {
        int y = 100 + rand() % 400;
        int x = 100 + rand() % 1000;
        // AddToMap(glm::vec2(x, y), glm::vec2(100, 100), "star" + std::to_string(starsCount++), meshes["star"]);
        obj = Star(glm::vec2(x, y), glm::vec2(100, 100), meshes["star"]);
        gameObjects["star" + std::to_string(starsCount++)] = obj;
    }
}

void Tema1::GenerateEnemies()
{
    if (!(time % 600))
    {
        // random enemy
        int color = rand() % 4;
        int row = rand() % 3;
        std::string name;

        switch (color) {
        case 0:
            name = "enemy_orange" + std::to_string(enemyID++);
            obj = Enemy(glm::vec2(1270, 100 + 150 * row), glm::vec2(100, 100), meshes["enemy_orange"], orange);
            gameObjects[name] = obj;
            break;
        case 1:
            name = "enemy_blue" + std::to_string(enemyID++);
            obj = Enemy(glm::vec2(1270, 100 + 150 * row), glm::vec2(100, 100), meshes["enemy_blue"], blue);
            gameObjects[name] = obj;
            break;
        case 2:
            name = "enemy_yellow" + std::to_string(enemyID++);
            obj = Enemy(glm::vec2(1270, 100 + 150 * row), glm::vec2(100, 100), meshes["enemy_yellow"], yellow);
            gameObjects[name] = obj;
            break;
        case 3:
            name = "enemy_purple" + std::to_string(enemyID++);
            obj = Enemy(glm::vec2(1270, 100 + 150 * row), glm::vec2(100, 100), meshes["enemy_purple"], purple);
            gameObjects[name] = obj;
            break;
        }

        switch (row) {
        case 0:
            lines[0].enemies[name] = gameObjects[name];
            break;
        case 1:
            lines[1].enemies[name] = gameObjects[name];
            break;
        case 2:
            lines[2].enemies[name] = gameObjects[name];
            break;
        }

        printLines();
    }
}

void Tema1::CheckStarEnemyCollision()
{
    for (auto& pair : gameObjects)
    {
        const std::string& objName = pair.first;
        GameObject& obj = pair.second;

        if (objName.compare(0, 13, "launched_star") == 0)
        {
            for (auto& pair2 : gameObjects)
            {
                const std::string& objName2 = pair2.first;
                GameObject& obj2 = pair2.second;

                if (objName2.compare(0, 5, "enemy") == 0)
                {
                    if (CheckCollision(obj.center, obj.size, obj2.center, obj2.size))
                    {
                        if(obj.color == obj2.color)
                        {
                            obj2.strength--;
                            objectsToRemove.push_back(objName);
                        }

                        if (obj2.strength == 0)
                            obj2.isBeingDestroyed = true;
                            // objectsToRemove.push_back(objName2);

                        break;
                    }
                }
            }
        }
    }
}

void Tema1::CheckCannonEnemyCollision()
{
    for (auto& pair : gameObjects)
    {
        const std::string& objName = pair.first;
        GameObject& obj = pair.second;

        if (objName.compare(0, 6, "cannon") == 0)
        {
            bool isPlaced = false;

            for (int i = 0; i < 3; i++)
            {
                for (auto& pair2 : lines[i].cannons)
                {
					const std::string& objName2 = pair2.first;
					GameObject& obj2 = pair2.second;

                    if (obj.center == obj2.center)
                        isPlaced = true;
				}
            }

            if(!isPlaced)
                continue;

            for (auto& pair2 : gameObjects)
            {
                const std::string& objName2 = pair2.first;
                GameObject& obj2 = pair2.second;

                if (objName2.compare(0, 5, "enemy") == 0)
                {
                    if (CheckCollision(obj.center, obj.size, obj2.center, obj2.size))
                    {
                        obj.isBeingDestroyed = true;
                        break;
                    }
                }
            }
        }
    }
}

void Tema1::printLines()
{
    std::cout << "First line: ";
    std::cout << "Cannons: ";
    for (auto& pair : lines[0].cannons)
        std::cout << pair.first << " ";

    std::cout << "Enemies: ";
    for (auto& pair : lines[0].enemies)
        std::cout << pair.first << " ";

    std::cout << std::endl;

    std::cout << "Second line: ";
    std::cout << "Cannons: ";
    for (auto& pair : lines[1].cannons)
        std::cout << pair.first << " ";

    std::cout << "Enemies: ";
    for (auto& pair : lines[1].enemies)
        std::cout << pair.first << " ";

    std::cout << std::endl;

    std::cout << "Third line: ";
    std::cout << "Cannons: ";
    for (auto& pair : lines[2].cannons)
        std::cout << pair.first << " ";

    std::cout << "Enemies: ";
    for (auto& pair : lines[2].enemies)
        std::cout << pair.first << " ";

    std::cout << std::endl << std::endl;
}

void Tema1::RemoveObject(const std::string& objName)
{
    objectsToRemove.push_back(objName);

    // remove the enemy from the line map
    for (int i = 0; i < 3; i++)
    {
        lines[i].enemies.erase(objName);
        lines[i].cannons.erase(objName);
    }
}

void Tema1::Update(float deltaTimeSeconds)
{
    for (auto& pair : gameObjects) 
    {
        const std::string& objName = pair.first;
        GameObject& obj = pair.second;

        modelMatrix = glm::mat3(1);

        // update the position of the enemy
        if (objName.compare(0, 5, "enemy") == 0 && !obj.isBeingDestroyed)
            obj.center.x -= 50 * deltaTimeSeconds;

        // update the position of the launched star
        if (objName.compare(0, 13, "launched_star") == 0)
        {
			obj.center.x += 200 * deltaTimeSeconds;
            angularStep -= 3 * deltaTimeSeconds;

            modelMatrix *= transform2D::Translate(obj.center.x, obj.center.y);
            modelMatrix *= transform2D::Rotate(angularStep);
            modelMatrix *= transform2D::Translate(-obj.center.x, -obj.center.y);
		}

        // remove the enemies that are outside of the screen
        if (obj.center.x < 0) 
        {
            RemoveObject(objName);

            gameObjects.erase("heart" + std::to_string(--lives)); // remove a heart
            std::cout << "lives: " << lives << std::endl;
        }

        // rescale if the object is being destroyed
        if(obj.isBeingDestroyed)
			obj.scale -= 0.8 * deltaTimeSeconds;

        // remove the object
        if(obj.scale < 0)
            RemoveObject(objName);

        // remove the stars that are outside of the screen
        if(obj.center.x > window->GetResolution().x)
            objectsToRemove.push_back(objName);

        // render the object
        modelMatrix *= transform2D::Translate(obj.center.x, obj.center.y);
        modelMatrix *= transform2D::Scale(obj.scale, obj.scale);
        modelMatrix *= transform2D::Translate(-obj.center.x, -obj.center.y);
        
        modelMatrix *= transform2D::Translate(obj.center.x, obj.center.y);
		RenderMesh2D(obj.mesh, shaders["VertexColor"], modelMatrix);
    }

    // Remove the objects outside of the loop
    for (const std::string& objname : objectsToRemove) 
        gameObjects.erase(objname);

    if(lives < 0)
		exit(1);

    time++;
    Shoot();
    GenerateStars();
    GenerateEnemies();
    CheckStarEnemyCollision();
    CheckCannonEnemyCollision();
}

void Tema1::FrameEnd()
{
}


bool Tema1::CheckClick(int mouseX, int mouseY, glm::vec2 center, glm::vec2 size)
{
    if (mouseX < (center.x - size.x / 2.f))
        return false;

    if (mouseX > (center.x + size.x / 2.f))
        return false;

    if (mouseY < (center.y - size.y / 2.f))
        return false;

    if (mouseY > (center.y + size.y / 2.f))
        return false;

    return true;
}

void Tema1::Pay(Mesh* mesh)
{
    if (mesh == meshes["cannon_orange"])
    {
        if (starsCollected < 1)
            return; // not enough stars
        else
            gameObjects.erase("star_grey" + std::to_string(--starsCollected));
    }

    if (mesh == meshes["cannon_blue"])
    {
        if (starsCollected < 2)
            return; // not enough stars
        else
        {
            gameObjects.erase("star_grey" + std::to_string(--starsCollected));
            gameObjects.erase("star_grey" + std::to_string(--starsCollected));
        }
    }

    if (mesh == meshes["cannon_yellow"])
    {
        if (starsCollected < 2)
            return; // not enough stars
        else
        {
            gameObjects.erase("star_grey" + std::to_string(--starsCollected));
            gameObjects.erase("star_grey" + std::to_string(--starsCollected));
        }
    }

    if (mesh == meshes["cannon_purple"])
    {
        if (starsCollected < 3)
            return; // not enough stars
        else
        {
            gameObjects.erase("star_grey" + std::to_string(--starsCollected));
            gameObjects.erase("star_grey" + std::to_string(--starsCollected));
            gameObjects.erase("star_grey" + std::to_string(--starsCollected));
        }
    }
}

bool Tema1::IsSpotOcupied(glm::vec2 center)
{
    for (int i = 0; i < 3; i++)
    {
        if (!lines[i].cannons.empty()) {
            for (auto& pair_cannon : lines[i].cannons)
            {
                const std::string& objName_cannon = pair_cannon.first;
                GameObject& obj_cannon = pair_cannon.second;

                if (obj_cannon.center == center)
                    return true;
            }
        }
    }

    return false;
}


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}

void Tema1::OnKeyPress(int key, int mods)
{
}

void Tema1::OnKeyRelease(int key, int mods)
{
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // compute the mouse coordinates
    mouseY = window->GetResolution().y - mouseY;

    for (auto& pair : gameObjects) {
        const std::string& objName = pair.first;
        GameObject& obj = pair.second;

        // update the position of the object based on the mouse cursor and offset
        if (obj.isBeingDragged) {
            obj.center.x += mouseX - obj.center.x;
            obj.center.y += mouseY - obj.center.y;
        }
    }
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // compute the mouse coordinates
    mouseY = window->GetResolution().y - mouseY;
    
    // Add mouse button press event
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        std::cout<< "Mouse clicked at " << mouseX << ", " << mouseY << endl;

        // check if a star can be collected
        for (auto& pair : gameObjects) {
            const std::string& objName = pair.first;
            GameObject& obj = pair.second;

            // check if the mouse is over the object
            if (CheckClick(mouseX, mouseY, obj.center, obj.size))
            {
                // check if the object can be clicked
                if (obj.isClickable)
                {
                    // if the object is a star, collect it
                    if (obj.mesh == meshes["star"])
                    {
                        obj = GameObject(glm::vec2(900 + 50 * starsCollected, 525), glm::vec2(40, 40), meshes["star_grey"]);
                        gameObjects["star_grey" + std::to_string(starsCollected++)] = obj;

                        // remove the object from the map
                        gameObjects.erase(objName);
                        return;
                    }
                }
            }
        }

        // check if a cannon can be dragged or clicked
        for (auto& pair : gameObjects) {
            const std::string& objName = pair.first;
            GameObject& obj = pair.second;

            // check if the mouse is over the object
            if (CheckClick(mouseX, mouseY, obj.center, obj.size))
            {
                // check if the object can be clicked
                if (obj.isClickable)
                {
                    // remove the cannon from the line map
                    RemoveObject(objName);
                    break;
                }

                // the object is not clickable or draggable
                if (!obj.isDraggable)
                    continue;

                // the object is draggable => create a new cannon and drag the old one
                obj = Cannon(obj.center, obj.size, obj.mesh, obj.color);
                gameObjects[objName + std::to_string(cannonID++)] = obj;

                obj.isBeingDragged = true;
                return;
            }
        }

        // remove the object from maps
        for (const std::string& objname : objectsToRemove)
            gameObjects.erase(objname);

        printLines();
    }
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // compute the mouse coordinates
    mouseY = window->GetResolution().y - mouseY;

    // Add mouse button release event
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        for (auto& pair : gameObjects) {
            const std::string& objName = pair.first;
            GameObject& obj = pair.second;

            if (obj.isBeingDragged) {
                // the object is no longer being dragged
                obj.isBeingDragged = false;

                // try and place the object
                bool collision = false;

                for (auto& pair2 : gameObjects) {
                    const std::string& objName2 = pair2.first;
                    GameObject& obj2 = pair2.second;

                    // check if the object can be placed
                    if (objName2 != objName && obj2.canPlaceObject) {
                        // check if the object is colliding with another object
                        if (CheckCollision(obj.center, obj.size, obj2.center, obj2.size)) {

                            // check if there is already a cannon on that square
                            if(IsSpotOcupied(obj2.center))
                                break;

                            // the object is colliding with another object => place it
                            obj.center = obj2.center;
                            obj.isDraggable = false;
                            obj.isClickable = true;
                            collision = true;

                            // add the cannon to the line map
                            if(objName2.compare(0, 7, "square0") == 0)
                                lines[0].cannons[objName] = gameObjects[objName];
                            else if (objName2.compare(0, 7, "square1") == 0)
                                lines[1].cannons[objName] = gameObjects[objName];
							else if (objName2.compare(0, 7, "square2") == 0)
                                lines[2].cannons[objName] = gameObjects[objName];

                            printLines();

                            // pay for the cannon
                            Pay(obj.mesh);

                            break;
						}
					}
                }

                // the object is not colliding with another object => remove it
                if (collision == false)
                    gameObjects.erase(objName);

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
