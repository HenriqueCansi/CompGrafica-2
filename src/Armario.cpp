#include "Armario.h"
#include <GL/glew.h>
#include <memory>
#include "Cube.h"
#include "Cylinder.h"

extern unsigned int texturaMadeiraEscura;
extern unsigned int texturaMadeiraClara;
extern unsigned int texturaInox;

Armario::Armario(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang)
    : Object(pos, rot, scl, ang)
{
    init();
}

void Armario::init()
{
    // 🔹 Medidas gerais
    float corpoAltura = 1.5f;
    float corpoLargura = 1.2f;
    float corpoProfundidade = 0.45f;
    float espessuraPorta = 0.05f;

    // Corpo principal (estrutura externa)
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, corpoAltura * 0.5f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(corpoLargura, corpoAltura, corpoProfundidade),
        0.0f));

    // Portas — com leve afastamento para frente
    float zOffsetPorta = corpoProfundidade * 0.5f + 0.025f;
    float portaAltura = corpoAltura * 0.95f;
    float portaLargura = corpoLargura * 0.48f;

    // Porta esquerda
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-portaLargura * 0.55f, corpoAltura * 0.5f, zOffsetPorta),
        glm::vec3(0.0f),
        glm::vec3(portaLargura, portaAltura, espessuraPorta),
        0.0f));

    // Porta direita
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(portaLargura * 0.55f, corpoAltura * 0.5f, zOffsetPorta),
        glm::vec3(0.0f),
        glm::vec3(portaLargura, portaAltura, espessuraPorta),
        0.0f));

    // Maçanetas (cilindros horizontais)
    float yHandle = corpoAltura * 0.5f;
    float zHandle = zOffsetPorta + 0.03f;
    float handleRadius = 0.03f;
    float handleLength = 0.15f;

    // Maçaneta esquerda
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(-0.15f, yHandle, zHandle),
        glm::vec3(0.0f, 90.0f, 0.0f),
        glm::vec3(handleLength, handleRadius, handleLength),
        0.0f, 16));

    // Maçaneta direita
    parts.push_back(std::make_unique<Cylinder>(
        glm::vec3(0.15f, yHandle, zHandle),
        glm::vec3(0.0f, 90.0f, 0.0f),
        glm::vec3(handleLength, handleRadius, handleLength),
        0.0f, 16));
}

void Armario::draw(Shader &shader, glm::mat4 model)
{
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    model = glm::scale(model, scale);

    // Corpo (madeira escura)
    glBindTexture(GL_TEXTURE_2D, texturaMadeiraEscura);
    parts[0]->draw(shader, model);

    // Portas (madeira clara)
    glBindTexture(GL_TEXTURE_2D, texturaMadeiraClara);
    parts[1]->draw(shader, model);
    parts[2]->draw(shader, model);

    // Maçanetas (inox)
    glBindTexture(GL_TEXTURE_2D, texturaInox);
    parts[3]->draw(shader, model);
    parts[4]->draw(shader, model);
}
