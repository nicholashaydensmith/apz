#include "stdafx.h"
#include "apzUtilities.h"
#include "apzShader.h"

using namespace apz;



Shader::Shader() {
  mProgramId = glCreateProgram();
  CHECK_GL_ERROR();
}

void Shader::CreateFragmentShader(Data &tData) {
  this->AddShaderObject(new FragmentShader(tData));
}

void Shader::CreateVertexShader(Data &tData) {
  this->AddShaderObject(new VertexShader(tData));
}

void Shader::CreateGeometryShader(Data &tData) {
  this->AddShaderObject(new GeometryShader(tData));
}

GLuint Shader::GetProgramObject() {
  return mProgramId;
}

GLint Shader::GetLUProjectionMatrix() {
  return m_luProjectionMatrix;
}
GLint Shader::GetLUModelviewMatrix() {
  return m_luModelviewMatrix;;
}
GLint Shader::GetLUNormalMatrix() {
  return m_luNormalMatrix;
}
GLint Shader::GetLAVertex() {
  return m_laVertex;
}
GLint Shader::GetLANormal() {
  return m_laNormal;
}
GLint Shader::GetLAColor() {
  return m_laColor;
}

void Shader::Begin() {
  if(!mReady) CRITICAL_ERROR("Shader not yet loaded!");

  glUseProgram(mProgramId);
}

void Shader::End() {

}

void Shader::Link() {
  if(mReady) return;

  glLinkProgram(mProgramId);
  CHECK_GL_ERROR();

  GLint linked = 0;
  glGetProgramiv(mProgramId, GL_LINK_STATUS, &linked);
  if(!linked){
    util::GetGLLinkerLog(mProgramId);
    mReady = false;
    return;
  }else{
    mReady = true;
  }
  glUseProgram(mProgramId);
  // We need to compile a list of all our uniforms and inputs
  SetupLocations();
}


void Shader::AddShaderObject(ShaderObject *tObj) {
  if(mReady) mReady = false;

  glAttachShader(mProgramId, tObj->GetShaderID());
  CHECK_GL_ERROR();
}

void Shader::SetupLocations() {


  m_luProjectionMatrix = glGetUniformLocation(mProgramId, "projectionMatrix");
  m_luModelviewMatrix  = glGetUniformLocation(mProgramId, "modelviewMatrix");
  m_luNormalMatrix     = glGetUniformLocation(mProgramId, "normalMatrix");
  m_laVertex           = glGetAttribLocation (mProgramId, "vertexPosition"); 
  m_laNormal           = glGetAttribLocation (mProgramId, "vertexNormal");
  m_laColor            = glGetAttribLocation (mProgramId, "vertexColor");

  // Compile other uniforms that we might be interested in by name
  int total = -1;
  glGetProgramiv( mProgramId, GL_ACTIVE_UNIFORMS, &total ); 
  for(int i=0; i<total; ++i)  {
    int name_len=-1, num=-1;
    GLenum type = GL_ZERO;
    char name[100];
    glGetActiveUniform( mProgramId, GLuint(i), sizeof(name)-1,
      &name_len, &num, &type, name );
    name[name_len] = 0;
    GLuint location = glGetUniformLocation( mProgramId, name );

    mUniforms[std::string(name)] = location;
  }


  glGetProgramiv( mProgramId, GL_ACTIVE_ATTRIBUTES, &total ); 
  for(int i=0; i<total; ++i)  {
    int name_len=-1, num=-1;
    GLenum type = GL_ZERO;
    char name[100];
    glGetActiveAttrib( mProgramId, GLuint(i), sizeof(name)-1,
      &name_len, &num, &type, name );
    name[name_len] = 0;
    GLuint location = glGetAttribLocation( mProgramId, name );

    mIns[std::string(name)] = location;
  }
}

GLint Shader::GetUniform(std::string tSelection) {
  return mUniforms[tSelection];
}

GLint Shader::GetAttrib(std::string tSelection) {
	return mIns[tSelection];
}

void Shader::SetUniform(GLint tSelection, glm::mat4    &tMatrix) {
  glUniformMatrix4fv(tSelection, 1, GL_FALSE, glm::value_ptr(tMatrix));
}

void Shader::SetUniform(GLint tSelection, glm::mat3    &tMatrix) {
  glUniformMatrix3fv(tSelection, 1, GL_FALSE, glm::value_ptr(tMatrix));
}

void Shader::SetUniform(GLint tSelection, glm::mat2    &tMatrix) {
  glUniformMatrix2fv(tSelection, 1, GL_FALSE, glm::value_ptr(tMatrix));
}

void Shader::SetUniform(GLint tSelection, glm::mat2x3  &tMatrix) {
  glUniformMatrix2x3fv(tSelection, 1, GL_FALSE, glm::value_ptr(tMatrix));
}

void Shader::SetUniform(GLint tSelection, glm::mat3x2  &tMatrix) {
  glUniformMatrix3x2fv(tSelection, 1, GL_FALSE, glm::value_ptr(tMatrix));
}

void Shader::SetUniform(GLint tSelection, glm::mat2x4  &tMatrix) {
  glUniformMatrix2x4fv(tSelection, 1, GL_FALSE, glm::value_ptr(tMatrix));
}

void Shader::SetUniform(GLint tSelection, glm::mat4x2  &tMatrix) {
  glUniformMatrix4x2fv(tSelection, 1, GL_FALSE, glm::value_ptr(tMatrix));
}

void Shader::SetUniform(GLint tSelection, glm::mat3x4  &tMatrix) {
  glUniformMatrix3x4fv(tSelection, 1, GL_FALSE, glm::value_ptr(tMatrix));
}

void Shader::SetUniform(GLint tSelection, glm::mat4x3  &tMatrix) {
  glUniformMatrix4x3fv(tSelection, 1, GL_FALSE, glm::value_ptr(tMatrix));
}

void Shader::SetUniform(GLint tSelection, glm::vec4    &tVec) {
  glUniform1fv(tSelection, 4, glm::value_ptr(tVec));
}

void Shader::SetUniform(GLint tSelection, glm::vec3    &tVec) {
  glUniform1fv(tSelection, 3, glm::value_ptr(tVec));
}

void Shader::SetUniform(GLint tSelection, glm::vec2    &tVec) {
  glUniform1fv(tSelection, 2, glm::value_ptr(tVec));
}

void Shader::SetUniform(GLint tSelection, glm::float_t tFloat) {
  glUniform1f(tSelection, tFloat);
}

void Shader::SetUniform(GLint tSelection, glm::int_t   tInt) {
  glUniform1i(tSelection, tInt);
}

void Shader::SetUniform(GLint tSelection, glm::uint_t  tInt) {
  glUniform1ui(tSelection, tInt);
}

void Shader::SetUniform(GLint tSelection, void *tData, int tSize) {

}
