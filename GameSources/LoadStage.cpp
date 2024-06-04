/*!
@file ClearStage.cpp
@brief クリアステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void LoadStage::CreateViewLight() {
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
	void LoadStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();


			AddGameObject<Sprite>(1280, 800, L"LoadScene", Vec3(0, 0, 0), -1);

			//auto moji1 = AddGameObject<Comment>(4, 0, 0.2f, 512, 128, 220, 60, 4, 1,
			//	Vec3(340.0f, 200.0f, 0.0f), L"LoadMoji");
			//auto moji2 = AddGameObject<CommentManager>(13, 0, 0.2f, 400, 128, 250, 80, 8, 2,
			//	Vec3(-555.0f, -50.0f, 0.0f), L"LoadMoji1");
		}
		catch (...) {
			throw;
		}
	}
	void LoadStage::OnUpdate() {
		StageChange();

		float delta = App::GetApp()->GetElapsedTime();
		m_countUp += 1 * delta;
		StageChange();


		if (m_count == 0)
		{
			if (m_countUp >= 1.0f && m_timeCount == 0)
			{
				//AddGameObject<TimeManager>(m_time, Vec3(450, 400, 0));
				auto moji1 = AddGameObject<Comment>(4, 0, 0.2f, 512, 128, 220, 60, 4, 1,
					Vec3(340.0f, 200.0f, 0.0f), L"LoadMoji");
				m_timeCount++;
			}


			else if (m_countUp >= 2.0f && m_timeCount == 1)
			{
				//auto ifClear = AddGameObject<Sprite>(512, 75, L"IfClear", Vec3(-300, 100, 0));
				//ifClear->UpdateIfClear(0);
				auto moji2 = AddGameObject<CommentManager>(13, 0, 0.2f, 400, 128, 250, 80, 8, 2,
					Vec3(-555.0f, -50.0f, 0.0f), L"LoadMoji1");
				m_timeCount++;
			}
			m_moveCount = -400;

		}
		wstringstream wss(L"");
		auto scene = App::GetApp()->GetScene<Scene>();
		wss << m_countUp << endl;

		scene->SetDebugString(wss.str());

	}
	void LoadStage::StageChange() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].bConnected) {
			if (m_countUp >= 4.0f && cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
			}
		}
	}

}