#include "Sink.h"
#include <GL/glew.h>
#include <memory>
#include "Cube.h"
#include "Cylinder.h"

extern unsigned int texturaInox;
extern unsigned int texturaCeramicaBranca;
extern unsigned int texturaPiso;
extern unsigned int texturaMadeiraClara;
extern unsigned int texturaAgua;

Sink::Sink(glm::vec3 pos)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), 0.0f)
{
    init();
}

void Sink::init()
{
    // --- Base da pia (móvel de apoio) ---
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.45f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(1.0f, 0.9f, 0.5f),
        0.0f));

    // --- Tampo da pia ---
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.95f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(1.05f, 0.05f, 0.55f),
        0.0f));

    // --- Cuba (parte interna branca) ---
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.97f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(0.5f, 0.08f, 0.35f),
        0.0f));

    // --- Torneira (corpo metálico) ---
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.15f, 0.97f, 0.15f),
        glm::vec3(0.0f),
        glm::vec3(0.03f, 0.25f, 0.03f),
        0.0f, 16));

    // --- Curva superior da torneira ---
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.15f, 1.25f, 0.05f),
        glm::vec3(90.0f, 0.0f, 0.0f),
        glm::vec3(0.03f, 0.12f, 0.03f),
        0.0f, 16));
}

void Sink::draw(Shader &shader, glm::mat4 model)
{
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, scale);

    // --- Base de madeira ---
    glBindTexture(GL_TEXTURE_2D, texturaMadeiraClara);
    parts[0]->draw(shader, model);

    // --- Tampo de cerâmica ---
    glBindTexture(GL_TEXTURE_2D, texturaCeramicaBranca);
    parts[1]->draw(shader, model);

    // --- Cuba ---
    glBindTexture(GL_TEXTURE_2D, texturaAgua);
    parts[2]->draw(shader, model);

    // --- Torneira metálica ---
    glBindTexture(GL_TEXTURE_2D, texturaInox);
    parts[3]->draw(shader, model);
    //parts[4]->draw(shader, model);
}
