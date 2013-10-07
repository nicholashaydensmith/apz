#pragma once
#include "stdafx.h"
#include "apzRenderObject.h"
#include "apzShader.h"
#include "apzData.h"
#include "apzUtilities.h"

namespace apz {

  class VelocityParticleSystem : public RenderObject {
  public:
    VelocityParticleSystem(Data &tPrevData, Data &tCurData, Data &tNextData);

    virtual void Render(MATRIX_RENDER_INFO_T &, Shader &);

  private:

    typedef struct {
      float x0, y0, z0;
      float x1, y1, z1;
      float x2, y2, z2;
      float m0, m1, m2;
    }VERTEX_INFO;

    typedef struct {
      float x, y, z, m;
    }READ_INFO;

    // VERTEX_INFO *m_data;
    unsigned long m_dataSize;
    GLuint m_vbo;

    void initFromMemory(VERTEX_INFO *tData, unsigned long tSize);
  };

};