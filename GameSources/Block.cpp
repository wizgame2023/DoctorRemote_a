/*!
@file Block.cpp
@brief ブロックのオブジェクトの実装
担当：大河原
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
		ptr->SetScale(6.0f, 6.0f, 6.0f);//初期が2.5f,2.5f,2.5f
		

		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.4f, 0.55f, 0.4f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f)
		);


		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"Obstacle_Mesh1");
		ptrDraw->SetTextureResource(L"WallSkin2");

		//ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshToTransformMatrix(spanMat);


		auto ptrColl = AddComponent<CollisionCapsule>();
		ptrColl->SetFixed(true);	
		ptrColl->SetSleepActive(true);//ぶつからない限りスリープ状態になる

		ptrColl->SetDrawActive(false);//コリジョンを見えるようにする


		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		AddTag(L"Obj");
	}
}

//end basecross
