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
		m_currentHp(0.0f),
		m_maxHp(100.0f)
	{}

	void StageManager::OnCreate() {

	}
	void StageManager::OnUpdate() {

	}

	float StageManager::GetHp() {
		return m_currentHp;
	}
	void StageManager::SetHp(float hp) {
		m_currentHp += hp;
	}
}
//end namespace basecross