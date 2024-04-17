/*!
@file Block.cpp
@brief ブロックのオブジェクトの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Block::Block(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{
	}
	void Block::OnCreate()
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
//end basecross
