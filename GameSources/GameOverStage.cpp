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
			//BGM
			BaseBGM();

			auto scene = App::GetApp()->GetScene<Scene>();
			scene->SetPlayFlag(false);

			//ビューとライトの作成
			CreateViewLight();

			AddGameObject<Sprite>(1280, 800, L"GameOver", Vec3());
		}
		catch (...) {
			throw;
		}
	}

	void GameOverStage::BaseBGM()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"GameOverBGM", XAUDIO2_LOOP_INFINITE, 0.2f);
	}

	void GameOverStage::OnUpdate() {
		StageChange();
	}

	void GameOverStage::OnDestroy()
	{
		auto scene = App::GetApp()->GetScene<Scene>();
		m_count = scene->GetBigPieceCount();
		scene->SetBigPieceCount(-m_count);
		scene->GetBigPieceCount();
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	void GameOverStage::StageChange() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto& scene = App::GetApp()->GetScene<Scene>();
		if (cntlVec[0].bConnected)
		{
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
			{
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStartStage");
			}
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
			{
				auto stage = scene->GetGameStage();

				wstring stageString = to_wstring(stage);
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage" + stageString);
			}
		}
	}

}
//end basecross