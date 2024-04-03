/*!
@file	MainCamera.h
@brief ƒƒCƒ“ƒJƒƒ‰
’S“–FˆíŒ©
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class MainCamera : public Camera;
	//--------------------------------------------------------------------------------------

	class MainCamera :public Camera {

		float m_angleY;
		float m_distance;
		float m_height;
	public:
		MainCamera() :
			m_angleY(0.0f),
			m_distance(5.0f),
			m_height(3.0f)
		{}
	};
}
//end namespace basecross
