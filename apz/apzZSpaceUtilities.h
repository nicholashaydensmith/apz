#pragma once

#include "stdafx.h"


namespace apz {
	namespace zsutil {
		void convertPoseToWorldSpace(const zspace::common::Matrix4& pose, zspace::common::Matrix4& worldPose, zspace::stereo::StereoWindow *tWindow);
	}
}