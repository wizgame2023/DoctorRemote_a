/*!
@file SatusManager.cpp
@brief ステート全体の処理等
担当：
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	enum STSTUS {
		DASH,
		BULLET_RANGE,
		PIECE_RANGE
	};

	StatusManager::StatusManager(const shared_ptr<Stage>& stagePtr):
		GameObject(stagePtr),
		m_maxX(0.0f),
		m_width(400.0f),
		m_checkR(false),
		m_checkL(false)
	{}

	void StatusManager::OnCreate() {
		auto stage = GetStage();
		auto sprite = stage->AddGameObject<Sprite>(300, 300, L"White", Vec3());
		

	}

	void StatusManager::OnUpdate() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		if (cntlVec[0].fThumbLX > 0.9f) {
			if (m_maxX == 0 && !m_checkR) {
				m_maxX = m_width;
				m_trans->SetPosition(m_maxX, 0, 0);
				m_checkR = true;
				m_status = PIECE_RANGE;
			}
			if (m_maxX < 0 && !m_checkR) {
				m_maxX = 0.0f;
				m_trans->SetPosition(m_maxX, 0, 0);
				m_checkR = true;
				m_status = BULLET_RANGE;
			}
		}
		if (cntlVec[0].fThumbLX < 0.9f && m_checkR == true)
		{
			m_checkR = false;
		}

		if (cntlVec[0].fThumbLX < -0.9f) {
			if (m_maxX == 0 && !m_checkL) {
				m_maxX = -m_width;
				m_trans->SetPosition(m_maxX, 0, 0);
				m_checkL = true;
				m_status = DASH;
			}
			if (m_maxX > 0 && !m_checkL) {
				m_maxX = 0.0f;
				m_trans->SetPosition(m_maxX, 0, 0);
				m_checkL = true;
				m_status = BULLET_RANGE;
			}
		}
		if (cntlVec[0].fThumbLX > -0.9f && m_checkL == true)
		{
			m_checkL = false;
		}

		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {

		}
		
	}
}
//end namespace basecross