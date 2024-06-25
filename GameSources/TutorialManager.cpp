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
		m_textutreCheck(false),
		m_mapSetumeiCheck(false),
		m_startFlag(false),
		m_raderFlag(false),
		m_enemyFlag(false),
		m_enemyFlag2(false)
	{}

	TutorialManager::~TutorialManager() {
	}
	void TutorialManager::OnCreate() {
		auto stage = GetStage();

		m_bButton = stage->AddGameObject<Sprite>(40, 40, L"Bbutton", Vec3(560.0f,-330.0f,0.0f),3);
	}
	void TutorialManager::OnUpdate() {
		auto stage = GetStage();
		auto elapsed = App::GetApp()->GetElapsedTime();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto stageManager = stage->GetSharedGameObject<StageManager>(L"StageManager");
		m_comFrameFlag = stageManager->GetComFrameFlag();
		m_stageManager = stage->GetSharedGameObject<StageManager>(L"StageManager");
		m_player = stage->GetSharedGameObject<Player>(L"GamePlayer");


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
		if (m_count < 10) {
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
			Comment(13 * 4, L"SetumeiStart");
			break;
		case 2:
			//コメントの説明
			UIComment(13 * 4, L"Comment_s", Vec3(260, -135, 0.0f), 0,Vec2(1280,800),L"CommentWaku",Vec3(0.0f), true, false);
			break;
		case 3:
			//体力の説明
			UIComment(13 * 4, L"Hp_s", Vec3(-80,-272,0.0f),0,Vec2(1280, 800), L"HPWaku", Vec3(0.0f));
			break;
		case 4:
			//マップの説明
			UIComment(13 * 4, L"Map_s", Vec3(-80, -280, 0.0f), 0, Vec2(1280, 800), L"ChargeWaku", Vec3(0.0f));
			break;
		case 5:
			//ゲージの説明
			UIComment(13 * 4, L"Garge_s", Vec3(-462, -50, 0.0f),-90, Vec2(1280, 800), L"GageWaku", Vec3(0.0f));
			break;
		case 6:
			//時間の説明
			UIComment(13 * 4, L"Time_s", Vec3(-111, 320, 0.0f), 90, Vec2(1280, 800), L"TimeWaku", Vec3(0.0f));
			break;
		case 7:
			//チャージゲージの説明
			UIComment(13 * 4, L"Charge_s", Vec3(330, 320, 0.0f), 90, Vec2(1280, 800), L"MapWaku", Vec3(0.0f));
			break;
		case 8:
			UIComment(13 * 4, L"Map_s2", Vec3(330, 100, 0.0f), 90, Vec2(1280, 800), L"Map_sWaku", Vec3(0.0f));
			if (!m_mapSetumeiCheck) {
				m_mapSetumei = stage->AddGameObject<Sprite>(256*0.8, 128*0.8,L"MapSetumei", Vec3(450, 80, 0.0f), 3);
				m_mapSetumeiCheck = true;
			}
			break;
		case 9:
			//UI説明終了
			Comment(13 * 2, L"UISetumeiEnd", true,true);
			break;
		case 10:
			//操作説明
			Comment(13 * 3, L"Sousa");
			break;
		case 11: 
			//欠片の説明
			Comment(13 * 3, L"Setumei1");
			if (m_stageManager->GetCountFlag()) {
				m_stageManager->SetStartFlag(true);
			}
			break;
		case 12:
			//レーダーの説明（ゲージMax時）
			if (!m_raderFlag) {
				Comment(13 * 3, L"Setumei3");
				m_raderFlag = true;
			}
			break;
		case 13:
			//脱出の説明（敵を倒したら）
			if (!m_enemyFlag2) {
				Comment(13 * 3, L"Dassyutu");
				m_enemyFlag2 = true;
			}
			break;
		default:
			break;
		}
		//if (m_stageManager->GetStartFlag()) {
		//	//m_stageManager->SetStartFlag(true);
		//}

		if (cntlVec[0].bConnected) {
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
				if (m_count < 11) {
					m_count++;
					m_textutreCheck = false;

				}

			}
		}
		if (m_player->GetRadarFlag()&&!m_raderFlag) {
			m_textutreCheck = false;
			m_count = 12;
		}

		if (m_stageManager->GetEnemyFlag()) {
			m_textutreCheck = false;
			m_count = 13;
		}

		//wstringstream wss(L"");
		//auto scene = App::GetApp()->GetScene<Scene>();
		//auto gameStage = scene->GetGameStage();
		//wss <<L"count : "
		//	<<m_count
		//	<< endl;
		//scene->SetDebugString(wss.str());

	}
	//コメントを表示　文字数と文字のテクスチャ
	void TutorialManager::Comment(int moji,wstring mesh,bool delet,bool delet2) {
		auto stage = GetStage();
		if (delet) {
			m_com[m_count - 1]->ThisDestroy();
		}
		if (delet2) {
			m_triDot[m_count - 3]->ThisDestory();
			m_frame[m_count - 3]->ThisDestory();
		}
		if (!m_textutreCheck) {
			m_com[m_count] = stage->AddGameObject<CommentManager>(13 * 4, 0, Vec3(250, -180, 0.0f), mesh);
			m_textutreCheck = true;
		}

	}
	//コメントの表示とUIの説明に使うポインタ
	void TutorialManager::UIComment(int moji, wstring mesh, Vec3 triPos, float deg,Vec2 size,wstring texture,Vec3 spPos, bool delet,bool delet2) {
		auto stage = GetStage();
		float rad = XMConvertToRadians(deg);
		if (delet) {
			m_com[m_count - 1]->ThisDestroy();
		}
		if (delet2) {
			m_triDot[m_count - 3]->ThisDestory();
			m_frame[m_count - 3]->ThisDestory();
		}
		if (!m_textutreCheck) {
			m_com[m_count] = stage->AddGameObject<CommentManager>(13 * 4, 0, Vec3(250, -180, 0.0f), mesh);
			m_triDot[m_count - 2] = stage->AddGameObject<Sprite>(30, 30, L"TriDot",triPos);
			m_triDot[m_count - 2]->AddComponent<Transform>()->SetRotation(Vec3(0.0f, 0.0f, rad));
			m_textutreCheck = true;
			m_frame[m_count - 2] = stage->AddGameObject<Sprite>(size.x, size.y, texture, spPos, 3);
		}
		m_triDot[m_count - 2]->SetColor(Col4(1.0f, 0.0f, 0.0f, m_blinking));
		m_frame[m_count - 2]->SetColor(Col4(1.0f, 0.0f, 0.0f, m_blinking));
	}

}