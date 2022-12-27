#include <ironengine/ironengine.h>
#include <iostream>

using namespace ironengine;

struct Player : Component
{
    Player() :
        m_angle(0)
    {}

    // void onInit()
    //{
    //   getEntity()->addComponent<Camera>();
    //   getEntity()->addComponent<AudioListener>();
    //} TODO LISTENER ON PLAYER, SOURCE ON OBJS
    // TODO ADD KEY PRESSES FOR CAMERA, REMOVE FROM QUAD

    void onTick()
    {
        m_angle += 1.0f;

        getParent()->getTransform()->setRotation(0, m_angle, 0);
    }

    float m_angle;
};

int main(int argc, char* argv[])
{
    std::shared_ptr<ironengine::Core> core = ironengine::Core::initialize(argv[0]);

    //
    auto e = core->addEntity();
    e->addComponent<Player>();

    //
    std::shared_ptr<TriangleRenderer> tr = e->addComponent<TriangleRenderer>();
    tr->setColor(1.0f, 1.0f, 0.0f, 0.5f);
    //tr->setModel(core->getResources()->load<Model>("models/curuthers"));
    //tr->setShader(core->getResources()->load<Shader>("shaders/basic")); TODO ADD THIS TO REPLACE HARD CODED PATHS
    //tr->setTexture(core->getResources()->load<Texture>("../data/box.jpg"));
    e->getTransform()->setPosition(glm::vec3(0.0f, 0.0f, -5.0f));
  
    //
    auto e2 = core->addEntity();
    e2->addComponent<SoundSource>();
    e2->getTransform()->setPosition(glm::vec3(0.0f, 0.0f, -10.0f));
    e2->addComponent<IrcComponent>();

    core->start();

    return 0;
}

//TODO MULTI CAMERA SPLIT SCREEN?