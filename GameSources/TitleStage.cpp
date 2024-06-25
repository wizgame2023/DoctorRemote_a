/*!
@file TitleStage.cpp
@brief タイトルステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void TitleStage::CreateViewLight() {
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
	void TitleStage::OnCreate() {
		try {
			auto& scene = App::GetApp()->GetScene<Scene>();
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



			auto spriteManager = AddGameObject<SelectSprite>();
			SetSharedGameObject(L"SelectSprite", spriteManager);

			auto titleManager = AddGameObject<TitleManager>();

			auto sprite = AddGameObject<Sprite>(512/2, 45/2, L"SelectTutorial", Vec3(0.0f,-100.0f,0.0f));
			auto sprite2 = AddGameObject<Sprite>(512/2, 45/2, L"SelectGameStage", Vec3(0.0f, -175.0f, 0.0f));
			auto sprite3 = AddGameObject<Sprite>(300/2, 45/2, L"SelectGameStage2", Vec3(0.0f, -250.0f, 0.0f));
			//auto sprite4 = AddGameObject<Sprite>(300/2, 45/2, L"SelectGameStage3", Vec3(0.0f, -325.0f, 0.0f));

			auto decisionButton = AddGameObject<Sprite>(150, 75, L"DecisionButton", Vec3(0, -350, 0.0f));
			decisionButton->SetColor(Col4(0.0f, 1.0f, 0.0f, 1.0f));
			SetSharedGameObject(L"decisionButton",decisionButton);
			//AddGameObject<Player>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
			AddGameObject<Sprite>(1280, 800, L"Title", Vec3(0, 0, 0),-3);

		}
		catch (...) {
			throw;
		}
	}
	void TitleStage::OnUpdate()
	{
		auto elapsed = App::GetApp()->GetElapsedTime();
		if (m_blinking > 0) {
			m_blinking -= elapsed;
		}
		else {
			m_blinking = 1.5f;
		}
		auto decButton = GetSharedGameObject<Sprite>(L"decisionButton");
		decButton->SetColor(Col4(0.0f, 1.0f, 0.0f, m_blinking));
	}
	void TitleStage::StageChange() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].bConnected) {
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
			}
		}
	}
}
