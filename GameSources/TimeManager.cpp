/*!
@file TimeManager.cpp
@brief 時間の表示
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	TimeManager::TimeManager(const shared_ptr<Stage>& stagePtr):
		GameObject(stagePtr),
		m_time(150.0f),
		m_move(true),
		m_pos(-90.0f,350.0f,0.0f)
	{}
	TimeManager::TimeManager(const shared_ptr<Stage>& stagePtr,int time,Vec3 pos) :
		GameObject(stagePtr),
		m_time(time),
		m_move(false),
		m_pos(pos)
	{}


	void TimeManager::OnCreate() {
		auto stage = GetStage();

		float sw = App::GetApp()->GetGameWidth();
		float sh = App::GetApp()->GetGameHeight();
		//Vec3 screen(-105.0f, sh * 0.5, 0.0f);
		//Vec3 dis(15.0f, -10.0f, 0);
		//Vec3 pos = screen + dis;
		Vec3 pos1(m_pos.x + 40, m_pos.y, m_pos.z);
		Vec3 posTen(m_pos.x + 70, m_pos.y, m_pos.z);
		Vec3 pos2(m_pos.x + 100, m_pos.y, m_pos.z);
		Vec3 pos3(m_pos.x + 140, m_pos.y, m_pos.z);

		m_firstNum = stage->AddGameObject<UITime>(m_first,pos3);
		m_secondNum = stage->AddGameObject<UITime>(m_seconds, pos2);
		m_thirdNum = stage->AddGameObject<UITime>(m_third, pos1);
		m_fourthNum = stage->AddGameObject<UITime>(m_fourth, m_pos);
		m_ten = stage->AddGameObject<UITime>(m_fourth, posTen);

	}
	void TimeManager::OnUpdate() {

		float elapsedTime = App::GetApp()->GetElapsedTime();
		bool start = GetStage()->GetSharedGameObject<StageManager>(L"StageManager")->StartFlag();
		if (m_move) {
			if (start) {
				m_time -= elapsedTime;
				if (m_time <= 0.0f) {
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");
				}
			}
		}


		int minutes = m_time / 60;
		int seconds = (int)m_time % 60;
		m_first = seconds % 10;
		m_second = (seconds / 10) % 10;
		m_third = minutes % 10;
		m_fourth = (minutes / 10) % 10;


		m_firstNum->UpdateValue(m_first);
		m_secondNum->UpdateValue(m_second);
		m_thirdNum->UpdateValue(m_third);
		m_fourthNum->UpdateValue(m_fourth);
		m_ten->UpdateValue(10);

		App::GetApp()->GetScene<Scene>()->SetTime(m_time);

		//デバック用
		wstringstream wss(L"");
		auto scene = App::GetApp()->GetScene<Scene>();

		//wss <<L"time : "
		//	<<m_time
		//	<<"\n"
		//	<< L"minutes : "
		//	<< minutes
		//	<< "\n"
		//	<< L"second : "
		//	<< seconds
		//	<<"\n"
		//	<<"Time : "
		//	<<m_fourth
		//	<<m_third
		//	<<L":"
		//	<<m_second
		//	<<m_first
		//	<< endl;


		wss << m_time << endl;

		auto dstr = scene->GetDebugString();
		scene->SetDebugString(dstr + wss.str());

	}

	void TimeManager::UpdateNumber() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_time -= elapsedTime;

		int minutes = m_time / 60;
		int seconds = (int)m_time % 60;
		m_first = seconds % 10;
		m_second = (seconds / 10) % 10;
		m_third = minutes % 10;
		m_fourth = (minutes / 10) % 10;

	}

	void TimeManager::SetTimeFlag(bool timeFlag) {
		m_move = timeFlag;
	}
}
//end namespace basecross