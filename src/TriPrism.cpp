// TriPrism.cpp
#include "TriPrism.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

TriangularPrism::TriangularPrism(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang)
    : Object(pos, rot, scl, ang)
{
    init();
}

void TriangularPrism::init() {
    float vertices[] = {
        // posição x,y,z   u,v
        -0.5f, 0.0f, -0.5f, 0.0f, 0.0f,  // base inferior
         0.5f, 0.0f, -0.5f, 1.0f, 0.0f,
         0.0f, 0.0f,  0.5f, 0.5f, 1.0f,

        -0.5f, 1.0f, -0.5f, 0.0f, 0.0f,  // base superior
         0.5f, 1.0f, -0.5f, 1.0f, 0.0f,
         0.0f, 1.0f,  0.5f, 0.5f, 1.0f
    };

    unsigned int indices[] = {
        0,1,2,  // base inferior
        3,4,5,  // base superior

        0,1,4, 0,4,3,  // lateral
        1,2,5, 1,5,4,  // lateral
        2,0,3, 2,3,5   // lateral
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // posição
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // textura
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void TriangularPrism::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    if(glm::length(rotation) > 0.0f)
        model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));
    model = glm::scale(model, scale);
    shader.setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
