/*!
@file Block.cpp
@brief ブロックのオブジェクトの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	BlockSecond::BlockSecond(const shared_ptr<Stage>& StagePtr, const Vec3& pos, const Vec3& rot, const Vec3& scale) :
		GameObject(StagePtr), m_pos(pos), m_rot(rot), m_scale(scale)
	{
	}
	void BlockSecond::OnCreate()
	{
		auto ptr = GetComponent<Transform>();
		ptr->SetPosition(m_pos);
		ptr->SetRotation(m_rot);
		ptr->SetScale(m_scale);

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CYLINDER");
		ptrDraw->SetFogEnabled(true);

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);
	}
}
//end namespeca basecross