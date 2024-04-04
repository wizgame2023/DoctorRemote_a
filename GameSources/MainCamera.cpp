/*!
@file MainCamera.cpp
@brief ƒƒCƒ“ƒJƒƒ‰À‘Ì
’S“–FˆíŒ©
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void MainCamera::SetTarget(const shared_ptr <GameObject>& target)
	{
		m_targetTrans = target->GetComponent<Transform>();
	}

	void MainCamera::OnCreate() {

	}

	void MainCamera::OnUpdate() {

		auto delta = App::GetApp()->GetElapsedTime();


	}
}
//end basecross
