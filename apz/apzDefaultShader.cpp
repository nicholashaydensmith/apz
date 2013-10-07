#include "stdafx.h"
#include "apzDefaultShader.h"

using namespace apz;

DefaultShader::DefaultShader(Data &tVertexData, Data *tFragData) : Shader() {

  mVertexS   = new VertexShader  (tVertexData);
  mFragmentS = new FragmentShader(tFragData);

  AddShaderObject(mVertexS);
  AddShaderObject(mFragmentS);

  Link();


  // Set up attributes
  glGenBuffers(1, mVbo);

}

void DefaultShader::SetBuffers(T_ATTRIBINFO *tVertexInfo, int tSize) {
  glBindBuffer(GL_ARRAY_BUFFER, mVbo[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(T_ATTRIBINFO) * tSize, (char *)tVertexInfo, GL_STATIC_DRAW);
}

void DefaultShader::Begin() {
  Shader::Begin();

  glBindBuffer(GL_ARRAY_BUFFER, mVbo[0]);
  //glEnableVertexAttribArray();
  //glVertexAttribPointer(mAttributes[ATTRIB_VertexPosition],
  //  3, GL_FLOAT, GL_FALSE, 0, NULL);

}