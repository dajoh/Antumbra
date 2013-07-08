#include <string>
#include <fstream>
#include "Shader.hpp"

namespace Antumbra
{
	Shader::Shader(const std::string &vsFile, const std::string &fsFile) : m_geomShader(0)
	{
		m_locationCache.set_empty_key("");

		CompileShader(vsFile, GL_VERTEX_SHADER);
		CompileShader(fsFile, GL_FRAGMENT_SHADER);
		Link();
	}

	Shader::Shader(const std::string &vsFile, const std::string &fsFile, const std::string &gsFile)
	{
		m_locationCache.set_empty_key("");

		CompileShader(vsFile, GL_VERTEX_SHADER);
		CompileShader(fsFile, GL_FRAGMENT_SHADER);
		CompileShader(gsFile, GL_GEOMETRY_SHADER);
		Link();
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_program);
		if(m_geomShader != 0) glDeleteShader(m_geomShader);
		if(m_fragShader != 0) glDeleteShader(m_fragShader);
		if(m_vertShader != 0) glDeleteShader(m_vertShader);
	}

	void Shader::SetUniform(const std::string &name, int value)
	{
		GLint location = LookupLocation(name);
		if(location != -1)
		{
			glUniform1i(location, value);
		}
	}

	void Shader::SetUniform(const std::string &name, int *value, int size)
	{
		GLint location = LookupLocation(name);
		if(location != -1)
		{
			glUniform1iv(location, size, value);
		}
	}

	void Shader::SetUniform(const std::string &name, float value)
	{
		GLint location = LookupLocation(name);
		if(location != -1)
		{
			glUniform1f(location, value);
		}
	}

	void Shader::SetUniform(const std::string &name, float *value, int size)
	{
		GLint location = LookupLocation(name);
		if(location != -1)
		{
			glUniform1fv(location, size, value);
		}
	}

	void Shader::SetUniform(const std::string &name, const glm::vec3 &value)
	{
		GLint location = LookupLocation(name);
		if(location != -1)
		{
			glUniform3fv(location, 1, &value[0]);
		}
	}

	void Shader::SetUniform(const std::string &name, const glm::vec4 &value)
	{
		GLint location = LookupLocation(name);
		if(location != -1)
		{
			glUniform4fv(location, 1, &value[0]);
		}
	}

	void Shader::SetUniform(const std::string &name, const glm::mat3 &value)
	{
		GLint location = LookupLocation(name);
		if(location != -1)
		{
			glUniformMatrix3fv(location, 1, GL_FALSE, &value[0][0]);
		}
	}

	void Shader::SetUniform(const std::string &name, const glm::mat4 &value)
	{
		GLint location = LookupLocation(name);
		if(location != -1)
		{
			glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
		}
	}

	void Shader::Bind()
	{
		glUseProgram(m_program);
	}

	void Shader::Link()
	{
		GLint linkStatus;

		m_program = glCreateProgram();
		glAttachShader(m_program, m_vertShader);
		glAttachShader(m_program, m_fragShader);

		if(m_geomShader != 0)
		{
			glAttachShader(m_program, m_geomShader);
		}

		glLinkProgram(m_program);
		glGetProgramiv(m_program, GL_LINK_STATUS, &linkStatus);

		if(!linkStatus)
		{
			throw std::exception("Couldn't link shader program.");
		}
	}

	void Shader::CompileShader(const std::string &file, GLenum type)
	{
		GLint status;
		std::string source;
		std::ifstream stream(file);

		if(!stream.is_open())
		{
			throw std::exception("Couldn't open shader file.");
		}

		stream.seekg(0, std::ios::end);   
		source.reserve((std::string::size_type)stream.tellg());
		stream.seekg(0, std::ios::beg);
		source.assign((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

		auto sourceStr = source.c_str();
		auto shader = glCreateShader(type);

		glShaderSource(shader, 1, &sourceStr, nullptr);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

		if(!status)
		{
			throw std::exception("Couldn't compile shader.");
		}

		switch(type)
		{
		case GL_VERTEX_SHADER: m_vertShader = shader; break;
		case GL_FRAGMENT_SHADER: m_fragShader = shader; break;
		case GL_GEOMETRY_SHADER: m_geomShader = shader; break;
		}
	}

	GLint Shader::LookupLocation(const std::string &name)
	{
		auto it = m_locationCache.find(name);
		if(it != m_locationCache.end())
		{
			return it->second;
		}

		GLint location = glGetUniformLocation(m_program, name.c_str());
		m_locationCache[name] = location;
		return location;
	}
}