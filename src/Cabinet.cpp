#include "Cabinet.h"
#include <GL/glew.h>

extern unsigned int texturaMadeiraEscura;
extern unsigned int texturaMadeiraClara;
extern unsigned int texturaInox;

Cabinet::Cabinet(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang)
    : Object(pos, rot, scl, ang)
{
    init();
}

void Cabinet::init() {
    // Corpo
    parts.push_back(std::make_unique<Cube>(glm::vec3(0.0f, 0.5f, 0.0f),
                                           glm::vec3(0.0f),
                                           glm::vec3(1.0f, 1.5f, 0.5f),
                                           0.0f));
    // Portas
    parts.push_back(std::make_unique<Cube>(glm::vec3(-0.25f, 0.5f, 0.26f),
                                           glm::vec3(0.0f),
                                           glm::vec3(0.45f, 1.4f, 0.05f),
                                           0.0f));
    parts.push_back(std::make_unique<Cube>(glm::vec3(0.25f, 0.5f, 0.26f),
                                           glm::vec3(0.0f),
                                           glm::vec3(0.45f, 1.4f, 0.05f),
                                           0.0f));
    // Maçanetas
    parts.push_back(std::make_unique<Cylinder>(glm::vec3(-0.25f, 0.5f, 0.31f),
                                               glm::vec3(0.0f),
                                               glm::vec3(0.03f, 0.03f, 0.03f),
                                               0.0f, 16));
    parts.push_back(std::make_unique<Cylinder>(glm::vec3(0.25f, 0.5f, 0.31f),
                                               glm::vec3(0.0f),
                                               glm::vec3(0.03f, 0.03f, 0.03f),
                                               0.0f, 16));
}

void Cabinet::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    // Body (wood)
    glBindTexture(GL_TEXTURE_2D, texturaMadeiraEscura);
    parts[0]->draw(shader, model);

    // Doors (light wood)
    glBindTexture(GL_TEXTURE_2D, texturaMadeiraClara);
    parts[1]->draw(shader, model);
    parts[2]->draw(shader, model);

    // Handles (steel)
    glBindTexture(GL_TEXTURE_2D, texturaInox);
    parts[3]->draw(shader, model);
    parts[4]->draw(shader, model);
}
