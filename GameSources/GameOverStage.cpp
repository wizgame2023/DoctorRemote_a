/*!
@file GameOverStageStage.cpp
@brief ゲームオーバーステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void GameOverStage::CreateViewLight() {
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
	void GameOverStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();

			AddGameObject<Sprite>(1280, 800, L"GameOver", Vec3());
		}
		catch (...) {
			throw;
		}
	}

	void GameOverStage::OnUpdate() {
		StageChange();
	}
	void GameOverStage::StageChange() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].bConnected) {
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStartStage");
			}
		}
	}

}
//end basecross