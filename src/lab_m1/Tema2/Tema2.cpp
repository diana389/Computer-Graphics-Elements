#include "lab_m1/Tema2/Tema2.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


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
        glm::vec3 forward = glm::vec3(0, 0, -1);
        modelMatrix = glm::translate(modelMatrix, position);

        Tank tank = Tank(GameObject(meshes["rails"], position, forward, modelMatrix),
            GameObject(meshes["body"], position, forward, modelMatrix),
            GameObject(meshes["turret"], position, forward, modelMatrix),
            GameObject(meshes["gun"], position, forward, modelMatrix));

        enemies.push_back(tank);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        glm::vec3 position = glm::vec3(6, 0, 2);
        glm::vec3 forward = glm::vec3(1, 0, 1);
        modelMatrix = glm::translate(modelMatrix, position);

        Tank tank = Tank(GameObject(meshes["rails"], position, forward, modelMatrix),
            GameObject(meshes["body"], position, forward, modelMatrix),
            GameObject(meshes["turret"], position, forward, modelMatrix),
            GameObject(meshes["gun"], position, forward, modelMatrix));

        enemies.push_back(tank);
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

        enemies.push_back(tank);
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

void Tema2::Update(float deltaTimeSeconds)
{
    // CheckTanksCollision(tank_rails, tank_rails);

    {
        RenderSimpleMesh(meshes["rails"], shaders["LabShader"], tank.tank_rails.modelMatrix);
        RenderSimpleMesh(meshes["body"], shaders["LabShader"], tank.tank_rails.modelMatrix);
        RenderSimpleMesh(meshes["turret"], shaders["LabShader"], tank.tank_rails.modelMatrix);
        RenderSimpleMesh(meshes["gun"], shaders["LabShader"], tank.tank_rails.modelMatrix);
    }

    for (Tank& enemy : enemies)
    {
		RenderSimpleMesh(enemy.tank_rails.mesh, shaders["LabShader"], enemy.tank_rails.modelMatrix);
		RenderSimpleMesh(enemy.tank_body.mesh, shaders["LabShader"], enemy.tank_rails.modelMatrix);
		RenderSimpleMesh(enemy.tank_turret.mesh, shaders["LabShader"], enemy.tank_rails.modelMatrix);
		RenderSimpleMesh(enemy.tank_gun.mesh, shaders["LabShader"], enemy.tank_rails.modelMatrix);
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

    // Remove objects that are out of bounds
    for (auto& pair : objectsToBeRemoved)
    {
        projectiles.erase(pair.first);
    }

    objectsToBeRemoved.clear();

    for (Tank& enemy : enemies)
    {
        CheckTanksCollision(tank, enemy);
	}
}


void Tema2::FrameEnd()
{
    // if(viewMatrix == GetSceneCamera()->GetViewMatrix())
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrixTank)
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

    //if (mesh == meshes["sphere"])
    //    glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(colorSphere));
    //else if (mesh == meshes["plane"])
    //    glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(colorPlane));
    //else
        glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(colorSphere));

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

	forward = rotationMatrix * glm::vec4(forward, 1.f);
}

void Tema2::RotateTank(Tank& tank, float angle)
{
	RotateObject(tank.tank_rails.modelMatrix, tank.tank_rails.position, tank.tank_rails.forward, angle);
    RotateObject(tank.tank_body.modelMatrix, tank.tank_body.position, tank.tank_body.forward, angle);
    RotateObject(tank.tank_turret.modelMatrix, tank.tank_turret.position, tank.tank_turret.forward, angle);
    RotateObject(tank.tank_gun.modelMatrix, tank.tank_gun.position, tank.tank_gun.forward, angle);
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    if (window->KeyHold(GLFW_KEY_W))
    {
        //glm::vec3 forward = glm::normalize(glm::vec3(camera->forward.x, 0, camera->forward.z));

        //MoveObjForward(tank.tank_rails.modelMatrix, tank.tank_rails.position, tank.tank_rails.forward, deltaTime * 4.0f);
        MoveTankForward(tank, tank.tank_rails.forward, deltaTime * 4.0f);
        camera->MoveForward(deltaTime * 4);
    }

    if (window->KeyHold(GLFW_KEY_A))
    {
        //glm::mat4 translationMatrix = glm::mat4(1);
        //translationMatrix = glm::translate(translationMatrix, -tank.tank_rails.position);
        //tank.tank_rails.modelMatrix = translationMatrix * tank.tank_rails.modelMatrix;

        //glm::mat4 rotationMatrix = glm::mat4(1);
        //rotationMatrix = glm::rotate(rotationMatrix, deltaTime * 2, glm::vec3(0, 1, 0));
        //tank.tank_rails.modelMatrix = rotationMatrix * tank.tank_rails.modelMatrix;

        //translationMatrix = glm::mat4(1);
        //translationMatrix = glm::translate(translationMatrix, tank.tank_rails.position);
        //tank.tank_rails.modelMatrix = translationMatrix * tank.tank_rails.modelMatrix;

        ////cout << "TANK RAILS FORWARD:";
        ////cout << tank_rails.forward.x << " " << tank_rails.forward.y << " " << tank_rails.forward.z << endl;
        ////cout << "COS: " << cos(deltaTime * 2) << endl;
        //tank.tank_rails.forward = rotationMatrix * glm::vec4(tank.tank_rails.forward, 1.f);
        //cout << tank_rails.forward.x << " " << tank_rails.forward.y << " " << tank_rails.forward.z << endl;

        RotateTank(tank, deltaTime * 2);

        camera->distanceToTarget = glm::distance(camera->position, tank.tank_rails.position);
        camera->RotateThirdPerson_OY(deltaTime * 2);
    }

    if (window->KeyHold(GLFW_KEY_S))
    {
        //glm::vec3 forward = glm::normalize(glm::vec3(camera->forward.x, 0, camera->forward.z));

        //MoveObjForward(tank.tank_rails.modelMatrix, tank.tank_rails.position, tank.tank_rails.forward, -deltaTime * 4.0f);
        MoveTankForward(tank, tank.tank_rails.forward, -deltaTime * 4.0f);

        camera->MoveForward(-deltaTime * 4);
    }

    if (window->KeyHold(GLFW_KEY_D))
    {
        //glm::mat4 translationMatrix = glm::mat4(1);
        //translationMatrix = glm::translate(translationMatrix, -tank.tank_rails.position);
        //tank.tank_rails.modelMatrix = translationMatrix * tank.tank_rails.modelMatrix;

        //glm::mat4 rotationMatrix = glm::mat4(1);
        //rotationMatrix = glm::rotate(rotationMatrix, - deltaTime * 2, glm::vec3(0, 1, 0));
        //tank.tank_rails.modelMatrix = rotationMatrix * tank.tank_rails.modelMatrix;

        //translationMatrix = glm::mat4(1);
        //translationMatrix = glm::translate(translationMatrix, tank.tank_rails.position);
        //tank.tank_rails.modelMatrix = translationMatrix * tank.tank_rails.modelMatrix;

        //tank.tank_rails.forward = rotationMatrix * glm::vec4(tank.tank_rails.forward, 1.f);

        RotateTank(tank, -deltaTime * 2);

        camera->distanceToTarget = glm::distance(camera->position, tank.tank_rails.position);
        camera->RotateThirdPerson_OY(-deltaTime * 2);
    }
}


void Tema2::OnKeyPress(int key, int mods)
{
    if (key == GLFW_KEY_C)
    {
        glm::vec3 position = tank.tank_rails.position - 3.f * tank.tank_rails.forward;
        position.y = 1.3f;
        camera->Set(position, normalize(2.f * position + tank.tank_rails.forward), glm::vec3(0, 1, 0));
        //camera->forward = tank_rails.forward;
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
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
    if (button == GLFW_MOUSE_BUTTON_2)
    {
        glm::mat4 modelMatrix = glm::mat4(1);

        //glm::vec3 forward = glm::normalize(glm::vec3(camera->forward.x, 0, camera->forward.z));
        glm::vec3 forward = tank.tank_rails.forward;
        glm::vec3 position = glm::vec3(tank.tank_rails.position.x, 0.4f, tank.tank_rails.position.z);
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
        cout << "tank_rails.position: " << tank.tank_rails.position.x << " " << tank.tank_rails.position.y << " " << tank.tank_rails.position.z << endl;
        cout << "tank_rails.forward: " << tank.tank_rails.forward.x << " " << tank.tank_rails.forward.y << " " << tank.tank_rails.forward.z << endl;

        projectiles["projectile" + std::to_string(projectileID++)] = GameObject(meshes["projectile"], position, forward, modelMatrix, Engine::GetElapsedTime());

        cout << "timeCreated: " << projectiles["projectile" + std::to_string(projectileID - 1)].timeCreated << endl;
    }
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{}


void Tema2::OnWindowResize(int width, int height)
{}
