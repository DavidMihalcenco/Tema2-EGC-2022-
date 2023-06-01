#pragma once

#include "components/simple_scene.h"
#include "lab_m1/lab5/lab_camera.h"


namespace m1
{
    class Lab5 : public gfxc::SimpleScene
    {
    public:
        Lab5();
        ~Lab5();

        void Init() override;

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

    protected:
        implemented::Camera* camera;
        glm::mat3 modelMatrix;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;
        std::vector<glm::vec3> allVertices;
        glm::mat4 modelMatrixF = glm::mat4(1);
        std::vector<glm::vec3> roadF;
        std::vector<glm::vec3> treePath;
        glm::vector<int> nrCars;
        glm::vector<glm::vector<glm::vec3>> allRoads;
        std::vector<glm::vec3> treeRight;
        std::vector<glm::vec3> treeLeft;
        glm::mat4 carMatrix;
        // PERSPECTIVE
        bool isPerspective;
        float fov;
        float aspectRatio;

        // ORTHO
        float isOrtho;
        float left;
        float right;
        float bottom;
        float top;
        float angle;
        float sAngle;
        float zNear;
        float zFar;
        int steps;
        int nrObs;
        float carSpeed;

        // TODO(student): If you need any other class variables, define them here.
        Mesh* CreateRoad(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
        bool Lab5::SameSide(glm::vec3 p1, glm::vec3 p2, glm::vec3 a, glm::vec3 b);
        bool Lab5::PointInTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c);
        bool Lab5::CheckColision(std::vector<glm::vec3> allVertices, glm::vec3 p);
        float Lab5::GetAngle(glm::vec3 curent, glm::vec3 next, float scaleF);
        bool Lab5::checkCollisionObj(glm::vec3 o1, glm::vec3 o2);
        bool Lab5::checkAllCollisions(glm::vec3 p);
        void Lab5::genNewRoute();
        void Lab5::genTreePosition();
        void Lab5::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, glm::mat4 proj, glm::mat4 viewMatrix);
        Mesh* Lab5::CreateGrassNew(const std::string& name,glm::vec3 leftBottomCorner,float length,glm::vec3 color,bool fill);
        Mesh* Lab5::CreateSquare(const std::string& name, float length ,glm::vec3 color, bool fill);
    };
}   // namespace m1
