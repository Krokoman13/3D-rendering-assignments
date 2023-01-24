#include "TerrainMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/config.hpp"

ShaderProgram* TerrainMaterial::_shader = NULL;

GLint TerrainMaterial::_uMVPMatrix = 0;
GLint TerrainMaterial::_USplatMapTexture = 0;

GLint TerrainMaterial::_aVertex = 0;
GLint TerrainMaterial::_aNormal = 0;
GLint TerrainMaterial::_aUV = 0;

GLint TerrainMaterial::_uHeightMapTexture = 0;
GLint TerrainMaterial::_uSplatMapTexture = 0;
GLint TerrainMaterial::_uDiffuseTexture1 = 0;
GLint TerrainMaterial::_uDiffuseTexture2 = 0;
GLint TerrainMaterial::_uDiffuseTexture3 = 0;
GLint TerrainMaterial::_uDiffuseTexture4 = 0;

TerrainMaterial::TerrainMaterial(Texture* pHeightMapTexture, Texture* pSplatmap, Texture* pDiffuseTexture1, Texture* pDiffuseTexture2, Texture* pDiffuseTexture3, Texture* pDiffuseTexture4)
    :_hightMapTexture(pHeightMapTexture), _splatmapTexture(pSplatmap), _diffuseTexture1(pDiffuseTexture1), _diffuseTexture2(pDiffuseTexture2), _diffuseTexture3(pDiffuseTexture3), _diffuseTexture4(pDiffuseTexture4)
{
    _lazyInitializeShader();
}

TerrainMaterial::~TerrainMaterial() {}

void TerrainMaterial::_lazyInitializeShader() {
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH +"hightmap.vert");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "splatmap.frag");
        _shader->finalize();

        //cache all the uniform and attribute indexes
        _uMVPMatrix = _shader->getUniformLocation("mvpMatrix");
        _USplatMapTexture = _shader->getUniformLocation("diffuseTexture");

        _aVertex = _shader->getAttribLocation("vertex");
        _aNormal = _shader->getAttribLocation("normal");
        _aUV = _shader->getAttribLocation("uv");

        _uHeightMapTexture = _shader->getUniformLocation("heightMapTexture");
        _uSplatMapTexture = _shader->getUniformLocation("textureSplatMap");
        _uDiffuseTexture1 = _shader->getUniformLocation("textureDiffuse1");
        _uDiffuseTexture2 = _shader->getUniformLocation("textureDiffuse2");
        _uDiffuseTexture3 = _shader->getUniformLocation("textureDiffuse3");
        _uDiffuseTexture4 = _shader->getUniformLocation("textureDiffuse4");
    }
}

void TerrainMaterial::setDiffuseTexture(Texture* pDiffuseTexture) {
    _splatmapTexture = pDiffuseTexture;
}

void TerrainMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
    if (!_splatmapTexture) return;

    _shader->use();

    //Print the number of lights in the scene and the position of the first light.
    //It is not used, but this demo is just meant to show you THAT materials can access the lights in a world
    //if (pWorld->getLightCount() > 0) {
    //    std::cout << "TextureMaterial has discovered light is at position:" << pWorld->getLightAt(0)->getLocalPosition() << std::endl;
    //}

    //setup texture slot 0
    glActiveTexture(GL_TEXTURE0);
    //bind the texture to the current active slot
    glBindTexture(GL_TEXTURE_2D, _splatmapTexture->getId());
    //tell the shader the texture slot for the diffuse texture is slot 0
    glUniform1i(_USplatMapTexture, 0);

    if (_hightMapTexture)
    {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, _hightMapTexture->getId());
        glUniform1i(_uHeightMapTexture, 1);
    }

    if (_splatmapTexture)
    {
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, _splatmapTexture->getId());
        glUniform1i(_uSplatMapTexture, 2);

        if (_diffuseTexture1)
        {
            glActiveTexture(GL_TEXTURE3);
            glBindTexture(GL_TEXTURE_2D, _diffuseTexture1->getId());
            glUniform1i(_uDiffuseTexture1, 3);
        }

        if (_diffuseTexture2)
        {
            glActiveTexture(GL_TEXTURE4);
            glBindTexture(GL_TEXTURE_2D, _diffuseTexture2->getId());
            glUniform1i(_uDiffuseTexture2, 4);
        }
        if (_diffuseTexture3)
        {
            glActiveTexture(GL_TEXTURE5);
            glBindTexture(GL_TEXTURE_2D, _diffuseTexture3->getId());
            glUniform1i(_uDiffuseTexture3, 5);
        }

        if (_diffuseTexture4)
        {
            glActiveTexture(GL_TEXTURE6);
            glBindTexture(GL_TEXTURE_2D, _diffuseTexture4->getId());
            glUniform1i(_uDiffuseTexture4, 6);
        }
    }

    //pass in a precalculate mvp matrix (see texture material for the opposite)
    glm::mat4 mvpMatrix = pProjectionMatrix * pViewMatrix * pModelMatrix;
    glUniformMatrix4fv(_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

    //now inform mesh of where to stream its data
    pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}
