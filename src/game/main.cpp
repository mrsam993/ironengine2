#include <ironengine/ironengine.h>
#include <iostream>

using namespace ironengine;

struct Player : Component
{
    Player() :
        m_angle(0)
    {}

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

    auto e = core->addEntity();
    e->addComponent<Player>();
    e->addComponent<ironengine::TriangleRenderer>()->SetColor(1.0f, 1.0f, 0.0f, 0.5f);
    e->getTransform()->setPosition(glm::vec3(0.0f, 0.0f, -5.0f));
  
    auto e2 = core->addEntity();
    e2->addComponent<SoundSource>();
    e2->getTransform()->setPosition(glm::vec3(0.0f, 0.0f, -10.0f));

    core->start();

    return 0;
}