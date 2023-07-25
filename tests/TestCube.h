#pragma once

#include "IndexBuffer.h"
#include "Shader.h"
#include "Test.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

#include <glm/glm.hpp>
#include <memory>

namespace test {

class TestCube : public Test {
public:
    TestCube();
    ~TestCube();

    void OnUpdate(float deltaTime) override;
    void OnRender() override;
    void OnImGuiRender() override;

private:
    std::unique_ptr<VertexArray> m_VAO;
    std::unique_ptr<VertexBuffer> m_VBO;
    std::unique_ptr<IndexBuffer> m_IBO;
    std::unique_ptr<Shader> m_Shader;

    glm::mat4 m_Proj;
    glm::mat4 m_View;
    glm::mat4 m_Model;

    float m_RotationSpeed;
};

}