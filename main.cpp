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

//  Texturas globais
unsigned int texturaPiso;
unsigned int texturaPisoBanheiro;
unsigned int texturaMadeiraEscura;
unsigned int texturaMadeiraClara;
unsigned int texturaInox;
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

// Variáveis de câmera
glm::vec3 cameraPos = glm::vec3(3.0f, 1.2f, 8.0f); // fora da casa
glm::vec3 cameraFront = glm::vec3(-0.3f, 0.0f, -1.0f); // olhando um pouco para a esquerda
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 800.0f / 2.0f;
float lastY = 600.0f / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    static float sensitivity = 0.1f;

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

void processInput(GLFWwindow *window)
{
    const float cameraSpeed = 3.5f * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

int main()
{
    Application app(1280, 720, "Casa 3D - Base");
    if (!app.init())
        return -1;

    GLFWwindow *window = app.getWindow();
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Shader shader("vertex.glsl", "fragment.glsl");
    shader.use();
    glEnable(GL_DEPTH_TEST);

    // Carrega texturas
    texturaPiso = loadTexture("assets/textures/chaoCasa.jpg");
    texturaPisoBanheiro = loadTexture("assets/textures/chaoBanheiro.jpg");
    texturaMadeiraEscura = loadTexture("assets/textures/madeiraEscura.jpg");
    texturaMadeiraClara = loadTexture("assets/textures/madeiraClara.jpg");
    texturaInox = loadTexture("assets/textures/inox.jpg");
    blackTex = loadTexture("assets/textures/preto.jpg");
    tecidoSofa = loadTexture("assets/textures/tecido_sofa.jpg");
    texturaVerdePeludo = loadTexture("assets/textures/verde-peludo.jpg");
    texturaTecidoBranco = loadTexture("assets/textures/tecidoBranco.jpg");
    texturaCeramicaBranca = loadTexture("assets/textures/ceramica.jpg");
    texturaAgua = loadTexture("assets/textures/agua.jpg");

    shader.setInt("texture1", 0);

    // Criar a casa (base maior)
    // Casa no centro
    Casa casa(glm::vec3(0.0f, 0.0f, 0.0f));
    casa.scale = glm::vec3(0.5f);

    // Banheiro
    Toilet vaso(glm::vec3(-3.25f, 0.0f, -3.0f));   // canto bem colado
    Sink pia(glm::vec3(-2.0f, 0.0f, -3.0f));

   Cube pisoBanheiro(glm::vec3(-2.5f, 0.04f, -2.5f),
                  glm::vec3(0.0f),
                  glm::vec3(2.5, 0.02f, 2.5f),
                  0.0f);


   /*Cube paredeBanheiro(glm::vec3(-1.2f, 0.0f, -3.0f),   // posição centralizada com o banheiro
   glm::vec3(0.0f),
   glm::vec3(0.1f, 3.0f, 2.5f),     // largura fina, altura 3, comprimento do banheiro
   0.0f); */
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

        glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                                1280.0f / 720.0f, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        glBindTexture(GL_TEXTURE_2D, texturaMadeiraEscura);

        casa.draw(shader, model);

        //Banheiro
        glBindTexture(GL_TEXTURE_2D, texturaCeramicaBranca);
        vaso.draw(shader, model);
        pia.draw(shader, model);

        /* Parede do banheiro
        glBindTexture(GL_TEXTURE_2D, texturaMadeiraEscura); // ou stoneTex, se quiser um visual mais sólido
        paredeBanheiro.draw(shader, model); */

        // Piso do banheiro
        glBindTexture(GL_TEXTURE_2D, texturaPisoBanheiro);
        pisoBanheiro.draw(shader, model);
        //Banheiro

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
