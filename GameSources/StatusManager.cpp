/*!
@file SatusManager.cpp
@brief ステート全体の処理等
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	enum STSTUS {
		DASH,
		BULLET,
		LIGHT
	};

	StatusManager::StatusManager(const shared_ptr<Stage>& stagePtr):
		GameObject(stagePtr),
		m_maxX(0.0f),
		m_width(400.0f),
		m_checkR(false),
		m_checkL(false),
		m_colorCheck(false),
		m_moveCheck(false),
		m_count(10.0f),
		m_status(1),
		m_score(100)
	{}

	void StatusManager::OnCreate() {
		auto stage = GetStage();
		m_sprite = stage->AddGameObject<Sprite>(330, 330, L"White", Vec3());
		m_trans = m_sprite->GetComponent<Transform>();

		m_color = Col4(0.105, 0.75, 0, 1.0f);
		m_sprite->SetColor(m_color);
		
		//m_player = stage->GetSharedGameObject<Player>(L"GamePlayer");
	}

	void StatusManager::OnUpdate() {
		auto stage = GetStage();
		auto& scene = App::GetApp()->GetScene<Scene>();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		float elapsedTime = App::GetApp()->GetElapsedTime();

		//選択
		if (cntlVec[0].fThumbLX > 0.9f) {
			if (m_moveCheck) return;
			if (m_maxX == 0 && !m_checkR) {
				m_maxX = m_width;
				m_trans->SetPosition(m_maxX, 0, 0);
				m_checkR = true;
				m_status = LIGHT;
			}
			if (m_maxX < 0 && !m_checkR) {
				m_maxX = 0.0f;
				m_trans->SetPosition(m_maxX, 0, 0);
				m_checkR = true;
				m_status = BULLET;
			}
		}
		if (cntlVec[0].fThumbLX < 0.9f && m_checkR == true)
		{
			if (m_moveCheck) return;
			m_checkR = false;
		}

		if (cntlVec[0].fThumbLX < -0.9f) {
			if (m_moveCheck) return;
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
				m_status = BULLET;
			}
		}
		if (cntlVec[0].fThumbLX > -0.9f && m_checkL == true)
		{
			if (m_moveCheck) return;
			m_checkL = false;
		}

		//スコアによって選べるステートが異なる
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
			m_moveCheck = true;
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

			//選択したステート
			switch (m_status)
			{
			case 0:
				App::GetApp()->GetScene<Scene>()->AddPlayerStatus(1);
				break;
			case 1:
				App::GetApp()->GetScene<Scene>()->AddBulletStatus(1);
				break;
			case 2:
				App::GetApp()->GetScene<Scene>()->AddLigthStatus(1);
				break;
			default:
				break;
			}

			//auto sprite = GetStage()->GetSharedGameObject<Sprite>(L"Moji2");
			//sprite->Blinking(20.0f, Col4(1, 1, 1, 1));

		}


		//決定を押したら点滅
		if (m_colorCheck) {
			if ((int)m_count % 2 == 0) {
				m_sprite->SetColor(Col4(0, 0, 0, 0));
			}
			else if ((int)m_count % 2 == 1) {
				m_sprite->SetColor(Col4(m_color));
			}
			m_count -= elapsedTime * 10.0f;


		}
		
		if (m_count < 0) {
			switch (scene->GetGameStage())
			{
			case 0:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStartStage");
				break;
			case 1:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage2");
				break;
			case 2:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStartStage");
				break;
			default:
				break;
			}

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