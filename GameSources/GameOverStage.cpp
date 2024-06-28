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

			AddGameObject<Sprite>(1280, 800, L"GameOverBackBoard", Vec3(),-3);
			AddGameObject<Comment>(9, 0, 0.3, 1350, 229, 900, 200, 9, 1, Vec3(-450.0f,300.0f,0.0f), L"GameOverRogo");

		}
		catch (...) {
			throw;
		}
	}

	void GameOverStage::OnUpdate() {
		auto elapsed = App::GetApp()->GetElapsedTime();
		auto& scene = App::GetApp()->GetScene<Scene>();
		StageChange();
		if (!m_buttonFlag) {
			m_buttonTime -= elapsed;
			if (m_buttonTime <= 0) {
				AddGameObject<Sprite>(250, 150, L"OverButton", Vec3(0.0f, -100.0f, 0.0f));
				m_buttonFlag = true;
			}
		}
	}

	void GameOverStage::BaseBGM()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"GameOverBGM", XAUDIO2_LOOP_INFINITE, 0.2f);
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
				if (!m_buttonSEFlag) {
					auto choiceSE = App::GetApp()->GetXAudio2Manager();
					choiceSE->Start(L"ChoiceSE", 0, 0.3f);
					m_buttonSEFlag = true;
				}
			}
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
			{
				auto stage = scene->GetGameStage();
				if (stage > 0) {
					wstring stageString = to_wstring(stage);
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage" + stageString);
				}
				else if (stage == 0) {
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTutorialStage");

				}
				
				if (!m_buttonSEFlag) {
					auto choiceSE = App::GetApp()->GetXAudio2Manager();
					choiceSE->Start(L"ChoiceSE", 0, 0.3f);
					m_buttonSEFlag = false;
				}

			}
		}
	}

}
//end basecross