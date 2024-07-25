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
			PieceManager::enemyPieces.clear();
			//BGM
			BaseBGM();
			auto scene = App::GetApp()->GetScene<Scene>();
			//ポイント等リセット
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
			//タイトル
			auto titleMoji = AddGameObject<Sprite>(150, 50, L"ClearTitle", Vec3(400, -350, 0.0f));
			titleMoji->SetColor(Col4(0.0f));
			SetSharedGameObject(L"TitleMoji", titleMoji);
			//Aボタン
			auto aButton = AddGameObject<Sprite>(50, 50, L"GameClearAButton", Vec3(500, -350, 0.0f));
			aButton->SetColor(Col4(0.0f));
			SetSharedGameObject(L"Abutton", aButton);
			//Spaceキー
			auto spaceButton = AddGameObject<Sprite>(150, 50, L"GameClearSpace", Vec3(550, -350, 0.0f));
			spaceButton->SetColor(Col4(0.0f));
			SetSharedGameObject(L"SpaceButton", spaceButton);

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
		auto titleMoji = GetSharedGameObject<Sprite>(L"TitleMoji");
		auto aButton = GetSharedGameObject<Sprite>(L"Abutton");
		auto spaceButton = GetSharedGameObject<Sprite>(L"SpaceButton");

		m_time += elapsed * 0.5;
		//2秒後にタイトルの文字表示
		if (m_time >= 1.0f) {
			titleMoji->SetColor(Col4(1.0f));
			if (cntlVec[0].bConnected) {
				aButton->SetColor(Col4(1.0f));
				spaceButton->SetColor(Col4(0.0f));
			}
			else {
				aButton->SetColor(Col4(0.0f));
				spaceButton->SetColor(Col4(1.0f));
			}
		}
		//メッセージを徐々に表示
		else {
			if (m_time <= 1.0f) {
				messege->SetColor(Col4(1.0f, 1.0f, 1.0f, m_time));
			}
		}
		//2秒後にボタンが押せるように
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
		m_BGM = XAPtr->Start(L"GameClearBGM",0.0f, 0.2f);
	}

	void ClearStage::OnDestroy()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}
}
//end basecross