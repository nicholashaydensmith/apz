#pragma once
#include "stdafx.h"
#include "apzRenderObject.h"
#include "apzShader.h"
#include "apzData.h"
#include "apzUtilities.h"

namespace apz {

  class BolshoiSystem : public RenderObject {
  public:
    BolshoiSystem(Data &tData);

    virtual void Render(MATRIX_RENDER_INFO_T &, Shader &);

  private:

    typedef struct {
      float x, y, z, m;
	  int type;
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