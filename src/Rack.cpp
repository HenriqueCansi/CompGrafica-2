#include "Rack.h"
#include <GL/glew.h>
#include <memory>  // precisa para std::make_unique
#include "Cube.h"  // mesmo que as outras classes usam (para reconhecer Cube)

extern unsigned int texturaMadeiraEscura;
extern unsigned int blackTex;

Rack::Rack(glm::vec3 pos)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), 0.0f)
{
    init();
}

void Rack::init()
{
    // Base inferior (leve, encostada ao chão)
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.1f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(2.0f, 0.1f, 0.6f),
        0.0f));

    // Tampo superior — onde a TV fica
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.6f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(2.0f, 0.1f, 0.6f),
        0.0f));

    // Laterais
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-0.95f, 0.35f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(0.1f, 0.5f, 0.6f),
        0.0f));

    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.95f, 0.35f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(0.1f, 0.5f, 0.6f),
        0.0f));

    // Divisória central
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.35f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(0.05f, 0.5f, 0.6f),
        0.0f));

    // Fundo escuro (decorativo)
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.35f, -0.28f),
        glm::vec3(0.0f),
        glm::vec3(1.9f, 0.5f, 0.02f),
        0.0f));
}

void Rack::draw(Shader &shader, glm::mat4 model)
{
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    // Madeira
    glBindTexture(GL_TEXTURE_2D, texturaMadeiraEscura);
    parts[0]->draw(shader, model);
    parts[1]->draw(shader, model);
    parts[2]->draw(shader, model);
    parts[3]->draw(shader, model);
    parts[4]->draw(shader, model);

    // Fundo preto
    glBindTexture(GL_TEXTURE_2D, blackTex);
    parts[5]->draw(shader, model);
}
