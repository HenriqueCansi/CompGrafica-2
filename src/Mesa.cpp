#include "Mesa.h"
#include <GL/glew.h>
#include <memory>
#include "Cube.h"
#include "Cylinder.h"
#include "Sphere.h"

extern unsigned int texturaMadeiraEscura;
extern unsigned int texturaPiso;
extern unsigned int texturaCeramicaBranca;
extern unsigned int texturaPoteAmarelo;

Mesa::Mesa(glm::vec3 pos)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), 0.0f)
{
    init();
}

void Mesa::init()
{
    float topHeight = 0.85f;
    float topThickness = 0.1f;

    // --- tampo principal ---
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, topHeight, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(1.6f, topThickness, 0.9f),
        0.0f));

    // --- base inferior ---
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.45f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(0.25f, 0.05f, 0.7f),
        0.0f));

    // --- pernas em V ---
    const float legAngle = 15.0f;
    const float legOffsetX = 0.65f;
    const float legOffsetZ = 0.35f;

    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-legOffsetX, 0.45f, -legOffsetZ),
        glm::vec3(0.0f, 0.0f, legAngle),
        glm::vec3(0.1f, 0.9f, 0.1f),
        0.0f));
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(legOffsetX, 0.45f, -legOffsetZ),
        glm::vec3(0.0f, 0.0f, -legAngle),
        glm::vec3(0.1f, 0.9f, 0.1f),
        0.0f));
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-legOffsetX, 0.45f, legOffsetZ),
        glm::vec3(0.0f, 0.0f, -legAngle),
        glm::vec3(0.1f, 0.9f, 0.1f),
        0.0f));
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(legOffsetX, 0.45f, legOffsetZ),
        glm::vec3(0.0f, 0.0f, legAngle),
        glm::vec3(0.1f, 0.9f, 0.1f),
        0.0f));

    // --- pratos ---
    float pratoRadius = 0.22f;
    float pratoThickness = 0.02f;
    float pratoY = topHeight + topThickness * 0.5f + pratoThickness * 0.5f;

    glm::vec3 pratosPos[4] = {
        {-0.5f, pratoY, -0.25f},
        {0.5f,  pratoY, -0.25f},
        {-0.5f, pratoY,  0.25f},
        {0.5f,  pratoY,  0.25f}
    };

    for (auto &p : pratosPos)
        parts.push_back(std::make_unique<Cylinder>(p, glm::vec3(0.0f),
            glm::vec3(pratoRadius, pratoThickness, pratoRadius), 0.0f, 32));

    // --- pote central ---
    float poteRadius = 0.18f;
    float poteHeight = 0.28f;
    float poteY = topHeight + topThickness * 0.5f + poteHeight * 0.5f;

    // base do pote (disco fino)
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.0f, poteY - poteHeight * 0.5f - 0.03f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(poteRadius * 1.1f, 0.10f, poteRadius * 1.1f),
        0.0f, 32));

    // corpo
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.0f, poteY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(poteRadius, poteHeight * 0.5f, poteRadius),
        0.0f, 32));

    // tampa
    parts.push_back(std::make_unique<Sphere>(
        glm::vec3(0.0f, poteY + poteHeight * 0.5f + 0.02f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(poteRadius * 0.9f, 0.06f, poteRadius * 0.9f),
        0.0f));
}

void Mesa::draw(Shader &shader, glm::mat4 model)
{
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    // madeira
    glBindTexture(GL_TEXTURE_2D, texturaMadeiraEscura);
    for (int i = 0; i <= 5; ++i){
        if(i == 1)
            continue;
        parts[i]->draw(shader, model);
    }

    // pratos
    glBindTexture(GL_TEXTURE_2D, texturaCeramicaBranca);
    for (int i = 6; i < 10; ++i)
        parts[i]->draw(shader, model);


    glBindTexture(GL_TEXTURE_2D, texturaPoteAmarelo);
    // pote
   // for (int i = 10; i < parts.size(); ++i)
     //   parts[i]->draw(shader, model);

    parts[10]->draw(shader, model);


}
