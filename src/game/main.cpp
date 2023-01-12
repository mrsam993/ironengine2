#include <ironengine/ironengine.h>
#include <iostream>

using namespace ironengine;

/// @brief Player, has an attached camera, model and audio listener, inherits from component
struct Player : Component
{
    /// @brief Initial setup for the player, only called once
    void onInit()
    {
        // Attach components to player
        camera = getParent()->addComponent<Camera>(45.0f, 0.1f, 100.0f);
        listener = getParent()->addComponent<SoundListener>();
        transform = getParent()->getTransform();
        boxCollider = getParent()->addComponent<BoxCollider>(glm::vec3(0.1f), glm::vec3(0.0f), false);
        transform->setPosition(0.0f, 2.0f, 0.0f);
    } 

    /// @brief Function that updates every tick allowing constant updates
    void onTick()
    {   
        // When UP is pressed move forwards
        if (getCore()->getKeyboard()->GetKey(KeyCode::up))
        {
            transform->changePosition(0.0f, 0.0f, -0.01f);
        }
        // When DOWN is pressed move backwards
        if (getCore()->getKeyboard()->GetKey(KeyCode::down))
        {
            transform->changePosition(0.0f, 0.0f, 0.01f);
        }
        // When LEFT is pressed turn left
        if (getCore()->getKeyboard()->GetKey(KeyCode::left))
        {
            transform->changeRotation(0.0f, 0.1f, 0.0f);
        }
        // When Right is pressed turn right
        if (getCore()->getKeyboard()->GetKey(KeyCode::right))
        {
            transform->changeRotation(0.0f, -0.1f, 0.0f);
        }
    }

    /// @brief Shared pointer to the player model
    std::shared_ptr<ModelRenderer> model;
    /// @brief Shared pointer to the player camera
    std::shared_ptr<Camera> camera;
    /// @brief Listener for audio in the scene
    std::shared_ptr<SoundListener> listener;
    /// @brief Shared pointer to the players box collider
    std::shared_ptr<BoxCollider> boxCollider;
    /// @brief Shared pointer to the players transform component
    std::shared_ptr<Transform> transform;
};

/// @brief Main function of the program and where the program begins
int main(int argc, char* argv[])
{
    auto core = ironengine::Core::initialize(argv[0]);

    // First entity that hold the player
    auto e1 = core->addEntity();
    auto player = e1->addComponent<Player>();
    auto rigidbody = e1->addComponent<RigidBody>();

    //// Second entity that holds our basic triangle (EXAMPLE OF ADDING A TRIANGLE)
    //auto e2 = core->addEntity();
    //std::shared_ptr<TriangleRenderer> tr = e2->addComponent<TriangleRenderer>();
    //tr->setColor(1.0f, 1.0f, 0.0f, 0.5f);
    //tr->setShader(core->getResources()->load<Shader>("../data/shaders/basic"));
    //e2->getTransform()->setPosition(glm::vec3(0.0f, 0.0f, -15.0f));

    //// Second entity that holds our basic cat model (EXAMPLE OF ADDING A DIFFERENT MODEL)
    //auto e2 = core->addEntity();
    //auto mr = e2->addComponent<ModelRenderer>();
    //mr->setShader(core->getResources()->load<Shader>("../data/shaders/basic"));
    //mr->setModel(core->getResources()->load<Model>("../data/curuthers/curuthers"));
    //mr->setTexture(core->getResources()->load<Texture>("../data/curuthers/Whiskers_diffuse"));
    //e2->getTransform()->setPosition(glm::vec3(0.0f, 0.0f, -15.0f));
    //auto bc = e2->addComponent<BoxCollider>(glm::vec3(3.0f, 5.5f, 1.1f), glm::vec3(0.0f, 0.75f, 0.0f), true);
    //auto ss1 = e2->addComponent<SoundSource>(1.0f, 1.0f, true);
    //ss1->setAudio(core->getResources()->load<Audio>("../data/audio/dixie_horn"));

     // Second entity that holds our enviroment model 
    auto e2 = core->addEntity();
    auto mr = e2->addComponent<ModelRenderer>();
    mr->setShader(core->getResources()->load<Shader>("../data/shaders/basic"));
    mr->setModel(core->getResources()->load<Model>("../data/export/export"));
    mr->setTexture(core->getResources()->load<Texture>("../data/export/exporttex"));
    e2->getTransform()->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    // Wall colliders
    auto wall1Collider = e2->addComponent<BoxCollider>(glm::vec3(100.0f, 10.0f, 4.0f), glm::vec3(0.0f, 0.0f, -24.0f), true);
    auto wall2Collider = e2->addComponent<BoxCollider>(glm::vec3(100.0f, 10.0f, 4.0f), glm::vec3(0.0f, 0.0f, 20.0f), true);
    auto wall3Collider = e2->addComponent<BoxCollider>(glm::vec3(4.0f, 10.0f, 100.0f), glm::vec3(22.0f, 0.0f, 0.0f), true);
    auto wall4Collider = e2->addComponent<BoxCollider>(glm::vec3(4.0f, 10.0f, 100.0f), glm::vec3(-18.0f, 0.0f, 0.0f), true);
    auto wall5Collider = e2->addComponent<BoxCollider>(glm::vec3(40.0f, 10.0f, 11.0f), glm::vec3(30.0f, 0.0f, -1.0f), true);
    // Pole colliders
    auto pole1Collider = e2->addComponent<BoxCollider>(glm::vec3(1.0f, 10.0f, 1.0f), glm::vec3(-12.5f, 0.0f, -16.5f), true);
    auto pole2Collider = e2->addComponent<BoxCollider>(glm::vec3(1.0f, 10.0f, 1.0f), glm::vec3(-1.5f, 0.0f, -16.5f), true);
    auto pole3Collider = e2->addComponent<BoxCollider>(glm::vec3(1.0f, 10.0f, 1.0f), glm::vec3(10.25f, 0.0f, -16.5f), true);
    auto pole4Collider = e2->addComponent<BoxCollider>(glm::vec3(1.0f, 10.0f, 1.0f), glm::vec3(9.75f, 0.0f, -10.5f), true);
    auto pole5Collider = e2->addComponent<BoxCollider>(glm::vec3(1.0f, 10.0f, 1.0f), glm::vec3(-12.5f, 0.0f, 15.0f), true);
    auto pole6Collider = e2->addComponent<BoxCollider>(glm::vec3(1.0f, 10.0f, 1.0f), glm::vec3(-1.75f, 0.0f, 15.0f), true);
    auto pole7Collider = e2->addComponent<BoxCollider>(glm::vec3(1.0f, 10.0f, 1.0f), glm::vec3(10.25f, 0.0f, 15.0f), true);
    auto pole8Collider = e2->addComponent<BoxCollider>(glm::vec3(1.0f, 10.0f, 1.0f), glm::vec3(9.75f, 0.0f, 7.5f), true);
    // Object colliders
    auto tableCollider = e2->addComponent<BoxCollider>(glm::vec3(14.0f, 10.0f, 4.0f), glm::vec3(20.0f, 0.0f, 6.0f), true);
  
    // Third entity that holds our irc component and audio
    auto e3 = core->addEntity();
    e3->getTransform()->setPosition(glm::vec3(-15.0f, 0.0f, 0.0f));

#ifndef __EMSCRIPTEN__
    e3->addComponent<IrcComponent>();
#endif

    auto ss1 = e3->addComponent<SoundSource>(2.0f, 1.0f, true);
    ss1->setAudio(core->getResources()->load<Audio>("../data/audio/darkness"));

    // Start the program
    core->start();

    return 0;
}