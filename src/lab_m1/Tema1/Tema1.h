#pragma once

#include "components/simple_scene.h"

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

        // Struct to store the game objects
        struct GameObject {
            glm::vec2 center;
            glm::vec2 size;
            bool isBeingDragged = false;
            bool isDraggable = false;
            bool canPlaceObject = false;
            bool isClickable = false;
            Mesh* mesh;
            glm::vec3 color = glm::vec3(1, 1, 1);
            int strength = 1;
            bool isBeingDestroyed = false;
            float scale = 1;

            // Default constructor
            GameObject::GameObject() {
                GameObject(glm::vec2(0, 0), glm::vec2(0, 0), NULL);
            }

            // Constructor to initialize the class members
            GameObject::GameObject(glm::vec2 center, glm::vec2 size, Mesh* mesh) {
                this->center = center;
                this->size = size;
                this->mesh = mesh;
            }
        };

        // Structs for each type of object

        struct Cannon : GameObject
        {
            Cannon::Cannon(glm::vec2 center, glm::vec2 size, Mesh* mesh, glm::vec3 color)
            {
                this->center = center;
                this->size = size;
                this->mesh = mesh;
                this->isDraggable = true; // can be dragged
                this->color = color;
            }
        };

        struct Star : GameObject
        {
            Star::Star(glm::vec2 center, glm::vec2 size, Mesh* mesh)
            {
                this->center = center;
                this->size = size;
                this->mesh = mesh;
                this->isClickable = true; // can be clicked
            }
        };

        struct LaunchedStar : GameObject
        {
            LaunchedStar::LaunchedStar()
            {
                LaunchedStar(glm::vec2(0, 0), glm::vec2(0, 0), NULL, glm::vec3(1, 1, 1));
            }

            LaunchedStar::LaunchedStar(glm::vec2 center, glm::vec2 size, Mesh* mesh, glm::vec3 color)
            {
                this->center = center;
                this->size = size;
                this->mesh = mesh;
                this->color = color;
            }
        };

        struct Square : GameObject
        {
            Square::Square(glm::vec2 center, glm::vec2 size, Mesh* mesh)
            {
                this->center = center;
                this->size = size;
                this->mesh = mesh;
                this->canPlaceObject = true; // a cannon can be placed here
            }
        };

        struct Enemy : GameObject
        {
            Enemy::Enemy(glm::vec2 center, glm::vec2 size, Mesh* mesh, glm::vec3 color)
            {
                this->center = center;
                this->size = size;
                this->mesh = mesh;
                this->color = color;
                this->strength = 3; // 3 hits to destroy
            }
        };

        struct Line
        {
            std::unordered_map<std::string, GameObject> cannons; // cannons on the line
            std::unordered_map<std::string, GameObject> enemies; // enemies on the line
        };

        struct ViewportSpace
        {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}
            ViewportSpace(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace
        {
            LogicSpace() : x(0), y(0), width(1), height(1) {}
            LogicSpace(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {}
            float x;
            float y;
            float width;
            float height;
        };

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        bool Tema1::CheckCollision(glm::vec2 center1, glm::vec2 size1, glm::vec2 center2, glm::vec2 size2);
        void Tema1::Shoot();
        void Tema1::GenerateStars();
        void Tema1::GenerateEnemies();
        void Tema1::CheckStarEnemyCollision();
        bool Tema1::MouseHover(int mouseX, int mouseY, glm::vec2 center, glm::vec2 size);
        void Tema1::Pay(Mesh* mesh);
        bool Tema1::IsSpotOcupied(glm::vec2 center);
        void Tema1::RemoveObject(const std::string& objName);
        void Tema1::CheckCannonEnemyCollision();

    protected:

        std::unordered_map<std::string, GameObject> gameObjects; // all the game objects
        std::vector<std::string> objectsToRemove; // objects to be removed from the game
        GameObject obj;

        Line lines[3]; // the 3 lines

        glm::mat3 modelMatrix = glm::mat3(1);
        float angularStep = 0;

        int lives = 3;
        int starsCount = 0; 
        int starsCollected = 6;
        float time = 0;
        float timeToShoot = 0;
        float timeToGenerateStars = 0;
		float timeToGenerateEnemies = 0;
        int cannonID = 0;
        int enemyID = 0;
        int starsLaunched = 0;

        // colors
        glm::vec3 red = glm::vec3(1, 0, 0);
        glm::vec3 green = glm::vec3(0, 1, 0);
        glm::vec3 blue = glm::vec3(0, 0, 1);
        glm::vec3 yellow = glm::vec3(1, 1, 0);
        glm::vec3 orange = glm::vec3(1, 0.5, 0);
        glm::vec3 purple = glm::vec3(0.5, 0, 0.5);
        glm::vec3 white = glm::vec3(1, 1, 1);
        glm::vec3 jordyBlue = glm::vec3(143.0 / 255, 184.0 / 255, 222.0 / 255);
        glm::vec3 raisinBlack = glm::vec3(46.0 / 255, 40.0 / 255, 42.0 / 255);
        glm::vec3 lightGreen = glm::vec3(124.0 / 255, 234.0 / 255, 156.0 / 255);
        glm::vec3 coolGray = glm::vec3(154.0 / 255, 148.0 / 255, 188.0 / 255);
        glm::vec3 lightGray = glm::vec3(0.5, 0.5, 0.5);
        glm::vec3 hunyadiYellow = glm::vec3(246.0 / 255, 174.0 / 255, 45.0 / 255);
        glm::vec3 lavanderPink = glm::vec3(226.0 / 255, 163.0 / 255, 199.0 / 255);
        glm::vec3 snow = glm::vec3(253.0 / 255, 247.0 / 255, 250.0 / 255);

        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        glm::mat3 visMatrix;
    };
}
