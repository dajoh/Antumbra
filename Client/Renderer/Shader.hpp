#ifndef RENDERER_SHADER_HPP
#define RENDERER_SHADER_HPP

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <sparsehash/dense_hash_map>

namespace Antumbra
{
	class Shader
	{
	public:
		Shader(const std::string &vsFile, const std::string &fsFile);
		Shader(const std::string &vsFile, const std::string &fsFile, const std::string &gsFile);
		~Shader();

		void SetUniform(const std::string &name, int value);
		void SetUniform(const std::string &name, int *value, int size);
		void SetUniform(const std::string &name, float value);
		void SetUniform(const std::string &name, float *value, int size);
		void SetUniform(const std::string &name, const glm::vec3 &value);
		void SetUniform(const std::string &name, const glm::vec4 &value);
		void SetUniform(const std::string &name, const glm::mat3 &value);
		void SetUniform(const std::string &name, const glm::mat4 &value);

		void Bind();
	private:
		Shader(const Shader &);
		Shader &operator=(const Shader &);

		void Link();
		void CompileShader(const std::string &file, GLenum type);
		GLint LookupLocation(const std::string &name);

		GLuint m_program;
		GLuint m_vertShader;
		GLuint m_fragShader;
		GLuint m_geomShader;
		google::dense_hash_map<std::string, GLint> m_locationCache;

		friend class Mesh;
	};
}

#endif