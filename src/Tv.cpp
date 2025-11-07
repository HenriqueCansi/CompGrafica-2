#include "Tv.h"
#include <GL/glew.h>

extern unsigned int texturaInox;  // moldura e suporte
extern unsigned int blackTex;  // tela

Tv::Tv(glm::vec3 pos)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), 0.0f)
{
    init();
}

void Tv::init()
{
    // Moldura metálica externa (estrutura)
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 1.1f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(1.6f, 0.9f, 0.05f),
        0.0f));

    // Tela principal (preta, mais fina e levemente à frente)
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 1.1f, 0.028f),
        glm::vec3(0.0f),
        glm::vec3(1.45f, 0.8f, 0.01f),
        0.0f));

    // Suporte vertical (haste)
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.45f, -0.05f),
        glm::vec3(0.0f),
        glm::vec3(0.08f, 0.35f, 0.05f),
        0.0f));

    // Base inferior metálica
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.25f, -0.05f),
        glm::vec3(0.0f),
        glm::vec3(0.5f, 0.05f, 0.3f),
        0.0f));

    // Pequeno pedestal decorativo embaixo (mais largo, fininho)
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.22f, -0.05f),
        glm::vec3(0.0f),
        glm::vec3(0.8f, 0.02f, 0.35f),
        0.0f));
}

void Tv::draw(Shader &shader, glm::mat4 model)
{
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    // Moldura metálica e suporte
    glBindTexture(GL_TEXTURE_2D, texturaInox);
    parts[0]->draw(shader, model);  // moldura
    parts[2]->draw(shader, model);  // haste
    parts[3]->draw(shader, model);  // base principal
    parts[4]->draw(shader, model);  // pedestal inferior

    // Tela preta
    glBindTexture(GL_TEXTURE_2D, blackTex);
    parts[1]->draw(shader, model);
}
