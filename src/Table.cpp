#include "Table.h"
#include <GL/glew.h>

extern unsigned int woodTex;
extern unsigned int stoneTex;

Table::Table(glm::vec3 pos)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), 0.0f)
{
    init();
}

void Table::init() {
    float topHeight = 1.0f;
    float topThickness = 0.1f;
    float legRadius = 0.15f;
    float legHeight = topHeight - topThickness;
    float legCenterY = topThickness;

    // Tampo
    parts.push_back(std::make_unique<Cube>(glm::vec3(0.0f, topHeight, 0.0f),
                                           glm::vec3(0.0f),
                                           glm::vec3(1.7f, topThickness, 1.0f),
                                           0.0f));

    // Pernas
    parts.push_back(std::make_unique<Cylinder>(glm::vec3(-0.7f, legCenterY, -0.4f), glm::vec3(0.0f),
                                               glm::vec3(legRadius, legHeight, legRadius), 0.0f, 16));
    parts.push_back(std::make_unique<Cylinder>(glm::vec3(0.7f, legCenterY, -0.4f), glm::vec3(0.0f),
                                               glm::vec3(legRadius, legHeight, legRadius), 0.0f, 16));
    parts.push_back(std::make_unique<Cylinder>(glm::vec3(-0.7f, legCenterY, 0.4f), glm::vec3(0.0f),
                                               glm::vec3(legRadius, legHeight, legRadius), 0.0f, 16));
    parts.push_back(std::make_unique<Cylinder>(glm::vec3(0.7f, legCenterY, 0.4f), glm::vec3(0.0f),
                                               glm::vec3(legRadius, legHeight, legRadius), 0.0f, 16));
}

void Table::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    // Top (light wood)
    glBindTexture(GL_TEXTURE_2D, stoneTex);
    parts[0]->draw(shader, model);

    // Legs (dark wood)
    glBindTexture(GL_TEXTURE_2D, woodTex);
    for (int i = 1; i < 5; i++)
        parts[i]->draw(shader, model);
}
