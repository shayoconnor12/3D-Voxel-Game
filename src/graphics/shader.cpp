#include "shader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "renderer.h"

shader::shader(const std::string& filepath)
	: mFilePath(filepath), mRendererID(0)
{
    ShaderProgramSource source = parseShader(filepath);
    mRendererID = createShader(source.VertexSource, source.FragmentSource);
}

shader::~shader()
{
    glDeleteProgram(mRendererID);
}

ShaderProgramSource shader::parseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];

    ShaderType type = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << "\n";
        }
    }

    return { ss[0].str(), ss[1].str() };

}

unsigned int shader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

unsigned int shader::compileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "FAILED TO COMPILE" << (type == GL_VERTEX_SHADER ? " vertex" : " fragment") << " SHADER!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

void shader::Bind() const
{
    glUseProgram(mRendererID);
}

void shader::unBind() const
{
    glUseProgram(0);
}

void shader::setUniform1i(const std::string& name, int value)
{
    glUniform1i(getUniformLocation(name), value);
}

void shader::setMatrixUniform(const std::string& matrixName, glm::mat4 matrix)
{
    glUniformMatrix4fv(getUniformLocation(matrixName), 1, GL_FALSE, glm::value_ptr(matrix));
}

void shader::setAtlasUniform(const std::string& atlasName, const std::string& offsetName, int atlasDimension, float xOffset, float yOffset)
{
    glUniform1i(getUniformLocation(atlasName), atlasDimension);
    glUniform2f(getUniformLocation(offsetName), xOffset, yOffset);
}

void shader::setUniform1f(const std::string& name, float value)
{
    glUniform1f(getUniformLocation(name), value);
}

void shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}

int shader::getUniformLocation(const std::string& name)
{
    if (mUniformLocationCache.find(name) != mUniformLocationCache.end())
        return mUniformLocationCache[name];

    int location = glGetUniformLocation(mRendererID, name.c_str());
    if (location == -1)
        std::cout << "warning: uniform ' " << name << " ' doesn't exist!" << std::endl;
    
    mUniformLocationCache[name] = location;

    return location;
}
