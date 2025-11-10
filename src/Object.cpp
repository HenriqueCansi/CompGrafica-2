#include "Object.h"
#include <glm/gtc/matrix_transform.hpp>  // se usar glm::rotate, glm::translate etc.
#include <glm/gtc/type_ptr.hpp>

Object::Object()
    : position(0.0f), rotation(1.0f, 0.0f, 0.0f), scale(1.0f), angle(0.0f)
{}

Object::Object(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle)
    : position(pos), rotation(rot), scale(scl), angle(angle)
{

}

void Object::draw(Shader& shader, glm::mat4 parentTransform)
{

}
