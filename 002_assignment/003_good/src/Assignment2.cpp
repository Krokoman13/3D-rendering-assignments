
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
#include "mge/materials/TextureMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "Assignment2.hpp"
#include "../src/FollowBehaviour.hpp"
#include "../src/CameraFollowBehaviour.hpp"

//construct the game class into _window, _renderer and hud (other parts are initialized by build)
Assignment2::Assignment2() :AbstractGame(), _hud(0)
{
}

void Assignment2::initialize() {
    //setup the core part
    AbstractGame::initialize();

    //setup the custom part so we can display some text
    std::cout << "Initializing HUD" << std::endl;
    _hud = new DebugHud(_window);
    std::cout << "HUD initialized." << std::endl << std::endl;
}

//build the game _world
void Assignment2::_initializeScene()
{
    //MESHES

    //load a bunch of meshes we will be using throughout this demo
    //each mesh only has to be loaded once, but can be used multiple times:
    //F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
    Mesh* planeMeshDefault = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");
    Mesh* diceMesh = Mesh::load("other/models/d20.obj");

    //MATERIALS

    //create some materials to display the cube and the plane
    AbstractMaterial* diceMaterial = new TextureMaterial(Texture::load("other/textures/allFailDice.png"));
    AbstractMaterial* groundMaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "land.jpg"));
    AbstractMaterial* colorMaterial = new ColorMaterial(glm::vec3(0.8,0.8,0.8));

    //SCENE SETUP

   //add camera first (it will be updated last)
    Camera* camera = new Camera("camera", glm::vec3(0, 6, 7));
    camera->rotate(glm::radians(-40.0f), glm::vec3(1, 0, 0));
    _world->add(camera);
    _world->setMainCamera(camera);

    //add the floor
    GameObject* ground = new GameObject("plane", glm::vec3(0, -1, 0));
    ground->scale(glm::vec3(10, 1, 10));
    ground->setMesh(planeMeshDefault);
    ground->setMaterial(groundMaterial);
    _world->add(ground);

    GameObject* plane = new GameObject("plane", glm::vec3(0, 0, 0));
    plane->scale(glm::vec3(2, 1, 1));
    plane->setMesh(planeMeshDefault);
    plane->setMaterial(colorMaterial);
    
    GameObject* dice = new GameObject("dice", glm::vec3(-0.9f, -0.9f, -0.75f));
    dice->scale(glm::vec3(0.5f, 0.5f, 0.5f));
    dice->setMesh(diceMesh);
    dice->setMaterial(diceMaterial);
    
    GameObject* nestedStr = new GameObject("nestedStr");
    nestedStr->add(plane);
    nestedStr->add(dice);
    nestedStr->setBehaviour(new KeysBehaviour(5, 80));
    _world->add(nestedStr);
    camera->setBehaviour(new CameraFollowBehaviour(nestedStr));
}

void Assignment2::_render() {
    AbstractGame::_render();
    _updateHud();
}

void Assignment2::_updateHud() {
    std::string debugInfo = "";
    debugInfo += std::string("FPS:") + std::to_string((int)_fps) + "\n";

    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}

Assignment2::~Assignment2()
{
    //dtor
}


