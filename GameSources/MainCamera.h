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

	class MainCamera :public Camera{

		weak_ptr<Transform> m_targetTrans;

		shared_ptr<Stage> m_stage;

		float m_angleY;
		float m_distance;
		float m_height;
		float m_camDis;

		bool m_MoveFlag;
		Vec3 m_playerAngle;

	public:
		MainCamera(float angleY);
		MainCamera();
		virtual ~MainCamera(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void SetTarget(const shared_ptr <GameObject>& target);
		void SetAngle();
		void SetMove(bool MoveOn);

	};
}
//end namespace basecross
