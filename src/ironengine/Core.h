#include "Entity.h"
#include "Component.h"
#include "Resources.h"
#include <memory>
#include <list>
#include <vector>
#include <SDL2/SDL.h>
#include <rend/rend.h>

#define INITIAL_WIDTH 640
#define INITIAL_HEIGHT 480

namespace ironengine
{
	// Forward declarations
	struct Entity;
	struct Component;
	class Keyboard;
	class Camera;

	/// @brief Core struct, controls the program
	struct Core
	{
		// Friend declarations
		friend class Camera;

	private:
		/// @brief Pointer to self, preventing self destruction
		std::weak_ptr<Core> m_self;
		/// @brief Controls the running of the program
		bool m_running;
		/// @brief List of entities held by the core
		std::vector<std::shared_ptr<Entity> > m_entities;
		/// @brief Keyboard for the program
		std::shared_ptr<Keyboard> m_keyboard;
		/// @brief Camera for the program
		std::weak_ptr<Camera> m_camera;
		/// @brief Renderer for the program
		std::shared_ptr<rend::Renderer> m_renderer;
		/// @brief Resources for the program
		std::shared_ptr<Resources> m_resources;

		/// @brief Window for the program
		SDL_Window* m_window;
		/// @brief Context for the window
		SDL_GLContext m_context;

	public:
		/// @brief Basic constructor for core
		Core();
		/// @brief Basic deconstructor for core
		~Core();

		/// @brief Initialises certain things like SDL and AL
		/// @param _projectWorkingDirectory
		/// @return Shared pointer to the core
		static std::shared_ptr<Core> initialize(const char* _projectWorkingDirectory);

		/// @brief Starts and manages the program
		void start();
		/// @brief Ends the program
		void stop();

		/// @brief Allows creation of entites from the core
		/// @return Shared pointer to the entity
		std::shared_ptr<Entity> addEntity();

		/// @brief Get the engine keyboard object
		/// @return Shared pointer to the keyboard object.
		std::shared_ptr<Keyboard> getKeyboard();

		/// @brief Get the engine camera object
		/// @return Shared pointer to the camera object.
		std::shared_ptr<Camera> getCamera();

		/// @brief Get the engine resources object
		/// @return Shared pointer to the resources object.
		std::shared_ptr<Resources> getResources();

		/// @brief 
		/// @param _out
		template <typename T>
		void find(std::vector<std::shared_ptr<T> >& _out)
		{
			// Go through each Entity in Core
			for (size_t ei = 0; ei < m_entities.size(); ++ei)
			{
				std::shared_ptr<Entity> e = m_entities.at(ei);
				// Go through each Component in Entity
				for (size_t ci = 0; ci < e->m_components.size(); ++ci)
				{
					std::shared_ptr<Component> c = e->m_components.at(ci);
					// Try to dynamic cast the Component to a T
					std::shared_ptr<T> t = std::dynamic_pointer_cast<T>(c);
					// If succeeds then add it to the output array
					if (t)
					{
						_out.push_back(t);
					}
				}
			}
		}
	};
}