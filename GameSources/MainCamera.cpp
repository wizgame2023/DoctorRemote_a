/*!
@file MainCamera.cpp
@brief メインカメラ実体
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class MainCamera : public Camera;
	//--------------------------------------------------------------------------------------

	MainCamera::MainCamera():
		m_angleY(0.0f),
		m_distance(5.0f),
		m_height(10.0f)
	{
	}

	void MainCamera::OnCreate() {
	}

	void MainCamera::OnUpdate() {

		auto delta = App::GetApp()->GetElapsedTime();


		auto targetTrans = m_targetTrans.lock();
		//カメラの注視点の設定
		auto targetPos = targetTrans->GetPosition();
		auto targetRot = targetTrans->GetRotation();
		Vec3 at(targetPos.x, targetPos.y, targetPos.z);
		SetAt(at);


		//カメラの座標点を設定
		Vec3 rot(targetRot.x, 0.0f, targetRot.z);
		auto eye = rot;
		eye.y = m_height;
		SetEye(eye);

	}

	void MainCamera::SetTarget(const shared_ptr <GameObject>& target)
	{
		m_targetTrans = target->GetComponent<Transform>();
		m_stage = target->GetStage();
	}

	void MainCamera::SetAngle() {

	}
}
//end basecross
