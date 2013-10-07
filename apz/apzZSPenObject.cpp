#include "stdafx.h"
#include "apzZSPenObject.h"
#include "apzUtilities.h"
#include "apzZSpaceUtilities.h"

using namespace apz;

void ZSPenObject::update(const zspace::tracker::TrackerSystem *tSystem, zspace::stereo::StereoWindow *tWindow) {
  zspace::tracker::TrackerTarget *primaryTarget = tSystem->getDefaultTrackerTarget(zspace::tracker::TrackerTarget::TYPE_PRIMARY);

  if(primaryTarget) {
    zspace::common::Matrix4 primaryPose = zspace::common::Matrix4::IDENTITY();
	zspace::common::Matrix4 primaryWorldPose = zspace::common::Matrix4::IDENTITY();
    primaryTarget->getPose(primaryPose);

	zsutil::convertPoseToWorldSpace(primaryPose, primaryWorldPose, tWindow);

    GLfloat poseGl[16];
    zspace::common::MathConverterGl::convertMatrix4ToMatrixGl(primaryWorldPose, poseGl);

    m_matrix = glm::make_mat4(poseGl);

    m_active = true;



    // Check if any buttons are pressed
    zspace::tracker::ITrackerButtonCapability* trackerButtonCapability = 
      static_cast<zspace::tracker::ITrackerButtonCapability*>(primaryTarget->getCapability(zspace::tracker::ITrackerCapability::TYPE_BUTTON));

    if (!trackerButtonCapability) {
      CRITICAL_ERROR("Button capability not found");
      return;
    }

    m_topButton = trackerButtonCapability->isButtonPressed(0);
    m_leftButton = trackerButtonCapability->isButtonPressed(1);
    m_rightButton = trackerButtonCapability->isButtonPressed(2);



  }else{
    m_active = false;
  }


}

ZSPenObject::ZSPenObject() : 
  m_active(false) 
  ,m_rightButton(false)
  ,m_leftButton(false)
  ,m_topButton(false) {
}

glm::mat4 ZSPenObject::getMatrix() const {
  return m_matrix;
}

bool ZSPenObject::getRightButton() const {
  return m_rightButton;
}

bool ZSPenObject::getLeftButton() const {
  return m_leftButton;
}

bool ZSPenObject::getTopButton() const {
  return m_topButton;
}

bool ZSPenObject::getPenActive() const {
  return m_active;
}