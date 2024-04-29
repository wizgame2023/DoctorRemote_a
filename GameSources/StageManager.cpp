/*!
@file StageManager.cpp
@brief ステージ全体の処理等
担当：
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	StageManager::StageManager(const shared_ptr<Stage>& stagePtr):
		GameObject(stagePtr),
		m_currentHp(100.0f),
		m_maxHp(100.0f),
		m_hpSpeed(3.0f)
	{}

	void StageManager::OnCreate() {

	}
	void StageManager::OnUpdate() {

		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_currentHp -= elapsedTime * m_hpSpeed;

		if (m_currentHp <= 0.0f) {
			m_currentHp = m_maxHp;
		}

		//デバック用
		//wstringstream wss(L"");
		//auto scene = App::GetApp()->GetScene<Scene>();
		//wss << L"currentHp : " <<
		//	m_currentHp <<
		//	"\n" <<
		//	endl;
		//auto dstr = scene->GetDebugString();
		//scene->SetDebugString(dstr + wss.str());
	}

	float StageManager::GetHp() {
		return m_currentHp;
	}
	float StageManager::GetHpRatio() {
		auto ratio = m_currentHp / m_maxHp;
		return ratio;
	}
	void StageManager::SetHp(float hp) {
		m_currentHp += hp;
	}
}
//end namespace basecross