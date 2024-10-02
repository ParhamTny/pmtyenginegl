#include "pmtyenginegl/elementBuffer.h"

namespace pmtyenginegl
{

	ElementBuffer::ElementBuffer(const std::vector<std::uint32_t>& indices)
		: m_count(static_cast<std::uint32_t>(indices.size()))
	{
		glGenBuffers(1, &m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indices.size(), indices.data(), GL_STATIC_DRAW);
	}

	ElementBuffer::~ElementBuffer()
	{
		glDeleteBuffers(1, &m_EBO);
	}

	void ElementBuffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	}

	void ElementBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}