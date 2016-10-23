#ifndef __FB_RENDERVIEW_H__
#define __FB_RENDERVIEW_H__

#include "common.h"

namespace fb
{
	class RenderView
	{
	public:
	  unsigned int m_dirtyFlags;
	  int m_type;
	  bool m_rightHanded;
	  float m_fovMultiplier;
	  float m_fovY;
	  float m_fovX;
	  float m_defaultFov;
	  float m_nearPlane;
	  float m_farPlane;
	  float m_aspect;
	  float m_orthoWidth;
	  float m_orthoHeight;
	  float m_lodDistanceScale;
	  float m_minScreenAreaScale;
	  float m_overgrowthLodDistanceScale;
	  float m_viewportOffset[2];
	  float m_viewportScale[2];
	  char _pad[4];
	  LinearTransform m_transform;
	  Frustum m_frustum;
	  float m_fovConst;
	  float m_fovConstDefault;
	  float m_fovScale;
	  float m_fovScaleSqr;
	  char _pad2[12]; 
	  Mat4 m_viewMatrix;
	  Mat4 m_viewMatrixTranspose;
	  Mat4 m_viewMatrixInverse;
	  Mat4 m_projectionMatrix;
	  Mat4 m_projectionMatrixTranspose;
	  Mat4 m_projectionMatrixInverse;
	  Mat4 m_viewProjectionMatrix;
	  Mat4 m_viewProjectionMatrixTranspose;
	  Mat4 m_viewProjectionMatrixInverse;
	};
}
#endif