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
#include <Casa.h>

// 🔹 Texturas globais
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

// 🔹 Função para carregar textura
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

// Variáveis de câmera
glm::vec3 cameraPos = glm::vec3(25.0f, 1.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 800.0f / 2.0f;
float lastY = 450.0f / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Controle da visão com o mouse
void viraCamera(double xpos, double ypos)
{
    const float sensitivity = 0.1f;

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

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

// Callback do mouse
void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    viraCamera(xpos, ypos);
}

// Controle de movimento
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 5.0f * deltaTime; // mais rápido e fluido

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        cameraPos.y += cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
        cameraPos.y -= cameraSpeed;
}

// Função principal
int main()
{
    Application app(640, 360, "Scene with All Objects");
    if (!app.init())
        return -1;

    GLFWwindow *window = app.getWindow();

    // Configura captura do mouse
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Shader shader("vertex.glsl", "fragment.glsl");
    shader.use();
    glEnable(GL_DEPTH_TEST);

    // Carrega texturas
    stoneTex = loadTexture("stone.png");
    woodTex = loadTexture("wood.png");
    lightWoodTex = loadTexture("lightwood.png");
    steelTex = loadTexture("steel.png");
    blackTex = loadTexture("black.png");
    tecidoSofa = loadTexture("assets/textures/tecido_sofa.jpg");
    texturaVerdePeludo = loadTexture("assets/textures/verde-peludo.jpg");
    texturaTecidoBranco = loadTexture("assets/textures/tecidoBranco.jpg");
    texturaCeramicaBranca = loadTexture("assets/textures/ceramica.jpg");
    texturaAgua = loadTexture("assets/textures/agua.jpg");

    shader.setInt("texture1", 0);

    // Cria objetos

    Cube cube(glm::vec3(-7.5f, 0.5f, 0.0f));
    TriangularPrism prism(glm::vec3(-5.0f, 0.5f, 0.0f));
    Cylinder cylinder(glm::vec3(-2.5f, 0.5f, 0.0f));
    Sphere sphere(glm::vec3(0.0f, 0.5f, 0.0f));
    Chair chair(glm::vec3(2.5f, 0.0f, 0.0f));
    Cabinet cabinet(glm::vec3(5.0f, 0.0f, 0.0f));
    Table table(glm::vec3(7.5f, 0.0f, 0.0f));
    Geladeira geladeira(glm::vec3(10.0f, 0.0f, 0.0f));
    Stove stove(glm::vec3(12.5f, 0.0f, 0.0f));
    Sofa sofa(glm::vec3(15.0f, 0.0f, 0.0f));
    Rack rack(glm::vec3(17.5f, 0.0f, 0.0f));
    Tv tv(glm::vec3(17.5f, 0.4f, 0.0f));
    Bed bed(glm::vec3(20.0f, 0.0f, 0.0f));
    Toilet toilet(glm::vec3(22.5f, 0.0f, 0.0f));
    Sink sink(glm::vec3(25.0f, 0.0f, 0.0f));
    Casa casa(glm::vec3(0.0f, 0.0f, 0.0f));

    // Loop principal
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        glActiveTexture(GL_TEXTURE0);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1600.0f / 900.0f, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);

        // Desenha tudo
        glBindTexture(GL_TEXTURE_2D, stoneTex);
        cube.draw(shader, model);
        prism.draw(shader, model);
        cylinder.draw(shader, model);
        sphere.draw(shader, model);

        chair.draw(shader, model);
        cabinet.draw(shader, model);
        table.draw(shader, model);
        geladeira.draw(shader, model);
        stove.draw(shader, model);
        sofa.draw(shader, model);
        rack.draw(shader, model);
        tv.draw(shader, model);
        bed.draw(shader, model);
        toilet.draw(shader, model);
        sink.draw(shader, model);
        casa.draw(shader, model);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
