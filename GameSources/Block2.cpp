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

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMultiMeshResource(L"Obstacle_Mesh3");
		//ptrDraw->SetTextureResource(L"Obstacle3-1");
		//ptrDraw->SetFogEnabled(true);

		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);


		auto ptrColl = AddComponent<CollisionCapsule>();
		ptrColl->SetFixed(true);
		ptrColl->SetDrawActive(true);//コリジョンを見えるようにする
		ptrDraw->SetMeshToTransformMatrix(spanMat);


		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		AddTag(L"Obj");

	}
}
//end namespeca basecross