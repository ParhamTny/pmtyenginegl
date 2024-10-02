#ifndef _PMTYENGINEGL_ELEMENTBUFFER_H_
#define _PMTYENGINEGL_ELEMENTBUFFER_H_

#include <glad/gl.h>

#include <vector>

namespace pmtyenginegl
{

	class ElementBuffer
	{
	public:
		ElementBuffer(const std::vector<std::uint32_t>& indices);
		~ElementBuffer();

		void bind() const;
		void unbind() const;
	private:
		GLuint m_EBO;
		std::uint32_t m_count;
	};

}

#endif