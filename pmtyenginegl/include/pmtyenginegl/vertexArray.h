#ifndef _PMTYENGINEGL_VERTEXARRAY_H_
#define _PMTYENGINEGL_VERTEXARRAY_H_

#include "pmtyenginegl/vertexBuffer.h"
#include "pmtyenginegl/elementBuffer.h"

namespace pmtyenginegl
{

	struct VertexElement
	{
		int size;
		bool normalized;
	};

	class VertexLayout
	{
	public:
		VertexLayout(std::initializer_list<VertexElement> elements = {});

		void addElement(VertexElement element);
		const std::vector<VertexElement>& getElements() const { return m_elements; }
	
		int getStride() const { return m_stride; }
	private:
		std::vector<VertexElement> m_elements;
		int m_stride;
	};

	class VertexArray
	{
	public:
		VertexArray(const VertexBuffer& vertexBuffer, const VertexLayout& vertexLayout, const ElementBuffer& elementBuffer);
		~VertexArray();

		void bind() const;
		void unbind() const;
	private:
		GLuint m_VAO;
	};

}

#endif