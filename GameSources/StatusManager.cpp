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
		PIECE
	};

	StatusManager::StatusManager(const shared_ptr<Stage>& stagePtr) :
		GameObject(stagePtr),
		m_maxX(0.0f),
		m_width(400.0f),
		m_checkR(false),
		m_checkL(false),
		m_colorCheck(false),
		m_moveCheck(false),
		m_moveStick(false),
		m_count(10.0f),
		m_status(1),
		m_score(100),
		m_control(0)
	{}

	void StatusManager::OnCreate() {
		float sizeX = 200;
		float sizeY = 200;
		Col4 green = Col4(0.1640f, 0.8632f, 0.2109f, 1.0f);
		auto stage = GetStage();
		auto& scene = App::GetApp()->GetScene<Scene>();

		m_selectSprite = stage->AddGameObject<StageSelectSprite>(Vec3(-450, 170, 0.0f),
			sizeX, sizeY, 300, 300, 3, 2, 40, L"White_2", L"White", false, false);

		auto dashButton = stage->AddGameObject<Sprite>(sizeX, sizeY, L"DashButton", m_selectSprite->GetSpritePostion(1,1));
		auto bulletLenght = stage->AddGameObject<Sprite>(sizeX, sizeY, L"BulletButton", m_selectSprite->GetSpritePostion(2, 1));
		auto pieceButton = stage->AddGameObject<Sprite>(sizeX, sizeY, L"GageButton", m_selectSprite->GetSpritePostion(3, 1));
		auto chainRarge = stage->AddGameObject<Sprite>(sizeX, sizeY, L"ScopeButton", m_selectSprite->GetSpritePostion(1, 2));
		auto bulletPower = stage->AddGameObject<Sprite>(sizeX, sizeY, L"PowerButton", m_selectSprite->GetSpritePostion(2, 2));
		auto bulletTime = stage->AddGameObject<Sprite>(sizeX, sizeY, L"ChargeButton", m_selectSprite->GetSpritePostion(3, 2));

		auto frame = stage->AddGameObject<Sprite>(350, 300, L"CommentFrame", Vec3(450.0f, 100.0f, 0.0f));
		m_score = scene->GetAchievementPoint();
		//m_score = 1234;
		
		//ポイントの表示
		auto pos = Vec3(430.0f, 350.0f, 0.0f);
		for (int i = 0; i < 4; i++) {
			float p = pow(10, 4 - (i + 1));
			int num = (m_score / (int)p) % 10;
			m_pointNum[i] = stage->AddGameObject<UITime>(num, Vec3(pos.x + i * 40, pos.y, pos.z));
		}
		//auto pointTex = stage->AddGameObject<Sprite>(50, 50, L"PointTexture", Vec3(pos.x-30,pos.y-30,pos.z));
		//pointTex->SetColor(green);

		
		NumDisplay(2, 25, Vec3(-500.0f, 45.0f, 0.0f));
		NumDisplay(2, 25, Vec3(-200.0f, 45.0f, 0.0f));
		NumDisplay(2, 25, Vec3(100.0f, 45.0f, 0.0f));
		NumDisplay(2, 50, Vec3(-500.0f, -250.0f, 0.0f));
		NumDisplay(2, 75, Vec3(-200.0f, -250.0f, 0.0f));
		NumDisplay(3, 100, Vec3(100.0f, -250.0f, 0.0f));

		//ポイントで制限
		if (m_score>=100) {
			m_selectSprite->SetLimitNum(6);
		}
		else if (m_score >= 75) {
			m_selectSprite->SetLimitNum(5);
		}
		else if (m_score >= 50) {
			m_selectSprite->SetLimitNum(4);
		}
		else if(m_score>=25){
			m_selectSprite->SetLimitNum(3);
		}
		else {
			m_selectSprite->SetLimitNum(0);
		}
	}

	void StatusManager::OnUpdate() {
		auto stage = GetStage();
		auto& scene = App::GetApp()->GetScene<Scene>();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		Col4 white = Col4(1.0f);

		if (m_moveStick && m_selectSprite->StickFlag()) {
			for (int i = 0; i < 6; i++) {
				if (m_com[i]) {
					m_com[i]->ThisDestroy();
				}
			}
				m_moveStick = false;
		}

		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
			auto stage = App::GetApp()->GetScene<Scene>()->GetGameStage();
			//stage = 1;
			wstring nextStage = to_wstring(stage + 1);
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage" + nextStage);

		}


		if (!m_moveStick&& !m_selectSprite->StickFlag()) {
			switch (m_selectSprite->GetNum())
			{
			case 1:
				m_com[0] = stage->AddGameObject<CommentManager>(13 * 4, 0, Vec3(300.0f, 230.0f, 0.0f), L"StatusMoji1-3");
				m_com[0]->SetIntervalTime(0.025);
				m_moveStick = true;
				if (!m_moveCheck) {
				}
				break;
			case 2:
				m_com[1] = stage->AddGameObject<CommentManager>(13 * 4, 0, Vec3(300.0f, 230.0f, 0.0f), L"StatusMoji1-2");
				m_com[1]->SetIntervalTime(0.025);
				m_moveStick = true;
				break;
			case 3:
				m_com[2] = stage->AddGameObject<CommentManager>(13 * 4, 0, Vec3(300.0f, 230.0f, 0.0f), L"StatusMoji1-1");
				m_com[2]->SetIntervalTime(0.025);
				m_moveStick = true;
				break;
			case 4:
				m_com[3] = stage->AddGameObject<CommentManager>(13 * 4, 0, Vec3(300.0f, 230.0f, 0.0f), L"StatusMoji1-6");
				m_com[3]->SetIntervalTime(0.025);
				m_moveStick = true;
				break;
			case 5:
				m_com[4] = stage->AddGameObject<CommentManager>(13 * 4, 0, Vec3(300.0f, 230.0f, 0.0f), L"StatusMoji1-4");
				m_com[4]->SetIntervalTime(0.025);
				m_moveStick = true;
				break;
			case 6:
				m_com[5] = stage->AddGameObject<CommentManager>(13 * 4, 0, Vec3(300.0f, 230.0f, 0.0f), L"StatusMoji1-5");
				m_com[5]->SetIntervalTime(0.025);
				m_moveStick = true;
				break;
			default:
				m_moveStick = true;
				break;
			}
		}

		if (m_selectSprite->GetBlinkTime() <= 0) {

			//選択したステート
			switch (m_selectSprite->GetNum())
			{
			case 1:
				scene->AddDashStatus(1);
				scene->MinusAchievementPoint(25);
				break;
			case 2:
				scene->AddBulletLengthStatus(1);
				scene->MinusAchievementPoint(25);
				break;
			case 3:
				scene->AddBigPieceUpStatus(1);
				scene->MinusAchievementPoint(25);
				break;
			case 4:
				scene->AddChainRargeStatus(1);
				scene->MinusAchievementPoint(50);
				break;
			case 5:
				scene->AddBulletPowerStatus(1);
				scene->MinusAchievementPoint(75);
				break;
			case 6:
				scene->AddBulletTimeStatus(1);
				scene->MinusAchievementPoint(100);
				break;
			default:
				break;
			}

			auto stage = App::GetApp()->GetScene<Scene>()->GetGameStage();
			//stage = 1;
			wstring nextStage = to_wstring(stage + 1);
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage" + nextStage);

		}




		
		//int test = scene->GetAchievementPoint();//デバック用変数
		//wstringstream wss(L"");
		//wss << test <<"\n" << m_score << endl;
		//scene->SetDebugString( wss.str());

	}

	void StatusManager::NumDisplay(int digit, int num,Vec3 pos) {
		auto stage = GetStage();
		for (int i = 0; i < digit; i++) {
			float p = pow(10, digit - (i + 1));
			int n = (num / (int)p) % 10;
			auto numSprite = stage->AddGameObject<UITime>(n, Vec3(pos.x + i * 30, pos.y, pos.z),40,60,L"NumbersWhite");
			//auto pointTex = stage->AddGameObject<Sprite>(40, 40, L"PointTexture", Vec3(pos.x - 20, pos.y - 25, pos.z));
			//pointTex->SetColor(Col4(0.1640f, 0.8632f, 0.2109f, 1.0f));

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