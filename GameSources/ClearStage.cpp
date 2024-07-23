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
			auto scene = App::GetApp()->GetScene<Scene>();
			scene->SetAchievementPoint(0);
			scene->SetDashStatus(0);
			scene->SetBulletLengthStatus(0);
			scene->SetBigPieceUpStatus(0);
			scene->SetChainRargeStatus(0);
			scene->SetBulletPowerStatus(0);
			scene->SetBulletTimeStatus(0);

			//ビューとライトの作成
			CreateViewLight();
			scene->SetPlayFlag(false);


			AddGameObject<Sprite>(1280, 800, L"Back", Vec3(),-3);
			AddGameObject<Comment>(10, 0, 0.1, 1350, 229, 900, 200, 10, 1, Vec3(-450.0f, 300.0f, 0.0f), L"GameCleraRogo");
			auto messege = AddGameObject<Sprite>(500, 200, L"Thank", Vec3(0.0f,-100.0f,0.0f));
			messege->SetColor(Col4(1.0f,1.0f,1.0f,0.0f));
			SetSharedGameObject(L"Messege", messege);
			auto button = AddGameObject<Sprite>(200, 75, L"ClearButton", Vec3(450, -350, 0.0f));
			button->SetColor(Col4(0.0f));
			SetSharedGameObject(L"Button", button);

		}
		catch (...) {
			throw;
		}
	}

	void ClearStage::OnUpdate() {
		App::GetApp()->GetScene<Scene>()->ResetButton();
		auto elapsed = App::GetApp()->GetElapsedTime();
		auto& cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto messege = GetSharedGameObject<Sprite>(L"Messege");
		auto button = GetSharedGameObject<Sprite>(L"Button");
		m_time += elapsed * 0.5;
		if (m_time >= 1.0f) {
			//m_time = 1.0f;
			button->SetColor(Col4(1.0f));
		}
		else {
			messege->SetColor(Col4(1.0f, 1.0f, 1.0f, m_time));
		}
		if (m_time >= 1.0) {
			StageChange();

		}
	}
	void ClearStage::StageChange() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto keyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || keyState.m_bPressedKeyTbl[VK_SPACE]) {
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStartStage");
			if (!m_buttonSEFlag) {
				auto choiceSE = App::GetApp()->GetXAudio2Manager();
				choiceSE->Start(L"ChoiceSE", 0, 0.4f);
				m_buttonSEFlag = true;
			}
		}
	}

	void ClearStage::BaseBGM()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"GameClearBGM", XAUDIO2_LOOP_INFINITE, 0.2f);
	}

	void ClearStage::OnDestroy()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}
}
//end basecross