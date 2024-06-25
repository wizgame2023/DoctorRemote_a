/*!
@file SelectSprite.cpp
@brief 動かすことができるスプライト
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	enum STAGE {
		TUTORIAL,
		STAGESELECT,
		EXIT,
	};

	SelectSprite::SelectSprite(const shared_ptr<Stage>& stagePtr):
		GameObject(stagePtr),
		m_height(-100),
		m_heightMax(-100),
		m_heightMin(-250),
		m_spaces(75.0f),
		m_count(10.0f),
		m_checkD(false),
		m_checkU(false),
		m_moveCheck(false),
		m_blinkCheck(false),
		m_selectStageFlag(false),
		m_stageMove(false),
		m_stageStart(false),
		m_color(1.0f,1.0f,1.0f,1.0f)
	{}

	void SelectSprite::OnCreate() {
		auto stage = GetStage();
		m_sprite = stage->AddGameObject<Sprite>(170, 70, L"SelectWhite", Vec3(0.0f, -175.0f, 0.0f),-1);
		m_trans = m_sprite->GetComponent<Transform>();
		m_trans->SetPosition(Vec3(0, -100, 0));
		m_color = Col4(1.0f, 1.0f, 1.0f, 0.5f);
		m_sprite->SetColor(m_color);

	}
	void SelectSprite::OnUpdate() {
		auto stage = GetStage();
		float elapsed = App::GetApp()->GetElapsedTime();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		//ステージを選ぶ
		if (cntlVec[0].fThumbLY < -0.9f) {
			if (m_moveCheck) return;
			if (m_heightMin < m_height && !m_checkD) {
				m_height -= m_spaces;
				m_trans->SetPosition(0.0f,m_height, 0.0f);
				m_checkD = true;
			}
		}
		if (cntlVec[0].fThumbLY > -0.9f && m_checkD == true) {
			if (m_moveCheck) return;
			m_checkD = false;
		}

		if (cntlVec[0].fThumbLY > 0.9) {
			if (m_moveCheck) return;
			if (m_heightMax > m_height && !m_checkU) {
				m_height += m_spaces;
				m_trans->SetPosition(0.0f, m_height, 0.0f);
				m_checkU = true;
			}
		}
		if (cntlVec[0].fThumbLY < 0.9 && m_checkU == true) {
			if (m_moveCheck) return;
			m_checkU = false;
		}

		//Bボタンで決定
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
			if (m_stage == TUTORIAL && m_stage == EXIT) {
				m_moveCheck = true;
			}
			if (m_stage == STAGESELECT) {
				m_count = 0;
			}
			m_blinkCheck = true;
		}
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
			if (m_selectStageFlag) {
				m_selectStage->ThisDestroy();
				m_RetrunCom->ThisDestory();
				m_stageFrame->ThisDestory();
				m_sprite->SetColor(Col4(1.0f, 1.0f, 1.0, 0.5f));
				m_count = 10.0f;
				m_selectStageFlag = false;
				m_blinkCheck = false;
			}
		}

		if (m_height == m_heightMax) {
			m_stage = TUTORIAL;
		}
		else if (m_height == m_heightMax-m_spaces) {
			m_stage = STAGESELECT;
		}
		else if (m_height == m_heightMax - m_spaces * 2) {
			m_stage = EXIT;
		}

		//決定したら点滅
		if (m_blinkCheck) {
			if ((int)m_count % 2 == 0) {
				m_sprite->SetColor(Col4(0, 0, 0, 0));
			}
			else if ((int)m_count % 2 == 1) {
				m_sprite->SetColor(m_color);
			}
			m_count -= elapsed * 10.0f;
		}
		if (m_count < 0) {
			switch (m_stage)
			{
			case 0:
				if (!m_selectStageFlag) {
					m_stageMove = true;
					if (!m_stageStart) return;
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTutorialStage");
				}
				break;
			case 1:
				if (!m_selectStageFlag) {
					m_stageFrame = stage->AddGameObject<Sprite>(600, 300, L"Score", Vec3(0.0f));
					m_RetrunCom = stage->AddGameObject<Sprite>(120, 60, L"RetrunButton", Vec3(200.0f,-100.0f,0.0f));
					m_selectStage = GetStage()->AddGameObject<StageSelectSprite>(L"Kakera",L"Kakera");
					m_selectStage->SetLimitNum(10);
					m_selectStageFlag = true;
				}
				break;
			case 2:
				if (!m_selectStageFlag) {
					m_stageMove = true;
					if (!m_stageStart) return;
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage10");
				}
				break;
			default:
				break;
			}

			if (m_selectStageFlag) {
				if (m_selectStage->GetBlinkTime() <= 0) {
					int stage = m_selectStage->GetNum();
					wstring stageNum = to_wstring(stage);
					m_stageMove = true;
					if (!m_stageStart) return;
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage" + stageNum);
				}

			}
		}

		//wstringstream wss(L"");
		//auto scene = App::GetApp()->GetScene<Scene>();
		//auto gameStage = scene->GetGameStage();
		//wss <<L"stage : "
		//	<<m_stage
		//	<<L"\nheight : "
		//	<<m_height
		//	<<L"\ncount"
		//	<<m_count
		//	<<L"\nBlink"
		//	<<m_blinkCheck
		//	<< endl;
		//scene->SetDebugString(wss.str());

	}
	bool SelectSprite::GetStageMove()
	{
		return m_stageMove;
	}
	void SelectSprite::SetStageStart(bool start) {
		m_stageStart = start;
	}
	void SelectSprite::StageMove(wstring stage) {
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage"+stage);
	}
}