#include "Arvore.h"
#include <GL/glew.h>

extern unsigned int texturaMadeiraEscura;
extern unsigned int texturaVerdePeludo;
extern unsigned int texturaArvore;

Arvore::Arvore(glm::vec3 pos)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), 0.0f)
{
    init();
}

void Arvore::init()
{
    // Tronco
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(0.15f, 0.75f, 0.15f),
        0.0f,
        16));

    // Copa (folhas)
    parts.push_back(std::make_unique<Sphere>(
        glm::vec3(0.0f, 0.75f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(0.8f, 0.8f, 0.8f),
        0.0f,
        16, 16));
}

void Arvore::draw(Shader &shader, glm::mat4 model)
{
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    // Tronco
    glBindTexture(GL_TEXTURE_2D, texturaMadeiraEscura);
    parts[0]->draw(shader, model);

    // Copa
    glBindTexture(GL_TEXTURE_2D, texturaArvore);
    parts[1]->draw(shader, model);
}
