/*!
@file StageManager.cpp
@brief ステージ全体の処理等
担当：
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	StageManager::StageManager(const shared_ptr<Stage>& stagePtr) :
		GameObject(stagePtr),
		m_currentHp(100.0f),
		m_maxHp(100.0f),
		m_hpSpeed(3.0f),
		m_ligthStatus(0)
	{}

	void StageManager::OnCreate() {
		auto stage = GetStage();
		m_ligthStatus = App::GetApp()->GetScene<Scene>()->GetLigthStatus();
		switch (m_ligthStatus)
		{
		case 0:
			stage->AddGameObject<Sprite>(1280, 800, L"Ligth", Vec3());
			break;
		case 1:
			stage->AddGameObject<Sprite>(1280, 800, L"Ligth2", Vec3());
			break;
		case 2:
			stage->AddGameObject<Sprite>(1280, 800, L"Ligth3", Vec3());
			break;
		default:
			break;
		}
	}
	void StageManager::OnUpdate() {

		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_currentHp -= elapsedTime * m_hpSpeed * 0.5f;

		if (m_currentHp > m_maxHp) {
			m_currentHp = m_maxHp;
		}

		if (m_currentHp <= 0.0f) {
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");
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