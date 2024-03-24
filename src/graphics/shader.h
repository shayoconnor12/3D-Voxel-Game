#pragma once
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class shader
{
private:
	std::string mFilePath;
	unsigned int mRendererID;
	std::unordered_map<std::string, int> mUniformLocationCache;

public:
	shader(const std::string& filepath);
	~shader();

	void Bind() const;
	void unBind() const;

	//set uniforms
	void setMatrixUniform(const std::string& matrixName, glm::mat4 matrix);
	void setAtlasUniform(const std::string& atlasName, const std::string& offsetName, int atlasDimension, float xOffset, float yOffset);
	void setUniform1i(const std::string& name, int value);
	void setUniform1f(const std::string& name, float value);
	void setUniform4f(const std::string& name, float v0, float v1, float f2, float f3);
private:
	ShaderProgramSource parseShader(const std::string& filepath);
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
	int getUniformLocation(const std::string& name);
};