#include "OpenGLShaderProgram.h"
#include "OpenGLUtils.h" // TODO Remove?
#include <iostream>

using namespace std;
using namespace dawn;

OpenGLShaderProgram::OpenGLShaderProgram() : program(0)
{
}

OpenGLShaderProgram::OpenGLShaderProgram(const std::string &vs, const std::string &fs) : program(OpenGLUtils::CreateShaderProgram(vs, fs))
{
}

OpenGLShaderProgram::OpenGLShaderProgram(GLuint program) : program(program)
{
}

OpenGLShaderProgram::~OpenGLShaderProgram()
{
  if (program)
    glDeleteProgram(program);
}

void OpenGLShaderProgram::Bind()
{
  glUseProgram(program);
}

void OpenGLShaderProgram::uniform(const std::string &name, GLint v0)
{
  GLint loc = GetUniformLocation(name);
  glUniform1i(loc, v0);
}

void OpenGLShaderProgram::uniform(const std::string &name, GLfloat v0)
{
  GLint loc = GetUniformLocation(name);
  glUniform1f(loc, v0);
}

void OpenGLShaderProgram::uniform(const std::string &name, vec2f v)
{
  GLint loc = GetUniformLocation(name);
  glUniform2f(loc, v[0], v[1]);
}

void OpenGLShaderProgram::uniform(const std::string &name, vec3f v)
{
  GLint loc = GetUniformLocation(name);
  glUniform3f(loc, v[0], v[1], v[2]);
}

void OpenGLShaderProgram::uniform(const std::string &name, vec4f v)
{
  GLint loc = GetUniformLocation(name);
  glUniform4f(loc, v[0], v[1], v[2], v[3]);
}

void OpenGLShaderProgram::uniform(const std::string &name, mat3f m)
{
  GLint loc = GetUniformLocation(name);

  GLfloat fv[9];
  for (unsigned int i = 0; i < 9; i++) {
    fv[i] = m(i);
  }

  glUniformMatrix3fv(loc, 1, GL_FALSE, fv);
}

void OpenGLShaderProgram::uniform(const std::string &name, mat4f m)
{
  GLint loc = GetUniformLocation(name);

  GLfloat fv[16];
  for (unsigned int i = 0; i < 16; i++) {
    fv[i] = m(i);
  }

  glUniformMatrix4fv(loc, 1, GL_FALSE, fv);
}

GLint OpenGLShaderProgram::GetUniformLocation(const string &name)
{
  UniformLUTMap::iterator itr = uniformLUT.find(name);

  if (itr == uniformLUT.end())
  {
    std::cout << "Looking up uniform " << name << std::endl;
    GLint loc = glGetUniformLocation(program, name.c_str());
    uniformLUT[name] = loc;
    return loc;
  }

  return itr->second;
}
