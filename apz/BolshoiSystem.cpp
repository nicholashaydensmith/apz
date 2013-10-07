#include "stdafx.h"
#include "apzBolshoiSystem.h"

#define BUFFER_OFFSET(i) ((char*)NULL + (i))

using namespace apz;

BolshoiSystem::BolshoiSystem(Data &tData) {
  VERTEX_INFO   *buffer;

  unsigned long minSize;

  tData.copyAndAllocate((char **)&buffer, &minSize);
  minSize = minSize / sizeof(VERTEX_INFO);


  /*
  // COnstruct an actual vertex info
  VERTEX_INFO *vertexInfo;
  vertexInfo = new VERTEX_INFO[minSize];



  for(int i = 0; i < minSize; ++i){
    vertexInfo[i].x = buffer[i].x;
    vertexInfo[i].y = buffer[i].y;
    vertexInfo[i].z = buffer[i].z;
    vertexInfo[i].m = buffer[i].m;
	vertexInfo[i].type = 0;

  }
  */
  

  m_dataSize = minSize;


  initFromMemory(buffer, minSize);

  delete buffer;
}

void BolshoiSystem::Render(MATRIX_RENDER_INFO_T &tMatInfo, Shader &tShaderInfo) {
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

  GLint v0bind = 0; 
  GLint m0bind = 3; 
  GLint t0bind = 4; 

  // 0  v0
  // 1  v0
  // 2  v0
  // 3  v1 <-
  // 4  v1 <-
  // 5  v1 <-

  glEnableVertexAttribArray(v0bind);
  glVertexAttribPointer    (v0bind, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_INFO), 0);

  glEnableVertexAttribArray(m0bind);
  glVertexAttribPointer    (m0bind, 1, GL_FLOAT, GL_FALSE, sizeof(VERTEX_INFO), BUFFER_OFFSET(sizeof(float)*3));

  glEnableVertexAttribArray(t0bind);
  glVertexAttribPointer    (t0bind, 1, GL_INT, GL_FALSE, sizeof(VERTEX_INFO), BUFFER_OFFSET(sizeof(float)*6));


  glDrawArrays(GL_POINTS, 0, m_dataSize);
}

void BolshoiSystem::initFromMemory(VERTEX_INFO *tData, unsigned long tSize) {
  // Send everything to OpenGL
  glGenBuffers(1, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(VERTEX_INFO) * tSize, tData, GL_STATIC_DRAW);
}