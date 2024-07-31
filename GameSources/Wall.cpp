/*!
@file BreakWall.cpp
@brief ï«
íSìñÅFëÂâÕå¥
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
		ptr->SetPosition(m_pos + Vec3(0.0f, 1.5f, 0.0f));
		ptr->SetRotation(m_rot);
		ptr->SetScale(m_scale);

		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(1.0f, 11.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f)
		);

		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetTextureResource(L"WallSkin");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		//ptrDraw->SetFogEnabled(true);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		ptrColl->SetDrawActive(false);


		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);
	}

}
//end namespace basecross