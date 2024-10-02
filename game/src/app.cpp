#include "game/app.h"

namespace game
{

	App::App(const std::string& name)
	{
		m_window = std::make_unique<pmtyenginegl::Window>(std::make_pair(1600, 900), std::make_pair(200, 100), name, false);
	}

	void App::run()
	{
		std::vector<float> vertices = {
			 0.5f,  0.5f,
			 0.5f, -0.5f,
			-0.5f, -0.5f,
			-0.5f,  0.5f
		};
		
		std::vector<std::uint32_t> indices = { 0, 1, 2, 0, 2, 3 };

		pmtyenginegl::VertexBuffer vertexBuffer(vertices);
		pmtyenginegl::ElementBuffer elementBuffer(indices);
		
		pmtyenginegl::VertexLayout vertexLayout = { { 2, false } };
		pmtyenginegl::VertexArray vertexArray(vertexBuffer, vertexLayout, elementBuffer);

		pmtyenginegl::Shader shader("shaders/basic.vert", "shaders/basic.frag");

		while (!m_window->isClosing())
		{
			glClearColor(0.5f, 0.2f, 0.6f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			shader.use();
			vertexArray.bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

			m_window->swapBuffers();
		}
	}

}