#include "Cylinder.h"
#include <cmath>

Cylinder::Cylinder(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, int segments)
    : Object(pos, rot, scl, ang)
{
    init(segments);
}

void Cylinder::init(int segments){
    float radius = 0.5f, height = 1.0f;

    for(int i = 0; i < segments; i++){
        float theta = 2.0f * M_PI * i / segments;
        float x = radius * cos(theta);
        float z = radius * sin(theta);
        float u = (float)i / segments; // coordenada horizontal

        // base
        vertices.push_back(x); vertices.push_back(0.0f); vertices.push_back(z); vertices.push_back(u); vertices.push_back(0.0f);
        // topo
        vertices.push_back(x); vertices.push_back(height); vertices.push_back(z); vertices.push_back(u); vertices.push_back(1.0f);
    }

    // centro base e topo
    vertices.push_back(0.0f); vertices.push_back(0.0f); vertices.push_back(0.0f); vertices.push_back(0.5f); vertices.push_back(0.0f);
    vertices.push_back(0.0f); vertices.push_back(height); vertices.push_back(0.0f); vertices.push_back(0.5f); vertices.push_back(1.0f);

    // indices
    for(int i = 0; i < segments; i++){
        int next = (i+1)%segments;
        // lateral
        indices.push_back(i*2); indices.push_back(i*2+1); indices.push_back(next*2+1);
        indices.push_back(i*2); indices.push_back(next*2+1); indices.push_back(next*2);
        // base
        indices.push_back(2*segments); indices.push_back(next*2); indices.push_back(i*2);
        // topo
        indices.push_back(2*segments+1); indices.push_back(i*2+1); indices.push_back(next*2+1);
    }

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // posição
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // textura
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Cylinder::draw(Shader &shader, glm::mat4 model){
    model = glm::translate(model, position);
    if(glm::length(rotation) > 0.0f)
        model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));
    model = glm::scale(model, scale);

    shader.setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
