#pragma once

#include "stdafx.h"
#include "apzShaderObject.h"
#include "apzFragmentShader.h"
#include "apzVertexShader.h"
#include "apzGeometryShader.h"
#include "apzData.h"

namespace apz {

  class Shader {
  public:
    Shader();
    ~Shader();

    GLuint GetProgramObject();

    void SwitchTo();
    void AddShaderObject(ShaderObject *tObj);

    void CreateFragmentShader(Data &tData);
    void CreateVertexShader(Data &tData);
    void CreateGeometryShader(Data &tData);

    void Begin();
    void End();
    void Link();

    // Basic Locations
    GLint m_luProjectionMatrix;
    GLint m_luModelviewMatrix;
    GLint m_luNormalMatrix;
    GLint m_laVertex;
    GLint m_laNormal;
    GLint m_laColor;

    GLint GetLUProjectionMatrix();
    GLint GetLUModelviewMatrix();
    GLint GetLUNormalMatrix();
    GLint GetLAVertex();
    GLint GetLANormal();
    GLint GetLAColor();

    // Set by identifiers
    void SetUniform(GLint tSelection, glm::mat4    &tMatrix);
    void SetUniform(GLint tSelection, glm::mat3    &tMatrix);
    void SetUniform(GLint tSelection, glm::mat2    &tMatrix);
    void SetUniform(GLint tSelection, glm::mat2x3  &tMatrix);
    void SetUniform(GLint tSelection, glm::mat3x2  &tMatrix);
    void SetUniform(GLint tSelection, glm::mat2x4  &tMatrix);
    void SetUniform(GLint tSelection, glm::mat4x2  &tMatrix);
    void SetUniform(GLint tSelection, glm::mat3x4  &tMatrix);
    void SetUniform(GLint tSelection, glm::mat4x3  &tMatrix);
    void SetUniform(GLint tSelection, glm::vec4    &tVec);
    void SetUniform(GLint tSelection, glm::vec3    &tVec);
    void SetUniform(GLint tSelection, glm::vec2    &tVec);
    void SetUniform(GLint tSelection, glm::float_t tFloat);
    void SetUniform(GLint tSelection, glm::int_t   tInt);
    void SetUniform(GLint tSelection, glm::uint_t  tInt);
    void SetUniform(GLint tSelection, void *tData, int tSize);

	GLint GetAttrib(std::string tSelection);

    GLint GetUniform(std::string tSelection);

  protected:
    void SetupLocations();

    std::map<std::string, GLint> mUniforms;
    std::map<std::string, GLint> mIns;

    GLuint mProgramId;
    bool mReady;

    // Uniforms

  private:

  };

};