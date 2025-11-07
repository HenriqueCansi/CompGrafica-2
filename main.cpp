#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <iostream>
#include <Shader.h>
#include <Application.h>
#include <Cube.h>
#include <TriPrism.h>
#include <Cylinder.h>
#include <Sphere.h>
#include <Chair.h>
#include <Cabinet.h>
#include <Table.h>
#include <Geladeira.h>
#include <Stove.h>
#include <Sofa.h>
#include <Tv.h>
#include <Bed.h>
#include <Toilet.h>
#include <Sink.h>
#include <Rack.h>

// 🔹 Definições globais (torna visíveis para outros .cpp)
unsigned int stoneTex;
unsigned int woodTex;
unsigned int lightWoodTex;
unsigned int steelTex;
unsigned int blackTex;
unsigned int tecidoSofa;
unsigned int texturaVerdePeludo;
unsigned int texturaTecidoBranco;
unsigned int texturaCeramicaBranca;
unsigned int texturaAgua;

unsigned int loadTexture(const char *path)
{
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data)
    {
        GLenum format = (nrChannels == 3) ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture: " << path << std::endl;
    }
    stbi_image_free(data);

    return texture;
}

glm::vec3 cameraPos = glm::vec3(25.0f, 1.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float sensitivity = 25.0f;
float yaw = -90.0f;
float pitch = 0.0f;

float deltaTime = 0.0f; // tempo entre frames
float lastFrame = 0.0f;

void viraCamera(float x, float y)
{
    yaw += x * sensitivity * deltaTime;
    pitch += y * sensitivity * deltaTime;
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    const float cameraSpeed = 2.0f * deltaTime;
    // ajustar de acordo com a velocidade do computador
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        cameraPos += glm::vec3(0.0f, 1.0f, 0.0f) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
        cameraPos += glm::vec3(0.0f, -1.0f, 0.0f) * cameraSpeed;

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        viraCamera(0.0f, 1.0f);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        viraCamera(0.0f, -1.0f);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        viraCamera(-1.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        viraCamera(1.0f, 0.0f);
}

int main()
{
    Application app(640, 360, "Scene with All Objects");
    if (!app.init())
        return -1;

    Shader shader("vertex.glsl", "fragment.glsl");
    shader.use();
    glEnable(GL_DEPTH_TEST);

    // carrega texturas
    stoneTex = loadTexture("stone.png");
    if (!stoneTex)
        std::cout << "Failed to load stone texture!\n";
    woodTex = loadTexture("wood.png");
    if (!woodTex)
        std::cout << "Failed to load wood texture!\n";
    lightWoodTex = loadTexture("lightwood.png");
    if (!lightWoodTex)
        std::cout << "Failed to load light wood texture!\n";
    steelTex = loadTexture("steel.png");
    if (!steelTex)
        std::cout << "Failed to load steel texture!\n";
    blackTex = loadTexture("black.png");
    if (!blackTex)
        std::cout << "Failed to load black texture!\n";
    tecidoSofa = loadTexture("assets/textures/tecido_sofa.jpg");
    if (!tecidoSofa)
        std::cout << "Failed to load green fabric texture!\n";
    texturaVerdePeludo = loadTexture("assets/textures/verde-peludo.jpg");
    if (!texturaVerdePeludo)
        std::cout << "Failed to load red fabric texture!\n";
    texturaTecidoBranco = loadTexture("assets/textures/tecidoBranco.jpg");
    if (!texturaTecidoBranco)
        std::cout << "Failed to load white fabric texture!\n";
    texturaCeramicaBranca = loadTexture("assets/textures/ceramica.jpg");
    if (!texturaCeramicaBranca)
        std::cout << "Failed to load white ceramic texture!\n";
    texturaAgua = loadTexture("assets/textures/agua.jpg");
    if (!texturaAgua)
        std::cout << "Failed to load water ripple texture!\n";

    shader.setInt("texture1", 0);

    // criação de objetos (EXEMPLO)
    Cube cube(glm::vec3(-7.5f, 0.5f, 0.0f));
    TriangularPrism prism(glm::vec3(-5.0f, 0.5f, 0.0f));
    Cylinder cylinder(glm::vec3(-2.5f, 0.5f, 0.0f));
    Sphere sphere(glm::vec3(0.0f, 0.5f, 0.0f));
    Chair chair(glm::vec3(2.5f, 0.0f, 0.0f));
    Cabinet cabinet(glm::vec3(5.0f, 0.0f, 0.0f));
    Table table(glm::vec3(7.5f, 0.0f, 0.0f));
    Geladeira Geladeira(glm::vec3(10.0f, 0.0f, 0.0f));
    Stove stove(glm::vec3(12.5f, 0.0f, 0.0f));
    Sofa sofa(glm::vec3(15.0f, 0.0f, 0.0f));
    Rack rack(glm::vec3(17.5f, 0.0f, 0.0f));
    Tv tv(glm::vec3(17.5f, 0.4f, 0.0f));
    Bed bed(glm::vec3(20.0f, 0.0f, 0.0f));
    Toilet toilet(glm::vec3(22.5f, 0.0f, 0.0f));
    Sink sink(glm::vec3(25.0f, 0.0f, 0.0f));

    GLFWwindow *window = app.getWindow();

    viraCamera(0.0f, 0.0f);

    // loop de renderização
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        glActiveTexture(GL_TEXTURE0);

        // câmera e matrizes
        glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                                1600.0f / 900.0f, 0.1f, 100.0f);
        glm::mat4 view;

        processInput(window);

        deltaTime = glfwGetTime() - lastFrame;
        lastFrame = glfwGetTime();

        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);

        // primitivos
        glBindTexture(GL_TEXTURE_2D, stoneTex);
        cube.draw(shader, model);
        prism.draw(shader, model);
        cylinder.draw(shader, model);
        sphere.draw(shader, model);

        chair.draw(shader, model);
        cabinet.draw(shader, model);
        table.draw(shader, model);
        Geladeira.draw(shader, model);
        stove.draw(shader, model);
        sofa.draw(shader, model);
        rack.draw(shader, model);
        tv.draw(shader, model);
        bed.draw(shader, model);
        toilet.draw(shader, model);
        sink.draw(shader, model);

        glfwSwapBuffers(app.getWindow());
        glfwPollEvents();
    }

    return 0;
}
