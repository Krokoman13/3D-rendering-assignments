#include <iostream>
#include <string>

#include "glm.hpp"

#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/GameObject.hpp"

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "TerrainMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "CameraFollowBehaviour.hpp"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "Assignment4.hpp"

#include "mge/materials/TextureMaterial.hpp"

//construct the game class into _window, _renderer and hud (other parts are initialized by build)
Assignment4::Assignment4() :AbstractGame(), _hud(0)
{
}

void Assignment4::initialize() {
    //setup the core part
    AbstractGame::initialize();

    //setup the custom part so we can display some text
    std::cout << "Initializing HUD" << std::endl;
    _hud = new DebugHud(_window);
    std::cout << "HUD initialized." << std::endl << std::endl;
}

//build the game _world
void Assignment4::_initializeScene()
{
    //MESHES

    //load a bunch of meshes we will be using throughout this demo
    //each mesh only has to be loaded once, but can be used multiple times:
    //F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
    Mesh* planeMesh = Mesh::load(config::MGE_MODEL_PATH + "plane_8192.obj");

    //MATERIALS

    //create some materials to display the cube, the plane and the light
    AbstractMaterial* landMaterial = new TerrainMaterial(
        Texture::load(config::MGE_TEXTURE_PATH + "terrain/heightmap.png"),
        Texture::load(config::MGE_TEXTURE_PATH + "terrain/splatmap.png"),
        Texture::load(config::MGE_TEXTURE_PATH + "terrain/diffuse1.jpg"),
        Texture::load(config::MGE_TEXTURE_PATH + "terrain/diffuse2.jpg"),
        Texture::load(config::MGE_TEXTURE_PATH + "terrain/diffuse3.jpg"),
        Texture::load(config::MGE_TEXTURE_PATH + "terrain/diffuse4.jpg")
    );
    //SCENE SETUP
    // 
    //add the floor
    GameObject* plane = new GameObject("plane", glm::vec3(0, 0, 0));
    plane->scale(glm::vec3(5, 5, 5));
    plane->setMesh(planeMesh);
    plane->setMaterial(landMaterial);
    _world->add(plane);

    //add camera first (it will be updated last)
    Camera* camera = new Camera("camera", glm::vec3(0, 6, 7));
    camera->rotate(glm::radians(-40.0f), glm::vec3(1, 0, 0));
    _world->add(camera);
    _world->setMainCamera(camera);
    camera->setBehaviour(new CameraFollowBehaviour(plane));

}

void Assignment4::_render() {
    AbstractGame::_render();
    _updateHud();
}

void Assignment4::_updateHud() {
    std::string debugInfo = "";
    debugInfo += std::string("FPS:") + std::to_string((int)_fps) + "\n";

    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}

Assignment4::~Assignment4()
{
    //dtor
}
