#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


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

    glm::vec3 corner = glm::vec3(0, 0, 0);
    lives = 3;
    starsCount = 0;
    starsCollected = 0;
    time = 0;
    cannonID = 0;

    // TODO(student): Compute coordinates of a square's center, and store
    // then in the `cx` and `cy` class variables (see the header). Use
    // `corner` and `squareSide`. These two class variables will be used
    // in the `Update()` function. Think about it, why do you need them?

    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;

    // Initialize angularStep
    angularStep = 0;

    Mesh* rect = object2D::CreateRectangle("rect", corner, 100, 400, jordyBlue, true);
    AddMeshToList(rect);
    AddToMap(glm::vec2(75, 250), glm::vec2(100, 400), "rect", false, false, false, rect);

    Mesh* squares[3][3];

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
        {
            std::string name = "square" + std::to_string(i) + std::to_string(j);
            cout << name << endl;
            squares[i][j] = object2D::CreateSquare(name, corner, 100, lightGreen, true);
            AddMeshToList(squares[i][j]);
            AddToMap(glm::vec2(200 + 150 * i, 100 + 150 * j), glm::vec2(100, 100), name, false, true, false, squares[i][j]);
        }

    Mesh* hearts[3];
    for (int i = 0; i < lives; i++)
    {
        std::string name = "heart" + std::to_string(i);
		hearts[i] = object2D::CreateHeart(name, corner, 3, red, true);
		AddMeshToList(hearts[i]);
        AddToMap(glm::vec2(950 + 125 * i, 650), glm::vec2(100, 100), name, false, false, false, hearts[i]);
	}

    Mesh* cannon_outline[4];
    for (int i = 0; i < 4; i++)
    {
        std::string name = "cannon" + std::to_string(i);
		cannon_outline[i] = object2D::CreateSquare(name, corner, 150, white, false);
		AddMeshToList(cannon_outline[i]);
		AddToMap(glm::vec2(125 + 200 * i, 625), glm::vec2(150, 150), name, false, false, false, cannon_outline[i]);
	}

    // yellow star
    Mesh* star = object2D::CreateStar("star", corner, 100, yellow, true);
    AddMeshToList(star);
    AddToMap(glm::vec2(900, 300), glm::vec2(100, 100), "star", false, false, true, star);

    Mesh* cannon = object2D::CreateCannon("white_cannon", corner, 100, white, true);
    AddMeshToList(cannon);
    AddToMap(glm::vec2(700, 200), glm::vec2(100, 100), "white_cannon", true, false, false, cannon);

    Mesh* cannons_to_pick[4];

    // orange cannon
    cannons_to_pick[0] = object2D::CreateCannon("orange_cannon", corner, 100, orange, true);
    AddMeshToList(cannons_to_pick[0]);
    AddToMap(glm::vec2(100, 625), glm::vec2(100, 100), "orange_cannon", true, false, false, cannons_to_pick[0]);

    // blue cannon
    cannons_to_pick[1] = object2D::CreateCannon("blue_cannon", corner, 100, blue, true);
    AddMeshToList(cannons_to_pick[1]);
    AddToMap(glm::vec2(300, 625), glm::vec2(100, 100), "blue_cannon", true, false, false, cannons_to_pick[1]);

    // yellow cannon
    cannons_to_pick[2] = object2D::CreateCannon("yellow_cannon", corner, 100, yellow, true);
    AddMeshToList(cannons_to_pick[2]);
    AddToMap(glm::vec2(500, 625), glm::vec2(100, 100), "yellow_cannon", true, false, false, cannons_to_pick[2]);

    // purple cannon
    cannons_to_pick[3] = object2D::CreateCannon("purple_cannon", corner, 100, purple, true);
    AddMeshToList(cannons_to_pick[3]);
    AddToMap(glm::vec2(700, 625), glm::vec2(100, 100), "purple_cannon", true, false, false, cannons_to_pick[3]);

    // grey stars
    Mesh* star_grey = object2D::CreateStar("star_grey", corner, 40, lightGray, true);
    AddMeshToList(star_grey);

    AddToMap(glm::vec2(75, 525), glm::vec2(40, 40), "star_grey00", false, false, false, star_grey);
    AddToMap(glm::vec2(275, 525), glm::vec2(40, 40), "star_grey01", false, false, false, star_grey);
    AddToMap(glm::vec2(325, 525), glm::vec2(40, 40), "star_grey02", false, false, false, star_grey);
    AddToMap(glm::vec2(475, 525), glm::vec2(40, 40), "star_grey03", false, false, false, star_grey);
    AddToMap(glm::vec2(525, 525), glm::vec2(40, 40), "star_grey04", false, false, false, star_grey);
    AddToMap(glm::vec2(675, 525), glm::vec2(40, 40), "star_grey05", false, false, false, star_grey);
    AddToMap(glm::vec2(725, 525), glm::vec2(40, 40), "star_grey06", false, false, false, star_grey);
    AddToMap(glm::vec2(775, 525), glm::vec2(40, 40), "star_grey07", false, false, false, star_grey);


    // enemys

    // purple enemy
    Mesh* enemy = object2D::CreateEnemy("enemy_purple", corner, 50, purple, coolGray, true);
    AddMeshToList(enemy);
    AddToMap(glm::vec2(1000, 100), glm::vec2(50, 50), "enemy_purple", false, false, false, enemy);

    // blue enemy
    Mesh* enemy2 = object2D::CreateEnemy("enemy_blue", corner, 50, blue, jordyBlue, true);
    AddMeshToList(enemy2);
    AddToMap(glm::vec2(1000, 300), glm::vec2(50, 50), "enemy_blue", false, false, false, enemy2);

    // yellow enemy
    Mesh* enemy3 = object2D::CreateEnemy("enemy_yellow", corner, 50, yellow, lightGreen, true);
    AddMeshToList(enemy3);
    // AddToMap(glm::vec2(1000, 500), glm::vec2(50, 50), "enemy_yellow", false, false, false, enemy3);

    // orange enemy
    Mesh* enemy4 = object2D::CreateEnemy("enemy_orange", corner, 50, orange, raisinBlack, true);
    AddMeshToList(enemy4);
    // AddToMap(glm::vec2(1000, 700), glm::vec2(50, 50), "enemy_orange", false, false, false, enemy4);
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(46.0/255, 40.0/255, 42.0/255, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::RenderPermanentObjects()
{
    // rectangle
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(75, 250);

    modelMatrix *= transform2D::Scale(1, 4);
    RenderMesh2D(meshes["rect"], shaders["VertexColor"], modelMatrix);

    // green squares
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            std::string name = "square" + std::to_string(i) + std::to_string(j);
            obj = gameObjects[name];

            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(obj.center.x,obj.center.y);

            RenderMesh2D(meshes[name], shaders["VertexColor"], modelMatrix);
        }

    // cannon outline
    for (int i = 0; i < 4; i++)
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(125 + 200 * i, 625);

        RenderMesh2D(meshes["cannon_outline"], shaders["VertexColor"], modelMatrix);
    }

    // yellow star
    obj = gameObjects["star"];

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(obj.center.x, obj.center.y);

    if(!obj.isClicked)
		RenderMesh2D(obj.mesh, shaders["VertexColor"], modelMatrix);

    // cannons_to_pick
    // orange cannon
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(100, 625);

    RenderMesh2D(meshes["orange_cannon"], shaders["VertexColor"], modelMatrix);

    // blue cannon
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(300, 625);

    RenderMesh2D(meshes["blue_cannon"], shaders["VertexColor"], modelMatrix);

    // yellow cannon
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(500, 625);

    RenderMesh2D(meshes["yellow_cannon"], shaders["VertexColor"], modelMatrix);


    // purple cannon
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(700, 625);

    RenderMesh2D(meshes["purple_cannon"], shaders["VertexColor"], modelMatrix);

    // grey stars

    // orange cannon
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(75, 525);

    RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);

    // blue cannon
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(275, 525);

    RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(325, 525);

    RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);

    // yellow cannon
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(475, 525);

    RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(525, 525);

    RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);

    // purple cannon
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(675, 525);

    RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(725, 525);

    RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(775, 525);

    RenderMesh2D(meshes["star_grey"], shaders["VertexColor"], modelMatrix);

    // red hearts
    for (int i = 0; i < lives; i++)
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(950 + 125 * i, 650);

        RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
    }

    // enemy
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(1000, 100);

    RenderMesh2D(meshes["enemy_purple"], shaders["VertexColor"], modelMatrix);

    // enemy2
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(1000, 300);

    RenderMesh2D(meshes["enemy_blue"], shaders["VertexColor"], modelMatrix);

    // cannon
    obj = gameObjects["cannon"];
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(obj.center.x, obj.center.y);

    if (!obj.isClicked)
        RenderMesh2D(obj.mesh, shaders["VertexColor"], modelMatrix);
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


void Tema1::Update(float deltaTimeSeconds)
{
    //RenderPermanentObjects();
    for (auto& pair : gameObjects) {
        const std::string& objName = pair.first;
        GameObject& obj = pair.second;

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(obj.center.x, obj.center.y);

        if(!obj.isClicked)
			RenderMesh2D(obj.mesh, shaders["VertexColor"], modelMatrix);
    }

    time++;

    if(time % 500)
		return;

    int y = 100 + rand() % 400;
    AddToMap(glm::vec2(1200, y), glm::vec2(100, 100), "star" + std::to_string(starsCount++), false, false, true, meshes["star"]);

    if (time % 1000)
        return;

    cout << "Time: " << time << endl;

    // random enemy
    int x = rand() % 4;

    switch (x) {
        case 0:
            AddToMap(glm::vec2(1000, 625), glm::vec2(100, 100), "enemy_orange", false, false, false, meshes["enemy_orange"]);
			break;
		case 1:
            AddToMap(glm::vec2(1000, 625), glm::vec2(100, 100), "enemy_blue", false, false, false, meshes["enemy_blue"]);
			break;
		case 2:
			AddToMap(glm::vec2(1000, 625), glm::vec2(100, 100), "enemy_yellow", false, false, false, meshes["enemy_yellow"]);
			break;
		case 3:
			AddToMap(glm::vec2(1000, 625), glm::vec2(100, 100), "enemy_purple", false, false, false, meshes["enemy_purple"]);
			break;
    }
}

void Tema1::AddToMap(glm::vec2 center, glm::vec2 size,const std::string& name, bool isDraggable, bool canPlaceObject, bool isClickable, Mesh* mesh)
{
    GameObject obj;
    obj.center = center;
    obj.size = size;
    obj.isBeingDragged = false;
    obj.isDraggable = isDraggable;
    obj.canPlaceObject = canPlaceObject;
    obj.isClicked = false;
    obj.isClickable = isClickable;
    obj.mesh = mesh;
    gameObjects[name] = obj;
}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


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
    cout<< "Mouse clicked at " << mouseX << ", " << mouseY << endl;

    // Add mouse button press event
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {

        cout << "click right" << endl;

        for (auto& pair : gameObjects) {
            const std::string& objName = pair.first;
            GameObject& obj = pair.second;

            // cout << "Object " << objName << " is at " << obj.center.x << ", " << obj.center.y << " with size " << obj.size.x << ", " << obj.size.y << endl;

            if (mouseX >= (obj.center.x - obj.size.x / 2.f) && mouseX <= (obj.center.x + obj.size.x / 2.f) && mouseY >= (obj.center.y - obj.size.y / 2.f) && mouseY <= (obj.center.y + obj.size.y / 2.f))
            {
                if (obj.isClickable)
                {
                    // obj.isClicked = true;

                    if(obj.mesh == meshes["star"])
                    {
                        AddToMap(glm::vec2(900 + 50 * starsCollected, 525), glm::vec2(40, 40), "star_grey" + std::to_string(starsCollected++), false, false, false, meshes["star_grey"]);
                        cout << "Collected " << starsCollected << " stars" << endl;
                    }

                    gameObjects.erase(objName);

                    return;
                }

                if (!obj.isDraggable)
                    continue;

                AddToMap(obj.center, obj.size, objName + std::to_string(cannonID++), true, false, false, obj.mesh);

                obj.isBeingDragged = true;
                cout << "Object " << objName << " is being dragged" << endl;

                return;
            }
        }

        
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    mouseY = window->GetResolution().y - mouseY;

    cout << "Mouse released at " << mouseX << ", " << mouseY << endl;

    // Add mouse button release event
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        for (auto& pair : gameObjects) {
            const std::string& objName = pair.first;
            GameObject& obj = pair.second;

            if (obj.isBeingDragged) {
                obj.isBeingDragged = false;
                cout << "Object " << objName << " is no longer being dragged" << endl;

                bool collision = false;

                for (auto& pair2 : gameObjects) {
                    const std::string& objName2 = pair2.first;
                    GameObject& obj2 = pair2.second;

                    if (objName2 != objName && obj2.canPlaceObject) {
                        if (CheckCollision(obj.center, obj.size, obj2.center, obj2.size)) {
							cout << "Collision between " << objName << " and " << objName2 << endl;
                            obj.center = obj2.center;
                            obj.isPlaced = true;
                            obj.isDraggable = false;
                            obj.isClickable = true;
                            collision = true;
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
