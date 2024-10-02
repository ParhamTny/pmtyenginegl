#ifndef _GAME_APP_H_
#define _GAME_APP_H_

#include <iostream>
#include <memory>

#include <pmtyenginegl/pmtyenginegl.h>

namespace game
{

	class App
	{
	public:
		App(const std::string& name);

		void run();
	private:
		std::unique_ptr<pmtyenginegl::Window> m_window;
	};

}

#endif