/*!
@file TimeManager.cpp
@brief ŽžŠÔ‚Ì•\Ž¦
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
		Vec3 f(50, 0, 0);
		m_firstNum = stage->AddGameObject<UITime>(m_first,f);
		m_secondNum = stage->AddGameObject<UITime>(m_seconds, Vec3(0, 0, 0));
	}
	void TimeManager::OnUpdate() {

		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_time -= elapsedTime*10.0f;

		if (m_time <= 0.0f) {
			m_time = 100.0f;
		}

		int minutes = m_time / 60;
		int seconds = (int)m_time % 60;
		m_first = seconds % 10;
		m_second = (seconds / 10) % 10;
		m_third = minutes % 10;
		m_fourth = (minutes / 10) % 10;

		m_firstNum->UpdateValue(m_first);
		m_secondNum->UpdateValue(m_second);

		wstringstream wss(L"");
		auto scene = App::GetApp()->GetScene<Scene>();

		wss <<L"time : "
			<<m_time
			<<"\n"
			<< L"minutes : "
			<< minutes
			<< "\n"
			<< L"second : "
			<< seconds
			<<"\n"
			<<"Time : "
			<<m_fourth
			<<m_third
			<<L":"
			<<m_second
			<<m_first
			<< endl;

		auto dstr = scene->GetDebugString();
		scene->SetDebugString(dstr + wss.str());

	}

	void TimeManager::UpdateNumber() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_time -= elapsedTime * 10.0f;

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