#include "lab_m1/Tema2/Tema2.h"

#include <vector>
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>

using namespace std;
using namespace m1;

Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    // Create a camera
    camera = new implemented::MyCamera();
    glm::vec3 position = glm::vec3(0, 1.3, 3);
    camera->Set(position, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
    viewMatrix = camera->GetViewMatrix();

    // Create a plane mesh
    {
        Mesh* mesh = new Mesh("plane");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Create a buildings meshes
    for (int i = 0; i < 21; i++)
    {
        int id = i / 3 + 1;

		Mesh* mesh = new Mesh("building" + std::to_string(i));
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "building" + std::to_string(id) + ".obj");
		meshes[mesh->GetMeshID()] = mesh;

        // Generate random coordinates for the building
        float coordX = rand() % 81 - 40;
        float coordZ = rand() % 81 - 40;

        while ((coordX > -7 && coordX < 7) || (coordZ > -7 && coordZ < 7))
        {
            coordX = rand() % 81 - 40;
            coordZ = rand() % 81 - 40;
        }

        switch(id)
        {
            case 1:
            {
                buildings["building" + std::to_string(i)] = Building(mesh, glm::vec3(coordX, 0, coordZ), 2.f, 2.f);
                break;
            }
            case 2:
            {
                buildings["building" + std::to_string(i)] = Building(mesh, glm::vec3(coordX, 0, coordZ), 14.f, 10.f);
                break;
            }
            case 3:
            {
                buildings["building" + std::to_string(i)] = Building(mesh, glm::vec3(coordX, 0, coordZ), 6.f, 7.f);
                break;
            }
            case 4:
            {
                buildings["building" + std::to_string(i)] = Building(mesh, glm::vec3(coordX, 0, coordZ), 2.6f, 2.7f);
                break;
            }
            case 5:
            {
                buildings["building" + std::to_string(i)] = Building(mesh, glm::vec3(coordX, 0, coordZ), 5.f, 5.f);
                break;
            }
            case 6:
            {
                buildings["building" + std::to_string(i)] = Building(mesh, glm::vec3(coordX, 0, coordZ), 12.f, 8.f);
                break;
            }
            case 7:
            {
                buildings["building" + std::to_string(i)] = Building(mesh, glm::vec3(coordX, 0, coordZ), 5.f, 5.f);
                break;
            }
        }
	}

    // Create tank meshes
    {
        Mesh* mesh = new Mesh("rails");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "rails.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("body");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "body.obj");
		meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("turret");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "turret.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("gun");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "gun.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("projectile");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Create the player's tank
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::rotate(modelMatrix, RADIANS(180.0f), glm::vec3(0, 1, 0));

    tank = Tank(GameObject(meshes["rails"], glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), modelMatrix),
        				GameObject(meshes["body"], glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), modelMatrix),
        				GameObject(meshes["turret"], glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), modelMatrix),
        				GameObject(meshes["gun"], glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), modelMatrix));

    // Create enemies
    for (int i = 0; i < 20; i++)
    {
        // Generate random coordinates for the tank
        float coordX = rand() % 100 - 50;
        float coordZ = rand() % 100 - 50;

        while ((coordX > -5 && coordX < 5) || (coordZ > -5 && coordZ < 5))
        {
            coordX = rand() % 100 - 50;
            coordZ = rand() % 100 - 50;
        }

        // Create the tank
        glm::mat4 modelMatrix = glm::mat4(1);
        glm::vec3 position = glm::vec3(coordX, 0, coordZ);
        glm::vec3 forward = glm::vec3(0, 0, 1);
        modelMatrix = glm::translate(modelMatrix, position);

        Tank tank = Tank(GameObject(meshes["rails"], position, forward, modelMatrix),
            			GameObject(meshes["body"], position, forward, modelMatrix),
            			GameObject(meshes["turret"], position, forward, modelMatrix),
            			GameObject(meshes["gun"], position, forward, modelMatrix));

        // Add the tank to the list of enemies
        enemies["enemy" + std::to_string(enemyID++)] = tank;
    }

    // Create a shader program for drawing face polygon with the color of the normal
    {
        Shader* shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    // Create a sphere mesh
    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
}

void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(lightBlue.x, lightBlue.y, lightBlue.z, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);

    
}

// Move object forward
void MoveObjForward(glm::mat4& modelMatrix, glm::vec3& position, glm::vec3 forward, float distance)
{
    glm::mat4 translationMatrix = glm::mat4(1);
    position += forward * distance;

    translationMatrix = glm::translate(translationMatrix, forward * distance);
    modelMatrix = translationMatrix * modelMatrix;
}

// Move tank forward
void Tema2::MoveTankForward(Tank& tank, glm::vec3 forward, float distance)
{
    // Check if tank is in range of the map
    if(tank.tank_rails.position.x + forward.x * distance < -49 || tank.tank_rails.position.x + forward.x * distance > 49)
		return;

    if (tank.tank_rails.position.z + forward.z * distance < -49 || tank.tank_rails.position.z + forward.z * distance > 49)
        return;

    // Move tank
	MoveObjForward(tank.tank_rails.modelMatrix, tank.tank_rails.position, forward, distance);
	MoveObjForward(tank.tank_body.modelMatrix, tank.tank_body.position, forward, distance);
	MoveObjForward(tank.tank_turret.modelMatrix, tank.tank_turret.position, forward, distance);
	MoveObjForward(tank.tank_gun.modelMatrix, tank.tank_gun.position, forward, distance);

    // Move camera if the tank is the player's tank
    if(&tank == &this->tank)
		camera->MoveForward(distance);
}

// Rotate an object at a given angle
void Tema2::RotateObject(glm::mat4& modelMatrix, glm::vec3& position, glm::vec3& forward, float angle)
{
    glm::mat4 translationMatrix = glm::mat4(1);
    translationMatrix = glm::translate(translationMatrix, -position);
    modelMatrix = translationMatrix * modelMatrix;

    glm::mat4 rotationMatrix = glm::mat4(1);
    rotationMatrix = glm::rotate(rotationMatrix, angle, glm::vec3(0, 1, 0));
    modelMatrix = rotationMatrix * modelMatrix;

    translationMatrix = glm::mat4(1);
    translationMatrix = glm::translate(translationMatrix, position);
    modelMatrix = translationMatrix * modelMatrix;

    // Rotate the forward vector
    forward = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(forward, 1.0f)));
}

// Rotate tank at a given angle
void Tema2::RotateTank(Tank& tank, float angle)
{
    RotateObject(tank.tank_rails.modelMatrix, tank.tank_rails.position, tank.tank_rails.forward, angle);
    RotateObject(tank.tank_body.modelMatrix, tank.tank_body.position, tank.tank_body.forward, angle);
    RotateObject(tank.tank_turret.modelMatrix, tank.tank_turret.position, tank.tank_turret.forward, angle);
    RotateObject(tank.tank_gun.modelMatrix, tank.tank_gun.position, tank.tank_gun.forward, angle);
}

// Check if a tank is in range of the player's tank
void Tema2::CheckTanksCollision(Tank &tank1, Tank &tank2)
{
	float distance = glm::distance(tank1.tank_rails.position, tank2.tank_rails.position);
    if (distance < 1.3f)
    {
		float p = 1.3f - distance;
		glm::vec3 P = glm::normalize(tank1.tank_rails.position - tank2.tank_rails.position) * p;

        // Move the tanks away from each other
        MoveTankForward(tank1, P, 0.5f);
        MoveTankForward(tank2, -P, 0.5f);

        if (&tank1 == &this->tank || &tank2 == &this->tank)
            RepositionateCamera();
	}
}

// Check if a projectile hit a tank
bool Tema2::CheckTankProjectileCollision(Tank& tank, GameObject& projectile)
{
	float distance = glm::distance(tank.tank_rails.position, projectile.position);
    if (distance < 1.3f)
    {
        tank.damage++;
		return true;
	}

	return false;
}

bool isAboveFirstDiagonal(double x1, double z1, double x2, double z2, double px, double py) {

        // Determine the equation of the first diagonal
        double m1 = (z2 - z1) / (x2 - x1);
        double diagonal1 = z1 + m1 * (px - x1);

        // Compare py with the computed y value for the first diagonal
        return py > diagonal1;
}

bool isBelowSecondDiagonal(double x1, double z1, double x2, double z2, double px, double py) {

        // Determine the equation of the second diagonal
        double m2 = (z1 - z2) / (x2 - x1);
        double diagonal2 = z1 + m2 * (px - x1);

        // Compare py with the computed y value for the second diagonal
        return py < diagonal2;
}

// Check tank's proximity to buildings and move it if necessary
void Tema2::CheckTankBuildingCollision(Tank& tank, Building building)
{
    glm::vec3 dif = tank.tank_rails.position - building.position;

    if (abs(dif.x) < (building.dimOx / 2.f + 0.7f) && abs(dif.z) < (building.dimOz / 2.f + 0.7f))
    {
        glm::vec3 P = -glm::normalize(dif) * std::min(building.dimOx / 2.f - abs(dif.x), building.dimOz / 2.f - abs(dif.z));
        MoveTankForward(tank, P, 1);

        if (&tank == &this->tank)
            RepositionateCamera();
	}
}

// Check player's tank proximity and shoot if possible
void Tema2::DetectTank(Tank& enemy)
{
    float distance = glm::distance(tank.tank_rails.position, enemy.tank_rails.position);

    // Check if player's tank is in range
    if (distance < 10)
    {
        // Compute the new forward vector
        glm::vec3 new_forward = glm::normalize(tank.tank_body.position - enemy.tank_gun.position);

        // Compute the angle between the new forward vector and the current forward vector
        float angle = acos(glm::dot(new_forward, enemy.tank_gun.forward));

        // Compute the rotated vector and check if it is the same as the new forward vector
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::vec3 rotatedVector = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(enemy.tank_gun.forward, 1.0f)));

        if (abs(rotatedVector.x - new_forward.x) > 0.01f && abs(rotatedVector.z - new_forward.z) > 0.01f)
			angle = -angle;

        // Rotate enemy's turret and gun
        if(abs(angle) > 0.01f)
        {       
            RotateObject(enemy.tank_turret.modelMatrix, enemy.tank_turret.position, enemy.tank_turret.forward, angle);
            RotateObject(enemy.tank_gun.modelMatrix, enemy.tank_gun.position, enemy.tank_gun.forward, angle);
        }

        // Shoot every 5 seconds
        float time = Engine::GetElapsedTime();
        if (time - lastEnemyShot > 5)
        {
			Shoot(enemy);
			lastEnemyShot = time;
		}
    }
}

// Generate a move for the tank
void Tema2::GenerateRandomMove(Tank& tank, float deltaTimeSeconds)
{
    // Generate a new move every 4 seconds
    if (Engine::GetElapsedTime() - tank.timeMoveGenerated > 4)
    {
        tank.moveType = rand() % 4;
        tank.timeMoveGenerated = Engine::GetElapsedTime();
    }

    // Move the tank
    switch (tank.moveType)
    {
        case 0:
        {
   	    	   MoveTankForward(tank, tank.tank_rails.forward, deltaTimeSeconds);
   	           break;
   	    }
   	    case 1:
        {
   	    	   RotateTank(tank, deltaTimeSeconds * 0.5f);
   	    	   break;
   	    }
   	    case 2:
        {
   	    	   MoveTankForward(tank, tank.tank_rails.forward, -deltaTimeSeconds);
   	    	   break;
   	    }
   	    case 3:
        {
   	    	   RotateTank(tank, -deltaTimeSeconds * 0.5f);
   	    	   break;
   	    }
   
    }
}

// Render game ojects
void Tema2::RenderObjects()
{
    // Render tank
    {
        RenderSimpleMesh(meshes["rails"], shaders["LabShader"], tank.tank_rails.modelMatrix, true, tank.damage);
        RenderSimpleMesh(meshes["body"], shaders["LabShader"], tank.tank_body.modelMatrix, true, tank.damage);
        RenderSimpleMesh(meshes["turret"], shaders["LabShader"], tank.tank_turret.modelMatrix, true, tank.damage);
        RenderSimpleMesh(meshes["gun"], shaders["LabShader"], tank.tank_gun.modelMatrix, true, tank.damage);
    }

    // Render enemies
    for (auto& enemy_pair : enemies)
    {
        Tank& enemy = enemy_pair.second;

        RenderSimpleMesh(enemy.tank_rails.mesh, shaders["LabShader"], enemy.tank_rails.modelMatrix, false, enemy.damage);
        RenderSimpleMesh(enemy.tank_body.mesh, shaders["LabShader"], enemy.tank_body.modelMatrix, false, enemy.damage);
        RenderSimpleMesh(enemy.tank_turret.mesh, shaders["LabShader"], enemy.tank_turret.modelMatrix, false, enemy.damage);
        RenderSimpleMesh(enemy.tank_gun.mesh, shaders["LabShader"], enemy.tank_gun.modelMatrix, false, enemy.damage);
    }

    // Render buildings
    for (auto& pair : buildings)
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, pair.second.position);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -0.3f, 0));
        RenderSimpleMesh(pair.second.mesh, shaders["LabShader"], modelMatrix);
    }

    // Render plane
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -0.15f, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(2, 1, 2));
        RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix);
    }

    // Render light sphere
    {
        lightPosition = glm::vec3(5.f, 1.f, -1.f);
        glm::mat4 modelMatrix = glm::mat4(1);

        modelMatrix = glm::translate(modelMatrix, lightPosition);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));

        RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix);
    }

    // Render projectiles
    for (auto& pair : projectiles)
        RenderSimpleMesh(pair.second.mesh, shaders["LabShader"], pair.second.modelMatrix);
}

// Render objects and check conditions
void Tema2::RenderScene(float deltaTimeSeconds)
{
    RenderObjects();

    // Rotate turret and gun with mouse
    RotateObject(tank.tank_turret.modelMatrix, tank.tank_turret.position, tank.tank_turret.forward, angle_mouse - old_angle_mouse);
    RotateObject(tank.tank_gun.modelMatrix, tank.tank_gun.position, tank.tank_gun.forward, angle_mouse - old_angle_mouse);
    old_angle_mouse = angle_mouse;

    // Generate random moves for enemies
    for (auto& enemy_pair : enemies)
    {
        Tank& enemy = enemy_pair.second;
        GenerateRandomMove(enemy, deltaTimeSeconds);
    }

    for (auto& pair : projectiles)
    {
        // Move projectiles
        MoveObjForward(pair.second.modelMatrix, pair.second.position, pair.second.forward, deltaTimeSeconds * 4.0f);

        // Check if projectile has been created more than 3 seconds ago
        if (pair.second.timeCreated + 3 < Engine::GetElapsedTime())
        {
            projectilesToBeRemoved[pair.first] = pair.second;
        }

        // Check building collision
        for (auto& building_pair : buildings)
        {
            glm::vec3 dif = pair.second.position - building_pair.second.position;

            if (abs(dif.x) < building_pair.second.dimOx / 2.f && abs(dif.z) < building_pair.second.dimOz / 2.f)
            {
                projectilesToBeRemoved[pair.first] = pair.second;
            }
        }
    }

    // Detect player's tank and shoot
    for (auto& enemy_pair : enemies)
    {
        DetectTank(enemy_pair.second);
    }

    // Check collisions between tank and enemies
    for (auto& enemy_pair : enemies)
    {
        Tank& enemy = enemy_pair.second;
        CheckTanksCollision(tank, enemy);
    }

    // Check collisions between enemies
    for (auto& enemy_pair : enemies)
    {
        for (auto& enemy_pair2 : enemies)
        {
			if (enemy_pair.first == enemy_pair2.first)
				continue;

			CheckTanksCollision(enemy_pair.second, enemy_pair2.second);
		}
	}

    // Check collisions between enemies and buildings
    for (auto& tank_pair : enemies)
    {
        Tank& enemy = tank_pair.second;
        for (auto& building_pair : buildings)
        {
            CheckTankBuildingCollision(enemy, building_pair.second);
        }
    }

    // Check collisions between player's tank and buildings
    for (auto& building_pair : buildings)
    {
        CheckTankBuildingCollision(tank, building_pair.second);
    }

    for (auto& projectile_pair : projectiles)
    {
        for (auto& enemy_pair : enemies)
        {
            // Don't check collision between a projectile and the tank that shot it
            if (projectile_pair.second.id == enemy_pair.first)
                continue;

            // Check collision between projectiles and tanks
            if (CheckTankProjectileCollision(enemy_pair.second, projectile_pair.second))
            {
                // Remove projectiles that hit tanks
                projectilesToBeRemoved[projectile_pair.first] = projectile_pair.second;
            }

            // Remove tanks that are destroyed
            if (enemy_pair.second.damage == 3)
            {
                enemiesToBeRemoved[enemy_pair.first] = enemy_pair.second;
            }
        }

        // Don't check collision between a projectile and the tank that shot it
        if (projectile_pair.second.id == "MyTank")
            continue;

        // Check collision between projectiles and player's tank
        if (CheckTankProjectileCollision(tank, projectile_pair.second))
        {
            // Remove projectiles that hit tanks
            projectilesToBeRemoved[projectile_pair.first] = projectile_pair.second;
        }

        // Exit game if player's tank is destroyed
        if (tank.damage >= 3)
        {
            cout << "GAME OVER" << endl;
            exit(0);
        }
    }

    // Remove unwanted projectiles
    for (auto& pair : projectilesToBeRemoved)
    {
        projectiles.erase(pair.first);
    }

    projectilesToBeRemoved.clear();

    // Remove enemies that are destroyed
    for (auto& pair : enemiesToBeRemoved)
    {
        enemies.erase(pair.first);
        cout << "ENEMY DESTROYED" << endl;
        cout << "SCORE: " << ++score << endl;
    }

    enemiesToBeRemoved.clear();

    // Check if game is over
    if (Engine::GetElapsedTime() > 120)
        exit(0);
}

void Tema2::Update(float deltaTimeSeconds)
{

    glm::ivec2 resolution = window->GetResolution();
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
    viewMatrix = camera->GetViewMatrix();
    glViewport(0, 0, resolution.x, resolution.y);

    // Render the scene
    RenderScene(deltaTimeSeconds);

    glClear(GL_DEPTH_BUFFER_BIT);
    projectionMatrix = glm::ortho(left, right, bottom, top, 0.01f, 200.0f);
    viewMatrix = glm::lookAt(tank.tank_body.position + glm::vec3(0, 9.f, 0), tank.tank_body.position, glm::vec3(0, 0, -1));
    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);

    // render the scene to the small viewport area - close-up view
    RenderScene(deltaTimeSeconds);

}

// Render an object using the specified shader and the specified position
void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, bool isMyTank, int damage)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Set shader uniforms for light & material properties
    // Set light position uniform
    glUniform3fv(glGetUniformLocation(shader->program, "light_position"), 1, glm::value_ptr(lightPosition));
    glUniform3fv(glGetUniformLocation(shader->program, "light_position2"), 1, glm::value_ptr(lightPosition2));


    glm::vec3 eyePosition = camera->position;
    // Set eye position (camera position) uniform
    glUniform3fv(glGetUniformLocation(shader->program, "eye_position"), 1, glm::value_ptr(eyePosition));

    // Set material property uniforms (shininess, kd, ks, object color)
    glUniform1i(glGetUniformLocation(shader->program, "material_shininess"), materialShininess);

    // Set material kd and ks uniforms
    if(mesh == meshes["sky"])
		glUniform1f(glGetUniformLocation(shader->program, "material_kd"), 0.3f / 0.25f);
	else
		glUniform1f(glGetUniformLocation(shader->program, "material_kd"), materialKd);

    glUniform1f(glGetUniformLocation(shader->program, "material_ks"), materialKs);

    // Set material color uniform
    if (isMyTank)
    {
        if(mesh == meshes["rails"])
            glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(colorTankRails));
        else if (mesh == meshes["body"])
            glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(colorTankBody));
		else if (mesh == meshes["turret"])
			glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(colorTankTurret));
		else if (mesh == meshes["gun"])
			glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(colorTankGun));
    }
    else if (mesh == meshes["rails"])
		glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(colorEnemyRails));
	else if (mesh == meshes["body"])
		glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(colorEnemyBody));
    else if (mesh == meshes["turret"])
        glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(colorEnemyTurret));
    else if (mesh == meshes["gun"])
        glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(colorEnemyGun));
	else if (mesh == meshes["projectile"])
		glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(colorProjectile));
    else if (mesh == meshes["plane"])
		glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(colorPlane));
	else
		glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(colorBuilding));

    // Set damage uniform
     glUniform1i(glGetUniformLocation(shader->program, "damage"), damage);

     // Set component uniform
     if(mesh == meshes["rails"])
		glUniform1i(glGetUniformLocation(shader->program, "component"), 1);
	 else if (mesh == meshes["body"])
		 glUniform1i(glGetUniformLocation(shader->program, "component"), 2);
     else if (mesh == meshes["turret"])
         glUniform1i(glGetUniformLocation(shader->program, "component"), 3);
	 else if (mesh == meshes["gun"])
		 glUniform1i(glGetUniformLocation(shader->program, "component"), 4);
	 else
		 glUniform1i(glGetUniformLocation(shader->program, "component"), 0);

    //  Get shader location for uniform mat4 "Model"
    int location_model = glGetUniformLocation(shader->program, "Model");

    // Set shader uniform "Model" to modelMatrix
    glUniformMatrix4fv(location_model, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Get shader location for uniform mat4 "View"
    int location_view = glGetUniformLocation(shader->program, "View");

    // Set shader uniform "View" to viewMatrix
    glUniformMatrix4fv(location_view, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Get shader location for uniform mat4 "Projection"
    int location_projection = glGetUniformLocation(shader->program, "Projection");

    // Set shader uniform "Projection" to projectionMatrix
    glUniformMatrix4fv(location_projection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

// Move tank and camera positions
void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    // Move tank forward
    if (window->KeyHold(GLFW_KEY_W))
    {
        MoveTankForward(tank, tank.tank_rails.forward, deltaTime * 4.0f);
    }

    // Rotate tank and camera to the left
    if (window->KeyHold(GLFW_KEY_A))
    {
        RotateTank(tank, deltaTime * 2);

        camera->distanceToTarget = glm::distance(camera->position, tank.tank_rails.position);
        camera->RotateThirdPerson_OY(deltaTime * 2);
    }

    // Move tank backwards
    if (window->KeyHold(GLFW_KEY_S))
    {
        MoveTankForward(tank, tank.tank_rails.forward, -deltaTime * 4.0f);
    }

    // Rotate tank and camera to the right
    if (window->KeyHold(GLFW_KEY_D))
    {
        RotateTank(tank, -deltaTime * 2);

        camera->distanceToTarget = glm::distance(camera->position, tank.tank_rails.position);
        camera->RotateThirdPerson_OY(-deltaTime * 2);
    }
}

// Set camera posision behind tank
void Tema2::RepositionateCamera()
{
    // Set camera posision behind tank
    glm::vec3 position = tank.tank_rails.position - 3.f * normalize(tank.tank_rails.forward);
    position.y = 1.3f;

    camera->Set(position, tank.tank_rails.position, glm::vec3(0, 1, 0));
}

void Tema2::OnKeyPress(int key, int mods)
{
    if (key == GLFW_KEY_C)
    {
        // Set camera posision behind tank
        RepositionateCamera();
	}
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Rotate the camera
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (window->GetSpecialKeyState() == 0) {
            camera->RotateThirdPerson_OX(-deltaY * sensivityOX);
            camera->RotateThirdPerson_OY(-deltaX * sensivityOY);
        }
    }

    // Calculates the angle between the mouse and the center of the screen
    angle_mouse = std::atan((float)((float)window->GetResolution().x / 2.0 - (float)mouseX) / ((float)window->GetResolution().y - (float)mouseY));
}

// Launches a projectile from the tank
void Tema2::Shoot(Tank& tank)
{
    glm::mat4 modelMatrix = glm::mat4(1);
    glm::vec3 forward = tank.tank_gun.forward;
    glm::vec3 position = glm::vec3(tank.tank_gun.position.x, 0.4f, tank.tank_gun.position.z);

    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));

    // Offset the projectile so that it appears in front of the gun
    MoveObjForward(modelMatrix, position, forward, 1.f);

    // Tank from which the projectile was launched
    std::string enemyName = "MyTank";

    // Search for the tank in the enemies map
    // If the enemy is not found, the projectile was launched from the player's tank
    for (auto& enemy : enemies)
        if (&enemy.second == &tank)
        {
			enemyName = enemy.first;
            break;
		}

    // Add the projectile to the projectiles map
    projectiles["projectile" + std::to_string(projectileID++)] = GameObject(meshes["projectile"], position, forward, modelMatrix, Engine::GetElapsedTime(), enemyName);
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
    if (button == GLFW_MOUSE_BUTTON_2) // left click
    {
        Shoot(tank);
    }
}
