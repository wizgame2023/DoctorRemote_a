/*!
@file Character.cpp
@brief “G‚È‚ÇŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Enemy::Enemy(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{
	}
	void Enemy::OnCreate()
	{
		auto ptr = GetComponent<Transform>();
		ptr->SetPosition(0, 0, 0);
		ptr->SetRotation(0, 0, 0);
		ptr->SetScale(1, 1, 1);

		AddTag(L"Enemy");

		auto shadowPtr = AddComponent<Shadowmap>();
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);

	}

}
//end basecross
