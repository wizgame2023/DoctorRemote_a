/*!
@file ClearStage.cpp
@brief スコアステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void ScoreStage::CreateViewLight() {
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
	void ScoreStage::OnCreate() {
		try {
			//何回クリアしたか
			auto& scene = App::GetApp()->GetScene<Scene>();
			m_stageCount = scene->GetGameStage();
			scene->SetGameStage(m_stageCount);


			//auto moji1 = AddGameObject<CommentManager>(3, 0, 0.2f, 512, 216, 512, 216, 7, 3,
			//	Vec3(-500.0f, 0.0f, 0.0f), L"IfClear");


			//auto rank = AddGameObject<Sprite>(500, 500, L"Rank", Vec3(300, 0, 0));
			//rank->UpdateRank(0);

			//ビューとライトの作成
			CreateViewLight();

			AddGameObject<Sprite>(1280, 800, L"Score", Vec3(), -1);
			m_time = App::GetApp()->GetScene<Scene>()->GetTime();
		}
		catch (...) {
			throw;
		}
	}

	void ScoreStage::OnUpdate()
	{
		float delta = App::GetApp()->GetElapsedTime();
		m_countUp += 1 * delta;
		StageChange();


		if (m_count == 0)
		{
			if (m_countUp >= 1.0f && m_timeCount == 0)
			{
				//AddGameObject<TimeManager>(m_time, Vec3(450, 400, 0));
				auto moji = AddGameObject<Comment>(4, 0, 0.2f, 400, 90, 400, 90, 4, 1,
					Vec3(-550.0f, 350.0f, 0.0f), L"ResultMoji1");
				m_timeCount++;
			}

			
			else if (m_time >= 50 && m_countUp >= 2.0f && m_timeCount == 1)
			{
				//auto ifClear = AddGameObject<Sprite>(512, 75, L"IfClear", Vec3(-300, 100, 0));
				//ifClear->UpdateIfClear(0);
				auto moji1 = AddGameObject<Comment>(7, 0, 0.2f, 512, 256, 512, 256, 7, 4, // 50秒残して生還
					Vec3(-500.0f, 0.0f, 0.0f), L"IfClear");
				m_timeCount++;
			}
			else if (m_time >= 40 && m_time < 50 && m_countUp >= 2.0f && m_timeCount == 1)
			{
				//auto ifClear = AddGameObject<Sprite>(512, 75, L"IfClear", Vec3(-300, 100, 0));
				//ifClear->UpdateIfClear(0);
				auto moji1 = AddGameObject<Comment>(7, 1, 0.2f, 512, 256, 512, 256, 7, 4, // 40秒残して生還
					Vec3(-500.0f, 70.0f, 0.0f), L"IfClear");
				m_timeCount++;
			}
			else if (m_time >= 25 && m_time < 40 && m_countUp >= 2.0f && m_timeCount == 1)//m_time >= 40 && m_time < 50 &&
			{
				//auto ifClear = AddGameObject<Sprite>(512, 75, L"IfClear", Vec3(-300, 10, 0));
				//ifClear->UpdateIfClear(1);
				auto moji2 = AddGameObject<Comment>(7, 2, 0.2f, 512, 256, 512, 256, 7, 4, // 25秒残して生還
					Vec3(-500.0f, 130.0f, 0.0f), L"IfClear");
				m_timeCount++;
			}


			else if (m_time <= 25 && m_countUp >= 2.0f && m_timeCount == 1)//m_time >= 25 && m_time < 40 &&
			{
				//auto ifClear = AddGameObject<Sprite>(512, 75, L"IfClear", Vec3(-300, -80, 0));
				//ifClear->UpdateIfClear(2);
				auto moji3 = AddGameObject<Comment>(2, 3, 0.2f, 512, 256, 512, 256, 7, 4, // 生還
					Vec3(-500.0f, 200.0f, 0.0f), L"IfClear");
				m_timeCount++;
			}


			//Rank
			else if (m_time >= 50 && m_countUp >= 4.0f && m_timeCount == 2)
			{
				auto rank = AddGameObject<Sprite>(400, 400, L"Rank", Vec3(270, 0, 0)); // S
				rank->UpdateRank(0);
				m_timeCount++;
			}
			else if (m_time >= 40 && m_time < 50 && m_countUp >= 4.0f && m_timeCount == 2)
			{
				auto rank = AddGameObject<Sprite>(400, 400, L"Rank", Vec3(350, 0, 0)); // A
				rank->UpdateRank(1);
				m_timeCount++;
			}
			else if (m_time >= 25 && m_time < 40 && m_countUp >= 4.0f && m_timeCount == 2)
			{
				auto rank = AddGameObject<Sprite>(400, 400, L"Rank", Vec3(350, 0, 0)); // B
				rank->UpdateRank(2);
				m_timeCount++;
			}
			else if (m_time <= 25 && m_countUp >= 4.0f && m_timeCount == 2)
			{
				auto rank = AddGameObject<Sprite>(400, 400, L"Rank", Vec3(350, 0, 0)); // C
				rank->UpdateRank(3);
				m_timeCount++;
			}


			else if (m_countUp >= 5.0f && m_timeCount == 3)
			{
				auto moji3 = AddGameObject<Comment>(7, 0, 0.2f, 256, 64, 256, 64, 7, 1, // Bボタンで次へ
					Vec3(-550.0f, -300.0f, 0.0f), L"ResultMoji2");
				m_timeCount++;
			}

				m_moveCount = -400;

		}
		//wstringstream wss(L"");
		//auto scene = App::GetApp()->GetScene<Scene>();
		//wss << m_countUp << endl;

		//scene->SetDebugString( wss.str());
	}
	void ScoreStage::StageChange() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].bConnected)
		{
			if (m_countUp >= 6.0f && cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
			{
				switch (m_stageCount)
				{
				case 0:
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStartStage");
					break;
				case 1:
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStatusStage");
					break;
				case 2:
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStartStage");
					break;
				case 3:
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStartStage");
					break;
				default:
					break;
				}
			}
		}
	}

}