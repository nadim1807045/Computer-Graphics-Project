//
//  main.cpp
//  3D Object Drawing
//  Created by Nazirul Hasan on 4/9/23.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <random>
#include "shader.h"
#include "camera.h"
#include "basic_camera.h"
#include "pointLight.h"
#include "directionLight.h"
#include "sphere.h"
#include "spotLight.h"
#include "cube.h"
#include "stb_image.h"
#include "cylinder.h"

#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b);
void func(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);
void craine(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;
float run_speed = 0.004f;
float shoot_angle = 0.0f;
float truck_angle = 0.0f;
float ship_z = 0.0;
float ship_inc = 0.05f;
float con_inc = 0.1f;
//initial values

float gun_x=0.0f;
float gun_y=0.7f;
float balloon_x=1.5f;
float balloon_y = 1.2f;

bool fruit = true;
float fruit_y = 0.0f;
float inc = 1.0f;

// camera
float camera_z = 0.0f;
Camera camera(glm::vec3(0.0f, 1.0f, -6.5f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
float truck_z = -3.0f;
bool forwardb = true;
bool backwardb = false;
int count_turn = 0;

float container_y = 0.0f;

float eyeX = 0.0, eyeY = 10.0, eyeZ = 1.0;
float lookAtX = 0.0, lookAtY = 10.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);
SpotLight spotlight(
    0.0f,1.0f,-3.0f,
    0.0f, -1.0f, 0.0f,
    .0f, .0f, .0f,
    .0f, .0f, .0f,
    0.0f, 0.0f, 0.0f,
    30.0f,
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f //k_q
);

DirectionLight directlight(
    0.5f, 5.5f, 0.5f,     // position
    0.8f, 0.8f, 0.8f,     // ambient
    1.0f, 1.0f, 1.0f,     //diffuse
    0.0f, 0.0f, 0.0f,    //specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f //k_q
);
// positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(1.50f,  2.50f,  -3.5f),
    glm::vec3(1.5f,  2.5f,  8.5f),
    glm::vec3(-1.5f,  2.5f,  -3.5f),
    glm::vec3(-1.5f,  2.5f,  8.5f)
};
PointLight pointlight1(

    pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);
PointLight pointlight2(

    pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);
PointLight pointlight3(

    pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    3       // light number
);
PointLight pointlight4(

    pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    4       // light number
);


// light settings
bool pointLightOn = true;
bool directionLighton = true;
bool spotlighton = true;
bool ambientToggle = true;
bool diffuseToggle = true;
bool specularToggle = true;
bool shoot = false;
float bullet_z = -5.2f;
int score = 3;
bool touched = false;
bool flag = true;
bool up = false;

float stop_angle = -60.0f;
float stop_inc = 0.0f;

// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;
float speed = 0.003;
bool down = false;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("vertexShaderForPhongShading.vs", "fragmentShaderForPhongShading.fs");
    //Shader lightingShader("vertexShaderForGouraudShading.vs", "fragmentShaderForGouraudShading.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    float cube_vertices[] = {
        // positions      // normals
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f
    };
    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    unsigned int cubeVAO, cubeVBO, cubeEBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Cylinder craine_b = Cylinder();
    craine_b.setRadius(0.1);
    Cylinder shipC = Cylinder();
    Sphere sphere = Sphere();
    Sphere shipTop = Sphere();
    Sphere shipf = Sphere();
    shipf.setRadius(2.0f);
    shipf.setRadius(0.5f);
    shipf.diffuse = glm::vec3(0.3f, 0.4f, 0.3f);
    shipf.ambient = glm::vec3(0.3f, 0.4f, 0.3f);

    shipTop.diffuse = glm::vec3(0.3f, 0.4f, 0.3f);
    shipTop.ambient = glm::vec3(0.3f, 0.4f, 0.3f);

    float inc2 = 0.0f;

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");
    string diffuseMapPath = "water.jpg";
    string specularMapPath = "water.jpg";
    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath2 = "sand.jpg";
    string specularMapPath2 = "sand.jpg";
    unsigned int diffMap2 = loadTexture(diffuseMapPath2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap2 = loadTexture(specularMapPath2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube sand = Cube(diffMap2, specMap2, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);


    string diffuseMapPath3 = "road.jpg";
    string specularMapPath3 = "road.jpg";
    unsigned int diffMap3 = loadTexture(diffuseMapPath3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap3 = loadTexture(specularMapPath3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube road = Cube(diffMap3, specMap3, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);


    string diffuseMapPath4 = "container1.jpg";
    string specularMapPath4 = "container1.jpg";
    unsigned int diffMap4 = loadTexture(diffuseMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap4 = loadTexture(specularMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube container1 = Cube(diffMap4, specMap4, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath5 = "container2.jpeg";
    string specularMapPath5 = "container2.jpeg";
    unsigned int diffMap5 = loadTexture(diffuseMapPath5.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap5 = loadTexture(specularMapPath5.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube container2 = Cube(diffMap5, specMap5, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath6 = "container3.jpeg";
    string specularMapPath6 = "container3.jpeg";
    unsigned int diffMap6 = loadTexture(diffuseMapPath6.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap6 = loadTexture(specularMapPath6.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube container3 = Cube(diffMap6, specMap6, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath7 = "container4.jpeg";
    string specularMapPath7 = "container4.jpeg";
    unsigned int diffMap7 = loadTexture(diffuseMapPath7.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap7 = loadTexture(specularMapPath7.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube container4 = Cube(diffMap7, specMap7, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath8 = "container5.jpeg";
    string specularMapPath8 = "container5.jpeg";
    unsigned int diffMap8 = loadTexture(diffuseMapPath8.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap8 = loadTexture(specularMapPath8.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube container5 = Cube(diffMap8, specMap8, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath9 = "stop-sign.jpg";
    string specularMapPath9 = "stop-sign.jpg";
    unsigned int diffMap9 = loadTexture(diffuseMapPath9.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap9 = loadTexture(specularMapPath9.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube stop_sign = Cube(diffMap9, specMap9, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);


    string diffuseMapPath10 = "stop_line.png";
    string specularMapPath10 = "stop_line.png";
    unsigned int diffMap10 = loadTexture(diffuseMapPath10.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap10 = loadTexture(specularMapPath10.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube stop_line = Cube(diffMap10, specMap10, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);


    diffuseMapPath10 = "water1.png";
    specularMapPath10 = "water1.png";
    diffMap10 = loadTexture(diffuseMapPath10.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap10 = loadTexture(specularMapPath10.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube water1 = Cube(diffMap10, specMap10, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath10 = "water2.png";
    specularMapPath10 = "water2.png";
     diffMap10 = loadTexture(diffuseMapPath10.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
   specMap10 = loadTexture(specularMapPath10.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube water2 = Cube(diffMap10, specMap10, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath10 = "water3.png";
    specularMapPath10 = "water3.png";
     diffMap10 = loadTexture(diffuseMapPath10.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap10 = loadTexture(specularMapPath10.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube water3 = Cube(diffMap10, specMap10, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath10 = "water4.png";
    specularMapPath10 = "water4.png";
    diffMap10 = loadTexture(diffuseMapPath10.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap10 = loadTexture(specularMapPath10.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube water4 = Cube(diffMap10, specMap10, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    //ourShader.use();
    //lightingShader.use();

    // render loop
    // -----------

    std::random_device rd;  // Seed for the random number engine
    std::mt19937 gen(rd());  // Mersenne Twister engine
    std::uniform_real_distribution<float> dis(-1.0f, 1.0f);
    float randomValue = dis(gen);

    float time = 0.0f;
    float time2 = 0.0f;
    float time3 = 0.0f;
    bool first = false;
    int cnt = 0;
    int ind = 0;

    Sphere moon = Sphere();
    moon.diffuse = glm::vec3(1.0, 1.0, 1.0);
    moon.ambient = glm::vec3(1.0, 1.0, 1.0);
    moon.specular = glm::vec3(1.0, 1.0, 1.0);

    while (!glfwWindowShouldClose(window))
    {
        
        // per-frame time logic
        // --------------------
        cnt++;
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        //printf("%d\n", cnt);
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);

        // point light 1
        pointlight1.setUpPointLight(lightingShader);
        // point light 2
        pointlight2.setUpPointLight(lightingShader);
        // point light 3
        pointlight3.setUpPointLight(lightingShader);
        // point light 4
        pointlight4.setUpPointLight(lightingShader);

        directlight.setUpDirectionLight(lightingShader);

        spotlight.setUpSpotLight(lightingShader);

        // activate shader
        lightingShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        
        //glm::mat4 view = basic_camera.createViewMatrix();
        lightingShader.setMat4("view", view);

        //printf("%f  %f\n", currentFrame,time);

        if (forwardb && !backwardb)
        {
            down = true;
            truck_z += 0.05;
        }
        if (backwardb)
        {
            truck_z -= 0.05;
            up = true;
        }
            


        if (truck_z >= 8.0f)
        {
            forwardb = false;
            truck_z = 7.99f;
            time = currentFrame;
        }
        else if (truck_z <= -3.0)
        {
            backwardb = false;
            truck_z = -2.99;
            time = currentFrame;
        }
        
        int diff = currentFrame - time;
        if (flag && diff==10)
        {
            backwardb = true;
            flag = false;
            time = 0.0;
        }
        else if (!flag && diff == 10)
        {
            forwardb = true;
            flag = true;
            time = 0.0;
        }

        
        

        // Modelling Transformation
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        lightingShader.setMat4("model", model);

        func(cubeVAO, lightingShader, model);
        //craine
        craine(cubeVAO, lightingShader, model);

        glm::mat4 modelForC= glm::mat4(1.0f);
        modelForC = glm::translate(identityMatrix, glm::vec3(2.35f, 3.25f, -2.25f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 0.8f, 0.2f));
        glm::mat4 rotateC_Z = glm::rotate(identityMatrix, glm::radians(-25.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 rotateC_Y = glm::rotate(identityMatrix, glm::radians(-25.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        modelForC = model * modelForC * rotateC_Y * rotateC_Z * scaleMatrix;
        craine_b.drawCylinder(lightingShader, modelForC, 0.1, 0.2, 0.3);


        modelForC = glm::mat4(1.0f);
        modelForC = glm::translate(identityMatrix, glm::vec3(3.35f, 3.25f, -2.25f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 0.8f, 0.2f));
        rotateC_Z = glm::rotate(identityMatrix, glm::radians(25.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        rotateC_Y = glm::rotate(identityMatrix, glm::radians(25.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        modelForC = model * modelForC * rotateC_Y * rotateC_Z * scaleMatrix;
        craine_b.drawCylinder(lightingShader, modelForC, 0.1, 0.2, 0.3);

        modelForC = glm::mat4(1.0f);
        modelForC = glm::translate(identityMatrix, glm::vec3(2.35f, 3.25f, -1.23f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 0.8f, 0.2f));
        rotateC_Z = glm::rotate(identityMatrix, glm::radians(-25.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        rotateC_Y = glm::rotate(identityMatrix, glm::radians(25.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        modelForC = model * modelForC * rotateC_Y * rotateC_Z * scaleMatrix;
        craine_b.drawCylinder(lightingShader, modelForC, 0.1, 0.2, 0.3);

        modelForC = glm::mat4(1.0f);
        modelForC = glm::translate(identityMatrix, glm::vec3(3.35f, 3.25f, -1.23f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 0.8f, 0.2f));
        rotateC_Z = glm::rotate(identityMatrix, glm::radians(25.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        rotateC_Y = glm::rotate(identityMatrix, glm::radians(-25.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        modelForC = model * modelForC * rotateC_Y * rotateC_Z * scaleMatrix;
        craine_b.drawCylinder(lightingShader, modelForC, 0.1, 0.2, 0.3);


        modelForC = glm::mat4(1.0f);
        modelForC = glm::translate(identityMatrix, glm::vec3(5.1f, 3.15f, -1.23f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.1f, 0.1f));
        rotateC_Z = glm::rotate(identityMatrix, glm::radians(67.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        rotateC_Y = glm::rotate(identityMatrix, glm::radians(-25.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        modelForC = model * modelForC  * rotateC_Z* scaleMatrix;
        craine_b.drawCylinder(lightingShader, modelForC, 0.1, 0.2, 0.3);

        modelForC = glm::mat4(1.0f);
        modelForC = glm::translate(identityMatrix, glm::vec3(5.1f, 3.15f, -2.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 2.1f, 0.1f));
        rotateC_Z = glm::rotate(identityMatrix, glm::radians(67.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        rotateC_Y = glm::rotate(identityMatrix, glm::radians(-25.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        modelForC = model * modelForC * rotateC_Z * scaleMatrix;
        craine_b.drawCylinder(lightingShader, modelForC, 0.1, 0.2, 0.3);

        //glBindVertexArray(cubeVAO);
        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 36);

       
        //if (balloon)
        //{
        //    glm::mat4 modelForSphere = glm::mat4(1.0f);
        //    modelForSphere = glm::translate(model, glm::vec3(balloon_x, balloon_y, 5.0f));
        //    sphere.drawSphere(lightingShader, modelForSphere);
        //}

        //translateMatrix = glm::translate(identityMatrix, glm::vec3(0.4f, -2.2f, -2.6f));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8f, 0.8f, 2.5f));

        glm::mat4 modelForSphere = glm::mat4(1.0f);
        modelForSphere = glm::translate(identityMatrix, glm::vec3(0.4f, -2.5f, truck_z -2.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 1.0f, 1.0f));
        modelForSphere = model * modelForSphere  * scaleMatrix;
        sphere.drawSphere(lightingShader, modelForSphere);
        glm::mat4 rotateMM = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        modelForSphere = modelForSphere * rotateMM * scaleMatrix;
        sphere.drawSphere(lightingShader, modelForSphere);

        modelForSphere = glm::translate(identityMatrix, glm::vec3(0.4f, -2.5f, truck_z + 0.3f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 1.0f, 1.0f));
        modelForSphere = model * modelForSphere * scaleMatrix;
        sphere.drawSphere(lightingShader, modelForSphere);
        modelForSphere =  modelForSphere * rotateMM * scaleMatrix;
        sphere.drawSphere(lightingShader, modelForSphere);


        modelForSphere = glm::translate(identityMatrix, glm::vec3(1.2f, -2.5f, truck_z -2.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 1.0f, 1.0f));
        modelForSphere = model * modelForSphere * scaleMatrix;
        sphere.drawSphere(lightingShader, modelForSphere);
        modelForSphere =  modelForSphere * rotateMM * scaleMatrix;
        sphere.drawSphere(lightingShader, modelForSphere);

        modelForSphere = glm::translate(identityMatrix, glm::vec3(1.2f, -2.5f, truck_z + 0.3f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 1.0f, 1.0f));
        modelForSphere = model * modelForSphere * scaleMatrix;
        sphere.drawSphere(lightingShader, modelForSphere);
        modelForSphere =  modelForSphere * rotateMM * scaleMatrix;
        sphere.drawSphere(lightingShader, modelForSphere);

      
        //ship
        ship_z += ship_inc;

        if (ship_z >= 30.0)
            ship_inc = -0.1;
        if (ship_z <= 0.0)
        {
            count_turn++;
            ship_z = 0.001f;
            ship_inc = 0.0f;
            time2 = currentFrame;
            cout << count_turn << endl;
        }
        

        if (ship_inc == 0 && currentFrame - time2 >= 5.0)
        {

            ship_inc = 0.1f;
        }
            
        
        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.0, -2.0, -2.5+ship_z));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0, 0.1,8.0));
        glm::mat4 model3 = model * translateMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model3, 0.3, 0.4, 0.3);

        float yyy = 1.5f;
        float zzz = 0.02f;
        float sc_x = 2.56f;
        float sc_z = 2.0f;

        for (int i = 0; i < 1000; i++)
        {
            modelForSphere = glm::translate(model3, glm::vec3(0.5f, yyy, zzz + (ship_z*0.001)));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(sc_x, 1.5f, sc_z));
            rotateMM = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            modelForSphere =  modelForSphere * rotateMM * scaleMatrix;
            shipf.drawSphere(lightingShader, modelForSphere);
            yyy -= 0.01f;
            zzz += 0.0001f;
            sc_x -= 0.0006;
            sc_z -= 0.0006;
        }

        

        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.3f, -2.0f, 0.15f + ship_z));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 3.0f));
        glm::mat4 conship1 = model * translateMatrix * scaleMatrix;
        container1.drawCubeWithTexture(lightingShaderWithTexture, conship1);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.3f, -1.0f, 0.15f + ship_z));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 3.0f));
        glm::mat4 conship2 = model * translateMatrix * scaleMatrix;
        container4.drawCubeWithTexture(lightingShaderWithTexture, conship2);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(6.5f, -2.0f, 0.15f + ship_z));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 3.0f));
        glm::mat4 conship4 = model * translateMatrix * scaleMatrix;
        container5.drawCubeWithTexture(lightingShaderWithTexture, conship4);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(6.5f, -1.0f, 0.15f + ship_z));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 3.0f));
        glm::mat4 conship3 = model * translateMatrix * scaleMatrix;
        container3.drawCubeWithTexture(lightingShaderWithTexture, conship3);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.75f, -2.0f, 0.15f + ship_z));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 3.0f));
        glm::mat4 conship5 = model * translateMatrix * scaleMatrix;
        container4.drawCubeWithTexture(lightingShaderWithTexture, conship5);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(7.75f, -1.0f, 0.15f + ship_z));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 3.0f));
        glm::mat4 conship6 = model * translateMatrix * scaleMatrix;
        container1.drawCubeWithTexture(lightingShaderWithTexture, conship6);

        glm::mat4 model2;

        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.08, -2.0, -2.5 + ship_z));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0, 0.1, 8.0));
        rotateMM = glm::rotate(identityMatrix, glm::radians(-60.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model2 = model * translateMatrix * rotateMM * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model2, 0.3, 0.4, 0.3);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(8.9, -2.0, -2.5 + ship_z));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0, 0.1, 8.0));
        rotateMM = glm::rotate(identityMatrix, glm::radians(240.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model2 = model * translateMatrix * rotateMM * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model2, 0.3, 0.4, 0.3);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.01, -2.0, -2.4 + ship_z));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1, 0.5, 7.9));
        model2 = model * translateMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model2, 0.4, 0.4, 0.4);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(8.86, -2.0, -2.4 + ship_z));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1, 0.5, 7.9));
        model2 = model * translateMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model2, 0.4, 0.4, 0.4);

        glm::mat4 shipCModel = glm::mat4(1.0f);
        shipCModel = glm::translate(identityMatrix, glm::vec3(7.0f, -1.3f, -4.0f + ship_z));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 1.1f, 0.2f));
        shipCModel = model * shipCModel * scaleMatrix;
        shipC.drawCylinder(lightingShader, shipCModel, 0.3, 0.4, 0.4);
        
        translateMatrix = glm::translate(identityMatrix, glm::vec3(6.7f, -1.0f, -4.3f + ship_z));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6, 0.1, 0.6));
        model2 = model * translateMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model2, 0.4, 0.4, 0.4);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(6.8f, -0.7f, -4.2f + ship_z));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4, 0.1, 0.4));
        model2 = model * translateMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model2, 0.4, 0.4, 0.4);

        modelForSphere = glm::translate(identityMatrix, glm::vec3(7.0f, -0.2f, -4.0f + ship_z));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4, 0.4, 0.4));
        modelForSphere = model * modelForSphere * scaleMatrix;
        shipTop.drawSphere(lightingShader, modelForSphere);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.4f, -2.0f, 0.0f+ship_z));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 3.0f));
        glm::mat4 conshipp = model * translateMatrix * rotateYMatrix * scaleMatrix;
        container2.drawCubeWithTexture(lightingShaderWithTexture, conshipp);


        if (count_turn % 2 == 0)
        {
            if (ship_inc == 0 && currentFrame - time2 < 5.0)
            {
                if (container_y <= 0.0f)
                    con_inc = 0.0f;
                else
                    con_inc = -0.05f;
                container_y += con_inc;
                translateMatrix = glm::translate(identityMatrix, glm::vec3(5.4f, -2.0f + container_y, -1.2f));
                rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 3.0f));
                conshipp = model * translateMatrix * rotateYMatrix * scaleMatrix;
                container5.drawCubeWithTexture(lightingShaderWithTexture, conshipp);
            }
            else
            {
                translateMatrix = glm::translate(identityMatrix, glm::vec3(5.4f, -2.0f, -1.2f + ship_z));
                rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 3.0f));
                conshipp = model * translateMatrix * rotateYMatrix * scaleMatrix;
                container5.drawCubeWithTexture(lightingShaderWithTexture, conshipp);
            }
                
            
            
        }
        else
        {
           if (ship_inc == 0 && currentFrame - time2 < 5.0 && container_y <3.0f)
                con_inc = 0.05f;
            container_y += con_inc;

            if (container_y >= 3.0f)
                con_inc = 0.0f;
            translateMatrix = glm::translate(identityMatrix, glm::vec3(5.4f, -2.0f + container_y, -1.2f));
            rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 3.0f));
            conshipp = model * translateMatrix * rotateYMatrix * scaleMatrix;
            container5.drawCubeWithTexture(lightingShaderWithTexture, conshipp);
           
        }

        

        /*modelForSphere = modelForSphere * rotateMM;
        shipTop.drawSphere(lightingShader, modelForSphere);*/






        // also draw the lamp object(s)
        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);
        float cr, cg, cb;
        if (pointLightOn)
        {
            cr = 0.8f;
            cg = 0.8f;
            cb = 0.8f;
        }
        else
        {
            cr = 0.0f;
            cg = 0.0f;
            cb = 0.0f;
        }
        // point lights

        glBindVertexArray(lightCubeVAO);
        for (unsigned int i = 0; i < 4; i++)
        {
            model2 = glm::mat4(1.0f);
            model2 = glm::translate(model, pointLightPositions[i]);
            model2 = glm::scale(model2, glm::vec3(0.2f)); // Make it a smaller cube
            ourShader.setMat4("model", model2);
            ourShader.setVec3("color", glm::vec3(cr, cg, cb));
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            //glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        //stand
        glm::mat4 transM, scaleM,stand;
        stand = identityMatrix;
        transM = glm::translate(identityMatrix, glm::vec3(2.0f, -3.8, -3.5f));
        scaleM = glm::scale(identityMatrix, glm::vec3(0.1, 7.0, 0.1));
        stand = model * stand * transM * scaleM;
        drawCube(cubeVAO, lightingShader, stand, 0.0, 0.0, 0.0);

        stand = identityMatrix;
        transM = glm::translate(identityMatrix, glm::vec3(1.5f, 2.7, -3.5f));
        scaleM = glm::scale(identityMatrix, glm::vec3(0.6, 0.05, 0.1));
        stand = model * stand * transM * scaleM;
        drawCube(cubeVAO, lightingShader, stand, 0.0, 0.0, 0.0);


        stand = identityMatrix;
        transM = glm::translate(identityMatrix, glm::vec3(2.0f, -3.8, 8.5f));
        scaleM = glm::scale(identityMatrix, glm::vec3(0.1, 7.0, 0.1));
        stand = model * stand * transM * scaleM;
        drawCube(cubeVAO, lightingShader, stand, 0.0, 0.0, 0.0);

        stand = identityMatrix;
        transM = glm::translate(identityMatrix, glm::vec3(1.5f, 2.7, 8.5f));
        scaleM = glm::scale(identityMatrix, glm::vec3(0.6, 0.05, 0.1));
        stand = model * stand * transM * scaleM;
        drawCube(cubeVAO, lightingShader, stand, 0.0, 0.0, 0.0);


        ////
        stand = identityMatrix;
        transM = glm::translate(identityMatrix, glm::vec3(-2.0f, -3.8, -3.5f));
        scaleM = glm::scale(identityMatrix, glm::vec3(0.1, 7.0, 0.1));
        stand = model * stand * transM * scaleM;
        drawCube(cubeVAO, lightingShader, stand, 0.0, 0.0, 0.0);

        stand = identityMatrix;
        transM = glm::translate(identityMatrix, glm::vec3(-2.0f, 2.7, -3.5f));
        scaleM = glm::scale(identityMatrix, glm::vec3(0.6, 0.05, 0.1));
        stand = model * stand * transM * scaleM;
        drawCube(cubeVAO, lightingShader, stand, 0.0, 0.0, 0.0);


        stand = identityMatrix;
        transM = glm::translate(identityMatrix, glm::vec3(-2.0f, -3.8, 8.5f));
        scaleM = glm::scale(identityMatrix, glm::vec3(0.1, 7.0, 0.1));
        stand = model * stand * transM * scaleM;
        drawCube(cubeVAO, lightingShader, stand, 0.0, 0.0, 0.0);

        stand = identityMatrix;
        transM = glm::translate(identityMatrix, glm::vec3(-2.0f, 2.7, 8.5f));
        scaleM = glm::scale(identityMatrix, glm::vec3(0.6, 0.05, 0.1));
        stand = model * stand * transM * scaleM;
        drawCube(cubeVAO, lightingShader, stand, 0.0, 0.0, 0.0);




        ///////////////////----moon------//////////////////////

        glm::mat4 modelForMoon = identityMatrix;
        transM = glm::translate(identityMatrix, glm::vec3(0.5, 5.5, 0.5f));
        scaleM = glm::scale(identityMatrix, glm::vec3(1.5, 1.5, 1.5));
        modelForMoon = model * modelForMoon * transM * scaleM;
        moon.drawSphere(lightingShader, modelForMoon);

        modelForMoon = identityMatrix;
        glm::mat4 rotM = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.0));
        modelForMoon = model * modelForMoon * transM * rotM * scaleM;
        moon.drawSphere(lightingShader, modelForMoon);


        ////////////////
        lightingShaderWithTexture.use();
        lightingShaderWithTexture.setVec3("viewPos", camera.Position);
        lightingShaderWithTexture.setMat4("projection", projection);
        lightingShaderWithTexture.setMat4("view", view);

        lightingShaderWithTexture.use();
        // point light 1
        pointlight1.setUpPointLight(lightingShaderWithTexture);
        // point light 2
        pointlight2.setUpPointLight(lightingShaderWithTexture);
        // point light 3
        pointlight3.setUpPointLight(lightingShaderWithTexture);
        // point light 4
        pointlight4.setUpPointLight(lightingShaderWithTexture);

        directlight.setUpDirectionLight(lightingShaderWithTexture);


        //sea

        if (currentFrame - time3 >= 0.2)
        {
            if (ind == 4)
                ind = 1;
            else ind++;
            time3 = currentFrame;
        }

        if (ind==1)
        {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(-20.5f, -3.1f, -5.0f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(40.0f, 0.2f, 40.0f));
            glm::mat4 modelMatrixForContainer3 = model * translateMatrix * scaleMatrix;
            water1.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3);
        }
        else if(ind==2)
        {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(-20.5f, -3.1f, -5.0f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(40.0f, 0.2f, 40.0f));
            glm::mat4 modelMatrixForContainer3 = model * translateMatrix * scaleMatrix;
            water2.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3);
        }
        else if (ind == 3)
        {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(-20.5f, -3.1f, -5.0f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(40.0f, 0.2f, 40.0f));
            glm::mat4 modelMatrixForContainer3 = model * translateMatrix * scaleMatrix;
            water3.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3);
        }
        else if (ind == 4)
        {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(-20.5f, -3.1f, -5.0f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(40.0f, 0.2f, 40.0f));
            glm::mat4 modelMatrixForContainer3 = model * translateMatrix * scaleMatrix;
            water4.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3);
        }
        

        //base
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.5f, -3.0f, -5.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.0f, 0.2f, 15.0f));
        glm::mat4 modelMatrixForContainer = model * translateMatrix * scaleMatrix;
        sand.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);
        //road
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.5f, -2.9f, 10.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(15.0f, 0.2f, 3.0f));
        glm::mat4 modelMatrixForContainer2 = model * translateMatrix * rotateYMatrix * scaleMatrix;
        road.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2);

        //container
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, -2.8f, 5.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 3.0f));
        glm::mat4 conModel1 = model * translateMatrix  * scaleMatrix;
        container1.drawCubeWithTexture(lightingShaderWithTexture, conModel1);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, -1.8f, 5.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 3.0f));
        glm::mat4 conModel2 = model * translateMatrix * scaleMatrix;
        container2.drawCubeWithTexture(lightingShaderWithTexture, conModel2);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.2f, -2.8f, 5.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 3.0f));
        glm::mat4 conModel3 = model * translateMatrix * scaleMatrix;
        container3.drawCubeWithTexture(lightingShaderWithTexture, conModel3);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.2f, -1.8f, 5.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 3.0f));
        glm::mat4 conModel4 = model * translateMatrix * scaleMatrix;
        container4.drawCubeWithTexture(lightingShaderWithTexture, conModel4);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.2f, -2.8f, 1.8f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 3.0f));
        glm::mat4 conModel5 = model * translateMatrix * scaleMatrix;
        container5.drawCubeWithTexture(lightingShaderWithTexture, conModel5);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.2f, -2.8f, -1.05f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8f, 0.8f, 2.0f));
        glm::mat4 conModel7 = model * translateMatrix * rotateYMatrix * scaleMatrix;
        container4.drawCubeWithTexture(lightingShaderWithTexture, conModel7);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.2f, -2.8f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8f,0.8f, 2.0f));
        glm::mat4 conModel6 = model * translateMatrix * rotateYMatrix * scaleMatrix;
        container3.drawCubeWithTexture(lightingShaderWithTexture, conModel6);

        


        //TollBox
        glm::mat4 TollHandle = glm::mat4(1.0f);
        TollHandle = glm::translate(identityMatrix, glm::vec3(2.0f, -3.0f, 9.7f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 1.5f, 0.3f));
        TollHandle = model * TollHandle * scaleMatrix;
        shipC.drawCylinder(lightingShader, TollHandle, 0.3, 0.4, 0.4);

        
        if (down)
        {
            stop_inc = 0.2f;
            down = false;
        }

        stop_angle += stop_inc;
        if (stop_angle <= -60.0)
            stop_inc = 0.0f;
        if (stop_angle >= 0.0f)
            stop_inc = 0.0f;

        if (up)
        {
            stop_inc = -0.2f;
            up = false;
        }

        glm::mat4 rotateHandle = glm::rotate(identityMatrix, glm::radians(stop_angle), glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 rotateYHandle = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0f, -1.8f, 9.7f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, 0.1f, 0.1f));
        TollHandle = model * translateMatrix * rotateHandle * rotateYHandle* scaleMatrix;
        stop_line.drawCubeWithTexture(lightingShaderWithTexture, TollHandle);


        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, -1.8f, 9.2f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.5f, 0.1f));
        TollHandle = model * translateMatrix  * scaleMatrix;
        stop_sign.drawCubeWithTexture(lightingShaderWithTexture, TollHandle);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.8f, -3.3f, 9.2f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.5f, 0.1f));
        TollHandle = model * translateMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, TollHandle, 0.3, 0.4, 0.4);

        //truck er uporer container
        glm::mat4 rotatecon = glm::rotate(identityMatrix, glm::radians(truck_angle), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.4f, -2.2f, truck_z-2.6f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8f, 0.8f, 2.5f));
        glm::mat4 conTruck = model * translateMatrix * rotatecon * scaleMatrix;
        container2.drawCubeWithTexture(lightingShaderWithTexture, conTruck);




        //translateMatrix = glm::translate(identityMatrix, glm::vec3(2.05f, 0.1f, grass2));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.2f, 10.0f));
        //glm::mat4 modelMatrixForContainer4 = translateMatrix * scaleMatrix;
        //cube.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer4);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &cubeEBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    lightingShader.setFloat("material.shininess", 22.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(cubeVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}



void func(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    //truck
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.4, -2.5, truck_z+0.0));
    //rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(truck_angle), glm::vec3(0.0f, 1.0f, 0.0f));
    //rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8,0.8, 0.8));
    model = alTogether * translateMatrix  * rotateYMatrix* scaleMatrix;
    drawCube(cubeVAO, lightingShader, model,0.5,0.8,0.3);


    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.4, -2.5, truck_z -2.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8, 0.3, 2.5));
    model = alTogether * translateMatrix * rotateYMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.1, 0.2, 0.3);

}

void craine(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //base - 4
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0f, -3.3f, -2.5f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2, 6.0, 0.2));
    model = alTogether * translateMatrix  * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.1, 0.2, 0.3);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.5f, -3.3f, -2.5f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2, 6.0, 0.2));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.1, 0.2, 0.3);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0f, -3.3f, -1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2, 6.0, 0.2));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.1, 0.2, 0.3);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.5f, -3.3f, -1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2, 6.0, 0.2));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.1, 0.2, 0.3);

    // bottom - connectors
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0f, -2.5f, -2.5f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 0.2, 0.2));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.1, 0.2, 0.3);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0f, -2.5f, -1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 0.2, 0.2));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.1, 0.2, 0.3);
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.2f, -1.3f, -2.5f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 0.2, 0.2));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = alTogether * translateMatrix * rotateYMatrix* scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.1, 0.2, 0.3);
    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.7f, -1.3f, -2.5f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 0.2, 0.2));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = alTogether * translateMatrix * rotateYMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.1, 0.2, 0.3);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0f, 0.5f, -2.5f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 0.2, 0.2));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.1, 0.2, 0.3);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0f, 0.5f, -1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 0.2, 0.2));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.1, 0.2, 0.3);


    //top-connectors
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0f, 2.5f, -2.5f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 0.2, 0.2));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.1, 0.2, 0.3);
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0f, 2.5f, -1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 0.2, 0.2));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.1, 0.2, 0.3);
    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.2f, 2.5f, -2.5f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 0.2, 0.2));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = alTogether * translateMatrix * rotateYMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.1, 0.2, 0.3);
    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.7f, 2.5f, -2.5f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 0.2, 0.2));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = alTogether * translateMatrix * rotateYMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.1, 0.2, 0.3);


    //hand
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0f, 2.3f, -2.3f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(6.0, 0.15, 0.15));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.1, 0.2, 0.3);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.0f, 2.3f, -1.1f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(6.0, 0.15, 0.15));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.1, 0.2, 0.3);
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.15f, 2.3f, -2.2f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.2, 0.15, 0.15));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = alTogether * translateMatrix * rotateYMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.1, 0.2, 0.3);
    translateMatrix = glm::translate(identityMatrix, glm::vec3(6.97f, 2.3f, -2.2f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.2, 0.15, 0.15));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = alTogether * translateMatrix * rotateYMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.1, 0.2, 0.3);


    translateMatrix = glm::translate(identityMatrix, glm::vec3(2.3f, 3.8f, -2.2f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0, 0.2, 1.0));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.1, 0.2, 0.3);



    translateMatrix = glm::translate(identityMatrix, glm::vec3(6.8f, 2.0f, -2.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2, 0.4, 0.2));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(6.8f, 2.0f, -1.5f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2, 0.4, 0.2));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        if (rotateAxis_X) rotateAngle_X -= 0.1;
        else if (rotateAxis_Y) rotateAngle_Y -= 0.1;
        else rotateAngle_Z -= 0.1;
    }
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) translate_Y += 0.1;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) translate_Y -= 0.1;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) translate_X += 0.1;
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) translate_X -= 0.1;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) translate_Z += 0.1;
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) translate_Z -= 0.1;


    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(YAW_R, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(YAW_L, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(PITCH_D, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(PITCH_U, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(ROLL_R, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(ROLL_L, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{   
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
        if (directionLighton)
        {
            directlight.turnOff();
            directionLighton = !directionLighton;
        }
        else
        {
            directlight.turnOn();
            directionLighton = !directionLighton;
        }
    }
    else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    {
        if (pointLightOn)
        {
            pointlight1.turnOff();
            pointlight2.turnOff();
            pointlight3.turnOff();
            pointlight4.turnOff();
            pointLightOn = !pointLightOn;
        }
        else
        {
            pointlight1.turnOn();
            pointlight2.turnOn();
            pointlight3.turnOn();
            pointlight4.turnOn();
            pointLightOn = !pointLightOn;
        }
    }
    else if (key == GLFW_KEY_3 && action == GLFW_PRESS)
    {
        if (spotlighton)
        {
            spotlight.turnOff();
            spotlighton = !spotlighton;
        }
        else
        {
            spotlight.turnOn();
            spotlighton = !spotlighton;
        }
    }
    else if (key == GLFW_KEY_4 && action == GLFW_PRESS)
    {
        if (ambientToggle)
        {
            pointlight1.turnAmbientOff();
            pointlight2.turnAmbientOff();
            pointlight3.turnAmbientOff();
            pointlight4.turnAmbientOff();
            directlight.turnAmbientOff();
            spotlight.turnAmbientOff();
            ambientToggle = !ambientToggle;
        }
        else
        {
            pointlight1.turnAmbientOn();
            pointlight2.turnAmbientOn();
            pointlight3.turnAmbientOn();
            pointlight4.turnAmbientOn();
            directlight.turnAmbientOn();
            spotlight.turnAmbientOn();
            ambientToggle = !ambientToggle;
        }
    }
    else if (key == GLFW_KEY_5 && action == GLFW_PRESS)
    {
        if (diffuseToggle)
        {
            pointlight1.turnDiffuseOff();
            pointlight2.turnDiffuseOff();
            pointlight3.turnDiffuseOff();
            pointlight4.turnDiffuseOff();
            directlight.turnDiffuseOff();
            spotlight.turnDiffuseOff();
            diffuseToggle = !diffuseToggle;
        }
        else
        {
            pointlight1.turnDiffuseOn();
            pointlight2.turnDiffuseOn();
            pointlight3.turnDiffuseOn();
            pointlight4.turnDiffuseOn();
            directlight.turnDiffuseOn();
            spotlight.turnDiffuseOn();
            diffuseToggle = !diffuseToggle;
        }
    }
    else if (key == GLFW_KEY_6 && action == GLFW_PRESS)
    {
        if (specularToggle)
        {
            pointlight1.turnSpecularOff();
            pointlight2.turnSpecularOff();
            pointlight3.turnSpecularOff();
            pointlight4.turnSpecularOff();
            directlight.turnSpecularOff();
            spotlight.turnSpecularOff();
            specularToggle = !specularToggle;
        }
        else
        {
            pointlight1.turnSpecularOn();
            pointlight2.turnSpecularOn();
            pointlight3.turnSpecularOn();
            pointlight4.turnSpecularOn();
            directlight.turnSpecularOn();
            spotlight.turnSpecularOn();
            specularToggle = !specularToggle;
        }
    }

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}