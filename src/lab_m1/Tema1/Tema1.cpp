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
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			std::string name = "square" + std::to_string(j) + std::to_string(i);
			AddMeshToList(square);
			obj = Square(glm::vec2(200 + 150 * i, 100 + 150 * j), glm::vec2(100, 100), square);
			gameObjects[name] = obj;
		}

	// RED HEARTS
	Mesh* heart = object2D::CreateHeart("heart", corner, 3, red, true);
	for (int i = 0; i < lives; i++)
	{
		std::string name = "heart" + std::to_string(i);
		AddMeshToList(heart);
		obj = GameObject(glm::vec2(950 + 125 * i, 650), glm::vec2(100, 100), heart);
		gameObjects[name] = obj;
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

	// blue cannon
	Mesh* cannon_blue = object2D::CreateCannon("cannon_blue", corner, 100, blue, true);
	AddMeshToList(cannon_blue);
	obj = Cannon(glm::vec2(300, 625), glm::vec2(100, 100), cannon_blue, blue);
	gameObjects["cannon_blue"] = obj;

	// yellow cannon
	Mesh* cannon_yellow = object2D::CreateCannon("cannon_yellow", corner, 100, yellow, true);
	AddMeshToList(cannon_yellow);
	obj = Cannon(glm::vec2(500, 625), glm::vec2(100, 100), cannon_yellow, yellow);
	gameObjects["cannon_yellow"] = obj;

	// purple cannon
	Mesh* cannon_purple = object2D::CreateCannon("cannon_purple", corner, 100, purple, true);
	AddMeshToList(cannon_purple);
	obj = Cannon(glm::vec2(700, 625), glm::vec2(100, 100), cannon_purple, purple);
	gameObjects["cannon_purple"] = obj;

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
	glClearColor(46.0 / 255, 40.0 / 255, 42.0 / 255, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// Sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->Update();

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
	// Spawn a star every 2 seconds
	if (time - timeToShoot < 2)
		return;

	timeToShoot = time;

	for (int i = 0; i < 3; i++)
	{
		// check if the line has a cannon and an enemy
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

				// check if the cannon and the enemy have the same color
				if (obj_cannon.color == obj_enemy.color)
				{
					// create a new launched star
					LaunchedStar launched_star;

					if (obj_cannon.color == orange)
						launched_star = LaunchedStar(glm::vec2(obj_cannon.center.x + 50, obj_cannon.center.y), glm::vec2(50, 50), meshes["launched_star_orange"], obj_cannon.color);

					if (obj_cannon.color == blue)
						launched_star = LaunchedStar(glm::vec2(obj_cannon.center.x + 50, obj_cannon.center.y), glm::vec2(50, 50), meshes["launched_star_blue"], obj_cannon.color);

					if (obj_cannon.color == yellow)
						launched_star = LaunchedStar(glm::vec2(obj_cannon.center.x + 50, obj_cannon.center.y), glm::vec2(50, 50), meshes["launched_star_yellow"], obj_cannon.color);

					if (obj_cannon.color == purple)
						launched_star = LaunchedStar(glm::vec2(obj_cannon.center.x + 50, obj_cannon.center.y), glm::vec2(50, 50), meshes["launched_star_purple"], obj_cannon.color);

					// add the launched star to the map
					gameObjects["launched_star" + std::to_string(starsLaunched++)] = launched_star;
					break;
				}
			}
		}
	}
}

void Tema1::GenerateStars()
{
	// Spawn a star every 5 seconds
	if (time - timeToGenerateStars < 5)
		return;

	timeToGenerateStars = time;
	
	// Set the position of the star
	int y = 100 + rand() % 400;
	int x = 100 + rand() % 1000;
		
	// Create the star and add it to the maps
	obj = Star(glm::vec2(x, y), glm::vec2(100, 100), meshes["star"]);
	gameObjects["star" + std::to_string(starsCount++)] = obj;
}

void Tema1::GenerateEnemies()
{
	// Spawn an enemy every 7 seconds
	if (time - timeToGenerateEnemies < 7)
		return;

	timeToGenerateEnemies = time;
	
	// Set the line and the color of the enemy
	int color = rand() % 4;
	int row = rand() % 3;
	std::string name;

	// Create the enemy
	switch (color) {
	case 0:
		name = "enemy_orange" + std::to_string(enemyID++);
		obj = Enemy(glm::vec2(1270, 100 + 150 * row), glm::vec2(100, 100), meshes["enemy_orange"], orange);
		break;
	case 1:
		name = "enemy_blue" + std::to_string(enemyID++);
		obj = Enemy(glm::vec2(1270, 100 + 150 * row), glm::vec2(100, 100), meshes["enemy_blue"], blue);
		break;
	case 2:
		name = "enemy_yellow" + std::to_string(enemyID++);
		obj = Enemy(glm::vec2(1270, 100 + 150 * row), glm::vec2(100, 100), meshes["enemy_yellow"], yellow);
		break;
	case 3:
		name = "enemy_purple" + std::to_string(enemyID++);
		obj = Enemy(glm::vec2(1270, 100 + 150 * row), glm::vec2(100, 100), meshes["enemy_purple"], purple);
		break;
	}

	// Add the enemy to the map
	gameObjects[name] = obj;

	// Add the enemy to the line map
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
}

void Tema1::CheckStarEnemyCollision()
{
	for (auto& pair : gameObjects)
	{
		const std::string& objName = pair.first;
		GameObject& obj = pair.second;

		// check if the object is a launched star
		if (objName.compare(0, 13, "launched_star") != 0)
			continue;

		for (auto& pair2 : gameObjects)
		{
			const std::string& objName2 = pair2.first;
			GameObject& obj2 = pair2.second;

			// check if the object is an enemy
			if (objName2.compare(0, 5, "enemy") != 0)
				continue;

			// check if the objects are colliding
			if (!CheckCollision(obj.center, obj.size, obj2.center, obj2.size))
				continue;

			// check if the objects have the same color
			if (obj.color == obj2.color)
			{
				// decrease the strength of the enemy
				obj2.strength--;

				// remove the launched star
				objectsToRemove.push_back(objName);
			}

			// check if the enemy is destroyed
			if (obj2.strength == 0)
				obj2.isBeingDestroyed = true;

			break;
		}
	}
}

void Tema1::CheckCannonEnemyCollision()
{
	for (auto& pair : gameObjects)
	{
		const std::string& objName = pair.first;
		GameObject& obj = pair.second;

		// check if the object is a cannon
		if (objName.compare(0, 6, "cannon") != 0)
			continue;
		
		bool isPlaced = false;

		// check if the cannon is placed on a square
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

		if (!isPlaced)
			continue;

		for (auto& pair2 : gameObjects)
		{
			const std::string& objName2 = pair2.first;
			GameObject& obj2 = pair2.second;

			// check if the object is an enemy
			if (objName2.compare(0, 5, "enemy") != 0)
				continue;

			// check if the objects are colliding
			if (CheckCollision(obj.center, obj.size, obj2.center, obj2.size))
			{
				// destroy the cannon
				obj.isBeingDestroyed = true;
				break;
			}
		}
	}
}

void Tema1::RemoveObject(const std::string& objName)
{
	objectsToRemove.push_back(objName);

	// remove the object from the line maps
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
			angularStep -= 4 * deltaTimeSeconds;

			modelMatrix *= transform2D::Translate(obj.center.x, obj.center.y);
			modelMatrix *= transform2D::Rotate(angularStep);
			modelMatrix *= transform2D::Translate(-obj.center.x, -obj.center.y);
		}

		// an enemy has reached the end of the screen
		if (obj.center.x < 0)
		{
			// remove the enemy
			RemoveObject(objName);

			// remove a heart
			gameObjects.erase("heart" + std::to_string(--lives));
		}

		// rescale if the object is being destroyed
		if (obj.isBeingDestroyed)
			obj.scale -= 1.5f * deltaTimeSeconds;

		// remove the object
		if (obj.scale < 0)
			RemoveObject(objName);

		// remove the stars that are outside of the screen
		if (obj.center.x > window->GetResolution().x)
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

	// the game is over
	if (lives < 0)
		exit(1);

	time = Engine::GetElapsedTime();
	Shoot();
	GenerateStars();
	GenerateEnemies();
	CheckStarEnemyCollision();
	CheckCannonEnemyCollision();
}

void Tema1::FrameEnd()
{
}

bool Tema1::MouseHover(int mouseX, int mouseY, glm::vec2 center, glm::vec2 size)
{
	// check if the mouse is over the object

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
	// pay for the cannon that was placed

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
	// check if there is already a cannon on that square

	for (int i = 0; i < 3; i++)
	{
		for (auto& pair_cannon : lines[i].cannons)
		{
			const std::string& objName_cannon = pair_cannon.first;
			GameObject& obj_cannon = pair_cannon.second;

			if (obj_cannon.center == center)
				return true;
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

	// left click
	if (button == GLFW_MOUSE_BUTTON_2) 
	{
		// check if a star can be collected
		for (auto& pair : gameObjects) {
			const std::string& objName = pair.first;
			GameObject& obj = pair.second;

			// check if the mouse is over the object
			if (MouseHover(mouseX, mouseY, obj.center, obj.size))
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

		// check if a cannon can be dragged
		for (auto& pair : gameObjects) {
			const std::string& objName = pair.first;
			GameObject& obj = pair.second;

			// check if the mouse is over the object
			if (MouseHover(mouseX, mouseY, obj.center, obj.size))
			{
				// the object is not clickable or draggable
				if (!obj.isDraggable)
					continue;

				if (obj.mesh == meshes["cannon_orange"] && starsCollected < 1)
					return; // not enough stars

				if (obj.mesh == meshes["cannon_blue"] && starsCollected < 2)
					return; // not enough stars

				if (obj.mesh == meshes["cannon_yellow"] && starsCollected < 2)
					return; // not enough stars

				if (obj.mesh == meshes["cannon_purple"] && starsCollected < 3)
					return; // not enough stars

				// the object is draggable => create a new cannon and drag the old one
				obj = Cannon(obj.center, obj.size, obj.mesh, obj.color);
				gameObjects[objName + std::to_string(cannonID++)] = obj;

				obj.isBeingDragged = true;
				return;
			}
		}
	}

	// right click
	if (button == GLFW_MOUSE_BUTTON_3)
	{
		// check if a cannon can be clicked
		for (auto& pair : gameObjects) {
			const std::string& objName = pair.first;
			GameObject& obj = pair.second;

			// check if the mouse is over the object
			if (MouseHover(mouseX, mouseY, obj.center, obj.size))
			{
				// check if the object can be clicked
				if (obj.isClickable)
				{
					// begin animation
					obj.isBeingDestroyed = true;
					return;
				}
			}
		}
	}
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// compute the mouse coordinates
	mouseY = window->GetResolution().y - mouseY;

	// left click
	if (button == GLFW_MOUSE_BUTTON_2) {
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
							if (IsSpotOcupied(obj2.center))
								break;

							// the object is colliding with another object => place it
							obj.center = obj2.center;
							obj.isDraggable = false;
							obj.isClickable = true;
							collision = true;

							// add the cannon to the line map
							if (objName2.compare(0, 7, "square0") == 0)
								lines[0].cannons[objName] = gameObjects[objName];
							else if (objName2.compare(0, 7, "square1") == 0)
								lines[1].cannons[objName] = gameObjects[objName];
							else if (objName2.compare(0, 7, "square2") == 0)
								lines[2].cannons[objName] = gameObjects[objName];

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
