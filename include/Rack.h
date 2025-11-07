#ifndef RACK_H
#define RACK_H
#pragma once
#include "Object.h"
#include "Cube.h"
#include "Cylinder.h"
#include <vector>
#include <memory>
#include "Object.h"

class Rack : public Object
{
public:
    Rack(glm::vec3 pos);
    void draw(Shader &shader, glm::mat4 model);

  private:
    std::vector<std::unique_ptr<Object>> parts;
    void init();
};

#endif
