#pragma once

#include <vector>

#include "components/simple_scene.h"
#include "lab_camera.h"

namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
    public:

        struct GameObject
        {
			GameObject() : mesh(nullptr), position(glm::vec3(0)), forward(glm::vec3(0)), modelMatrix(glm::mat4(1)) {}
			GameObject(Mesh* mesh, glm::vec3 position, glm::vec3 forward)
				: mesh(mesh), position(position), forward(forward), modelMatrix(glm::mat4(1)) {}
            GameObject(Mesh* mesh, glm::vec3 position, glm::vec3 forward, glm::mat4 modelMatrix)
				: mesh(mesh), position(position), forward(forward), modelMatrix(modelMatrix) {}
            GameObject(Mesh* mesh, glm::vec3 position, glm::vec3 forward, glm::mat4 modelMatrix, float timeCreated)
                : mesh(mesh), position(position), forward(forward), modelMatrix(modelMatrix), timeCreated(timeCreated) {}

			Mesh* mesh;
			glm::vec3 position;
            glm::vec3 forward;
            glm::mat4 modelMatrix;
            float timeCreated = 0;
		};

        struct Tank
        {
			Tank() : tank_rails(), tank_body(), tank_turret(), tank_gun() {}
			Tank(GameObject tank_rails, GameObject tank_body, GameObject tank_turret, GameObject tank_gun)
				: tank_rails(tank_rails), tank_body(tank_body), tank_turret(tank_turret), tank_gun(tank_gun) {}

            GameObject tank_rails;
			GameObject tank_body;
			GameObject tank_turret;
			GameObject tank_gun;
		};

        struct ViewportArea
        {
            ViewportArea() : x(0), y(0), width(1), height(1) {}
            ViewportArea(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        Tema2();
        ~Tema2();

        void Init() override;

        Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void Tema2::CheckTanksCollision(Tank& tank1, Tank& tank2);
        void Tema2::MoveTankForward(Tank& tank, glm::vec3 forward, float distance);
        void Tema2::RotateTank(Tank& tank, float angle);
        void Tema2::RotateObject(glm::mat4& modelMatrix, glm::vec3& position, glm::vec3& forward, float angle);
    protected:
        implemented::MyCamera* camera;
        bool renderCameraTarget;

        std::unordered_map<std::string, GameObject> projectiles;
        std::unordered_map<std::string, GameObject> objectsToBeRemoved;
        GameObject tank_rails, tank_body, tank_turret, tank_gun;

        Tank tank = Tank(tank_rails, tank_body, tank_turret, tank_gun);
        std::vector<Tank> enemies;

        glm::vec3 tankPosition = glm::vec3(0, 0, 0);
        bool up = false;
        float tankAngle = 0;

        int projectileID = 0;

        glm::mat4 modelMatrix;
        glm::mat4 modelMatrixTank;
        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;
        float FoV = RADIANS(60);
        float left = -10.0f;
        float right = 10.0f;
        float bottom = -10.0f;
        float top = 10.0f;
        ViewportArea miniViewportArea;

        glm::vec3 lightPosition = glm::vec3(0, 1, 1);
        unsigned int materialShininess = 30;
        float materialKd = 0.5;
        float materialKs = 0.5;
        glm::vec3& color = glm::vec3(1, 0, 0); // red
    };
}   // namespace m1
