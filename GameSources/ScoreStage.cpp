/*!
@file ClearStage.cpp
@brief スコアステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void ScoreStage::CreateViewLight() {
		auto ptrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto ptrMyCamera = ObjectFactory::Create<Camera>();
		ptrView->SetCamera(ptrMyCamera);
		ptrMyCamera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//マルチライトの作成
		auto ptrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		ptrMultiLight->SetDefaultLighting();
	}
	void ScoreStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();

			AddGameObject<Sprite>(1280, 800, L"Score", Vec3());
			auto rank= AddGameObject<Sprite>(512, 800, L"Rank", Vec3());
			srand(time(0));
			rank->UpdateValue(rand() % 4);
		}
		catch (...) {
			throw;
		}
	}

	void ScoreStage::OnUpdate() {
		StageChange();
	}
	void ScoreStage::StageChange() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].bConnected)
		{
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
			{
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStartStage");
			}
		}
	}

}