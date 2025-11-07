#include "Casa.h"
#include <GL/glew.h>

// Texturas usadas na casa
extern unsigned int texturaParede;
extern unsigned int texturaChao;
extern unsigned int texturaMadeiraPorta;
extern unsigned int texturaJanelaVidro;

Casa::Casa(glm::vec3 pos)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), 0.0f)
{
    init();
}

void Casa::init()
{
    // Piso
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(8.0f, 0.1f, 8.0f),
        0.0f));

    // Parede traseira
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 2.5f, -4.0f),
        glm::vec3(0.0f),
        glm::vec3(8.0f, 5.0f, 0.2f),
        0.0f));

    // Parede frontal (com abertura de porta)
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-2.0f, 2.5f, 4.0f),
        glm::vec3(0.0f),
        glm::vec3(4.0f, 5.0f, 0.2f),
        0.0f));

    // Parede frontal direita (depois da porta)
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(3.0f, 2.5f, 4.0f),
        glm::vec3(0.0f),
        glm::vec3(2.0f, 5.0f, 0.2f),
        0.0f));

    // Parede esquerda
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-4.0f, 2.5f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(0.2f, 5.0f, 8.0f),
        0.0f));

    // Parede direita (com uma janela)
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(4.0f, 2.5f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(0.2f, 5.0f, 8.0f),
        0.0f));

    // Porta
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.5f, 1.25f, 4.1f),
        glm::vec3(0.0f),
        glm::vec3(1.5f, 2.5f, 0.1f),
        0.0f));

    // Janela (vidro)
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(4.05f, 2.8f, -1.5f),
        glm::vec3(0.0f),
        glm::vec3(0.05f, 1.2f, 2.0f),
        0.0f));
}

void Casa::draw(Shader &shader, glm::mat4 model)
{
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    // Piso
    glBindTexture(GL_TEXTURE_2D, texturaChao);
    parts[0]->draw(shader, model);

    // Paredes
    glBindTexture(GL_TEXTURE_2D, texturaPar
