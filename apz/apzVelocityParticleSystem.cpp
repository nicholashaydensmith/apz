#include "stdafx.h"
#include "apzVelocityParticleSystem.h"

#define BUFFER_OFFSET(i) ((char*)NULL + (i))

using namespace apz;

VelocityParticleSystem::VelocityParticleSystem(Data &tPrevData, Data &tCurData, Data &tNextData) {
  READ_INFO *bufferPrev;
  READ_INFO *bufferCur;
  READ_INFO *bufferNext;
  unsigned long prevSize, curSize, nextSize, minSize;

  tPrevData.copyAndAllocate((char **)&bufferPrev, &prevSize);
  tCurData.copyAndAllocate((char **)&bufferCur, &curSize);
  tNextData.copyAndAllocate((char **)&bufferNext, &nextSize);
  

  // We only care about the smaller of the three
  minSize = glm::min(prevSize, curSize);
  minSize = glm::min(minSize, nextSize);
  minSize = minSize / sizeof(READ_INFO);


  // COnstruct an actual vertex info
  VERTEX_INFO *vertexInfo;
  vertexInfo = new VERTEX_INFO[minSize];


  for(int i = 0; i < minSize; ++i){
    vertexInfo[i].x0 = bufferPrev[i].x;
    vertexInfo[i].y0 = bufferPrev[i].y;
    vertexInfo[i].z0 = bufferPrev[i].z;
    vertexInfo[i].m0 = bufferPrev[i].m;

    vertexInfo[i].x1 = bufferCur[i].x;
    vertexInfo[i].y1 = bufferCur[i].y;
    vertexInfo[i].z1 = bufferCur[i].z;
    vertexInfo[i].m1 = bufferCur[i].m;

    vertexInfo[i].x2 = bufferNext[i].x;
    vertexInfo[i].y2 = bufferNext[i].y;
    vertexInfo[i].z2 = bufferNext[i].z;
    vertexInfo[i].m2 = bufferNext[i].m;
  }



  m_dataSize = minSize;

  delete bufferPrev;
  delete bufferCur;
  delete bufferNext;

  initFromMemory(vertexInfo, minSize);

  delete vertexInfo;
}

void VelocityParticleSystem::Render(MATRIX_RENDER_INFO_T &tMatInfo, Shader &tShaderInfo) {
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

  GLint v0bind = 4;
  GLint v1bind = 0;
  GLint v2bind = 6;
  GLint m0bind = 5;
  GLint m1bind = 3;
  GLint m2bind = 7;

  // 0  v0
  // 1  v0
  // 2  v0
  // 3  v1 <-
  // 4  v1
  // 5  v1
  // 6  v2 <-
  // 7  v2
  // 8  v2
  // 9  m0 <-
  // 10 m1 <-
  // 11 m2 <-


  glEnableVertexAttribArray(v0bind);
  glVertexAttribPointer    (v0bind, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_INFO), 0);

  glEnableVertexAttribArray(v1bind);
  glVertexAttribPointer    (v1bind, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_INFO), BUFFER_OFFSET(sizeof(float)*3));

  glEnableVertexAttribArray(v2bind);
  glVertexAttribPointer    (v2bind, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_INFO), BUFFER_OFFSET(sizeof(float)*6));

  glEnableVertexAttribArray(m0bind);
  glVertexAttribPointer    (m0bind, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_INFO), BUFFER_OFFSET(sizeof(float)*9));

  glEnableVertexAttribArray(m1bind);
  glVertexAttribPointer    (m1bind, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_INFO), BUFFER_OFFSET(sizeof(float)*10));

  glEnableVertexAttribArray(m2bind);
  glVertexAttribPointer    (m2bind, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_INFO), BUFFER_OFFSET(sizeof(float)*11));


  glDrawArrays(GL_POINTS, 0, m_dataSize);
}

void VelocityParticleSystem::initFromMemory(VERTEX_INFO *tData, unsigned long tSize) {
  // Send everything to OpenGL
  glGenBuffers(1, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(VERTEX_INFO) * tSize, tData, GL_STATIC_DRAW);
}