#pragma once

#include "stdafx.h"
#include "apzShader.h"
#include "apzFragmentShader.h"
#include "apzVertexShader.h"
#include "apzData.h"

namespace apz {

  /*  Provides the default shader functionality for our program. Also
      gives an example as to how shader inheritance will operate.
  */
  class DefaultShader : public Shader {
  public:

    typedef struct{
      glm::vec3 VertexPosition;
      glm::vec3 VertexNormal;
      glm::vec4 VertexColor;
    }T_ATTRIBINFO;

    // Inherited Overridden Methods
    DefaultShader(Data &tVertexData, Data &tFragData);

    void SetBuffers(T_ATTRIBINFO *tVertexInfo, int tSize);

    virtual void Begin();

  protected:
    FragmentShader *mFragmentS;
    VertexShader *mVertexS;

    GLuint mVbo[2];
  };

};
