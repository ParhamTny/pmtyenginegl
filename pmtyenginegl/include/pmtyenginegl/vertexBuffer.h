#ifndef _PMTYENGINEGL_VERTEXBUFFER_H_
#define _PMTYENGINEGL_VERTEXBUFFER_H_

#include <glad/gl.h>

#include <vector>

namespace pmtyenginegl
{

	class VertexBuffer
	{
	public:
		VertexBuffer(const std::vector<float>& vertices);
		~VertexBuffer();

		void bind() const;
		void unbind() const;
	private:
		GLuint m_VBO;
	};

}

#endif