#include <cstdarg>
#include "Mesh.hpp"

namespace Antumbra
{
	static size_t ComponentSize(GLenum component);

	Mesh::Mesh(GLenum indexType, ...) : m_indexType(indexType)
	{
		va_list args;
		Attribute attrib;

		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_indexBuffer);
		glGenBuffers(1, &m_vertexBuffer);

		va_start(args, indexType);

		while(true)
		{
			attrib.components = va_arg(args, int);
			if(attrib.components == 0)
			{
				break;
			}

			attrib.component = va_arg(args, GLenum);
			attrib.name = va_arg(args, const char *);
			m_attributes.push_back(attrib);
		}

		va_end(args);
	}

	Mesh::~Mesh()
	{
		glDeleteBuffers(1, &m_vertexBuffer);
		glDeleteBuffers(1, &m_indexBuffer);
		glDeleteVertexArrays(1, &m_vao);
	}

	void Mesh::LinkShader(Shader &shader)
	{
		size_t pointer = 0;
		size_t vertexSize = 0;

		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

		for(auto it = m_attributes.begin(); it != m_attributes.end(); ++it)
		{
			vertexSize += ComponentSize(it->component) * it->components;
		}

		for(auto it = m_attributes.begin(); it != m_attributes.end(); ++it)
		{
			GLint location = glGetAttribLocation(shader.m_program, it->name.c_str());
			if(location != -1)
			{
				glVertexAttribPointer(location, it->components, it->component, GL_FALSE, vertexSize, (GLvoid *)pointer);
				glEnableVertexAttribArray(location);
			}

			pointer += ComponentSize(it->component) * it->components;
		}
	}

	void Mesh::FillIndices(const void *data, size_t size, GLenum usage)
	{
		glBindVertexArray(m_vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
	}

	void Mesh::FillVertices(const void *data, size_t size, GLenum usage)
	{
		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	}

	void Mesh::DrawIndices(GLenum primitive, int first, int count) const
	{
		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
		glDrawRangeElements(primitive, first, (first + count - 1), count, m_indexType, nullptr);
	}

	void Mesh::DrawVertices(GLenum primitive, int first, int count) const
	{
		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		glDrawArrays(primitive, first, count);
	}

	size_t ComponentSize(GLenum component)
	{
		switch(component)
		{
		case GL_BYTE:
		case GL_UNSIGNED_BYTE:
			return 1;
		case GL_SHORT:
		case GL_HALF_FLOAT:
		case GL_UNSIGNED_SHORT:
			return 2;
		case GL_INT:
		case GL_FLOAT:
		case GL_FIXED:
		case GL_UNSIGNED_INT:
			return 4;
		case GL_DOUBLE:
			return 8;
		default:
			throw std::exception("Unsupported vertex buffer format.");
		}
	}
}