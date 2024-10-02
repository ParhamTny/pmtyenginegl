#ifndef _PMTYENGINEGL_SHADER_H_
#define _PMTYENGINEGL_SHADER_H_

#include <glad/gl.h>
#include <glm/glm.hpp>

#include <string>
#include <filesystem>
#include <unordered_map>

namespace pmtyenginegl
{

	class Shader
	{
	public:
		Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
		~Shader();

		void use() const;

		void setUniform1Int(const std::string& name, int uniform);
		void setUniform1Float(const std::string& name, float uniform);
		
		void setUniform2Float(const std::string& name, glm::vec2 uniform);
		void setUniform3Float(const std::string& name, glm::vec3 uniform);
		void setUniform4Float(const std::string& name, glm::vec4 uniform);
	
		void setUniform2x2Float(const std::string& name, glm::mat2 uniform);
		void setUniform3x3Float(const std::string& name, glm::mat3 uniform);
		void setUniform4x4Float(const std::string& name, glm::mat4 uniform);
	private:
		GLuint createShader(const std::filesystem::path& path, GLenum type);
		int getUniformLocation(const std::string& name);
	private:
		GLuint m_program;
		std::unordered_map<std::string, int> m_uniformLocations;
	};
	
}

#endif