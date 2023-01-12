#include "Core.h"
#include "Entity.h"
#include "Transform.h"
#include "Keyboard.h"
#include "Camera.h"
#include "Resources.h"
#include <stdexcept>
#include <AL/al.h>
#include <AL/alc.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#ifndef __EMSCRIPTEN__
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

namespace ironengine
{
	Core::Core() { }

	Core::~Core()
	{
		// Ensure everything is shut down properly when destroying the core
		SDL_GL_DeleteContext(m_context);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}

	std::shared_ptr<Core> Core::initialize(const char* _projectWorkingDirectory)
	{
		// Create a pointer to the core to avoid self destruction
		std::shared_ptr<Core> rtn = std::make_shared<Core>();
		rtn->m_self = rtn;
		rtn->m_running = false;

		// Start initialization of sdl
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			throw std::runtime_error("Failed to initalize SDL");
		}
		// Attempt to create a window 
		if (!(rtn->m_window = SDL_CreateWindow("SDL2 Platform", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL)))
		{
			SDL_Quit();
			throw std::runtime_error("Failed to create window");
		}
		// Attempt to create the context
		if (!(rtn->m_context = SDL_GL_CreateContext(rtn->m_window)))
		{
			SDL_DestroyWindow(rtn->m_window);
			SDL_Quit();
			throw std::runtime_error("Failed to create OpenGL context");
		}
        
		// Start initialization of al
		ALCdevice* device = alcOpenDevice(NULL);
		// Attempt to find audio device
		if (!device)
		{
			throw std::runtime_error("Failed to open audio device");
		}
		// Attempt to create context
		ALCcontext* context = alcCreateContext(device, NULL);
		if (!context)
		{
			alcCloseDevice(device);
			throw std::runtime_error("Failed to create audio context");
		}
		// Attempt to assign the current context
		if (!alcMakeContextCurrent(context))
		{
			alcDestroyContext(context);
			alcCloseDevice(device);
			throw std::runtime_error("Failed to make context current");
		}
		// Assign the defult position of the audio listener
		alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);

#ifndef __EMSCRIPTEN__
		WSADATA wsadata;
		// Attempt to initialize Winsock
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsadata);
		if (iResult != 0)
		{
			throw std::runtime_error("WSAStartup failed");
		}
#endif

		// Set up links to various other components and entites to establish the basic hierarchy of the core 
		rtn->m_keyboard = std::make_shared<Keyboard>();
		rtn->m_renderer = std::make_shared<rend::Renderer>(640, 480);
		rtn->m_renderer->projection(glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 100.f));
		rtn->m_renderer->backfaceCull(true);
		rtn->m_resources = std::make_shared<Resources>();

		return rtn;
	}

	void Core::_loop(void* _userdata)
	{
		Core* self = (Core*)_userdata;
		self->loop();
	}

	void Core::loop()
	{
		SDL_Event event = { 0 };
		// Update the keyboard and the renderer as often as possible
		m_keyboard->Update();
		m_renderer->clear();

		// Constantly check for any keyboard inputs
		while (SDL_PollEvent(&event))
		{
			// If esc is pressed close the program
			if (event.type == SDL_QUIT)
			{
				m_running = false;
			}

			// If a key is pressed down add it to the array of keys held down
			else if (event.type == SDL_KEYDOWN)
			{
				m_keyboard->m_keys.push_back(event.key.keysym.sym);
				m_keyboard->m_keysDown.push_back(event.key.keysym.sym);
			}
			// If a key is released remove it from the array of keys held down
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

		// Loop through every entity owned by the core and call all of their tick functions 
		for (std::vector<std::shared_ptr<Entity> >::iterator it = m_entities.begin();
			//for (auto it = m_entities.begin();
			it != m_entities.end(); ++it)
		{
			(*it)->tick();
		}

		// Clear the screen
		rend::Renderer r(INITIAL_WIDTH, INITIAL_HEIGHT);
		r.clear();

		// Loop through every entity owned by the core and call all of their display functions 
		for (std::vector<std::shared_ptr<Entity> >::iterator it = m_entities.begin();
			//for (auto it = m_entities.begin();
			it != m_entities.end(); ++it)
		{
			(*it)->display();
		}
		SDL_GL_SwapWindow(m_window);

		// Clear all keyboard arrays to avoid duplicate entries
		m_keyboard->m_keysDown.clear();
		m_keyboard->m_keysUp.clear();
	}

	void Core::start()
	{
		// Start the main loop of the program

		m_running = true;

#ifdef __EMSCRIPTEN__
		emscripten_set_main_loop_arg(_loop, (void*)this, 60, 1);
#else
		while (m_running)
		{
			loop();
		}
#endif

	}

	void Core::stop()
	{
		m_running = false;
	}

	std::shared_ptr<Entity> Core::addEntity()
	{
		// Create a shared pointer to the entity
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();

		// Add the entity to the cores hierarchy
		rtn->m_core = m_self;
		rtn->m_self = rtn;
		rtn->m_transform = rtn->addComponent<Transform>();
		// Add the entity to the vector of entities before returning it
		m_entities.push_back(rtn);
		return rtn;
	}

	std::shared_ptr<Keyboard> Core::getKeyboard()
	{
		return m_keyboard;
	}

	std::shared_ptr<Camera> Core::getCamera()
	{
		return m_camera.lock();
	}

	std::shared_ptr<Resources> Core::getResources()
	{
		return m_resources;
	}
}