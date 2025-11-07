#pragma once
#include "Object.h"
#include "Cube.h"
#include "Cylinder.h"
#include <vector>
#include <memory>

class Tv : public Object
{
public:
    Tv(glm::vec3 pos = glm::vec3(0.0f));
    void draw(Shader &shader, glm::mat4 model) override;

private:
    std::vector<std::unique_ptr<Object>> parts;
    void init();
};
