#pragma once
#include <string>
#include <unordered_map>

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
	void setUniform4f(const std::string& name, float v0, float v1, float f2, float f3);
private:
	ShaderProgramSource parseShader(const std::string& filepath);
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int getUniformLocation(const std::string& name);
};