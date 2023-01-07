#include <ironengine/ironengine.h>
#include <iostream>

using namespace ironengine;

/// @brief Player, has an attached camera, model and audio listener, inherits from component
struct Player : Component // TODO LISTENER ON PLAYER, SOURCE ON OBJS
{
    /// @brief Default constructor for the player 
    Player() :
        m_angle(0)
    {}

    /// @brief Initial setup for the player, only called once
    void onInit()
    {
        // Attach components to player
        model = getParent()->addComponent<TriangleRenderer>();
        camera = getParent()->addComponent<Camera>();
        transform = getParent()->getTransform();
        //getEntity()->addComponent<AudioListener>();
    } 

    /// @brief Function that updates every tick allowing constant updates
    void onTick()
    {   
        // When UP is pressed move forwards
        if (getCore()->getKeyboard()->GetKey(KeyCode::up))
        {
            transform->changePosition(0.0f, 0.0f, -0.1f);
        }
        // When DOWN is pressed move backwards
        if (getCore()->getKeyboard()->GetKey(KeyCode::down))
        {
            transform->changePosition(0.0f, 0.0f, 0.1f);
        }

        //m_angle += 0.1f;
        //getParent()->getTransform()->setRotation(0, m_angle, 0); //TODO add turning

        // Update the positions of the components attached to the player
        model->getParent()->getTransform()->setPosition(transform->getPosition());
        camera->getParent()->getTransform()->setPosition(transform->getPosition());
    }

    /// @brief Current angle of the player
    float m_angle;
    /// @brief Shared pointer to the player model
    std::shared_ptr<TriangleRenderer> model;
    /// @brief Shared pointer to the player camera
    std::shared_ptr<Camera> camera;
    /// @brief Shared pointer to the players transform component
    std::shared_ptr<Transform> transform;
};

/// @brief Main function of the program and where the program begins
int main(int argc, char* argv[]) // TODO COMMENT
{
    std::shared_ptr<ironengine::Core> core = ironengine::Core::initialize(argv[0]);

    //
    auto e = core->addEntity();
    auto player = e->addComponent<Player>();
    //player->onInit();

    //
    auto e1 = core->addEntity();
    std::shared_ptr<TriangleRenderer> tr = e1->addComponent<TriangleRenderer>();
    tr->setColor(1.0f, 1.0f, 0.0f, 0.5f);
    //tr->setModel(core->getResources()->load<Model>("models/curuthers"));
    //tr->setShader(core->getResources()->load<Shader>("shaders/basic")); TODO ADD THIS TO REPLACE HARD CODED PATHS
    //tr->setTexture(core->getResources()->load<Texture>("../data/box.jpg"));
    e1->getTransform()->setPosition(glm::vec3(0.0f, 0.0f, -5.0f));
  
    //
    auto e2 = core->addEntity();
    e2->addComponent<IrcComponent>();

    //
    std::shared_ptr<SoundSource> ss1 = e2->addComponent<SoundSource>();
    ss1->getParent()->getTransform()->setPosition(glm::vec3(0.0f, 0.0f, -10.0f));
    ss1->setAudio(core->getResources()->load<Audio>("../data/dixie_horn.ogg"));

    core->start();

    return 0;
}

// TODO MULTI CAMERA SPLIT SCREEN?