/*!
@file MainCamera.cpp
@brief ƒƒCƒ“ƒJƒƒ‰ŽÀ‘Ì
’S“–FˆíŒ©
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
		m_height(3.0f)
	{
	}

	void MainCamera::OnCreate() {
	}

	void MainCamera::OnUpdate() {

		auto delta = App::GetApp()->GetElapsedTime();

		auto trans = m_targetTrans.lock()->GetPosition();
		SetEye(trans);
	}

	void MainCamera::SetTarget(const shared_ptr <GameObject>& target)
	{
		m_targetTrans = target->GetComponent<Transform>();

	}
}
//end basecross
