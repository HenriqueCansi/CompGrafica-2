#pragma once
#include "Object.h"

class Casa : public Object
{
public:
    Casa(glm::vec3 pos);
    void init() ;
    void draw(Shader &shader, glm::mat4 model) override;
};
