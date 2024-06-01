/*!
@file TutorialManager.cpp
@brief チュートリアルの管理実体
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	TutorialManager::TutorialManager(const shared_ptr<Stage>& stagePtr) :
		GameObject(stagePtr),
		m_count(0),
		m_blinking(0.7f),
		m_blinking2(1.5f),
		m_blinkFlag(false),
		m_textutreCheck(false)
	{}

	void TutorialManager::OnCreate() {
		auto stage = GetStage();

		m_bButton = stage->AddGameObject<Sprite>(40, 40, L"Bbutton", Vec3(560.0f,-330.0f,0.0f),3);
		m_stageManager = stage->GetSharedGameObject<StageManager>(L"StageManager");
	}
	void TutorialManager::OnUpdate() {
		auto stage = GetStage();
		auto elapsed = App::GetApp()->GetElapsedTime();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto stageManager = stage->GetSharedGameObject<StageManager>(L"StageManager");
		m_comFrameFlag = stageManager->GetComFrameFlag();


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
		if (m_count < 8) {
			m_bButton->SetColor(Col4(1.0f, 1.0f, 1.0f, m_blinking2));
		}
		else {
			m_bButton->ThisDestory();
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
			//挨拶
			Comment(13 * 4, L"AIaisatu", false,false);
			break;
		case 1:
			//説明を始める
			Comment(13 * 4, L"SetumeiStart",true,false);
			break;
		case 2:
			//コメントの説明
			UIComment(13 * 4, L"Comment_s", Vec3(260, -150, 0.0f), 0, true,false);
			break;
		case 3:
			//体力の説明
			UIComment(13 * 4, L"Hp_s", Vec3(-80,-280,0.0f),0,true,true);
			break;
		case 4:
			//ゲージの説明
			UIComment(13 * 4, L"Garge_s", Vec3(-470, -50, 0.0f),-90,true,true);
			break;
		case 5:
			//時間の説明
			UIComment(13 * 4, L"Time_s", Vec3(-105, 320, 0.0f), 90,true,true);
			break;
		case 6:
			//マップの説明
			UIComment(13 * 4, L"Map_s", Vec3(330,320,0.0f),90,true,true);
			break;
		case 7:
			//UI説明終了
			Comment(13 * 2, L"UISetumeiEnd", true,true);
			break;
		case 8:
			//操作説明
			Comment(13 * 2, L"Sousa", true, false);
			m_stageManager->SetStartFlag(true);
			break;
		case 9:
			break;
		default:
			break;
		}

		if (cntlVec[0].bConnected) {
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
				if (m_count < 9) {
					m_count++;
					m_textutreCheck = false;

				}

			}
		}


		//m_triDot[0]->SetColor(Col4(1.0f, 0.0f, 0.0f, m_blinking));
		wstringstream wss(L"");
		auto scene = App::GetApp()->GetScene<Scene>();
		auto gameStage = scene->GetGameStage();
		wss <<L"count : "
			<<m_count
			<< endl;
		scene->SetDebugString(wss.str());

	}
	//コメントを表示　文字数と文字のテクスチャ
	void TutorialManager::Comment(int moji,wstring mesh,bool delet,bool delet2) {
		auto stage = GetStage();
		if (delet) {
			m_com[m_count - 1]->ThisDestroy();
		}
		if (delet2) {
			m_triDot[m_count - 3]->ThisDestory();
		}
		if (!m_textutreCheck) {
			m_com[m_count] = stage->AddGameObject<CommentManager>(13 * 4, 0, Vec3(250, -180, 0.0f), mesh);
			m_textutreCheck = true;
		}

	}
	//コメントの表示とUIの説明に使うポインタ
	void TutorialManager::UIComment(int moji, wstring mesh, Vec3 triPos, float deg, bool delet,bool delet2) {
		auto stage = GetStage();
		float rad = XMConvertToRadians(deg);
		if (delet) {
			m_com[m_count - 1]->ThisDestroy();
		}
		if (delet2) {
			m_triDot[m_count - 3]->ThisDestory();
		}
		if (!m_textutreCheck) {
			m_com[m_count] = stage->AddGameObject<CommentManager>(13 * 4, 0, Vec3(250, -180, 0.0f), mesh);
			m_triDot[m_count - 2] = stage->AddGameObject<Sprite>(30, 30, L"TriDot",triPos);
			m_triDot[m_count - 2]->AddComponent<Transform>()->SetRotation(Vec3(0.0f, 0.0f, rad));
			m_textutreCheck = true;
		}
		m_triDot[m_count - 2]->SetColor(Col4(1.0f, 0.0f, 0.0f, m_blinking));

	}
}