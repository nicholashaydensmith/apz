#include "stdafx.h"
#include "apzParticleSystem.h"


using namespace apz;


ParticleSystem::ParticleSystem(Data &tData) {


  READ_INFO *buffer;
  unsigned long size;

  tData.copyAndAllocate((char **)&buffer, &size);
  size = size / sizeof(READ_INFO);


  // COnstruct an actual vertex info
  VERTEX_INFO *vertexInfo;
  vertexInfo = new VERTEX_INFO[size];
  //float maximumValue = 0;


  for(int i = 0; i < size; ++i){
    vertexInfo[i].x = buffer[i].x;
    vertexInfo[i].y = buffer[i].y;
    vertexInfo[i].z = buffer[i].z;
  }


  m_dataSize = size;

  delete buffer;
  initFromMemory(vertexInfo, size);

  delete vertexInfo;
}



void ParticleSystem::Render(MATRIX_RENDER_INFO_T &tMatrixInfo, Shader &tShaderInfo) {
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

  glEnableVertexAttribArray(tShaderInfo.GetLAVertex());
  glVertexAttribPointer    (tShaderInfo.GetLAVertex(), 3, GL_FLOAT, GL_FALSE, 0, NULL);

  glDrawArrays(GL_POINTS, 0, m_dataSize);
}



void ParticleSystem::initFromMemory(VERTEX_INFO *tData, unsigned long tSize) {
  // Send everything to OpenGL
  glGenBuffers(1, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(VERTEX_INFO) * tSize, tData, GL_STATIC_DRAW);
}