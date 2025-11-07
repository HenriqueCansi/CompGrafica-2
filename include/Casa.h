#pragma once
#include "Object.h"
#include "Cube.h"
#include "Cylinder.h"
#include <vector>
#include <memory>

class Casa : public Object
{
public:
    Casa(glm::vec3 pos);
    void draw(Shader &shader, glm::mat4 model) override;

    private:
    std::vector<std::unique_ptr<Object>> parts;
    void init();
};
