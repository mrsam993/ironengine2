#include "Core.h"
#include "Entity.h"
#include "Transform.h"
#include "Keyboard.h"
#include "Camera.h"
#include "Resources.h"
#include <stdexcept>
#include <AL/al.h>
#include <AL/alc.h>
#include <winsock2.h>
#include <ws2tcpip.h>

namespace ironengine
{
	Core::Core()
	{
		//m_renderer->blend(true);
		//m_renderer->depthTest(true);
	}

	Core::~Core()
	{
		SDL_GL_DeleteContext(m_context);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}

	std::shared_ptr<Core> Core::initialize(const char* _projectWorkingDirectory)
	{
		std::shared_ptr<Core> rtn = std::make_shared<Core>();

		rtn->m_self = rtn;
		rtn->m_running = false;

		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			throw std::runtime_error("Failed to initalize SDL");
		}

		if (!(rtn->m_window = SDL_CreateWindow("SDL2 Platform",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL)))
		{
			SDL_Quit();
			throw std::runtime_error("Failed to create window");
		}

		if (!(rtn->m_context = SDL_GL_CreateContext(rtn->m_window)))
		{
			SDL_DestroyWindow(rtn->m_window);
			SDL_Quit();
			throw std::runtime_error("Failed to create OpenGL context");
		}

		ALCdevice* device = alcOpenDevice(NULL);

		if (!device)
		{
			throw std::runtime_error("Failed to open audio device");
		}

		ALCcontext* context = alcCreateContext(device, NULL);

		if (!context)
		{
			alcCloseDevice(device);
			throw std::runtime_error("Failed to create audio context");
		}

		if (!alcMakeContextCurrent(context))
		{
			alcDestroyContext(context);
			alcCloseDevice(device);
			throw std::runtime_error("Failed to make context current");
		}

		alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);

		WSADATA wsadata;

		/* Initialize Winsock */
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsadata);
		if (iResult != 0)
		{
			throw std::runtime_error("WSAStartup failed");
		}

		rtn->m_camera = std::make_shared<Camera>();
		rtn->m_keyboard = std::make_shared<Keyboard>();
		rtn->m_renderer = std::make_shared<rend::Renderer>(640, 480);
		rtn->m_renderer->projection(glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 100.f));
		rtn->m_renderer->backfaceCull(true);
		rtn->m_resources = std::make_shared<Resources>();

		return rtn;
	}

	void Core::start()
	{
		SDL_Event event = { 0 };
		m_running = true;

		while (m_running)
		{
			m_keyboard->Update();

			m_renderer->view(glm::inverse(m_camera->m_transform->getModelMatrix()));
			m_renderer->clear();

			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					m_running = false;
				}

				else if (event.type == SDL_KEYDOWN)
				{
					m_keyboard->m_keys.push_back(event.key.keysym.sym);
					m_keyboard->m_keysDown.push_back(event.key.keysym.sym);
				}
				else if (event.type == SDL_KEYUP)
				{
					for (size_t i = 0; i < m_keyboard->m_keys.size(); ++i)
					{
						if (m_keyboard->m_keys.at(i) == event.key.keysym.sym)
						{
							m_keyboard->m_keys.erase(m_keyboard->m_keys.begin() + i);
							i--;
						}
					}
					m_keyboard->m_keysUp.push_back(event.key.keysym.sym);
				}
			}

			for (std::vector<std::shared_ptr<Entity> >::iterator it = m_entities.begin();
				//for (auto it = m_entities.begin();
				it != m_entities.end(); ++it)
			{
				(*it)->tick();
			}

			rend::Renderer r(INITIAL_WIDTH, INITIAL_HEIGHT);
			r.clear();

			for (std::vector<std::shared_ptr<Entity> >::iterator it = m_entities.begin();
				//for (auto it = m_entities.begin();
				it != m_entities.end(); ++it)
			{
				(*it)->display();
			}

			SDL_GL_SwapWindow(m_window);

			m_keyboard->m_keysDown.clear();
			m_keyboard->m_keysUp.clear();
		}
	}

	void Core::stop()
	{
		m_running = false;
	}

	std::shared_ptr<Entity> Core::addEntity()
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();

		rtn->m_core = m_self;
		rtn->m_self = rtn;
		rtn->m_transform = rtn->addComponent<Transform>();
		m_entities.push_back(rtn);

		return rtn;
	}

	std::shared_ptr<Keyboard> Core::getKeyboard()
	{
		return m_keyboard;
	}

	std::shared_ptr<Camera> Core::getCamera()
	{
		return m_camera;
	}

	std::shared_ptr<Resources> Core::getResources()
	{
		return m_resources;
	}
}