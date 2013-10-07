#pragma once
#include "stdafx.h"
#include "apzRenderObject.h"
#include "apzShader.h"
#include "apzData.h"
#include "apzUtilities.h"

namespace apz {

  class ParticleSystem : public RenderObject {
  public:
    ParticleSystem(Data &tData);

    virtual void Render(MATRIX_RENDER_INFO_T &, Shader &);

  private:

    typedef struct {
      float x, y, z;
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