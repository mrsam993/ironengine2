#include <ironengine/ironengine.h>
#include <iostream>

using namespace ironengine;

struct Player : Component
{
    Player() :
        m_angle(0)
    {}

    void onInit()
    {
        model = getParent()->addComponent<TriangleRenderer>();
        camera = getParent()->addComponent<Camera>();
        transform = getParent()->getTransform();

        //getEntity()->addComponent<AudioListener>();
    } 
    // TODO LISTENER ON PLAYER, SOURCE ON OBJS
    // TODO ADD KEY PRESSES FOR CAMERA, REMOVE FROM QUAD

    void onTick()
    {   
        if (getCore()->getKeyboard()->GetKey(KeyCode::up))
        {
            transform->changePosition(0.0f, 0.0f, -0.001f);
        }

        if (getCore()->getKeyboard()->GetKey(KeyCode::down))
        {
            transform->changePosition(0.0f, 0.0f, 0.001f);
        }

        model->getParent()->getTransform()->setPosition(transform->getPosition());
        camera->getParent()->getTransform()->setPosition(transform->getPosition());
    }

    float m_angle;
    std::shared_ptr<TriangleRenderer> model;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Transform> transform;
};

int main(int argc, char* argv[])
{
    std::shared_ptr<ironengine::Core> core = ironengine::Core::initialize(argv[0]);

    //
    auto e = core->addEntity();
    auto player = e->addComponent<Player>();
    player->onInit();

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

    core->start();

    return 0;
}

//TODO MULTI CAMERA SPLIT SCREEN?