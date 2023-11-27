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
    glm::vec3 position = glm::vec3(0, 1.3, tankPosition.z + 3);
    camera->Set(position, normalize(tankPosition + position), glm::vec3(0, 1, 0));
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
    viewMatrix = camera->GetViewMatrix();

    // camera->MoveForward(20);
    // camera->RotateThirdPerson_OY(RADIANS(180));

    {
        Mesh* mesh = new Mesh("plane");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

  //  {
  //      Mesh* mesh = new Mesh("building1");
		//mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "building1.obj");
		//meshes[mesh->GetMeshID()] = mesh;
  //      buildings["building1"] = Building(mesh, glm::vec3(-10, 0, 4), 2.f, 2.f);
  //  }

    {
        Mesh *mesh = new Mesh("building2");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "building2.obj");
        meshes[mesh->GetMeshID()] = mesh;
        buildings["building2"] = Building(mesh, glm::vec3(-20, 0, 8), 14.f, 10.f);
    }

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

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        glm::vec3 position = glm::vec3(-3, 0, 5);
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
    }

    // Create a shader program for drawing face polygon with the color of the normal
    {
        Shader* shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);

    // Render buildings
    for (auto& pair : buildings)
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, pair.second.position);
		RenderSimpleMesh(pair.second.mesh, shaders["LabShader"], modelMatrix);
	}
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
	MoveObjForward(tank.tank_rails.modelMatrix, tank.tank_rails.position, forward, distance);
	MoveObjForward(tank.tank_body.modelMatrix, tank.tank_body.position, forward, distance);
	MoveObjForward(tank.tank_turret.modelMatrix, tank.tank_turret.position, forward, distance);
	MoveObjForward(tank.tank_gun.modelMatrix, tank.tank_gun.position, forward, distance);
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

        camera->MoveForward(-p * 0.5f);
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

        glm::vec3 P = -glm::normalize(dif) * std::min(building.dimOx / 2.f - abs(dif.x), building.dimOz / 2.f - abs(dif.z));
        MoveTankForward(tank, P, 1);
        camera->MoveForward(-glm::length(P) * 1);
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

void Tema2::Update(float deltaTimeSeconds)
{
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

    {
        glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -0.15f, 0));
		RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix);
    }

    for (auto& pair : projectiles)
    {
        RenderSimpleMesh(pair.second.mesh, shaders["LabShader"], pair.second.modelMatrix);
	}

    for (auto& pair : projectiles)
    {
		if(pair.second.mesh == meshes["projectile"])
        {
            //cout << "projectile" << endl;
            //cout << "position: " << pair.second.position.x << " " << pair.second.position.y << " " << pair.second.position.z << endl<<endl;
            MoveObjForward(pair.second.modelMatrix, pair.second.position, pair.second.forward, deltaTimeSeconds * 4.0f);

            // Check if projectile is out of bounds
            if (pair.second.timeCreated + 3 < Engine::GetElapsedTime())
            {
				objectsToBeRemoved[pair.first]= pair.second;
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
            if(projectile_pair.second.id == enemy_pair.first)
				continue;

            if (CheckTankProjectileCollision(enemy_pair.second, projectile_pair.second))
            {
                // Remove projectiles that hit tanks
                objectsToBeRemoved[projectile_pair.first] = projectile_pair.second;

                cout << "damage: " << enemy_pair.second.damage << endl;
            }

            if (enemy_pair.second.damage >= 3)
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
	}

    enemiesToBeRemoved.clear();
}


void Tema2::FrameEnd()
{
    // if(viewMatrix == GetSceneCamera()->GetViewMatrix())
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrixTank, bool isMyTank, int damage)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Set shader uniforms for light & material properties
    // TODO(student): Set light position uniform
    glUniform3fv(glGetUniformLocation(shader->program, "light_position"), 1, glm::value_ptr(lightPosition));

    glm::vec3 eyePosition = camera->position;
    // TODO(student): Set eye position (camera position) uniform
    glUniform3fv(glGetUniformLocation(shader->program, "eye_position"), 1, glm::value_ptr(eyePosition));

    // TODO(student): Set material property uniforms (shininess, kd, ks, object color)
    glUniform1i(glGetUniformLocation(shader->program, "material_shininess"), materialShininess);
    glUniform1f(glGetUniformLocation(shader->program, "material_kd"), materialKd);
    glUniform1f(glGetUniformLocation(shader->program, "material_ks"), materialKs);

    // Set colorSphere to red
    glm::vec3& colorSphere = glm::vec3(1, 0, 0); // red
    // Set colorPlane to dark grey
    glm::vec3& colorPlane = glm::vec3(0.2, 0.2, 0.2); // dark grey
    glm::vec3& green = glm::vec3(0, 1, 0); // green

    if (isMyTank)
        glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(green));
    else if (mesh == meshes["plane"])
        glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(colorPlane));
    else
        glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(colorSphere));

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
    glUniformMatrix4fv(location_view, 1, GL_FALSE, glm::value_ptr( camera->GetViewMatrix()));

    // Get shader location for uniform mat4 "Projection"
    int location_projection = glGetUniformLocation(shader->program, "Projection");

    // Set shader uniform "Projection" to projectionMatrix
    glUniformMatrix4fv(location_projection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // BONUS
    int location_time = glGetUniformLocation(shader->program, "Time");
    glUniform1f(location_time, Engine::GetElapsedTime());

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    if (window->KeyHold(GLFW_KEY_W))
    {
        MoveTankForward(tank, tank.tank_rails.forward, deltaTime * 4.0f);
        camera->MoveForward(deltaTime * 4);
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

        camera->MoveForward(-deltaTime * 4);
    }

    if (window->KeyHold(GLFW_KEY_D))
    {
        RotateTank(tank, -deltaTime * 2);

        camera->distanceToTarget = glm::distance(camera->position, tank.tank_rails.position);
        camera->RotateThirdPerson_OY(-deltaTime * 2);
    }
}


void Tema2::OnKeyPress(int key, int mods)
{
    if (key == GLFW_KEY_C)
    {
        // Set camera posision behind tank
        glm::vec3 position = tank.tank_rails.position - 3.f * tank.tank_rails.forward;
        position.y = 1.3f;
        camera->Set(position, normalize(2.f * position + tank.tank_rails.forward), glm::vec3(0, 1, 0));
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
