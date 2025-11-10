#include "Cadeira.h"
#include <GL/glew.h>

extern unsigned int texturaMadeiraEscura;
extern unsigned int texturaMadeiraClara;

Cadeira::Cadeira(glm::vec3 pos, glm::vec3 scl)
    : Object(pos, glm::vec3(0.0f), scl, 0.0f)
{
    init();
}

void Cadeira::init() {
    // assento
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.5f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(1.0f, 0.1f, 1.0f),
        0.0f
    ));

    // encosto
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 1.0f, -0.45f),
        glm::vec3(0.0f),
        glm::vec3(1.0f, 1.0f, 0.1f),
        0.0f
    ));

    // pernas
    float legX = 0.45f, legZ = 0.45f, legY = 0.5f;
    parts.push_back(std::make_unique<Cube>(glm::vec3(-legX, legY/2, legZ), glm::vec3(0.0f), glm::vec3(0.1f, legY, 0.1f), 0.0f));
    parts.push_back(std::make_unique<Cube>(glm::vec3(legX, legY/2, legZ), glm::vec3(0.0f), glm::vec3(0.1f, legY, 0.1f), 0.0f));
    parts.push_back(std::make_unique<Cube>(glm::vec3(-legX, legY/2, -legZ), glm::vec3(0.0f), glm::vec3(0.1f, legY, 0.1f), 0.0f));
    parts.push_back(std::make_unique<Cube>(glm::vec3(legX, legY/2, -legZ), glm::vec3(0.0f), glm::vec3(0.1f, legY, 0.1f), 0.0f));
}

void Cadeira::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    // assento
    glBindTexture(GL_TEXTURE_2D, texturaMadeiraClara);
    parts[0]->draw(shader, model);

    // encosto
    glBindTexture(GL_TEXTURE_2D, texturaMadeiraEscura);
    parts[1]->draw(shader, model);

    // pernas
    glBindTexture(GL_TEXTURE_2D, texturaMadeiraEscura);
    for (int i = 2; i < 6; i++)
        parts[i]->draw(shader, model);
}
