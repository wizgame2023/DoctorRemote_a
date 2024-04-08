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

		weak_ptr<Transform> m_targetTrans;

		float m_angleY;
		float m_distance;
		float m_height;

	public:
		MainCamera();
		virtual ~MainCamera(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void SetTarget(const shared_ptr <GameObject>& target);

	};
}
//end namespace basecross
