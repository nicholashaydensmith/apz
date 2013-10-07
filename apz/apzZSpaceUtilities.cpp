#include "stdafx.h"
#include "apzZSpaceUtilities.h"

using namespace apz;

void zsutil::convertPoseToWorldSpace(const zspace::common::Matrix4& pose, zspace::common::Matrix4& worldPose,  zspace::stereo::StereoWindow *tWindow)
{
	GLfloat monoModelViewGl[16];
	zspace::common::Matrix4 cameraLocalToWorld   = zspace::common::Matrix4::IDENTITY();
	zspace::common::Matrix4 trackerToCameraSpace = zspace::common::Matrix4::IDENTITY();
	zspace::common::Vector3 viewportOffset       = zspace::common::Vector3::ZERO();

	// Grab the mono (non-stereoscopic) model-view matrix in OpenGl format.
	glMatrixMode(GL_MODELVIEW);
	glGetFloatv(GL_MODELVIEW_MATRIX, monoModelViewGl);

	// Convert the OpenGl model-view matrix to the zSpace Matrix4 format and
	// invert it to obtain the non-stereo camera's matrix.
	zspace::common::MathConverterGl::convertMatrixGlToMatrix4(monoModelViewGl, cameraLocalToWorld);
	cameraLocalToWorld = cameraLocalToWorld.inverse();

	// Grab the display that the zSpace StereoWindow is currently on in order to 
	// calculate the tracker-to-camera space transform as well as the viewport offset.
	// Both the tracker-to-camera space transform and viewport offset are required
	// for transforming a tracker space pose into the application's world space.
	const zspace::common::DisplayInfo::Display* display = tWindow->getCurrentDisplay();

	if (display)
	{
		trackerToCameraSpace = zspace::common::DisplayInfo::getTrackerToCameraSpaceTransform(display);
		viewportOffset       = zspace::common::DisplayInfo::getViewportOffset(display,
			tWindow->getX(),
			tWindow->getY(),
			tWindow->getWidth(),
			tWindow->getHeight());
	}

	worldPose = cameraLocalToWorld * trackerToCameraSpace * zspace::common::Matrix4::getTrans(-viewportOffset) * pose;
}
