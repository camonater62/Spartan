#pragma once

#include "IndexBuffer.h"
#include "Shader.h"
#include "Test.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

#include <PxPhysicsAPI.h>
#include <glm/glm.hpp>
#include <memory>

namespace test {

class TestPhysX : public Test {
public:
    TestPhysX();
    ~TestPhysX();

    void OnUpdate(float deltaTime) override;
    void OnRender() override;
    void OnImGuiRender() override;

private:
    std::unique_ptr<VertexArray> m_VAO;
    std::unique_ptr<VertexBuffer> m_VBO;
    std::unique_ptr<IndexBuffer> m_IBO;
    std::unique_ptr<Shader> m_BlockShader;
    std::unique_ptr<Shader> m_GroundShader;
    std::unique_ptr<Texture> m_Texture;

    glm::mat4 m_Proj;
    glm::mat4 m_View;

    float m_RotationSpeed;

    physx::PxDefaultAllocator gDefaultAllocatorCallback;
    physx::PxDefaultErrorCallback gDefaultErrorCallback;
    physx::PxDefaultCpuDispatcher *gDispatcher;
    physx::PxTolerancesScale gTolerancesScale;

    physx::PxPhysics *gPhysics;
    physx::PxFoundation *gFoundation;

    physx::PxScene *gScene;
    physx::PxMaterial *gMaterial;

    physx::PxPvd *gPvd;
    physx::PxPvdTransport *transport;

    physx::PxRigidStatic *groundPlane;
    std::vector<physx::PxRigidDynamic *> boxes;

    void createStack(const physx::PxTransform &t, physx::PxU32 size, physx::PxReal halfExtent);
};

}