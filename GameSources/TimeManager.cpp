/*!
@file TimeManager.cpp
@brief 時間の表示
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	TimeManager::TimeManager(const shared_ptr<Stage>& stagePtr):
		GameObject(stagePtr),
		m_time(100.0f)
	{}

	void TimeManager::OnCreate() {
		auto stage = GetStage();

		float sw = App::GetApp()->GetGameWidth();
		float sh = App::GetApp()->GetGameHeight();
		Vec3 screen(-sw * 0.5, sh * 0.5, 0);
		Vec3 dis(15.0f, -10.0f, 0);
		Vec3 pos = screen + dis;
		Vec3 pos1(pos.x + 40, pos.y, pos.z);
		Vec3 pos2(pos.x + 100, pos.y, pos.z);
		Vec3 pos3(pos.x + 140, pos.y, pos.z);

		m_firstNum = stage->AddGameObject<UITime>(m_first,pos3);
		m_secondNum = stage->AddGameObject<UITime>(m_seconds, pos2);
		m_thirdNum = stage->AddGameObject<UITime>(m_third, pos1);
		m_fourthNum = stage->AddGameObject<UITime>(m_fourth, pos);
	}
	void TimeManager::OnUpdate() {

		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_time -= elapsedTime*10.0f;

		if (m_time <= 0.0f) {
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");

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

		//デバック用
		//wstringstream wss(L"");
		//auto scene = App::GetApp()->GetScene<Scene>();

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

		//auto dstr = scene->GetDebugString();
		//scene->SetDebugString(dstr + wss.str());

	}

	void TimeManager::UpdateNumber() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_time -= elapsedTime;

		if (m_time <= 0.0f) {
			m_time = 100.0f;
		}

		int minutes = m_time / 60;
		int seconds = (int)m_time % 60;
		m_first = seconds % 10;
		m_second = (seconds / 10) % 10;
		m_third = minutes % 10;
		m_fourth = (minutes / 10) % 10;

	}
}
//end namespace basecross