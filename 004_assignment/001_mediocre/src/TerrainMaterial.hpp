#ifndef TERRAINMATERIAL_HPP
#define TERRAINMATERIAL_HPP

#include "mge/materials/AbstractMaterial.hpp"
#include "GL/glew.h"


class ShaderProgram;
class Texture;

class TerrainMaterial : public AbstractMaterial
{
public:
    TerrainMaterial(Texture* pHeightMapTexture, Texture* pSplatmap, Texture* pDiffuseTexture1, Texture* pDiffuseTexture2, Texture* pDiffuseTexture3, Texture* pDiffuseTexture4);
    virtual ~TerrainMaterial();

    virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

    void setDiffuseTexture(Texture* pDiffuseTexture);

protected:
private:
    static ShaderProgram* _shader;
    static void _lazyInitializeShader();

    //in this example we cache all identifiers for uniforms & attributes
    static GLint _uMVPMatrix;
    static GLint _USplatMapTexture;

    static GLint _aVertex;
    static GLint _aNormal;
    static GLint _aUV;

    static GLint _uHeightMapTexture;
    static GLint _uSplatMapTexture;
    static GLint _uDiffuseTexture1;
    static GLint _uDiffuseTexture2;
    static GLint _uDiffuseTexture3;
    static GLint _uDiffuseTexture4;

    Texture* _splatmapTexture;
    Texture* _hightMapTexture;

    Texture* _diffuseTexture1;
    Texture* _diffuseTexture2;
    Texture* _diffuseTexture3;
    Texture* _diffuseTexture4;

    TerrainMaterial(const TerrainMaterial&);
    TerrainMaterial& operator=(const TerrainMaterial&);
};

#endif // TERRAINMATERIAL_HPP

