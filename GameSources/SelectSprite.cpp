/*!
@file SelectSprite.cpp
@brief 動かすことができるスプライト
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	SelectSprite::SelectSprite(const shared_ptr<Stage>& stagePtr):
		GameObject(stagePtr),
		m_height(100),
		m_heightMax(325)
	{}

	void SelectSprite::OnCreate() {
		auto stage = GetStage();
		auto sprite = stage->AddGameObject<Sprite>(170, 70, L"White", Vec3(0.0f, -100.0f, 0.0f));
		m_trans = sprite->GetComponent<Transform>();

		auto color = Col4(0.0f, 0.0f, 0, 1.0f);
		sprite->SetColor(color);

	}
	void SelectSprite::OnUpdate() {
		auto stage = GetStage();
		float elapsed = App::GetApp()->GetElapsedTime();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		if (cntlVec[0].fThumbLY > -0.9f) {
			if (m_moveCheck) return;
			if (m_heightMax > m_height && !m_checkR) {
				m_height -= 50;
				m_trans->SetPosition(0.0f,m_height, 0.0f);
				m_checkR = true;
			}
		}
		if (cntlVec[0].fThumbLY < -0.9f && m_checkR == true) {
			if (m_moveCheck) return;
			m_checkR = false;
		}
	}
}