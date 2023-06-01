#include "lab_m1/lab5/lab5.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;
#define POINT_NR 100
#define SCALE_F 3
#define ROADPOINTSNR 40
#define TREEDENS 2
#define NRCARS 5
#define GRASSP -20

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab5::Lab5()
{
    isOrtho = true;
    isPerspective = false;
    left = -4.0f;
    right = 4.0f;
    bottom = -4.0f;
    top = 4.0f;
    zFar = 200;
    zNear = 0.1f;
    fov = 45;
    aspectRatio = window->props.aspectRatio;
}

Mesh* Lab5::CreateGrassNew(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
 
    int nr_squares = 150;
    std::vector<VertexFormat> vertices;
    for (int j = 0; j < nr_squares; j++) {
        for (int i = 0; i < nr_squares; i++) {
            glm::vec3 corner = glm::vec3((length * i), 0, (length * j));
            vertices.push_back(VertexFormat(corner, color));
        }
    
    }
    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices;

   for (int k = 0; k < nr_squares-1; k++) {
        for (int i = 0 ; i < nr_squares-1; i++) {
            indices.push_back(0 + i + (nr_squares * k));
            indices.push_back(nr_squares + i + (nr_squares * k));
            indices.push_back((nr_squares + 1) + i + (nr_squares * k));

            indices.push_back(0 + i + (nr_squares * k));
            indices.push_back(1 + i + (nr_squares * k));
            indices.push_back((nr_squares + 1) + i + (nr_squares * k));
            
        }

    }
   if (!fill) {
       square->SetDrawMode(GL_LINE_LOOP);
   }
 
    square->InitFromData(vertices, indices);
    return square;
}


Mesh* Lab5::CreateSquare(
    const std::string& name, float size, glm::vec3 color,
    bool fill) {
    glm::vector<glm::vec3> box = {
         glm::vec3(-1, -0.5, -0.5),
         glm::vec3(1, -0.5, -0.5),
         glm::vec3(1, -0.5, 0.5),
         glm::vec3(-1, -0.5, 0.5),
         glm::vec3(-1, 0.5, -0.5),
         glm::vec3(1, 0.5, -0.5),
         glm::vec3(1, 0.5, 0.5),
         glm::vec3(-1, 0.5, 0.5)
    };
   
    std::vector<VertexFormat> vertices;
    for (int i = 0; i < box.size(); i++) {
        vertices.push_back(VertexFormat(box.at(i), color));
    }
    
    Mesh* tree = new Mesh(name);
    std::vector<unsigned int> indices = {
        // tree
        0, 1, 2,
        0, 2, 3,
        0, 4, 3,
        3, 4, 7,
        0, 1, 4,
        1, 4, 5,
        1, 2, 5,
        2, 5, 6,
        2, 3, 6,
        3, 6, 7,
        4, 5, 6,
        4, 6, 7,
    };

    for (int i = 0; i < box.size(); i++) {
        vertices.push_back(VertexFormat(box.at(i), color));
    }

    if (!fill) {
        tree->SetDrawMode(GL_LINE_LOOP);
    }

    tree->InitFromData(vertices, indices);
    return tree;
}

Mesh* Lab5::CreateRoad(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<glm::vec3> road1 = { glm::vec3(-2, 0, 3),  //A 1
       glm::vec3(-2.6, 0, 2.93), // B 2
       glm::vec3(-3.05, 0, 2.76),  // C 3
       glm::vec3(-3.39, 0, 2.57),  //D 4
       glm::vec3(-3.79, 0, 2.27), //E 5
       glm::vec3(-4.17, 0, 1.76), // F 6
       glm::vec3(-4.25, 0, 1.19),  // G 7 
       glm::vec3(-4.29, 0, 0.54),  // H 8 
       glm::vec3(-4.13, 0, 0.1),  // I 9 
       glm::vec3(-3.92, 0, -0.43),  // J 10
       glm::vec3(-3.24, 0, -0.72), // K 11
       glm::vec3(-2.37, 0, -0.82),  // L 12

       glm::vec3(-1.5, 0, -0.72),  //M 13
       glm::vec3(-0.57, 0, -0.57),  // N 14
       glm::vec3(0.21, 0, -0.55),  // O 15
       glm::vec3(0.98, 0, -0.76),  //P 16
       glm::vec3(1.6, 0, -1.12),  //Q 17
       glm::vec3(2.21, 0, -1.39),  // R 18
       glm::vec3(3.12, 0, -1.55),  // S 19
       glm::vec3(3.77, 0, -1.32),  // T 20
       glm::vec3(4.43, 0, -0.89),  // U 21
       glm::vec3(5.1, 0, -0.5),  // V 22
       glm::vec3(5.65, 0, 0),  // W 23
       glm::vec3(6.03, 0, 0.62),  // Z 24

       glm::vec3(6.18, 0, 1.22),  //A1 25
       glm::vec3(6.03, 0, 1.84),  // B1 26
       glm::vec3(5.67, 0, 2.39),  //C1 27
       glm::vec3(5.2, 0, 2.84), // D1 28
       glm::vec3(4.56, 0, 3.24),  // E1 29
       glm::vec3(3.93, 0, 3.41), // F1 30
       glm::vec3(3.32, 0, 3.34),  // G1 31
       glm::vec3(3, 0, 3), // H1 32
       glm::vec3(2.5, 0, 2.69),  // I1 33
       glm::vec3(2.07, 0, 2.31),  // J1 34

       glm::vec3(1.65, 0, 2.31),//K1 35
       glm::vec3(0.88, 0, 2.46), // L1 36
       glm::vec3(0.4, 0, 2.79),  // M1 37
       glm::vec3(-0.38, 0, 3.08),  //N1 38
       glm::vec3(-0.77, 0, 3.17),  // O1 39
       glm::vec3(-1.39, 0, 3.17)//P1 40
    };
    treePath = road1;
    int i = 0;
    while (i < road1.size()) {
        glm::vec3 pointA;
        glm::vec3 pointB;
        if (i == road1.size() - 1) {
            
            pointA = road1.at(0);
            pointB = road1.at(road1.size()-1);
            float diff_X = pointB.x - pointA.x;
            float diff_Z = pointB.z - pointA.z;

            float interval_X = diff_X / (POINT_NR + 1);
            float interval_Z = diff_Z / (POINT_NR + 1);

            for (int j = 1; j <= POINT_NR; j++)
            {
                roadF.push_back(glm::vec3(pointA.x + interval_X * j, 0, pointA.z + interval_Z * j));
            }
            i += 1;

        }
        else {
            pointA = road1.at(i);
            pointB = road1.at(i+1);

            float diff_X = pointB.x - pointA.x;
            float diff_Z = pointB.z - pointA.z;

            float interval_X = diff_X / (POINT_NR + 1);
            float interval_Z = diff_Z / (POINT_NR + 1);

            for (int j = 1; j <= POINT_NR; j++)
            {
                roadF.push_back(glm::vec3(pointA.x + interval_X * j, 0, pointA.z + interval_Z * j));
            }
            i += 1;
        }
    }
    std::vector<glm::vec3> r;
    std::vector<glm::vec3> a;
    glm::vec3 d;
    glm::vec3 p;
    i = 0;
    while (i < road1.size()) {
        if (i == road1.size() - 1) {
            d = road1.at(0) - road1.at(road1.size() - 1);
            p = glm::normalize(cross(d, glm::vec3(0, 1, 0)));
            r.push_back(road1.at(i) + p * glm::vec3(0.4, 0.4, 0.4));
            a.push_back(road1.at(i) - p * glm::vec3(0.4, 0.4, 0.4));
            i += 1;
        }
        else {
            d = road1.at(i + 1) - road1.at(i);
            p = glm::normalize(cross(d, glm::vec3(0, 1, 0)));
            r.push_back(road1.at(i) + p * glm::vec3(0.4, 0.4, 0.4));
            a.push_back(road1.at(i) - p * glm::vec3(0.4, 0.4, 0.4));
            i += 1;
        }  
    }
    std::vector<VertexFormat> vertices;
    
    for (int i = 0; i < r.size(); i++) {
        vertices.push_back(VertexFormat(r.at(i),color));
        allVertices.push_back(r.at(i));
    }
   
    for (int i = 0; i < a.size(); i++) {
        vertices.push_back(VertexFormat(a.at(i),color));
        allVertices.push_back(a.at(i));
    }
    Mesh* road = new Mesh(name);
    std::vector<unsigned int> indices;
    for (int i = 0; i <  road1.size() - 1 ; i++) {
        indices.push_back(i);
        indices.push_back(i + 1);
        indices.push_back(road1.size() + i);
        indices.push_back(i + 1);
        indices.push_back(road1.size() + i);
        indices.push_back(road1.size() + i + 1);
    }
    indices.push_back(road1.size() - 1);
    indices.push_back(0);
    indices.push_back(road1.size()*2 - 1);

    indices.push_back(0);
    indices.push_back(road1.size() * 2 - 1);
    indices.push_back(road1.size());

    if (!fill) {
        road->SetDrawMode(GL_LINE_LOOP);
    }

    road->InitFromData(vertices, indices);
    return road;
}

bool Lab5::SameSide(glm::vec3 p1, glm::vec3 p2, glm::vec3 a, glm::vec3 b) {
    glm::vec3 cp1;
    glm::vec3 cp2;
    cp1 = cross(b-a, p1-a);
    cp2 = cross(b-a, p2-a);
    if (dot(cp1, cp2) >= 0) {
        return true;
    }
    else {
        return false;
    }
}

bool Lab5::PointInTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c) {
    if (SameSide(p, a, b, c) && SameSide(p, b, a, c) && SameSide(p, c, a, b)) {
        return true;
    }
    else {
        return false;
    }
}

float Lab5::GetAngle(glm::vec3 curent, glm::vec3 next, float scaleF) {
    float x = curent.x * scaleF;
    float z = curent.z * scaleF;
    float x1 = next.x * scaleF;
    float z1 = next.z * scaleF;

    curent = glm::vec3(x, 0, z);
    next = glm::vec3(x1, 0, z1);

    float delta_x = next.x - curent.x;
    float delta_z = next.z - curent.z;
    float theta_radians = atan2(delta_z, delta_x);
    return (M_PI/2) - theta_radians;
}

bool Lab5::CheckColision(std::vector<glm::vec3> allVertices, glm::vec3 p) {
    for (int i = 0; i < (allVertices.size() / 2) - 1; i++) {
        glm::vec3 a = allVertices.at(i);
        glm::vec4 a1 = glm::vec4(a.x, a.y, a.z, 1) * modelMatrixF;
        a = glm::vec3(a1.x, a1.y, a1.z);
        glm::vec3 b = allVertices.at(i + 1);
        glm::vec4 b1 = glm::vec4(b.x, b.y, b.z, 1) * modelMatrixF;
        b = glm::vec3(b1.x, b1.y, b1.z);
        glm::vec3 c = allVertices.at((allVertices.size() / 2) + i);
        glm::vec4 c1 = glm::vec4(c.x, c.y, c.z, 1) * modelMatrixF;
        c = glm::vec3(c1.x, c1.y, c1.z);
        glm::vec3 d = allVertices.at((allVertices.size() / 2) + i + 1);
        glm::vec4 d1 = glm::vec4(d.x, d.y, d.z, 1) * modelMatrixF;
        d = glm::vec3(d1.x, d1.y, d1.z);

        glm::vec3 e = allVertices.at(0);
        glm::vec4 e1 = glm::vec4(e.x, e.y, e.z, 1) * modelMatrixF;
        e = glm::vec3(e1.x, e1.y, e1.z);
        glm::vec3 f = allVertices.at(allVertices.size() / 2);
        glm::vec4 f1 = glm::vec4(f.x, f.y, f.z, 1) * modelMatrixF;
        f = glm::vec3(f1.x, f1.y, f1.z);
        glm::vec3 g = allVertices.at((allVertices.size() / 2) - 1);
        glm::vec4 g1 = glm::vec4(g.x, g.y, g.z, 1) * modelMatrixF;
        g = glm::vec3(g1.x, g1.y, g1.z);
        glm::vec3 h = allVertices.at(allVertices.size() - 1);
        glm::vec4 h1 = glm::vec4(h.x, h.y, h.z, 1) * modelMatrixF;
        h = glm::vec3(h1.x, h1.y, h1.z);
        if (PointInTriangle(p, a, b, c) || PointInTriangle(p, b, c, d) || PointInTriangle(p, e, f, g) || PointInTriangle(p, g, f, h)) {
            return true;
        }
    }
    return false;
}

bool Lab5::checkCollisionObj(glm::vec3 o1, glm::vec3 o2){
    float xDiff = (o1.x - o2.x/SCALE_F) * (o1.x - o2.x/SCALE_F);
    float zDiff = (o1.z - o2.z/SCALE_F) * (o1.z - o2.z/SCALE_F);

    float sumOfDiff = (xDiff + zDiff);
    if (sqrt(sumOfDiff) <= 0.15) {
        return true;
    }

    return false;
}

bool Lab5::checkAllCollisions(glm::vec3 p) {
    for (int i = 0; i < NRCARS; i++) {
        glm::vec3 obsP = allRoads.at(i).at(nrCars.at(i));
        if (checkCollisionObj(obsP, p)) {
            return true;
        }
    }
    return false;
}

void Lab5::genNewRoute() {
    for (int j = 0; j < NRCARS; j++) {
        std::vector<glm::vec3> r;
        std::vector<glm::vec3> a;
        glm::vec3 d;
        glm::vec3 p;
        int i = 0;
        while (i < roadF.size()) {
            if (i == roadF.size() - 1) {
                d = roadF.at(0) - roadF.at(roadF.size() - 1);
                p = glm::normalize(cross(d, glm::vec3(0, 1, 0)));
                r.push_back(roadF.at(i) + p * glm::vec3(0.2, 0.2, 0.2));
                a.push_back(roadF.at(i) - p * glm::vec3(0.2, 0.2, 0.2));
                i += 1;
            }
            else {
                d = roadF.at(i + 1) - roadF.at(i);
                p = glm::normalize(cross(d, glm::vec3(0, 1, 0)));
                r.push_back(roadF.at(i) + p * glm::vec3(0.2, 0.2, 0.2));
                a.push_back(roadF.at(i) - p * glm::vec3(0.2, 0.2, 0.2));
                i += 1;
            }
        }
        allRoads.push_back(r);
        allRoads.push_back(a);
    }
}

void Lab5::genTreePosition(){
    std::vector<glm::vec3> r;
    std::vector<glm::vec3> a;
    glm::vec3 d;
    glm::vec3 p;
    int i = 0;
    while (i < treePath.size()) {
        if (i == treePath.size() - 1) {
            d = treePath.at(0) - treePath.at(treePath.size() - 1);
            p = glm::normalize(cross(d, glm::vec3(0, 1, 0)));
            r.push_back(treePath.at(i) + p * glm::vec3(0.5, 0.5, 0.5));
            a.push_back(treePath.at(i) - p * glm::vec3(0.5, 0.5, 0.5));
            i += TREEDENS;
        }
        else {
            d = treePath.at(i + 1) - treePath.at(i);
            p = glm::normalize(cross(d, glm::vec3(0, 1, 0)));
            r.push_back(treePath.at(i) + p * glm::vec3(0.5, 0.5, 0.5));
            a.push_back(treePath.at(i) - p * glm::vec3(0.5, 0.5, 0.5));
            i += TREEDENS;
        }
    }
    treeRight = r;
    treeLeft = a;
}

Lab5::~Lab5()
{
}

void Lab5::Init()
{
    renderCameraTarget = false;
    glm::vec3 corner = glm::vec3(-25, 0, -25);
    float squareSide = 50;
    carSpeed = 0;
    camera = new implemented::Camera();
    camera->Set(glm::vec3(0, 1, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
    camera->TranslateUpward(-0.5);
    camera->MoveForward(3);
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* road = Lab5::CreateRoad("road", corner, squareSide, glm::vec3(0, 0, 0), true);
        AddMeshToList(road);
    }
    {
        Mesh* stem = Lab5::CreateSquare("stem", squareSide, glm::vec3(175.0f/255, 75.0f/255, 0), true);
        AddMeshToList(stem);
    }
    {
        Mesh* leafs = Lab5::CreateSquare("leafs", squareSide, glm::vec3(36.0f / 255, 88.0f / 255, 0), true);
        AddMeshToList(leafs);
    }
    {
        Mesh* grass1 = Lab5::CreateGrassNew("grass1", corner, 1, glm::vec3(16.0f / 255, 88.0f / 255, 33.0f / 255), true);
        AddMeshToList(grass1);
    }
    {
        Mesh* car = Lab5::CreateSquare("car", squareSide, glm::vec3(189.0f / 255, 28.0f / 255, 28.0f / 255), true);
        AddMeshToList(car);
    }

    
    isPerspective = true;
    isOrtho = false;
    projectionMatrix = glm::perspective(fov, aspectRatio, zNear, zFar);
    angle = 0;
    steps = 0;

    for(int i = 0 ; i < NRCARS ; i++){
        int random = 1 + (rand() % (40*POINT_NR));
        int prandom = random;
        nrCars.push_back(random);
    }
    genNewRoute();
    genTreePosition();

    {
        Shader* shader = new Shader("MyShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab5", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab5", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
}

void Lab5::FrameStart()
{
    glClearColor(0, 158.0f / 255, 244.0f/255, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}

void Lab5::Update(float deltaTimeSeconds)
{   


    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
        modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f, 0.3f, 0.3f));
        carMatrix = modelMatrix;
        RenderSimpleMesh(meshes["car"], shaders["MyShader"], modelMatrix, projectionMatrix, camera->GetViewMatrix());
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(GRASSP,0,GRASSP));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1));
        RenderSimpleMesh(meshes["grass1"], shaders["MyShader"], modelMatrix, projectionMatrix, camera->GetViewMatrix());
    }

    for (int i = 0; i < treeRight.size()-1; i++){
        float xR = treeRight.at(i).x * SCALE_F;
        float zR = treeRight.at(i).z * SCALE_F;

        float xL = treeLeft.at(i).x * SCALE_F;
        float zL = treeLeft.at(i).z * SCALE_F;
       {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(xR, 0, zR));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15, 1, 0.15));
            RenderSimpleMesh(meshes["stem"], shaders["MyShader"], modelMatrix, projectionMatrix, camera->GetViewMatrix());
       }
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(xR, 1, zR));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5, 1, 1));
            RenderSimpleMesh(meshes["leafs"], shaders["MyShader"], modelMatrix, projectionMatrix, camera->GetViewMatrix());
        }
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(xL, 0, zL));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15, 1, 0.15));
            RenderSimpleMesh(meshes["stem"], shaders["MyShader"], modelMatrix, projectionMatrix, camera->GetViewMatrix());
        }
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(xL, 1, zL));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5, 1, 1));
            RenderSimpleMesh(meshes["leafs"], shaders["MyShader"], modelMatrix, projectionMatrix, camera->GetViewMatrix());
        }
       
    }

    glm::mat4 modelMatrix1 = glm::mat4(1);
    modelMatrix1 = glm::translate(modelMatrix1, glm::vec3(0, 0.05, 0));
    modelMatrix1 = glm::scale(modelMatrix1, glm::vec3(SCALE_F));
    modelMatrixF = modelMatrix1;
    RenderSimpleMesh(meshes["road"], shaders["MyShader"], modelMatrix1, projectionMatrix, camera->GetViewMatrix());
    
    for (int i = 0; i < NRCARS; i++) {
        float x = allRoads.at(i).at(nrCars.at(i)).x * SCALE_F;
        float z = allRoads.at(i).at(nrCars.at(i)).z * SCALE_F;
        float cAngle = GetAngle(allRoads.at(i).at(nrCars.at(i)), allRoads.at(i).at(nrCars.at(i)+2), 3);
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(x, 0.1, z));
            modelMatrix = glm::rotate(modelMatrix, cAngle, glm::vec3(0, 1, 0));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f, 0.3f, 0.3f));
            RenderSimpleMesh(meshes["car"], shaders["MyShader"], modelMatrix,projectionMatrix,camera->GetViewMatrix());
        }
        if (i % 2 == 0) {
            nrCars.at(i) = nrCars.at(i) + 2;
            if (nrCars.at(i) >= allRoads.at(i).size()-4) {
                nrCars.at(i) = 0;
            }
        }
        else {
            nrCars.at(i) = nrCars.at(i) - 2;
            if (nrCars.at(i) <= 0) {
                nrCars.at(i) = ROADPOINTSNR*POINT_NR - 4 ;
            }
        }
    }
    {
        glViewport(0, 0, 150, 150);
        float orthoLeft = -8.0f;
        float orthoRight = 8.0f;
        float orthoUp = 4.5f;
        float orthoDown = -4.5;
        glm::mat4 projectionMatrix1 = glm::ortho(orthoLeft, orthoRight, orthoDown, orthoUp, 0.0f, 200.0f);
        glm::mat4 view = glm::lookAt(glm::vec3(camera->GetTargetPosition().x, 20, camera->GetTargetPosition().z),
            glm::vec3(camera->GetTargetPosition().x, 20, camera->GetTargetPosition().z) +
            glm::vec3(0, -1, 0), glm::vec3(1, 0, 0));

        
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
            modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0, 1, 0));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f, 0.3f, 0.3f));
            RenderSimpleMesh(meshes["car"], shaders["VertexColor"], modelMatrix, projectionMatrix1, view);
        }

        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(GRASSP, 0, GRASSP));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(1));
            RenderSimpleMesh(meshes["grass1"], shaders["VertexColor"], modelMatrix, projectionMatrix1, view);
        }

        for (int i = 0; i < treeRight.size() - 1; i++) {
            float xR = treeRight.at(i).x * SCALE_F;
            float zR = treeRight.at(i).z * SCALE_F;

            float xL = treeLeft.at(i).x * SCALE_F;
            float zL = treeLeft.at(i).z * SCALE_F;
            {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, glm::vec3(xR, 0, zR));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15, 0.4, 0.15));
                RenderSimpleMesh(meshes["stem"], shaders["VertexColor"], modelMatrix, projectionMatrix1, view);
            }
            {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, glm::vec3(xR, 1, zR));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5, 1, 1));
                RenderSimpleMesh(meshes["leafs"], shaders["VertexColor"], modelMatrix, projectionMatrix1, view);
            }
            {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, glm::vec3(xL, 0, zL));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15, 0.4, 0.15));
                RenderSimpleMesh(meshes["stem"], shaders["VertexColor"], modelMatrix, projectionMatrix1, view);
            }
            {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, glm::vec3(xL, 1, zL));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5, 1, 1));
                RenderSimpleMesh(meshes["leafs"], shaders["VertexColor"], modelMatrix, projectionMatrix1, view);
            }
        }

        glm::mat4 modelMatrix1 = glm::mat4(1);
        modelMatrix1 = glm::translate(modelMatrix1, glm::vec3(0, 0.01, 0));
        modelMatrix1 = glm::scale(modelMatrix1, glm::vec3(SCALE_F));
        modelMatrixF = modelMatrix1;
        RenderSimpleMesh(meshes["road"], shaders["VertexColor"], modelMatrix1, projectionMatrix1, view);

        for (int i = 0; i < NRCARS; i++) {
            float x = allRoads.at(i).at(nrCars.at(i)).x * SCALE_F;
            float z = allRoads.at(i).at(nrCars.at(i)).z * SCALE_F;
            float cAngle = GetAngle(allRoads.at(i).at(nrCars.at(i)), allRoads.at(i).at(nrCars.at(i) + 2), 3);
            {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, glm::vec3(x, 0.1, z));
                modelMatrix = glm::rotate(modelMatrix, cAngle, glm::vec3(0, 1, 0));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f, 0.3f, 0.3f));
                RenderSimpleMesh(meshes["car"], shaders["VertexColor"], modelMatrix, projectionMatrix1, view);
            }
            if (i % 2 == 0) {
                nrCars.at(i) = nrCars.at(i) + 2;
                if (nrCars.at(i) >= allRoads.at(i).size() - 4) {
                    nrCars.at(i) = 0;
                }
            }
            else {
                nrCars.at(i) = nrCars.at(i) - 2;
                if (nrCars.at(i) <= 0) {
                    nrCars.at(i) = ROADPOINTSNR * POINT_NR - 4;
                }
            }
        }
    }
}

void Lab5::FrameEnd()
{
    
}

void Lab5::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, glm::mat4 proj, glm::mat4 view)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    glUseProgram(shader->program);

   
    int location = glGetUniformLocation(shader->program, "Model");
   
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));
   
    int locationview = glGetUniformLocation(shader->program, "View");
   
    glm::mat4 viewMatrix = view;
    glUniformMatrix4fv(locationview, 1, GL_FALSE, glm::value_ptr(viewMatrix));
   
    int locationproject = glGetUniformLocation(shader->program, "Projection");

    glm::mat4 projectionMatrix = proj;
    glUniformMatrix4fv(locationproject, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    
    int locationCar = glGetUniformLocation(shader->program, "CarPos");
    glm::vec4 carPosition = projectionMatrix * viewMatrix * carMatrix * glm::vec4(0, 0, 0, 1);
    glUniform4fv(locationCar, 1, glm::value_ptr(carPosition));
    

    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

void Lab5::OnInputUpdate(float deltaTime, int mods)
{       
    float cameraSpeed = 5.0f;
        if (window->KeyHold(GLFW_KEY_W)) {
            carSpeed = 5.0f;
            camera->MoveForward(deltaTime * carSpeed);
            glm::vec3 p = camera->GetTargetPosition();
            if (!CheckColision(allVertices, p) || checkAllCollisions(p)) {
                camera->MoveForward(-deltaTime * carSpeed);
                carSpeed = 0;
            }
        }

        if (window->KeyHold(GLFW_KEY_A)) {
           angle += cameraSpeed * deltaTime;
           camera->RotateThirdPerson_OY(deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            carSpeed = -5.0f;
            camera->MoveForward(deltaTime * carSpeed);
            glm::vec3 p = camera->GetTargetPosition();
            if (!CheckColision(allVertices, p) || checkAllCollisions(p)) {
                camera->MoveForward(-deltaTime * carSpeed);
                carSpeed = 0;
            }
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            angle -= cameraSpeed * deltaTime;
            camera->RotateThirdPerson_OY(-deltaTime * cameraSpeed);
        }

}

void Lab5::OnKeyPress(int key, int mods)
{

}

void Lab5::OnKeyRelease(int key, int mods)
{
  
}

void Lab5::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}

void Lab5::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}

void Lab5::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}

void Lab5::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Lab5::OnWindowResize(int width, int height)
{
}
