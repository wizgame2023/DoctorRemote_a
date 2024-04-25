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

	}
	void TimeManager::OnUpdate() {

		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_time -= elapsedTime*10.0f;

		if (m_time <= 0.0f) {
			m_time = 100.0f;
		}

		int minutes = m_time / 60;
		int seconds = (int)m_time % 60;

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
			<< endl;

		auto dstr = scene->GetDebugString();
		scene->SetDebugString(dstr + wss.str());

	}
}
//end namespace basecross