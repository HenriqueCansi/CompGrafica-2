#include "Stove.h"
#include <GL/glew.h>

extern unsigned int texturaInox;
extern unsigned int blackTex;
extern unsigned int texturaMadeiraClara;

Stove::Stove(glm::vec3 pos)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), 0.0f)
{
    init();
}

void Stove::init()
{
    // corpo principal
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.5f + 0.0f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        0.0f));

    // cabeça
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.5f + 0.5f + (0.25f / 2.0f), -0.5f + 0.05f),
        glm::vec3(0.0f),
        glm::vec3(1.0f, 0.25f, 0.1f),
        0.0f));

    // forno
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.5f + -0.1f, 0.5f + 0.05f / 2.0f),
        glm::vec3(0.0f),
        glm::vec3(0.9f, 0.7f, 0.05f),
        0.0f));

    // puxador
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.5f + 0.2f, 0.5f + 0.05f + 0.05f / 2.0f),
        glm::vec3(0.0f),
        glm::vec3(0.9f, 0.1f, 0.05f),
        0.0f));

    // 5 bocas
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(-0.325f, 0.5f + 0.5f, -0.225f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.25f, 0.05f, 0.25f),
        0.0f,
        20));
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(-0.325f, 0.5f + 0.5f, 0.325f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.25f, 0.05f, 0.25f),
        0.0f,
        20));
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.325f, 0.5f + 0.5f, -0.225f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.25f, 0.05f, 0.25f),
        0.0f,
        20));
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.325f, 0.5f + 0.5f, 0.325f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.25f, 0.05f, 0.25f),
        0.0f,
        20));
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.0f, 0.5f + 0.5f, 0.045f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.25f, 0.05f, 0.25f),
        0.0f,
        20));

    // botões (5)
    for (int i = 0; i < 5; ++i)
    {
        parts.push_back(std::make_unique<Cylinder>(
            glm::vec3(-0.4f + i * 0.2f, 0.5f + 0.375f, 0.5f),
            glm::vec3(0.0f, 90.0f, 0.0f),
            glm::vec3(0.15f, 0.05f, 0.15f),
            0.0f,
            20));
    }
}

void Stove::draw(Shader &shader, glm::mat4 model)
{
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    // Steel
    glBindTexture(GL_TEXTURE_2D, texturaInox);
    parts[0]->draw(shader, model);
    parts[1]->draw(shader, model);

    // Black
    glBindTexture(GL_TEXTURE_2D, blackTex);
    parts[2]->draw(shader, model);
    parts[3]->draw(shader, model);
    parts[4]->draw(shader, model);
    parts[5]->draw(shader, model);
    parts[6]->draw(shader, model);
    parts[7]->draw(shader, model);
    parts[8]->draw(shader, model);

    // Steel
    glBindTexture(GL_TEXTURE_2D, texturaInox);
    parts[9]->draw(shader, model);
    parts[10]->draw(shader, model);
    parts[11]->draw(shader, model);
    parts[12]->draw(shader, model);
    parts[13]->draw(shader, model);
}
