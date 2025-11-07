#include "Table.h"
#include <GL/glew.h>
#include <memory>
#include "Cube.h"
#include "Cylinder.h"
#include "Sphere.h"

extern unsigned int woodTex;
extern unsigned int stoneTex;
extern unsigned int texturaCeramicaBranca;

Table::Table(glm::vec3 pos)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), 0.0f)
{
    init();
}

void Table::init()
{
    // --- parâmetros principais ---
    float topHeight = 1.0f;
    float topThickness = 0.08f;

    // --- tampo principal ---
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, topHeight, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(1.6f, topThickness, 0.9f),
        0.0f));

    // --- base inferior central (apoio interno discreto) ---
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.45f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(0.2f, 0.05f, 0.6f),
        0.0f));

    // --- pernas em V (4 pernas diagonais duplas) ---
    // frente esquerda
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-0.7f, 0.5f, -0.35f),
        glm::vec3(0.0f, 0.0f, 15.0f),
        glm::vec3(0.1f, 0.9f, 0.1f),
        0.0f));
    // frente direita
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.7f, 0.5f, -0.35f),
        glm::vec3(0.0f, 0.0f, -15.0f),
        glm::vec3(0.1f, 0.9f, 0.1f),
        0.0f));
    // traseira esquerda
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-0.7f, 0.5f, 0.35f),
        glm::vec3(0.0f, 0.0f, -15.0f),
        glm::vec3(0.1f, 0.9f, 0.1f),
        0.0f));
    // traseira direita
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.7f, 0.5f, 0.35f),
        glm::vec3(0.0f, 0.0f, 15.0f),
        glm::vec3(0.1f, 0.9f, 0.1f),
        0.0f));

    // ------------------------
    // PRATOS (4)
    float pratoRadius = 0.22f;
    float pratoThickness = 0.02f;
    float pratoY = topHeight + topThickness * 0.5f + pratoThickness * 0.5f;

    const glm::vec3 pratosPos[4] = {
        glm::vec3(-0.5f, pratoY, -0.25f),
        glm::vec3(0.5f,  pratoY, -0.25f),
        glm::vec3(-0.5f, pratoY,  0.25f),
        glm::vec3(0.5f,  pratoY,  0.25f)
    };

    for (int i = 0; i < 4; ++i) {
        parts.push_back(std::make_unique<Cylinder>(
            pratosPos[i],
            glm::vec3(0.0f),
            glm::vec3(pratoRadius, pratoThickness, pratoRadius),
            0.0f, 32));
    }

    // ------------------------
    // POTE CENTRAL
    float poteRadius = 0.18f;
    float poteHeight = 0.28f;
    float poteY = topHeight + topThickness * 0.5f + poteHeight * 0.5f;

    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.0f, poteY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(poteRadius, poteHeight * 0.5f, poteRadius),
        0.0f, 32));

    parts.push_back(std::make_unique<Sphere>(
        glm::vec3(0.0f, poteY + poteHeight * 0.5f + 0.02f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(poteRadius * 0.9f, 0.06f, poteRadius * 0.9f),
        0.0f));
}

void Table::draw(Shader &shader, glm::mat4 model)
{
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    // madeira — tampo e pernas
    glBindTexture(GL_TEXTURE_2D, woodTex);
    for (int i = 0; i <= 5; ++i)
        parts[i]->draw(shader, model);

    // pratos — cerâmica branca
    glBindTexture(GL_TEXTURE_2D, texturaCeramicaBranca);
    for (int i = 6; i < 10; ++i)
        parts[i]->draw(shader, model);

    // pote — cerâmica
    parts[10]->draw(shader, model);
    parts[11]->draw(shader, model);
}
