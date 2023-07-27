#pragma once

#include "Test.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

namespace test {

class TestAssimp : public Test {
public:
    TestAssimp();
    ~TestAssimp();

    void OnUpdate(float deltaTime) override;
    void OnRender() override;
    void OnImGuiRender() override;

private:
    Assimp::Importer m_Importer;
    const aiScene *m_Scene;
};

}