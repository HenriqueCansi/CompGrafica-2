#pragma once
#include "Object.h"
#include "Cube.h"
#include "Cylinder.h"
#include <vector>
#include <memory>

class Cabinet : public Object {
public:
    Cabinet(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 rot = glm::vec3(0.0f),
            glm::vec3 scl = glm::vec3(1.0f), float ang = 0.0f);

    void draw(Shader &shader, glm::mat4 model) override;

private:
    std::vector<std::unique_ptr<Object>> parts;
    void init();
};
