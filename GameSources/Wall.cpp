/*!
@file BreakWall.cpp
@brief •Ç
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Wall::Wall(const shared_ptr<Stage>& StagePtr, const Vec3& pos, const Vec3& rot, const Vec3& scale) :
		GameObject(StagePtr),m_pos(pos),m_rot(rot),m_scale(scale)
	{
	}

	void Wall::OnCreate()
	{
		auto ptr = GetComponent<Transform>();
		ptr->SetPosition(m_pos);
		ptr->SetRotation(m_rot);
		ptr->SetScale(m_scale);

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetTextureResource(L"WallSkin");
		ptrDraw->SetFogEnabled(true);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		//ptrColl->SetDrawActive(true);//ƒRƒŠƒWƒ‡ƒ“‚ðŒ©‚¦‚é‚æ‚¤‚É‚·‚é


		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);
	}
}
//end namespace basecross