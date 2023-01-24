#include "glm.hpp"

#include "TextureMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/config.hpp"

ShaderProgram* TextureMaterial::_shader = NULL;

GLint TextureMaterial::_uMVPMatrix = 0;
GLint TextureMaterial::_uDiffuseTexture = 0;
//GLint TextureMaterial::_uMVMatrix = 0;
GLint TextureMaterial::_uMMatrix = 0;
GLint TextureMaterial::_uIntpLightPos = 0;
GLint TextureMaterial::_uAmbientLightColor = 0;
GLint TextureMaterial::_uPointLightColor = 0;
GLint TextureMaterial::_uCameraPos = 0;

GLint TextureMaterial::_aVertex = 0;
GLint TextureMaterial::_aNormal = 0;
GLint TextureMaterial::_aUV = 0;

TextureMaterial::TextureMaterial(Texture * pDiffuseTexture):_diffuseTexture(pDiffuseTexture) {
    _lazyInitializeShader();
}

TextureMaterial::~TextureMaterial() {}

void TextureMaterial::_lazyInitializeShader() {
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "texture_pointlight.vert");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "texture_pointlight.frag");
        _shader->finalize();

        //cache all the uniform and attribute indexes
        _uMVPMatrix = _shader->getUniformLocation("mvpMatrix");
        _uMMatrix = _shader->getUniformLocation("modelMatrix");
        //_uMVMatrix = _shader->getUniformLocation("modelMatrix");
        _uDiffuseTexture = _shader->getUniformLocation("diffuseTexture");
        _uIntpLightPos = _shader->getUniformLocation("intpLightPos");
        _uAmbientLightColor = _shader->getUniformLocation("ambientLightColor");
        _uPointLightColor = _shader->getUniformLocation("pointLightColor");
        _uCameraPos = _shader->getUniformLocation("cameraPos");

        _aVertex = _shader->getAttribLocation("vertex");
        _aNormal = _shader->getAttribLocation("normal");
        _aUV = _shader->getAttribLocation("uv");
    }
}

void TextureMaterial::setDiffuseTexture (Texture* pDiffuseTexture) {
    _diffuseTexture = pDiffuseTexture;
}

void TextureMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
    if (!_diffuseTexture) return;
    _shader->use();

    //setup texture slot 0
    glActiveTexture(GL_TEXTURE0);
    //bind the texture to the current active sl415+845ot
    glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
    //tell the shader the texture slot for the diffuse texture is slot 0
    glUniform1i (_uDiffuseTexture, 0);

    //pass in a precalculate mvp matrix (see texture material for the opposite)
    glm::mat4 mvMatrix = pViewMatrix * pModelMatrix;
    glm::mat4 mvpMatrix = pProjectionMatrix * mvMatrix;
    glUniformMatrix4fv(_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
    //glUniformMatrix4fv(_uMVMatrix, 1, GL_FALSE, glm::value_ptr(mvMatrix));
    glUniformMatrix4fv(_uMMatrix, 1, GL_FALSE, glm::value_ptr(pModelMatrix));

    //Light information
    if (effectedByLight)
    {
        glUniform3fv(_uAmbientLightColor, 1, glm::value_ptr(pWorld->ambientLightColor));    

        if (pWorld->getLightCount() > 0)
        {
            glUniform3fv(_uCameraPos, 1, glm::value_ptr(pWorld->getMainCamera()->getWorldPosition()));
            //std::cout << pWorld->getMainCamera()->getWorldPosition() << '\n';

            Light* light = pWorld->getLightAt(0);
            glUniform3fv(_uPointLightColor, 1, glm::value_ptr(light->lightColor));

            glm::vec3 intpLightPos = light->getWorldPosition();
            glUniform3fv(_uIntpLightPos, 1, glm::value_ptr(intpLightPos));
        }
    }
    else
    {
        glUniform3fv(_uAmbientLightColor, 1, glm::value_ptr(glm::vec3(1, 1, 1)));
    }

    //now inform mesh of where to stream its data
    pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}
