#include "Casa.h"
#include <GL/glew.h>

extern unsigned int texturaPiso;
extern unsigned int texturaMadeiraEscura;

Casa::Casa(glm::vec3 pos)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), 0.0f)
{
    init();
}

void Casa::init()
{
    float wallHeight = 3.0f;
    float wallThickness = 0.1f;
    float width = 15.0f;   // largura total da casa (eixo X)
    float depth = 15.0f;   // profundidade total da casa (eixo Z)

    //  CHÃO
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(width, 0.1f, depth),
        0.0f));

    //  PAREDES
    // Parede de trás
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, wallHeight / 2.0f, -depth / 2.0f),
        glm::vec3(0.0f),
        glm::vec3(width, wallHeight, wallThickness),
        0.0f));

    // Parede da frente
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, wallHeight / 2.0f, depth / 2.0f),
        glm::vec3(0.0f),
        glm::vec3(width, wallHeight, wallThickness),
        0.0f));

    // Parede esquerda
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-width / 2.0f, wallHeight / 2.0f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(wallThickness, wallHeight, depth),
        0.0f));

    // Parede direita
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(width / 2.0f, wallHeight / 2.0f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(wallThickness, wallHeight, depth),
        0.0f));
}

void Casa::draw(Shader &shader, glm::mat4 model)
{
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    // chão
    glBindTexture(GL_TEXTURE_2D, texturaPiso);
    parts[0]->draw(shader, model);

    // paredes
    glBindTexture(GL_TEXTURE_2D, texturaMadeiraEscura);
    for (int i = 1; i < parts.size(); i++)
        parts[i]->draw(shader, model);
}
