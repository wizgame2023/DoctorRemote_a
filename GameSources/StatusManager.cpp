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
		m_checkL(false),
		m_colorCheck(false),
		m_count(10.0f),
		m_status(1),
		m_score(100)
	{}

	void StatusManager::OnCreate() {
		auto stage = GetStage();
		m_sprite = stage->AddGameObject<Sprite>(350, 350, L"White", Vec3());
		m_trans = m_sprite->GetComponent<Transform>();
		m_sprite->SetColor(Col4(0, 0, 0, 1.0f));
	}

	void StatusManager::OnUpdate() {
		auto stage = GetStage();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		float elapsedTime = App::GetApp()->GetElapsedTime();

		//選択
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
			m_decision++;

			if (m_score >= 80) {
				m_colorCheck = true;

			}
			else if (m_score >= 50) {
				if (m_status == 0) {

				}
				else {
					m_colorCheck = true;
				}
			}
			else {
				if (m_status == 0 || m_status == 1) {

				}
				else {
					m_colorCheck = true;
				}
			}
		}


		//点滅
		if (m_colorCheck) {
			if ((int)m_count % 2 == 0) {
				m_sprite->SetColor(Col4(0, 0, 0, 0));
			}
			else if ((int)m_count % 2 == 1) {
				m_sprite->SetColor(Col4(0, 0, 0, 1));
			}
			m_count -= elapsedTime * 10.0f;


			switch (m_status)
			{
			case 0:
				//Player::STATUSPLAYER++;
				break;
			case 1:
				//Bullet::STATUSBULLET++;
			case 2:
				break;
			default:
				break;
			}

		}
		
		if (m_count < 0) {
			//PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");

		}
	}
	int StatusManager::GetStatus() {
		return m_status;
	}
	int StatusManager::GetDecision() {
		return m_decision;
	}
}
//end namespace basecross