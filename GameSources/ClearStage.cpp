/*!
@file ClearStage.cpp
@brief クリアステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void ClearStage::CreateViewLight() {
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
	void ClearStage::OnCreate() {
		try {
			//BGM
			BaseBGM();

			//ビューとライトの作成
			CreateViewLight();
			auto scene = App::GetApp()->GetScene<Scene>();
			scene->SetPlayFlag(false);


			AddGameObject<Sprite>(1280, 800, L"Back", Vec3());
			AddGameObject<Comment>(10, 0, 0.1, 1350, 229, 900, 200, 10, 1, Vec3(-450.0f, 300.0f, 0.0f), L"GameCleraRogo");
		}
		catch (...) {
			throw;
		}
	}

	void ClearStage::BaseBGM()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"GameClearBGM", XAUDIO2_LOOP_INFINITE, 0.2f);
	}

	void ClearStage::OnUpdate() {
		StageChange();
	}
	void ClearStage::StageChange() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].bConnected) {
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStartStage");
			}
		}
	}

	void ClearStage::OnDestroy()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}
}
//end basecross