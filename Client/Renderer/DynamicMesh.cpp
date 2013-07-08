#include "DynamicMesh.hpp"

namespace Antumbra
{
	DynamicMesh::DynamicMesh() :
		m_mesh(GL_UNSIGNED_SHORT,
			3, GL_FLOAT, "inColor",
			3, GL_FLOAT, "inNormal",
			3, GL_FLOAT, "inTexCoord",
			3, GL_FLOAT, "inPosition",
			0),
		m_building(false),
		m_vertCount(0)
	{
	}

	DynamicMesh::~DynamicMesh()
	{
	}

	void DynamicMesh::LinkShader(Shader &shader)
	{
		m_mesh.LinkShader(shader);
	}

	void DynamicMesh::StartBuilding(GLenum primitive)
	{
		if(m_building)
		{
			throw std::exception("Dynamic mesh already being built.");
		}

		m_building = true;
		m_primitive = primitive;
	}

	void DynamicMesh::StopBuilding()
	{
		if(!m_building)
		{
			throw std::exception("Dynamic mesh not being built.");
		}

		m_vertCount = m_vertices.size();
		if(m_vertCount > 0)
		{
			m_mesh.FillVertices(&m_vertices[0], sizeof(Vertex) * m_vertCount, GL_DYNAMIC_DRAW);
			m_vertices.clear();
		}

		m_building = false;
	}

	void DynamicMesh::Advance()
	{
		if(!m_building)
		{
			throw std::exception("Dynamic mesh not being built.");
		}

		m_vertices.push_back(m_currentVertex);
	}

	void DynamicMesh::SetColor(const glm::vec3 &color)
	{
		m_currentVertex.color = color;
	}

	void DynamicMesh::SetNormal(const glm::vec3 &normal)
	{
		m_currentVertex.normal = normal;
	}

	void DynamicMesh::SetTexCoord(const glm::vec3 &texCoord)
	{
		m_currentVertex.texCoord = texCoord;
	}

	void DynamicMesh::SetPosition(const glm::vec3 &position)
	{
		m_currentVertex.position = position;
	}

	void DynamicMesh::Draw() const
	{
		if(m_building)
		{
			throw std::exception("Tried to draw dynamic mesh while being built.");
		}

		m_mesh.DrawVertices(m_primitive, 0, m_vertCount);
	}
}