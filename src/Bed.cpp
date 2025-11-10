#include "Bed.h"
#include <GL/glew.h>

extern unsigned int texturaMadeiraEscura;
extern unsigned int texturaVerdePeludo;
extern unsigned int texturaTecidoBranco;

Bed::Bed(glm::vec3 pos)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), 0.0f)
{
    init();
}

void Bed::init()
{
    // Estrutura da base de madeira
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.25f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(1.5f, 0.2f, 2.8f),
        0.0f));

    // Cabeceira estofada
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.8f, -1.45f),
        glm::vec3(0.0f),
        glm::vec3(1.5f, 1.2f, 0.15f),
        0.0f));

    // Colchão espesso
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.55f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(1.45f, 0.35f, 2.7f),
        0.0f));

    // Travesseiro esquerdo
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-0.45f, 0.78f, -1.05f),
        glm::vec3(0.0f),
        glm::vec3(0.5f, 0.18f, 0.7f),
        0.0f));

    // Travesseiro direito
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.45f, 0.78f, -1.05f),
        glm::vec3(0.0f),
        glm::vec3(0.5f, 0.18f, 0.7f),
        0.0f));

    // Coberta (dobrada, cobre metade do colchão)
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.70f, 0.65f),
        glm::vec3(-3.0f, 0.0f, 0.0f),
        glm::vec3(1.5f, 0.22f, 1.5f),
        0.0f));

    // Base inferior de apoio
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.05f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(1.3f, 0.05f, 2.4f),
        0.0f));
}

void Bed::draw(Shader &shader, glm::mat4 model)
{
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    // Madeira — base e estrutura inferior
    glBindTexture(GL_TEXTURE_2D, texturaMadeiraEscura);
    parts[0]->draw(shader, model);  // estrutura
    parts[6]->draw(shader, model);  // base inferior
    parts[1]->draw(shader, model);  // cabeceira

    // Tecido branco — cabeceira, colchão e travesseiros
    glBindTexture(GL_TEXTURE_2D, texturaTecidoBranco);
    parts[2]->draw(shader, model);  // colchão
    parts[3]->draw(shader, model);  // travesseiro esq.
    parts[4]->draw(shader, model);  // travesseiro dir.

    // Tecido Verde — coberta
    glBindTexture(GL_TEXTURE_2D, texturaVerdePeludo);
    parts[5]->draw(shader, model);
}
