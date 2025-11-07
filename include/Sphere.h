// Sphere.h
#pragma once
#include "Object.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <vector>

class Sphere : public Object {
public:
    Sphere(glm::vec3 pos = glm::vec3(0.0f),
           glm::vec3 rot = glm::vec3(0.0f),
           glm::vec3 scl = glm::vec3(1.0f),
           float ang = 0.0f,
           int sectorCount = 20,
           int stackCount = 20);

    void draw(Shader &shader, glm::mat4 model) override;

private:
    unsigned int VAO, VBO, EBO;
    void init(int sectorCount, int stackCount);
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
};
