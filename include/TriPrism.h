// TriPrism.h
#pragma once
#include "Object.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class TriangularPrism : public Object {
public:
    TriangularPrism(glm::vec3 pos = glm::vec3(0.0f),
                     glm::vec3 rot = glm::vec3(0.0f),
                     glm::vec3 scl = glm::vec3(1.0f),
                     float ang = 0.0f);

    void draw(Shader &shader, glm::mat4 model) override;

private:
    unsigned int VAO, VBO, EBO;
    void init();
};
