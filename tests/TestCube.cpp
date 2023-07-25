#include "TestCube.h"

#include "Macros.h"
#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>
#include <iostream>

namespace test {

TestCube::TestCube()
    : m_RotationSpeed(1.0f) {
    float vertices[] = {
        // Position  // Normal
        // Front
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.f, // 0
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.f, // 1
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.f, // 2
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.f, // 3
        // Back
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.f, // 4
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.f, // 5
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.f, // 6
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.f, // 7
        // Left
        -0.5f, -0.5f, -0.5f, -1.f, 0.0f, 0.f, // 8
        -0.5f, -0.5f, 0.5f, -1.f, 0.0f, 0.f, // 9
        -0.5f, 0.5f, 0.5f, -1.f, 0.0f, 0.f, // 10
        -0.5f, 0.5f, -0.5f, -1.f, 0.0f, 0.f, // 11
        // Right
        0.5f, -0.5f, -0.5f, 1.f, 0.0f, 0.f, // 12
        0.5f, -0.5f, 0.5f, 1.f, 0.0f, 0.f, // 13
        0.5f, 0.5f, 0.5f, 1.f, 0.0f, 0.f, // 14
        0.5f, 0.5f, -0.5f, 1.f, 0.0f, 0.f, // 15
        // Top
        -0.5f, 0.5f, -0.5f, 0.f, 1.0f, 0.f, // 16
        -0.5f, 0.5f, 0.5f, 0.f, 1.0f, 0.f, // 17
        0.5f, 0.5f, 0.5f, 0.f, 1.0f, 0.f, // 18
        0.5f, 0.5f, -0.5f, 0.f, 1.0f, 0.f, // 19
        // Bottom
        -0.5f, -0.5f, -0.5f, 0.f, -1.0f, 0.f, // 20
        -0.5f, -0.5f, 0.5f, 0.f, -1.0f, 0.f, // 21
        0.5f, -0.5f, 0.5f, 0.f, -1.0f, 0.f, // 22
        0.5f, -0.5f, -0.5f, 0.f, -1.0f, 0.f, // 23
    };
    unsigned int indices[] = {
        0,
        1,
        2, // Front
        2,
        3,
        0,
        4,
        5,
        6, // Back
        6,
        7,
        4,
        8,
        9,
        10, // Left
        10,
        11,
        8,
        12,
        13,
        14, // Right
        14,
        15,
        12,
        16,
        17,
        18, // Top
        18,
        19,
        16,
        20,
        21,
        22, // Bottom
        22,
        23,
        20,
    };

    m_VAO = std::make_unique<VertexArray>();
    // 6 faces of 4 vertices of 6 floats
    m_VBO = std::make_unique<VertexBuffer>(vertices, 6 * 4 * 6 * sizeof(float));
    VertexBufferLayout layout = VertexBufferLayout();
    layout.Push<float>(3); // position
    layout.Push<float>(3); // normal
    m_VAO->AddBuffer(*m_VBO, layout);
    m_IBO = std::make_unique<IndexBuffer>(indices, 36);

    m_Proj = glm::perspective(glm::radians(45.f), 960.f / 540.f, 0.1f, 100.f);
    m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -4));
    m_Model = glm::mat4(1.0f);

    m_Shader = std::make_unique<Shader>("res/shaders/Normal.shader");
    m_Shader->Bind();

    m_VAO->Unbind();
    m_VBO->UnBind();
    m_IBO->UnBind();
    m_Shader->Unbind();
}

TestCube::~TestCube() {
}

void TestCube::OnUpdate(float deltaTime) {
    glm::vec3 axis = glm::normalize(glm::vec3(1.0f, 0.5f, 0.0f));
    float angle = m_RotationSpeed * deltaTime * glm::radians(45.f);
    m_Model = glm::rotate(m_Model, angle, axis);
}

void TestCube::OnRender() {
    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glDisable(GL_CULL_FACE));

    Renderer renderer;

    glm::mat4 mvp = m_Proj * m_View * m_Model;
    m_Shader->Bind();
    m_Shader->SetUniformMat4f("u_MVP", mvp);
    renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
}

void TestCube::OnImGuiRender() {
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
        ImGui::GetIO().Framerate);
    ImGui::SliderFloat("Rotation Speed", &m_RotationSpeed, 0.0f, 100.0f);
}

}