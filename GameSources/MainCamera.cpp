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

	void MainCamera::OnCreate() {
	}

	void MainCamera::OnUpdate() {

		auto delta = App::GetApp()->GetElapsedTime();

		
	}

	void MainCamera::SetTarget(const shared_ptr <GameObject>& target)
	{
		m_targetTrans = target->GetComponent<Transform>();
	}
}
//end basecross
