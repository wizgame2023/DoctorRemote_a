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
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		m_time -= elapsedTime;

		if (m_time <= 0.0f) {
			m_time = 100.0f;
		}


	}
}
//end namespace basecross