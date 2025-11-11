#pragma once
#include "Object.h"
#include "Cube.h"
#include "Cylinder.h"
#include <vector>
#include <memory>
#include "Sphere.h"

class Arvore : public Object
{
public:
    Arvore(glm::vec3 pos);
    void draw(Shader &shader, glm::mat4 model) override;

private:
    std::vector<std::unique_ptr<Object>> parts;
    void init();
};
