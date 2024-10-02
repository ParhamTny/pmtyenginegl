#include "pmtyenginegl/shader.h"

#include <glm/gtc/type_ptr.hpp>

#include <stdexcept>
#include <fstream>
#include <sstream>

namespace pmtyenginegl
{

	Shader::Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
	{
		GLuint vertexShader = createShader(vertexPath, GL_VERTEX_SHADER);
		GLuint fragmentShader = createShader(fragmentPath, GL_FRAGMENT_SHADER);

		m_program = glCreateProgram();
		glAttachShader(m_program, vertexShader);
		glAttachShader(m_program, fragmentShader);
		glLinkProgram(m_program);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		int success;
		glGetProgramiv(m_program, GL_LINK_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetProgramInfoLog(m_program, 512, nullptr, infoLog);
			throw std::runtime_error("failed to link the shader program: " + std::string(infoLog));
		}
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_program);
	}

	void Shader::use() const
	{
		glUseProgram(m_program);
	}

	void Shader::setUniform1Int(const std::string& name, int uniform)
	{
		glUniform1i(getUniformLocation(name), uniform);
	}

	void Shader::setUniform1Float(const std::string& name, float uniform)
	{
		glUniform1f(getUniformLocation(name), uniform);
	}

	void Shader::setUniform2Float(const std::string& name, glm::vec2 uniform)
	{
		glUniform2fv(getUniformLocation(name), 1, glm::value_ptr(uniform));
	}

	void Shader::setUniform3Float(const std::string& name, glm::vec3 uniform)
	{
		glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(uniform));
	}

	void Shader::setUniform4Float(const std::string& name, glm::vec4 uniform)
	{
		glUniform4fv(getUniformLocation(name), 1, glm::value_ptr(uniform));
	}

	void Shader::setUniform2x2Float(const std::string& name, glm::mat2 uniform)
	{
		glUniformMatrix2fv(getUniformLocation(name), 1, false, glm::value_ptr(uniform));
	}

	void Shader::setUniform3x3Float(const std::string& name, glm::mat3 uniform)
	{
		glUniformMatrix3fv(getUniformLocation(name), 1, false, glm::value_ptr(uniform));
	}

	void Shader::setUniform4x4Float(const std::string& name, glm::mat4 uniform)
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, false, glm::value_ptr(uniform));
	}

	GLuint Shader::createShader(const std::filesystem::path& path, GLenum type)
	{
		std::ifstream file(path);
		std::ostringstream stream;

		if (!file)
			throw std::runtime_error("failed to load the shader file: " + path.string());

		while (!file.eof())
		{
			std::string line;
			std::getline(file, line);
			stream << line << std::endl;
		}

		std::string source = stream.str();
		const char* string = source.c_str();

		GLuint shader = glCreateShader(type);
		glShaderSource(shader, 1, &string, nullptr);
		glCompileShader(shader);

		int success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			throw std::runtime_error("failed to compile the shader: " + std::string(infoLog));
		}

		return shader;
	}

	int Shader::getUniformLocation(const std::string& name)
	{
		if (m_uniformLocations.find(name) != m_uniformLocations.end())
			return m_uniformLocations[name];

		int location = glGetUniformLocation(m_program, name.c_str());
		if (location == -1)
			throw std::runtime_error("failed to find the uniform: " + name);
		
		m_uniformLocations[name] = location;
		return location;
	}

}