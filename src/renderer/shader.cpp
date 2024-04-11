#include "renderer/shader.h"

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    // read the content from the file into several string objects
    // ----------------------------------------------------------
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    // compile, link, report errors and delete shaders after linking
    // -------------------------------------------------------------

    //compile shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // 1. vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    // 2. fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    // shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    // delete the shaders after linking
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() const
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMaterial(float shininess, float reflectivity)
{
    setFloat("material.shininess", shininess);
    setFloat("material.reflectivity", reflectivity);
}

void Shader::setDirLight(DirLight dirLight)
{
    setVec3("dirLight.direction", dirLight.direction);
    setVec3("dirLight.ambient", dirLight.ambient);
    setVec3("dirLight.diffuse", dirLight.diffuse);
    setVec3("dirLight.specular", dirLight.specular);
}

void Shader::setPointLight(PointLight pointLight)
{
    setInt("nmPointLights", pointLight.N);
    for (unsigned int i = 0; i < pointLight.N; i++)
    {
        std::string pointLights = "pointLights[" + std::to_string(i) + "].";
        setVec3(pointLights + "position", pointLight.positions[i]);
        setVec3(pointLights + "ambient", pointLight.ambient);
        setVec3(pointLights + "diffuse", pointLight.diffuse);
        setVec3(pointLights + "specular", pointLight.specular);
        setFloat(pointLights + "constant", pointLight.constant);
        setFloat(pointLights + "linear", pointLight.linear);
        setFloat(pointLights + "quadratic", pointLight.quadratic);
    }
}

void Shader::setSpotLight(SpotLight spotLight)
{
    setVec3("spotLight.position", spotLight.position);
    setVec3("spotLight.direction", spotLight.direction);
    setFloat("spotLight.cutOffInner", glm::cos(glm::radians(spotLight.cutOffInner)));
    setFloat("spotLight.cutOffOuter", glm::cos(glm::radians(spotLight.cutOffOuter)));
    setVec3("spotLight.ambient", spotLight.ambient);
    setVec3("spotLight.diffuse", spotLight.diffuse);
    setVec3("spotLight.specular", spotLight.specular);
    setFloat("spotLight.constant", spotLight.constant);
    setFloat("spotLight.linear", spotLight.linear);
    setFloat("spotLight.quadratic", spotLight.quadratic);
}

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                      << infoLog << "\n"
                      << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                      << infoLog << "\n"
                      << std::endl;
        }
    }
}
