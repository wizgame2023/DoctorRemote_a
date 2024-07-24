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
			//BGM
			BaseBGM();
			auto& scene = App::GetApp()->GetScene<Scene>();
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

			auto decisionButton = AddGameObject<Sprite>(250, 125, L"Bbutton2", Vec3(0, -350, 0.0f));
			decisionButton->SetColor(Col4(0.0f, 1.0f, 0.0f, 0.0f));
			SetSharedGameObject(L"decisionButton",decisionButton);
			auto spaceButton = AddGameObject<Sprite>(150, 75, L"SpaceButton", Vec3(0.0f, -350.0f, 0.0f));
			spaceButton->SetColor(Col4(0.0f, 1.0f, 0.0f, 0.0f));
			SetSharedGameObject(L"spaceButton", spaceButton);
			//AddGameObject<Player>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
			AddGameObject<Sprite>(1280, 800, L"Title", Vec3(0, 0, 0),-5);

		}
		catch (...) {
			throw;
		}
	}

	void TitleStage::BaseBGM()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"TitleBGM", XAUDIO2_LOOP_INFINITE, 0.15f);

	}
	    
	void TitleStage::OnDestroy()
	{
		auto scene = App::GetApp()->GetScene<Scene>();
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
		scene->SetBigPieceCount(0);
	}

	void TitleStage::OnUpdate()
	{
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto elapsed = App::GetApp()->GetElapsedTime();
		auto decButton = GetSharedGameObject<Sprite>(L"decisionButton");
		auto spaceButton = GetSharedGameObject<Sprite>(L"spaceButton");

		if (m_blinking > 0) {
			m_blinking -= elapsed;
		}
		else {
			m_blinking = 1.5f;
		}

		if (cntlVec[0].bConnected) {
			decButton->SetColor(Col4(0.0f, 1.0f, 0.0f, m_blinking)); 
			spaceButton->SetColor(Col4(0.0f, 1.0f, 0.0f, 0.0f));
		}
		else {
			decButton->SetColor(Col4(0.0f, 1.0f, 0.0f, 0.0f));
			spaceButton->SetColor(Col4(0.0f, 1.0f, 0.0f, m_blinking));
		}
		//ResetButton();
	}

}
