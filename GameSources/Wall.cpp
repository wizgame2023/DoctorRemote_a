/*!
@file BreakWall.cpp
@brief •Ç
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Wall::Wall(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{
	}
	
	void Wall::OnCreate()
	{
		auto ptr = GetComponent<Transform>();
		ptr->SetPosition(0.0f, 0.5f, 0.0f);
		ptr->SetRotation(0, 0, 0);
		ptr->SetScale(1, 1, 1);

		auto shadowPtr = AddComponent<Shadowmap>();
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);

		auto ptrColl = AddComponent<CollisionSphere>();

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

	}

}
//end namespace basecross