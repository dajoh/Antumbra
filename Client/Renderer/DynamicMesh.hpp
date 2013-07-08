#ifndef RENDERER_DYNAMICMESH_HPP
#define RENDERER_DYNAMICMESH_HPP

#include <vector>
#include "Mesh.hpp"

namespace Antumbra
{
	// Attributes sent to shader:
	// vec3 inColor;
	// vec3 inNormal;
	// vec3 inTexCoord;
	// vec3 inPosition;

	class DynamicMesh
	{
	public:
		DynamicMesh();
		~DynamicMesh();

		void LinkShader(Shader &shader);

		void StartBuilding(GLenum primitive);
		void StopBuilding();

		void Advance();
		void SetColor(const glm::vec3 &color);
		void SetNormal(const glm::vec3 &normal);
		void SetTexCoord(const glm::vec3 &texCoord);
		void SetPosition(const glm::vec3 &position);

		void Draw() const;
	private:
		DynamicMesh(const DynamicMesh &);
		DynamicMesh &operator=(const DynamicMesh &);

		#pragma pack(push, 1)
		struct Vertex
		{
			glm::vec3 color;
			glm::vec3 normal;
			glm::vec3 texCoord;
			glm::vec3 position;
		};
		#pragma pack(pop)

		Mesh m_mesh;
		bool m_building;
		GLint m_vertCount;
		GLenum m_primitive;
		Vertex m_currentVertex;
		std::vector<Vertex> m_vertices;
	};
}

#endif