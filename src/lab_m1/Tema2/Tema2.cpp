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
    renderCameraTarget = false;

    camera = new implemented::MyCamera();
    glm::vec3 position = glm::vec3(0, 1.3, 3);
    camera->Set(position, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
    viewMatrix = camera->GetViewMatrix();

    // camera->MoveForward(20);
    // camera->RotateThirdPerson_OY(RADIANS(180));

    {
        Mesh* mesh = new Mesh("plane");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("sky");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

  //  {
  //      Mesh* mesh = new Mesh("building1");
		//mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "building1.obj");
		//meshes[mesh->GetMeshID()] = mesh;
  //      buildings["building1"] = Building(mesh, glm::vec3(-10, 0, 4), 2.f, 2.f);
  //  }

    for (int i = 0; i < 14; i++)
    {
        int id = i / 2 + 1;

		Mesh* mesh = new Mesh("building" + std::to_string(i));
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "building" + std::to_string(id) + ".obj");
		meshes[mesh->GetMeshID()] = mesh;

        float coordX = rand() % 81 - 40;
        float coordZ = rand() % 81 - 40;

        while ((coordX > -4 && coordX < 4) || (coordZ > -4 && coordZ < 4))
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

    //{
    //    Mesh *mesh = new Mesh("building2");
    //    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "building2.obj");
    //    meshes[mesh->GetMeshID()] = mesh;
    //    buildings["building2"] = Building(mesh, glm::vec3(-20, 0, 8), 14.f, 10.f);
    //}

 //   {
	//	Mesh *mesh = new Mesh("building3");
	//	mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "building3.obj");
	//	meshes[mesh->GetMeshID()] = mesh;
	//	buildings["building3"] = Building(mesh, glm::vec3(5, 0, -12), 6.f, 7.f);
	//}

 //   {
 //       Mesh* mesh = new Mesh("building4");
 //       mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "building4.obj");
 //       meshes[mesh->GetMeshID()] = mesh;
 //       buildings["building4"] = Building(mesh, glm::vec3(20, 0, 16), 2.6f, 2.7f);
 //   }

 //   {
	//	Mesh *mesh = new Mesh("building5");
	//	mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "building5.obj");
	//	meshes[mesh->GetMeshID()] = mesh;
	//	buildings["building5"] = Building(mesh, glm::vec3(-5, 0, 5), 5.f, 5.f);
	//}

 //   {
	//	Mesh *mesh = new Mesh("building6");
	//	mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "building6.obj");
	//	meshes[mesh->GetMeshID()] = mesh;
	//	buildings["building6"] = Building(mesh, glm::vec3(10, 0, -20), 12.f, 8.f);
	//}

 //   {
	//	Mesh *mesh = new Mesh("building7");
	//	mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "building7.obj");
	//	meshes[mesh->GetMeshID()] = mesh;
	//	buildings["building7"] = Building(mesh, glm::vec3(15, 0, 20), 5.f, 5.f);
	//}

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

    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, tankPosition);
    modelMatrix = glm::rotate(modelMatrix, RADIANS(180.0f), glm::vec3(0, 1, 0));

    tank_rails = GameObject(meshes["rails"], tankPosition, glm::vec3(0, 0, -1), modelMatrix);
    tank_body = GameObject(meshes["body"], tankPosition, glm::vec3(0, 0, -1), modelMatrix);
    tank_turret = GameObject(meshes["turret"], tankPosition, glm::vec3(0, 0, -1), modelMatrix);
    tank_gun = GameObject(meshes["gun"], tankPosition, glm::vec3(0, 0, -1), modelMatrix);

    tank = Tank(tank_rails, tank_body, tank_turret, tank_gun);

    modelMatrixTank = modelMatrix;

    for (int i = 0; i < 10; i++)
    {
        float coordX = rand() % 100 - 50;
        float coordZ = rand() % 100 - 50;

        bool inBuilding = false;

        for (auto& building_pair : buildings)
        {
            if (abs(building_pair.second.position.x - coordX) < building_pair.second.dimOx / 2.f + 1.5f)
            {
				inBuilding = true;
                break;
			}

            if (abs(building_pair.second.position.z - coordZ) < building_pair.second.dimOz / 2.f + 1.5f)
            {
                inBuilding = true;
                break;
            }
		}

        if (inBuilding)
        {
            i--;
            continue;
        }

        glm::mat4 modelMatrix = glm::mat4(1);
        glm::vec3 position = glm::vec3(coordX, 0, coordZ);
        glm::vec3 forward = glm::vec3(0, 0, 1);
        modelMatrix = glm::translate(modelMatrix, position);

        Tank tank = Tank(GameObject(meshes["rails"], position, forward, modelMatrix),
            			GameObject(meshes["body"], position, forward, modelMatrix),
            			GameObject(meshes["turret"], position, forward, modelMatrix),
            			GameObject(meshes["gun"], position, forward, modelMatrix));

        enemies["enemy" + std::to_string(enemyID++)] = tank;
    }

    /*{
        glm::mat4 modelMatrix = glm::mat4(1);
        glm::vec3 position = glm::vec3(10, 0, -20);
        glm::vec3 forward = glm::vec3(0, 0, 1);
        modelMatrix = glm::translate(modelMatrix, position);

        Tank tank = Tank(GameObject(meshes["rails"], position, forward, modelMatrix),
            GameObject(meshes["body"], position, forward, modelMatrix),
            GameObject(meshes["turret"], position, forward, modelMatrix),
            GameObject(meshes["gun"], position, forward, modelMatrix));

        enemies["enemy" + std::to_string(enemyID++)] = tank;
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        glm::vec3 position = glm::vec3(6, 0, 2);
        glm::vec3 forward = glm::vec3(0, 0, 1);
        modelMatrix = glm::translate(modelMatrix, position);

        Tank tank = Tank(GameObject(meshes["rails"], position, forward, modelMatrix),
            GameObject(meshes["body"], position, forward, modelMatrix),
            GameObject(meshes["turret"], position, forward, modelMatrix),
            GameObject(meshes["gun"], position, forward, modelMatrix));

        enemies["enemy" + std::to_string(enemyID++)] = tank;
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        glm::vec3 position = glm::vec3(0, 0, 3);
        glm::vec3 forward = glm::vec3(0, 0, 1);
        modelMatrix = glm::translate(modelMatrix, position);

        Tank tank = Tank(GameObject(meshes["rails"], position, forward, modelMatrix),
            GameObject(meshes["body"], position, forward, modelMatrix),
            GameObject(meshes["turret"], position, forward, modelMatrix),
            GameObject(meshes["gun"], position, forward, modelMatrix));

        enemies["enemy" + std::to_string(enemyID++)] = tank;
    }*/

    // Create a shader program for drawing face polygon with the color of the normal
    {
        Shader* shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Sets the resolution of the small viewport
    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(50, 50, resolution.x / 5.f, resolution.y / 5.f);
}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);

    
}

void MoveObjForward(glm::mat4& modelMatrix, glm::vec3& position, glm::vec3 forward, float distance)
{
    //cout << "position before: " << position.x << " " << position.y << " " << position.z << endl;
    //cout << "distance: " << distance << endl;
    glm::mat4 translationMatrix = glm::mat4(1);
    position += forward * distance;

    //cout << "position: " << position.x << " " << position.y << " " << position.z << endl;
    //cout << "forward: " << forward.x << " " << forward.y << " " << forward.z << endl << endl;

    translationMatrix = glm::translate(translationMatrix, forward * distance);
    modelMatrix = translationMatrix * modelMatrix;
}

void Tema2::MoveTankForward(Tank& tank, glm::vec3 forward, float distance)
{
    if(tank.tank_rails.position.x + forward.x * distance < -49 || tank.tank_rails.position.x + forward.x * distance > 49)
		return;

    if (tank.tank_rails.position.z + forward.z * distance < -49 || tank.tank_rails.position.z + forward.z * distance > 49)
        return;

	MoveObjForward(tank.tank_rails.modelMatrix, tank.tank_rails.position, forward, distance);
	MoveObjForward(tank.tank_body.modelMatrix, tank.tank_body.position, forward, distance);
	MoveObjForward(tank.tank_turret.modelMatrix, tank.tank_turret.position, forward, distance);
	MoveObjForward(tank.tank_gun.modelMatrix, tank.tank_gun.position, forward, distance);

    if(&tank == &this->tank)
		camera->MoveForward(distance);
}


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

    forward = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(forward, 1.0f)));
    // forward = glm::normalize(rotationMatrix * glm::vec4(forward, 1.f));
}

void Tema2::RotateTank(Tank& tank, float angle)
{
    RotateObject(tank.tank_rails.modelMatrix, tank.tank_rails.position, tank.tank_rails.forward, angle);
    RotateObject(tank.tank_body.modelMatrix, tank.tank_body.position, tank.tank_body.forward, angle);
    RotateObject(tank.tank_turret.modelMatrix, tank.tank_turret.position, tank.tank_turret.forward, angle);
    RotateObject(tank.tank_gun.modelMatrix, tank.tank_gun.position, tank.tank_gun.forward, angle);
}

void Tema2::CheckTanksCollision(Tank &tank1, Tank &tank2)
{
	float distance = glm::distance(tank1.tank_rails.position, tank2.tank_rails.position);
    if (distance < 1.3f)
    {
		float p = 1.3f - distance;
		glm::vec3 P = glm::normalize(tank1.tank_rails.position - tank2.tank_rails.position) * p;

		//MoveObjForward(tank1.tank_rails.modelMatrix, tank1.tank_rails.position, P, 0.5f);
  //      MoveObjForward(tank2.tank_rails.modelMatrix, tank2.tank_rails.position, -P, 0.5f);
        MoveTankForward(tank1, P, 0.5f);
        MoveTankForward(tank2, -P, 0.5f);

        RepositionateCamera();
	}
}

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

void Tema2::CheckTankBuildingCollision(Tank& tank, Building building)
{
    glm::vec3 dif = tank.tank_rails.position - building.position;

    if (abs(dif.x) < building.dimOx / 2.f + 0.7f && abs(dif.z) < building.dimOz / 2.f + 0.7f)
    {
		//float p = building.dimOx / 2 - abs(dif.x);
  //      glm::vec3 P = glm::normalize(glm::vec3(dif.x, 0, 0)) * p;

  //      MoveTankForward(tank, P, 0.5f);
  //      camera->MoveForward(-p * 0.5f);

  //      p = building.dimOz / 2 - abs(dif.z);
  //      P = glm::normalize(glm::vec3(0, 0, dif.z)) * p;

  //      MoveTankForward(tank, P, 0.5f);
  //      camera->MoveForward(-p * 0.5f);

        /////////////////////////////////////////////////////////////////////////////////

        //glm::vec3 P = ((building.dimOx / 2.f + 0.7f) * dif) / abs(dif.x) - dif;
        //MoveTankForward(tank, P, 1);
        //camera->MoveForward(-glm::length(P) * 1);

        /*glm::vec3 corner1 = building.position + glm::vec3(building.dimOx / 2.f, 0, building.dimOz / 2.f);
        glm::vec3 corner2 = building.position + glm::vec3(-building.dimOx / 2.f, 0, -building.dimOz / 2.f);
        glm::vec3 corner3 = building.position + glm::vec3(building.dimOx / 2.f, 0, -building.dimOz / 2.f);
        glm::vec3 corner4 = building.position + glm::vec3(-building.dimOx / 2.f, 0, building.dimOz / 2.f);

        if (isAboveFirstDiagonal(corner1.x, corner1.z, corner2.x, corner2.z, tank.tank_rails.position.x, tank.tank_rails.position.z))
        {
            if (isBelowSecondDiagonal(corner3.x, corner3.z, corner4.x, corner4.z, tank.tank_rails.position.x, tank.tank_rails.position.z))
            {
                cout << "1" << endl;
                float p = ((building.dimOx / 2.f) * glm::length(dif)) / abs(dif.x) - glm::length(dif);
                glm::vec3 P = -glm::normalize(dif) * p;

                MoveTankForward(tank, P, 1);

                RepositionateCamera();

                return;
            }
        }

        if (isAboveFirstDiagonal(corner3.x, corner3.z, corner4.x, corner4.z, tank.tank_rails.position.x, tank.tank_rails.position.z))
		{
            if (isBelowSecondDiagonal(corner1.x, corner1.z, corner2.x, corner2.z, tank.tank_rails.position.x, tank.tank_rails.position.z))
            {
                cout << "2" << endl;

                float p = ((building.dimOx / 2.f) * glm::length(dif)) / abs(dif.x) - glm::length(dif);
                glm::vec3 P = -glm::normalize(dif) * p;

                MoveTankForward(tank, P, 1);

                RepositionateCamera();

                return;
            }
        }

        cout << "3" << endl;
        float p = ((building.dimOz / 2.f) * glm::length(dif)) / abs(dif.z) - glm::length(dif);
        glm::vec3 P = -glm::normalize(dif) * p;

        MoveTankForward(tank, P, 1);

        RepositionateCamera();*/

        glm::vec3 P = -glm::normalize(dif) * std::min(building.dimOx / 2.f - abs(dif.x), building.dimOz / 2.f - abs(dif.z));
        MoveTankForward(tank, P, 1);

        //if(&tank == &this->tank)
        //    camera->MoveForward(-glm::length(P) * 1);

        RepositionateCamera();
	}
}

void Tema2::DetectTank(Tank& enemy)
{
    float distance = glm::distance(tank.tank_rails.position, enemy.tank_rails.position);

    if (distance < 5)
    {
        glm::vec3 new_forward = glm::normalize(tank.tank_body.position - enemy.tank_gun.position);
        float angle = acos(glm::dot(new_forward, enemy.tank_gun.forward));

        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::vec3 rotatedVector = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(enemy.tank_gun.forward, 1.0f)));

        if (abs(rotatedVector.x - new_forward.x) > 0.01f && abs(rotatedVector.z - new_forward.z) > 0.01f)
			angle = -angle;

        if(abs(angle) > 0.01f)
        {       
            RotateObject(enemy.tank_turret.modelMatrix, enemy.tank_turret.position, enemy.tank_turret.forward, angle);
            RotateObject(enemy.tank_gun.modelMatrix, enemy.tank_gun.position, enemy.tank_gun.forward, angle);
        }

        float time = Engine::GetElapsedTime();
        if (time - lastEnemyShot > 5)
        {
			Shoot(enemy);
			lastEnemyShot = time;
		}
    }
}

void Tema2::GenerateRandomMove(Tank& tank, float deltaTimeSeconds)
{
    if (Engine::GetElapsedTime() - tank.timeMoveGenerated > 4)
    {
        tank.moveType = rand() % 4;
        tank.timeMoveGenerated = Engine::GetElapsedTime();
    }

    switch (tank.moveType)
    {
        case 0:
        {
   	    	   MoveTankForward(tank, tank.tank_rails.forward, deltaTimeSeconds * 1.0f);
   	           break;
   	    }
   	    case 1:
        {
   	    	   RotateTank(tank, deltaTimeSeconds * 1);
   	    	   break;
   	    }
   	    case 2:
        {
   	    	   MoveTankForward(tank, tank.tank_rails.forward, -deltaTimeSeconds * 1.0f);
   	    	   break;
   	    }
   	    case 3:
        {
   	    	   RotateTank(tank, -deltaTimeSeconds * 1);
   	    	   break;
   	    }
   
    }
}

void Tema2::RenderScene(float deltaTimeSeconds)
{
    // Render tank
    {
        RenderSimpleMesh(meshes["rails"], shaders["LabShader"], tank.tank_rails.modelMatrix, true, tank.damage);
        RenderSimpleMesh(meshes["body"], shaders["LabShader"], tank.tank_body.modelMatrix, true, tank.damage);
        RenderSimpleMesh(meshes["turret"], shaders["LabShader"], tank.tank_turret.modelMatrix, true, tank.damage);
        RenderSimpleMesh(meshes["gun"], shaders["LabShader"], tank.tank_gun.modelMatrix, true, tank.damage);
    }

    RotateObject(tank.tank_turret.modelMatrix, tank.tank_turret.position, tank.tank_turret.forward, angle_mouse - old_angle_mouse);
    RotateObject(tank.tank_gun.modelMatrix, tank.tank_gun.position, tank.tank_gun.forward, angle_mouse - old_angle_mouse);
    old_angle_mouse = angle_mouse;

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

    // Render sky
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 10, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(100, 1, 100));
        RenderSimpleMesh(meshes["sky"], shaders["LabShader"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 50));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(1, 0, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(2, 1, 2));
        RenderSimpleMesh(meshes["sky"], shaders["LabShader"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, -50));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(1, 0, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(2, 1, 2));
        RenderSimpleMesh(meshes["sky"], shaders["LabShader"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(50, 0, 0));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 0, 1));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(2, 1, 2));
        RenderSimpleMesh(meshes["sky"], shaders["LabShader"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-50, 0, 0));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 0, 1));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(2, 1, 2));
        RenderSimpleMesh(meshes["sky"], shaders["LabShader"], modelMatrix);
    }

    {
        lightPosition = glm::vec3(5.f, 1.f, -1.f);
        glm::mat4 modelMatrix = glm::mat4(1);

        modelMatrix = glm::translate(modelMatrix, lightPosition);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));

        RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix);
    }

    for (auto& enemy_pair : enemies)
    {
        Tank& enemy = enemy_pair.second;
        GenerateRandomMove(enemy, deltaTimeSeconds);
    }

    for (auto& pair : projectiles)
    {
        RenderSimpleMesh(pair.second.mesh, shaders["LabShader"], pair.second.modelMatrix);
    }

    for (auto& pair : projectiles)
    {
        if (pair.second.mesh == meshes["projectile"])
        {
            //cout << "projectile" << endl;
            //cout << "position: " << pair.second.position.x << " " << pair.second.position.y << " " << pair.second.position.z << endl<<endl;
            MoveObjForward(pair.second.modelMatrix, pair.second.position, pair.second.forward, deltaTimeSeconds * 4.0f);

            // Check if projectile is out of bounds
            if (pair.second.timeCreated + 3 < Engine::GetElapsedTime())
            {
                objectsToBeRemoved[pair.first] = pair.second;
            }

            // Check building collision
            for (auto& building_pair : buildings)
            {
                glm::vec3 dif = pair.second.position - building_pair.second.position;

                if (abs(dif.x) < building_pair.second.dimOx / 2.f && abs(dif.z) < building_pair.second.dimOz / 2.f)
                {
                    objectsToBeRemoved[pair.first] = pair.second;
                }
            }
        }
    }

    for (auto& enemy_pair : enemies)
    {
        DetectTank(enemy_pair.second);
    }

    for (auto& enemy_pair : enemies)
    {
        Tank& enemy = enemy_pair.second;
        CheckTanksCollision(tank, enemy);
    }

    for (auto& tank_pair : enemies)
    {
        Tank& enemy = tank_pair.second;
        for (auto& building_pair : buildings)
        {
            CheckTankBuildingCollision(enemy, building_pair.second);
        }
    }

    for (auto& building_pair : buildings)
    {
        CheckTankBuildingCollision(tank, building_pair.second);
    }

    for (auto& projectile_pair : projectiles)
    {
        for (auto& enemy_pair : enemies)
        {
            if (projectile_pair.second.id == enemy_pair.first)
                continue;

            if (CheckTankProjectileCollision(enemy_pair.second, projectile_pair.second))
            {
                // Remove projectiles that hit tanks
                objectsToBeRemoved[projectile_pair.first] = projectile_pair.second;

                cout << "damage: " << enemy_pair.second.damage << endl;
            }

            if (enemy_pair.second.damage == 3)
            {
                // Remove tanks that are destroyed
                enemiesToBeRemoved[enemy_pair.first] = enemy_pair.second;
            }
        }

        if (projectile_pair.second.id == "MyTank")
            continue;

        if (CheckTankProjectileCollision(tank, projectile_pair.second))
        {
            // Remove projectiles that hit tanks
            objectsToBeRemoved[projectile_pair.first] = projectile_pair.second;

            cout << "damage: " << tank.damage << endl;
        }

        if (tank.damage >= 3)
        {
            // Remove tanks that are destroyed
            cout << "GAME OVER" << endl;
            exit(0);
        }
    }

    // Remove objects
    for (auto& pair : objectsToBeRemoved)
    {
        projectiles.erase(pair.first);
    }

    objectsToBeRemoved.clear();

    // Remove enemies
    for (auto& pair : enemiesToBeRemoved)
    {
        enemies.erase(pair.first);
        cout << "ENEMY DESTROYED" << endl;
        cout << "SCORE: " << ++score << endl;
    }

    enemiesToBeRemoved.clear();

    if (Engine::GetElapsedTime() > 120)
        exit(0);
}

void Tema2::Update(float deltaTimeSeconds)
{

    glm::ivec2 resolution = window->GetResolution();
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
    viewMatrix = camera->GetViewMatrix();
    glViewport(0, 0, resolution.x, resolution.y);

    RenderScene(deltaTimeSeconds);

    glClear(GL_DEPTH_BUFFER_BIT);
    projectionMatrix = glm::ortho(left, right, bottom, top, 0.01f, 200.0f);
    viewMatrix = glm::lookAt(tank.tank_body.position + glm::vec3(0, 9.f, 0), tank.tank_body.position, glm::vec3(0, 0, -1));
    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);

    // TODO(student): render the scene again, in the new viewport
    RenderScene(deltaTimeSeconds);

}


void Tema2::FrameEnd()
{
    // DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrixTank, bool isMyTank, int damage)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Set shader uniforms for light & material properties
    // TODO(student): Set light position uniform
    // glm::vec3 lightPosition = tank.tank_body.position + glm::vec3(0.f, 1.f, 0.f);
    glUniform3fv(glGetUniformLocation(shader->program, "light_position"), 1, glm::value_ptr(lightPosition));
    glUniform3fv(glGetUniformLocation(shader->program, "light_position2"), 1, glm::value_ptr(lightPosition2));


    glm::vec3 eyePosition = camera->position;
    // TODO(student): Set eye position (camera position) uniform
    glUniform3fv(glGetUniformLocation(shader->program, "eye_position"), 1, glm::value_ptr(eyePosition));

    // TODO(student): Set material property uniforms (shininess, kd, ks, object color)
    glUniform1i(glGetUniformLocation(shader->program, "material_shininess"), materialShininess);

    if(mesh == meshes["sky"])
		glUniform1f(glGetUniformLocation(shader->program, "material_kd"), 0.3f / 0.25f);
	else
		glUniform1f(glGetUniformLocation(shader->program, "material_kd"), materialKd);

    glUniform1f(glGetUniformLocation(shader->program, "material_ks"), materialKs);

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
    else if (mesh == meshes["sky"])
        glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(colorSky));
	else
		glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(colorBuilding));

    // Set damage uniform
     glUniform1i(glGetUniformLocation(shader->program, "damage"), damage);

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

    // Set shader uniform "Model" to modelMatrixTank
    glUniformMatrix4fv(location_model, 1, GL_FALSE, glm::value_ptr(modelMatrixTank));

    // Get shader location for uniform mat4 "View"
    int location_view = glGetUniformLocation(shader->program, "View");

    // Set shader uniform "View" to viewMatrix
    //glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    glUniformMatrix4fv(location_view, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Get shader location for uniform mat4 "Projection"
    int location_projection = glGetUniformLocation(shader->program, "Projection");

    // Set shader uniform "Projection" to projectionMatrix
    glUniformMatrix4fv(location_projection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    if (window->KeyHold(GLFW_KEY_W))
    {
        MoveTankForward(tank, tank.tank_rails.forward, deltaTime * 4.0f);
    }

    if (window->KeyHold(GLFW_KEY_A))
    {
        RotateTank(tank, deltaTime * 2);

        camera->distanceToTarget = glm::distance(camera->position, tank.tank_rails.position);
        camera->RotateThirdPerson_OY(deltaTime * 2);
    }

    if (window->KeyHold(GLFW_KEY_S))
    {
        MoveTankForward(tank, tank.tank_rails.forward, -deltaTime * 4.0f);
    }

    if (window->KeyHold(GLFW_KEY_D))
    {
        RotateTank(tank, -deltaTime * 2);

        camera->distanceToTarget = glm::distance(camera->position, tank.tank_rails.position);
        camera->RotateThirdPerson_OY(-deltaTime * 2);
    }
}

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


void Tema2::OnKeyRelease(int key, int mods)
{}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (window->GetSpecialKeyState() == 0) {
            camera->RotateThirdPerson_OX(-deltaY * sensivityOX);
            camera->RotateThirdPerson_OY(-deltaX * sensivityOY);
        }
    }

    angle_mouse = std::atan((float)((float)window->GetResolution().x / 2.0 - (float)mouseX) / ((float)window->GetResolution().y - (float)mouseY));
    //cout << (float)(window->GetResolution().x / 2.0 - (float)mouseX) / (window->GetResolution().y - (float)mouseY) << endl;

    //// double angle_mouse = CalculateAngle(mouseX, mouseY, window->GetResolution().x / 2, 0);
    //cout << "mouseX: " << mouseX << " mouseY: " << mouseY << endl;
    //cout << "angle_mouse: " << angle_mouse << endl;
}

void Tema2::Shoot(Tank& tank)
{
    glm::mat4 modelMatrix = glm::mat4(1);

    //glm::vec3 forward = glm::normalize(glm::vec3(camera->forward.x, 0, camera->forward.z));
    glm::vec3 forward = tank.tank_gun.forward;
    glm::vec3 position = glm::vec3(tank.tank_gun.position.x, 0.4f, tank.tank_gun.position.z);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));

    cout << "position before: " << position.x << " " << position.y << " " << position.z << endl;

    MoveObjForward(modelMatrix, position, forward, 1.f);


    cout << modelMatrix[0][0] << " " << modelMatrix[0][1] << " " << modelMatrix[0][2] << endl;
    cout << modelMatrix[1][0] << " " << modelMatrix[1][1] << " " << modelMatrix[1][2] << endl;
    cout << modelMatrix[2][0] << " " << modelMatrix[2][1] << " " << modelMatrix[2][2] << endl;
    cout << modelMatrix[3][0] << " " << modelMatrix[3][1] << " " << modelMatrix[3][2] << endl;

    cout << "position: " << position.x << " " << position.y << " " << position.z << endl;
    cout << "forward: " << forward.x << " " << forward.y << " " << forward.z << endl;
    cout << "tank_gun.position: " << tank.tank_gun.position.x << " " << tank.tank_gun.position.y << " " << tank.tank_gun.position.z << endl;
    cout << "tank_gun.forward: " << tank.tank_gun.forward.x << " " << tank.tank_gun.forward.y << " " << tank.tank_gun.forward.z << endl;

    std::string enemyName = "MyTank";

    for (auto& enemy : enemies)
    {
        if (&enemy.second == &tank)
        {
			enemyName = enemy.first;
			
            break;
		}
	}

    cout << "enemyName: " << enemyName << endl;

    projectiles["projectile" + std::to_string(projectileID++)] = GameObject(meshes["projectile"], position, forward, modelMatrix, Engine::GetElapsedTime(), enemyName);

    cout << "timeCreated: " << projectiles["projectile" + std::to_string(projectileID - 1)].timeCreated << endl;
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
    if (button == GLFW_MOUSE_BUTTON_2)
    {
        Shoot(tank);
    }
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{}


void Tema2::OnWindowResize(int width, int height)
{}
