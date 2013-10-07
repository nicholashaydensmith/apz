#pragma once

#include "stdafx.h"
#include "apzStructs.h"
#include "apzUtilities.h"


namespace apz {

  // Immutable type that lets us pass raw data from multiple potential sources
  class ZSPenObject {
  public:
    ZSPenObject();

    glm::mat4 getMatrix() const;
    bool getRightButton() const;
    bool getLeftButton() const;
    bool getTopButton() const;
    bool getPenActive() const;
    void update(const zspace::tracker::TrackerSystem *, zspace::stereo::StereoWindow *);

  private:
    glm::mat4 m_matrix;
    bool m_active;
    bool m_rightButton;
    bool m_leftButton;
    bool m_topButton;
  };
};