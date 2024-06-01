/*!
@file TutorialManager.cpp
@brief チュートリアルの管理実体
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	ToturialManager::ToturialManager(const shared_ptr<Stage>& stagePtr) :
		GameObject(stagePtr),
		m_count(0),
		m_blinking(0.7f),
		m_blinking2(1.5f),
		m_blinkFlag(false),
		m_textutreCheck(false)
	{}

	void ToturialManager::OnCreate() {
		auto stage = GetStage();

		m_bButton = stage->AddGameObject<Sprite>(50, 50, L"Bbutton", Vec3());
	}
	void ToturialManager::OnUpdate() {
		auto stage = GetStage();
		auto elapsed = App::GetApp()->GetElapsedTime();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto stageManager = stage->GetSharedGameObject<StageManager>(L"StageManager");
		m_comFrameFlag = stageManager->GetComFrameFlag();

		if (cntlVec[0].bConnected) {
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
				m_count++;
				m_textutreCheck = false;

			}
		}

		//点滅処理　Button
		if (m_blinking > 0) {
			if (!m_blinkFlag) {
			m_blinking -= elapsed;
			}
		}
		if(m_blinking < 0.0f) {
			m_blinkFlag = true;
		}
		if (m_blinkFlag) {
			if (m_blinking < 0.7f) {
				m_blinking += elapsed;
			}
			else {
				m_blinkFlag = false;
			}
		}
		
		//点滅処理　triDot
		if (m_blinking2 > 0) {
			m_blinking2 -= elapsed;
		}
		else {
			m_blinking2 = 1.5f;
		}

		//フレームがで終わるまで待つ
		if (!m_comFrameFlag) return;
		switch (m_count)
		{
		case 0:
			if (!m_textutreCheck) {
				m_com[m_count]=stage->AddGameObject<CommentManager>(13*4, 0, Vec3(250, -180, 0.0f), L"AIaisatu");
				m_textutreCheck = true;
			}
			break;
		case 1:
			m_com[m_count-1]->ThisDestroy();
			if (!m_textutreCheck) {
				m_com[m_count] = stage->AddGameObject<CommentManager>(13 * 4, 0, Vec3(250, -180, 0.0f), L"SetumeiStart");
				m_textutreCheck = true;
			}
			break;
		case 2:
			break;
			
		case 4:
			//if (!m_textutreCheck) {
			//	m_triDot[0]=stage->AddGameObject<Sprite>(50, 50, L"TriDot", Vec3());
			//	m_textutreCheck = true;
			//}
			break;
		case 5:
			//if (!m_textutreCheck) {
			//	m_triDot[0]->ThisDestory();
			//	m_textutreCheck = true;
			//}
			break;
		default:
			break;
		}

		//m_triDot[0]->SetColor(Col4(1.0f, 0.0f, 0.0f, m_blinking));
		wstringstream wss(L"");
		auto scene = App::GetApp()->GetScene<Scene>();
		auto gameStage = scene->GetGameStage();
		wss <<L"blinking : "
			<<m_blinking
			<< endl;
		scene->SetDebugString(wss.str());


	}
}