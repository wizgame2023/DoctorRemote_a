/*!
@file TitleManager.cpp
@brief タイトルの選択の実体
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	TitleManager::TitleManager(const shared_ptr<Stage>& stagePtr):
		GameObject(stagePtr)
	{}

	void TitleManager::OnCreate() {
		auto trans = GetComponent<Transform>();

		auto deg = -90;
		auto deg2 = -45;
		auto rad = XMConvertToRadians(deg);
		auto rad2 = XMConvertToRadians(deg2);

		trans->SetPosition(Vec3(-2.0f,0.0f,-2.0f));
		trans->SetRotation(Vec3(0.0f, rad, rad2));

		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.5f, 0.5f, 0.5f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		ptrDraw->SetMultiMeshResource(L"Sensuikan_Mesh");
		//ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->AddAnimation(L"Default", 0, 90, true, 30.0f);
		ptrDraw->ChangeCurrentAnimation(L"Default");

		//影をつける
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMultiMeshResource(L"Sensuikan_Mesh");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

	}

	void TitleManager::OnUpdate() {
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		auto drawComp = GetComponent<PNTBoneModelDraw>();
		drawComp->UpdateAnimation(elapsedTime);

	}
}
//end namespace basecross