#include "Sink.h"
#include <GL/glew.h>

extern unsigned int texturaCeramicaBranca;
extern unsigned int blackTex;
extern unsigned int texturaAgua;

Sink::Sink(glm::vec3 pos)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), 0.0f)
{
    init();
}

void Sink::init()
{
    // base
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.3f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(0.23f, 0.6f, 0.275f),
        0.0f));

    // tank
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.725f, 0.078f),
        glm::vec3(0.0f),
        glm::vec3(0.55f, 0.25f, 0.55f),
        0.0f));

    // valve
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.0f, 0.85f, -0.143f),
        glm::vec3(0.0f),
        glm::vec3(0.05f, 0.13f, 0.05f),
        0.0f,
        16));
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.0f, 0.98f, -0.143f),
        glm::vec3(0.0f),
        glm::vec3(0.09f, 0.03f, 0.09f),
        0.0f,
        16));
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.944f, -0.07f),
        glm::vec3(0.0f),
        glm::vec3(0.03f, 0.03f, 0.145f),
        0.0f));

    // water
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.834f, 0.103f),
        glm::vec3(0.0f),
        glm::vec3(0.4f, 0.07f, 0.4f),
        0.0f));
}

void Sink::draw(Shader &shader, glm::mat4 model)
{
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    // White ceramic
    glBindTexture(GL_TEXTURE_2D, texturaCeramicaBranca);
    parts[0]->draw(shader, model);
    parts[1]->draw(shader, model);

    // Black
    glBindTexture(GL_TEXTURE_2D, blackTex);
    parts[2]->draw(shader, model);
    parts[3]->draw(shader, model);
    parts[4]->draw(shader, model);

    // Water ripple
    glBindTexture(GL_TEXTURE_2D, texturaAgua);
    parts[5]->draw(shader, model);
}
