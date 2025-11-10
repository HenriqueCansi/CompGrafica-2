#include "Sofa.h"
#include <GL/glew.h>

extern unsigned int tecidoSofa;

Sofa::Sofa(glm::vec3 pos)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), 0.0f)
{
    init();
}

void Sofa::init()
{
    // Base do sofá (assento principal)
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.20f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(2.5f, 0.4f, 1.0f),
        0.0f));

    // Encosto levemente inclinado
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.70f, -0.45f),
        glm::vec3(-10.0f, 0.0f, 0.0f),
        glm::vec3(2.5f, 1.0f, 0.25f),
        0.0f));

    // Braço esquerdo (mais quadrado)
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-1.35f, 0.50f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(0.25f, 0.9f, 1.0f),
        0.0f));

    // Braço direito (mais quadrado)
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(1.35f, 0.50f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(0.25f, 0.9f, 1.0f),
        0.0f));

    // Almofada 1
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-0.65f, 0.50f, 0.05f),
        glm::vec3(0.0f),
        glm::vec3(1.0f, 0.3f, 0.9f),
        0.0f));

    // Almofada 2
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.65f, 0.50f, 0.05f),
        glm::vec3(0.0f),
        glm::vec3(1.0f, 0.3f, 0.9f),
        0.0f));
}

void Sofa::draw(Shader &shader, glm::mat4 model)
{
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    glBindTexture(GL_TEXTURE_2D, tecidoSofa);

    for (auto &part : parts)
        part->draw(shader, model);
}
