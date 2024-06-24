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
			auto scene = App::GetApp()->GetScene<Scene>();
			scene->SetPlayFlag(true);

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

	void GameOverStage::OnDestroy()
	{
		auto scene = App::GetApp()->GetScene<Scene>();
		m_count = scene->GetBigPieceCount();
		if (m_count == 1) // 大きい欠片を1個壊している
		{
			scene->SetBigPieceCount(-1);
		}
		if (m_count == 2)// 大きい欠片を2個壊している
		{
			scene->SetBigPieceCount(-2);
		}
		if (m_count == 3)// 大きい欠片を3個壊している
		{
			scene->SetBigPieceCount(-3);
		}
		scene->GetBigPieceCount();
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
				switch (stage)
				{
				case 0:
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTutorialStage");
					break;
				case 1:
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
					break;
				case 2:
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage2");
					break;
				case 3:
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage3");
					break;
				default:
					break;
				}
			}
		}
	}

}
//end basecross