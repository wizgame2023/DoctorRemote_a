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
		App::GetApp()->GetScene<Scene>()->ResetButton();
		auto elapsed = App::GetApp()->GetElapsedTime();
		auto& scene = App::GetApp()->GetScene<Scene>();
		auto& cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (!m_buttonFlag) {
			m_buttonTime -= elapsed;
			if (m_buttonTime <= 0) {
				AddGameObject<Sprite>(150, 50, L"ReStart", Vec3(-300.0f, -300.0f, 0.0f));//リスタート
				AddGameObject<Sprite>(150, 50, L"ReStart", Vec3(150.0f, -300.0f, 0.0f));//

				if (cntlVec[0].bConnected) {

				}
				else {
					AddGameObject<Sprite>(150, 50, L"GameOverSpace", Vec3(-130, -300, 0.0f));//Space
					AddGameObject<Sprite>(150, 50, L"GameOverBackSpace", Vec3(310, -300, 0.0f));//BackSpace

				}

				if (scene->GetTime() <= 0) {
					//時間切れ
					AddGameObject<Sprite>(500, 100, L"GameOverCommentName1", Vec3());
					AddGameObject<Sprite>(400, 100, L"GameOverComment1", Vec3(0,-150,0));
				}
				else{
					//体力が0
					AddGameObject<Sprite>(500, 100, L"GameOverCommentName2", Vec3());
					AddGameObject<Sprite>(400, 100, L"GameOverComment2", Vec3(0, -150, 0));
				}
				
				m_buttonFlag = true;
			}
		}
		if (m_buttonFlag) {
			StageChange();

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
		scene->SetBigPieceCount(0);
		scene->GetBigPieceCount();
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	void GameOverStage::StageChange() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto keyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto& scene = App::GetApp()->GetScene<Scene>();
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A||keyState.m_bPressedKeyTbl[VK_BACK])
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStartStage");
			if (!m_buttonSEFlag) {
				auto choiceSE = App::GetApp()->GetXAudio2Manager();
				choiceSE->Start(L"ChoiceSE", 0, 0.4f);
				m_buttonSEFlag = true;
			}
		}
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B || keyState.m_bPressedKeyTbl[VK_SPACE])
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
				choiceSE->Start(L"ChoiceSE", 0, 0.4f);
				m_buttonSEFlag = false;
			}

		}
	}

}
//end basecross