#ifndef RENDERER_MESH_HPP
#define RENDERER_MESH_HPP

#include <list>
#include "Shader.hpp"

namespace Antumbra
{
	class Mesh
	{
	public:
		Mesh(GLenum indexType, ...);
		~Mesh();

		void LinkShader(Shader &shader);

		void FillIndices(const void *data, size_t size, GLenum usage);
		void FillVertices(const void *data, size_t size, GLenum usage);

		void DrawIndices(GLenum primitive, int first, int count) const;
		void DrawVertices(GLenum primitive, int first, int count) const;
	private:
		Mesh(const Mesh &);
		Mesh &operator=(const Mesh &);

		struct Attribute
		{
			int components;
			GLenum component;
			std::string name;
		};

		GLuint m_vao;
		GLenum m_indexType;
		GLuint m_indexBuffer;
		GLuint m_vertexBuffer;
		std::list<Attribute> m_attributes;
	};
}

#endif