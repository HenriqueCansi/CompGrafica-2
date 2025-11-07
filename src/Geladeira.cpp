#include "Geladeira.h"
#include <GL/glew.h>
#include <memory>
#include "Cube.h"
#include "Cylinder.h"

extern unsigned int steelTex;         // corpo principal
extern unsigned int blackTex;         // divisórias / sombreamento
extern unsigned int lightWoodTex;     // detalhes ou puxadores opcionais

Geladeira::Geladeira(glm::vec3 pos)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), 0.0f)
{
    init();
}

void Geladeira::init()
{
    // Corpo principal
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 1.05f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(1.0f, 2.1f, 0.7f),
        0.0f));

    // Porta superior (freezer)
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 1.65f, 0.355f),
        glm::vec3(0.0f),
        glm::vec3(0.99f, 0.55f, 0.02f),
        0.0f));

    // Porta inferior (geladeira)
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.65f, 0.355f),
        glm::vec3(0.0f),
        glm::vec3(0.99f, 1.15f, 0.02f),
        0.0f));

    // Divisória entre freezer e geladeira
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 1.15f, 0.35f),
        glm::vec3(0.0f),
        glm::vec3(0.99f, 0.02f, 0.025f),
        0.0f));

    // Base metálica inferior (rodapé)
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(1.05f, 0.1f, 0.72f),
        0.0f));

    // Puxador embutido vertical esquerdo (freezer)
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-0.47f, 1.65f, 0.36f),
        glm::vec3(0.0f),
        glm::vec3(0.03f, 0.45f, 0.02f),
        0.0f));

    // Puxador embutido vertical esquerdo (geladeira)
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-0.47f, 0.65f, 0.36f),
        glm::vec3(0.0f),
        glm::vec3(0.03f, 1.0f, 0.02f),
        0.0f));
}

void Geladeira::draw(Shader &shader, glm::mat4 model)
{
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    // Corpo e portas — textura metálica (inox)
    glBindTexture(GL_TEXTURE_2D, steelTex);
    parts[0]->draw(shader, model); // corpo
    parts[1]->draw(shader, model); // porta superior
    parts[2]->draw(shader, model); // porta inferior
    parts[4]->draw(shader, model); // rodapé

    // Divisória preta entre portas
    glBindTexture(GL_TEXTURE_2D, blackTex);
    parts[3]->draw(shader, model);

    // Puxadores embutidos — leve contraste (madeira clara ou preto)
    glBindTexture(GL_TEXTURE_2D, lightWoodTex);
    parts[5]->draw(shader, model);
    parts[6]->draw(shader, model);
}
