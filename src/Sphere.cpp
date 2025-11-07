#include "Sphere.h"
#include <cmath>

Sphere::Sphere(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, int sectorCount, int stackCount)
    : Object(pos, rot, scl, ang)
{
    init(sectorCount, stackCount);
}

void Sphere::init(int sectorCount, int stackCount) {
    float radius = 0.5f;

    for(int i = 0; i <= stackCount; ++i){
        float stackAngle = M_PI/2 - i * M_PI / stackCount;
        float xy = radius * cos(stackAngle);
        float y = radius * sin(stackAngle);

        for(int j = 0; j <= sectorCount; ++j){
            float sectorAngle = j * 2 * M_PI / sectorCount;
            float x = xy * cos(sectorAngle);
            float z = xy * sin(sectorAngle);

            float u = (float)j / sectorCount;
            float v = (float)i / stackCount;

            vertices.push_back(x); vertices.push_back(y); vertices.push_back(z);
            vertices.push_back(u); vertices.push_back(v);
        }
    }

    for(int i = 0; i < stackCount; ++i){
        int k1 = i * (sectorCount + 1);
        int k2 = k1 + sectorCount + 1;
        for(int j = 0; j < sectorCount; ++j, ++k1, ++k2){
            if(i != 0){
                indices.push_back(k1); indices.push_back(k2); indices.push_back(k1+1);
            }
            if(i != (stackCount-1)){
                indices.push_back(k1+1); indices.push_back(k2); indices.push_back(k2+1);
            }
        }
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // posição
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // textura
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Sphere::draw(Shader &shader, glm::mat4 model){
    model = glm::translate(model, position);
    if(glm::length(rotation) > 0.0f)
        model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));
    model = glm::scale(model, scale);

    shader.setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
