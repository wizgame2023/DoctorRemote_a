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
			m_stageCount++;
			scene->SetGameStage(m_stageCount);

			//ビューとライトの作成
			CreateViewLight();

			AddGameObject<Sprite>(1280, 800, L"Score", Vec3());
			m_time = App::GetApp()->GetScene<Scene>()->GetTime();
		}
		catch (...) {
			throw;
		}
	}

	void ScoreStage::OnUpdate()
	{
		float delta = App::GetApp()->GetElapsedTime();
		m_countUp += 1*delta;
		StageChange();
		if (m_count == 0)
		{
			if (m_countUp >= 1.0f && m_timeCount == 0)
			{
				AddGameObject<TimeManager>(m_time, Vec3(450, 400, 0));
				m_timeCount++;
			}
			else if (m_countUp >= 2.0f && m_timeCount == 1)
			{
				auto ifClear = AddGameObject<Sprite>(512, 75, L"IfClear", Vec3(-300, 100, 0));
				ifClear->UpdateIfClear(0);
				m_timeCount++;
			}
			else if (m_time >= 25 && m_countUp >= 3.0f && m_timeCount == 2)
			{
				auto ifClear = AddGameObject<Sprite>(512, 75, L"IfClear", Vec3(-300, 10, 0));
				ifClear->UpdateIfClear(1);
				m_timeCount++;
			}
			else if (m_time >= 40 && m_countUp >= 4.0f && m_timeCount == 3)
			{
				auto ifClear = AddGameObject<Sprite>(512, 75, L"IfClear", Vec3(-300, -80, 0));
				ifClear->UpdateIfClear(2);
				m_timeCount++;
			}
			else if (m_time >= 50 && m_countUp >= 5.0f && m_timeCount == 4)
			{
				auto ifClear = AddGameObject<Sprite>(512, 75, L"IfClear", Vec3(-300, -170, 0));
				ifClear->UpdateIfClear(3);
				m_timeCount++;
			}

			else if (m_time >= 50 && m_countUp >= 6.0f && m_timeCount == 5)
			{
				auto rank = AddGameObject<Sprite>(512, 800, L"Rank", Vec3(350, 50, 0));
				rank->UpdateRank(0);
				m_count++;
			}
			else if (m_time >= 40 && m_time < 50 && m_countUp >= 6.0f && m_timeCount == 5)
			{
				auto rank = AddGameObject<Sprite>(512, 800, L"Rank", Vec3(350, 50, 0));
				rank->UpdateRank(1);
				m_count++;
			}
			else if (m_time >= 25 && m_time < 40 && m_countUp >= 6.0f && m_timeCount == 5)
			{
				auto rank = AddGameObject<Sprite>(512, 800, L"Rank", Vec3(350, 50, 0));
				rank->UpdateRank(2);
				m_count++;
			}
			else if (m_time < 25 && m_countUp >= 6.0f && m_timeCount == 5)
			{
				auto rank = AddGameObject<Sprite>(512, 800, L"Rank", Vec3(350, 50, 0));
				rank->UpdateRank(3);
				m_count++;
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
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
			{
				if (m_stageCount < 3) {
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStatusStage");
				}
				else if (m_stageCount >= 3) {
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStartStage");
				}
			}
		}
	}

}