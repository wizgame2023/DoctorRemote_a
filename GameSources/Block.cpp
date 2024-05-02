/*!
@file Block.cpp
@brief ブロックのオブジェクトの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Block::Block(const shared_ptr<Stage>& StagePtr, const Vec3& pos, const Vec3& rot) :
		GameObject(StagePtr), m_pos(pos), m_rot(rot)
	{
	}
	void Block::OnCreate()
	{
		auto ptr = GetComponent<Transform>();
		ptr->SetPosition(m_pos);
		ptr->SetRotation(m_rot);
		ptr->SetScale(2.5f, 2.5f, 2.5f);

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"Obstacle_Mesh1");
		ptrDraw->SetFogEnabled(true);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		ptrColl->SetDrawActive(true);//コリジョンを見えるようにする


		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		AddTag(L"Obj");
	}
}

//end basecross
