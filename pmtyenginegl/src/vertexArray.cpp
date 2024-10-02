#include "pmtyenginegl/vertexArray.h"

namespace pmtyenginegl
{

	VertexLayout::VertexLayout(std::initializer_list<VertexElement> elements)
		: m_elements(elements), m_stride(0)
	{
		for (auto element : elements)
			m_stride += sizeof(float) * element.size;
	}

	void VertexLayout::addElement(VertexElement element)
	{
		m_elements.push_back(element);
		m_stride += sizeof(float) * element.size;
	}

	VertexArray::VertexArray(const VertexBuffer& vertexBuffer, const VertexLayout& vertexLayout, const ElementBuffer& elementBuffer)
	{
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		vertexBuffer.bind();

		std::uint32_t index = 0;
		std::uint32_t offset = 0;

		const auto& elements = vertexLayout.getElements();
		for (auto element : elements)
		{
			glEnableVertexAttribArray(index);

			std::uintptr_t offsetPtr = offset;
			glVertexAttribPointer(index, element.size, GL_FLOAT, element.normalized, vertexLayout.getStride(), reinterpret_cast<const void*>(offsetPtr));

			index++;
			offset += sizeof(float) * element.size;
		}

		elementBuffer.bind();
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_VAO);
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(m_VAO);
	}

	void VertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

}