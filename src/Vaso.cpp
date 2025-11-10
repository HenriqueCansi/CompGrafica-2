#include "Vaso.h"
#include <GL/glew.h>

extern unsigned int texturaCeramicaBranca;
extern unsigned int texturaAgua;

Vaso::Vaso(glm::vec3 pos)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), 0.0f)
{
    init();
}

void Vaso::init()
{
    // base
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(0.24f, 0.21f, 0.35f),
        0.0f,
        16));

    // bowl
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.0f, 0.21f, 0.035f),
        glm::vec3(0.0f),
        glm::vec3(0.433f, 0.22f, 0.62f),
        0.0f,
        16));

    // lid
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.0f, 0.68f, -0.265f),
        glm::vec3(-90.0f, 0.0f, 0.0f),
        glm::vec3(0.433f, 0.07f, 0.5f),
        0.0f,
        16));

    // tank
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.67f, -0.387f),
        glm::vec3(0.0f),
        glm::vec3(0.577f, 0.7f, 0.223f),
        0.0f));

    // button
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.0f, 0.996f, -0.387f),
        glm::vec3(0.0f),
        glm::vec3(0.1f, 0.048f, 0.1f),
        0.0f,
        16));

    // water
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.0f, 0.23f, 0.025f),
        glm::vec3(0.0f),
        glm::vec3(0.327f, 0.22f, 0.4f),
        0.0f,
        16));
}

void Vaso::draw(Shader &shader, glm::mat4 model)
{
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    // White ceramic
    glBindTexture(GL_TEXTURE_2D, texturaCeramicaBranca);
    parts[0]->draw(shader, model);
    parts[1]->draw(shader, model);
    //parts[2]->draw(shader, model);
    parts[3]->draw(shader, model);
    parts[4]->draw(shader, model);

    // agua
    glBindTexture(GL_TEXTURE_2D, texturaAgua);
    parts[5]->draw(shader, model);
}
