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
		m_exitFlag(false),
		m_stageMove(false),
		m_stageStart(false),
		m_aButtonSEFlag(true),
		m_bButtonSEFlag(false),
		m_color(1.0f,1.0f,1.0f,1.0f)
	{}

	void SelectSprite::OnCreate() {
		auto stage = GetStage();
		m_sprite = stage->AddGameObject<Sprite>(170, 70, L"SelectWhite", Vec3(0.0f, -175.0f, 0.0f),-1);
		m_trans = m_sprite->GetComponent<Transform>();
		m_trans->SetPosition(Vec3(0, -100, 0));
		m_color = Col4(1.0f, 1.0f, 1.0f, 0.5f);
		m_sprite->SetColor(m_color);
		m_back = stage->AddGameObject<Sprite>(1280, 800, L"Black", Vec3(0.0f),-2);
		m_back->SetColor(Col4(0.0f));

	}
	void SelectSprite::OnUpdate() {
		auto stage = GetStage();
		auto& scene = App::GetApp()->GetScene<Scene>();
		float elapsed = App::GetApp()->GetElapsedTime();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto keyState = App::GetApp()->GetInputDevice().GetKeyState();


		//Aボタンが押されたらステージセレクト画面を消す
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A && m_stage == STAGESELECT||keyState.m_bPressedKeyTbl[VK_BACK]) {
			if (m_selectStageFlag) {
				m_selectStage->ThisDestroy();
				m_retrunCom->ThisDestory();
				m_stageFrame->ThisDestory();
				m_sprite->SetColor(Col4(1.0f, 1.0f, 1.0, 0.5f));
				m_back->SetColor(Col4(0.0f));
				m_count = 10.0f;
				m_selectStageFlag = false;
				m_blinkCheck = false;
			}
			//SE
			if (!m_aButtonSEFlag) {
				ChoiceSE();
				m_aButtonSEFlag = true;
			}

		}

		//Aボタンが押されたらExit画面を消す
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A && m_stage == EXIT|| keyState.m_bPressedKeyTbl[VK_BACK]) {
			if (m_exitFlag) {
				m_creditTex->ThisDestory();
				m_sprite->SetColor(Col4(1.0f, 1.0f, 1.0, 0.5f));
				m_back->SetColor(Col4(0.0f));
				m_count = 10.0f;
				m_exitFlag = false;
				m_blinkCheck = false;
			}
			//SE
			if (!m_aButtonSEFlag) {
				ChoiceSE();
				m_aButtonSEFlag = true;
			}

		}

		//決定したら点滅
		if (m_blinkCheck) {
			m_count -= elapsed * 10.0f;
			if ((int)m_count % 2 == 0) {
				m_sprite->SetColor(Col4(0, 0, 0, 0));
			}
			else if ((int)m_count % 2 == 1) {
				m_sprite->SetColor(m_color);
			}
		}

		//点滅が終わったら
		if (m_count <= 0) {
			switch (m_stage)
			{
			case 0:
				if (!m_selectStageFlag) {
					m_stageMove = true;
					if (!m_stageStart) return;
					scene->SetNextStage(0);
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToLoadStage");
				}
				break;
			case 1:
				if (!m_selectStageFlag && !m_exitFlag) {
					m_selectStageFlag = true;
					m_bButtonSEFlag = false;
					m_aButtonSEFlag = false;
					m_back->SetColor(Col4(1.0f, 1.0f, 1.0f, 0.7));
					m_stageFrame = stage->AddGameObject<Sprite>(600, 300, L"Score", Vec3(0.0f));
					m_retrunCom = stage->AddGameObject<Sprite>(120, 60, L"RetrunButton", Vec3(200.0f, -100.0f, 0.0f));
					m_selectStage = GetStage()->AddGameObject<StageSelectSprite>(L"Kakera", L"Kakera");
					m_selectStage->SetLimitNum(10);
				}
				break;
			case 2:
				if (!m_exitFlag && !m_selectStageFlag) {
					m_exitFlag = true;
					m_bButtonSEFlag = false;
					m_aButtonSEFlag = false;
					m_back->SetColor(Col4(1.0f, 1.0f, 1.0f, 0.7));
					m_creditTex = stage->AddGameObject<Sprite>(1280 * 0.85, 800 * 0.85, L"Credit", Vec3(1.0f), 2);
				}
				break;
			default:
				break;
			}

			if (m_selectStageFlag) {
				if (m_selectStage->GetBlinkTime() <= 0) {
					m_stage = 4;
					m_stageMove = true;
					//フェードインが終わったらtrue
					if (!m_stageStart) return;
					int stage = m_selectStage->GetNum();
					scene->SetNextStage(stage);
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToLoadStage");
				}

			}

		}


		if (m_exitFlag) return;

		//ステージを選ぶ
		if (cntlVec[0].bConnected) {
			if (cntlVec[0].fThumbLY < -0.9f||keyState.m_bPressedKeyTbl['S']) {
				if (m_moveCheck) return;
				if (m_heightMin < m_height && !m_checkD) {
					m_height -= m_spaces;
					m_trans->SetPosition(0.0f, m_height, 0.0f);
					m_checkD = true;
				}
			}
			if (cntlVec[0].fThumbLY > -0.9f || keyState.m_bLastKeyTbl['S']&& m_checkD == true ) {
				if (m_moveCheck) return;
				m_checkD = false;
			}

			if (cntlVec[0].fThumbLY > 0.9 || keyState.m_bPressedKeyTbl['W']) {
				if (m_moveCheck) return;
				if (m_heightMax > m_height && !m_checkU) {
					m_height += m_spaces;
					m_trans->SetPosition(0.0f, m_height, 0.0f);
					m_checkU = true;
				}
			}
			if (cntlVec[0].fThumbLY < 0.9 || keyState.m_bLastKeyTbl['W'] && m_checkU == true) {
				if (m_moveCheck) return;
				m_checkU = false;
			}

			//Bボタンで決定
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B ||keyState.m_bPressedKeyTbl[VK_SPACE] && !m_checkU && !m_checkD) {
				if (m_stage == TUTORIAL) {
					m_moveCheck = true;
				}
				else if (m_stage == STAGESELECT) {
					m_count = 0;
				}
				else if (m_stage == EXIT && !m_exitFlag) {
					m_count = 0;
				}
				m_blinkCheck = true;
				//SE
				if (!m_bButtonSEFlag) {
					ChoiceSE();
					m_bButtonSEFlag = true;
				}
			}
		}


		//選択しているモード
		if (m_height == m_heightMax) {
			m_stage = TUTORIAL;
		}
		else if (m_height == m_heightMax-m_spaces) {
			m_stage = STAGESELECT;
		}
		else if (m_height == m_heightMax - m_spaces * 2) {
			m_stage = EXIT;
		}



		//wstringstream wss(L"");
		//wss	<<L"\ncount"
		//	<<m_count
		//	<<"\n"
		//	<<m_blinkCheck
		//	<< endl;
		//scene->SetDebugString(wss.str());

	}

	//SE
	void SelectSprite::ChoiceSE() {
		auto choiceSE = App::GetApp()->GetXAudio2Manager();
		choiceSE->Start(L"ChoiceSE", 0, 0.4f);
	}
	//フェードアウト
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