#include "Stove.h"
#include <GL/glew.h>
#include <memory>
#include "Cube.h"
#include "Cylinder.h"

extern unsigned int texturaInox; // metal (placa/forno)
extern unsigned int texturaPreto;    // boca preta / vidros

Stove::Stove(glm::vec3 pos)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), 0.0f)
{
    init();
}

void Stove::init()
{
    // corpo / forno (base)
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.35f, 0.0f),    // ligeiro elevação
        glm::vec3(0.0f),
        glm::vec3(1.0f, 0.7f, 0.6f),     // largura x altura x profundidade
        0.0f));

    // tampo (superfície onde ficam as bocas) — mais fino e levemente acima
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.75f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(1.05f, 0.08f, 0.65f),
        0.0f));

    // vidro/porta do forno (painel frontal escuro)
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.25f, 0.33f),
        glm::vec3(0.0f),
        glm::vec3(0.9f, 0.4f, 0.02f),
        0.0f));

    // 4 bocas (discos pretos no topo)
    float hx = 0.35f; // offset x das bocas
    float hz = 0.20f; // offset z das bocas
    float bocaRadius = 0.18f;
    float bocaThickness = 0.04f;
    float bocaY = 0.75f + 0.04f; // ligeiramente acima do tampo

    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(-hx, bocaY, -hz),
        glm::vec3(0.0f),
        glm::vec3(bocaRadius, bocaThickness, bocaRadius),
        0.0f, 32));
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(hx, bocaY, -hz),
        glm::vec3(0.0f),
        glm::vec3(bocaRadius, bocaThickness, bocaRadius),
        0.0f, 32));
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(-hx, bocaY, hz),
        glm::vec3(0.0f),
        glm::vec3(bocaRadius, bocaThickness, bocaRadius),
        0.0f, 32));
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(hx, bocaY, hz),
        glm::vec3(0.0f),
        glm::vec3(bocaRadius, bocaThickness, bocaRadius),
        0.0f, 32));
}

void Stove::draw(Shader &shader, glm::mat4 model)
{
    model = glm::translate(model, position);

    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    // corpo / forno e tampo em inox
    glBindTexture(GL_TEXTURE_2D, texturaInox);
    parts[0]->draw(shader, model); // corpo
    parts[1]->draw(shader, model); // tampo

    // porta/vidro do forno em preto
    glBindTexture(GL_TEXTURE_2D, texturaPreto);
    parts[2]->draw(shader, model);

    // bocas em preto (discos)
    for (int i = 3; i < (int)parts.size(); ++i)
    {
        parts[i]->draw(shader, model);
    }
}
