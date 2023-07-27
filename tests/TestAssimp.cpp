#include "TestAssimp.h"

#include "Macros.h"
#include "Renderer.h"
#include "imgui.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace test {

TestAssimp::TestAssimp() {
    m_Scene = m_Importer.ReadFile("res/models/Lambo.glb",
        aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices
            | aiProcess_SortByPType | aiProcess_OptimizeGraph | aiProcess_GenNormals
            | aiProcess_GenUVCoords | aiProcess_GenBoundingBoxes | aiProcess_ValidateDataStructure);

    if (!m_Scene || m_Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !m_Scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << m_Importer.GetErrorString() << std::endl;
        return;
    }
}

TestAssimp::~TestAssimp() {
}

void TestAssimp::OnUpdate(float deltaTime) {
    (void) deltaTime;
}

void TestAssimp::OnRender() {
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void TestAssimp::OnImGuiRender() {
    ImGui::Text("Meshes: %d", m_Scene->mNumMeshes);
    ImGui::Separator();
    for (unsigned int i = 0; i < m_Scene->mNumMeshes; i++) {
        ImGui::Text("Name: %s", m_Scene->mMeshes[i]->mName.C_Str());
        ImGui::Text("Vertices: %d", m_Scene->mMeshes[i]->mNumVertices);
        ImGui::Text("Faces: %d", m_Scene->mMeshes[i]->mNumFaces);
        ImGui::Text("Material Index: %d", m_Scene->mMeshes[i]->mMaterialIndex);
        // ImGui::Text("Bones: %d", m_Scene->mMeshes[i]->mNumBones);
        // ImGui::Text("Has Normals: %s", m_Scene->mMeshes[i]->HasNormals() ? "true" : "false");
        // ImGui::Text("Has Tangents and Bitangents: %s",
        //     m_Scene->mMeshes[i]->HasTangentsAndBitangents() ? "true" : "false");
        // ImGui::Text("Has Texture Coordinates: %s",
        //     m_Scene->mMeshes[i]->HasTextureCoords(0) ? "true" : "false");
        // ImGui::Text(
        //     "Has Vertex Colors: %s", m_Scene->mMeshes[i]->HasVertexColors(0) ? "true" : "false");

        ImGui::Separator();
    }

    ImGui::Text("Materials: %d", m_Scene->mNumMaterials);
    ImGui::Separator();
    for (unsigned int i = 0; i < m_Scene->mNumMaterials; i++) {
        ImGui::Text("Name: %s", m_Scene->mMaterials[i]->GetName().C_Str());
        // for (unsigned int j = 0; j < m_Scene->mMaterials[i]->mNumProperties; j++) {
        //     ImGui::Text("Property Name: %s", m_Scene->mMaterials[i]->mProperties[j]->mKey.C_Str());
        //     ImGui::Text("Property Type: %d", m_Scene->mMaterials[i]->mProperties[j]->mType);
        //     ImGui::Text("Property Index: %d", m_Scene->mMaterials[i]->mProperties[j]->mIndex);
        //     ImGui::Text(
        //         "Property Data Length: %d", m_Scene->mMaterials[i]->mProperties[j]->mDataLength);
        //     ImGui::Separator();
        // }
        ImGui::Separator();
    }

    ImGui::Text("Textures: %d", m_Scene->mNumTextures);
    ImGui::Separator();
    for (unsigned int i = 0; i < m_Scene->mNumTextures; i++) {
        ImGui::Text("Name: %s", m_Scene->mTextures[i]->mFilename.C_Str());
        ImGui::Text("Width: %d", m_Scene->mTextures[i]->mWidth);
        ImGui::Text("Height: %d", m_Scene->mTextures[i]->mHeight);
        ImGui::Text("Format Hint: %s", m_Scene->mTextures[i]->achFormatHint);
        ImGui::Text("Data Length: %d", m_Scene->mTextures[i]->mWidth);
        ImGui::Separator();
    }

    ImGui::Text("Lights: %d", m_Scene->mNumLights);
    ImGui::Text("Cameras: %d", m_Scene->mNumCameras);
    ImGui::Text("Animations: %d", m_Scene->mNumAnimations);
}

}
