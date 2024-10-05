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
		m_aButtonSEFlag(false),
		m_count(10.0f),
		m_status(1),
		m_score(0),
		m_control(0)
	{}

	void StatusManager::OnCreate() {
		auto& scene = App::GetApp()->GetScene<Scene>();
		Displays();
		PointLevelDis();
		
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
		auto keyState = App::GetApp()->GetInputDevice().GetKeyState();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		Col4 white = Col4(1.0f);

		if (m_moveStick && m_selectSprite->StickFlag()) {
			for (int i = 0; i < 6; i++) {
				if (m_coms[i]) {
					m_coms[i]->ThisDestroy();
				}
			}
				m_moveStick = false;
		}

		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A|| keyState.m_bPressedKeyTbl[VK_BACK]) {
			auto stage = App::GetApp()->GetScene<Scene>()->GetGameStage();
			//stage = 1;
			wstring nextStage = to_wstring(stage + 1);
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage" + nextStage);
			if (!m_aButtonSEFlag) {
				auto pieceSE = App::GetApp()->GetXAudio2Manager();
				pieceSE->Start(L"ChoiceSE", 0, 1.2f);
				m_aButtonSEFlag = true;
			}
		}
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_Y || keyState.m_bPressedKeyTbl[VK_DELETE]) {
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStartStage");
			if (!m_aButtonSEFlag) {
				auto pieceSE = App::GetApp()->GetXAudio2Manager();
				pieceSE->Start(L"ChoiceSE", 0, 1.2f);
				m_aButtonSEFlag = true;
			}
		}

		//スティックを動かすとコメントが変わる
		if (!m_moveStick&& !m_selectSprite->StickFlag()) {
			switch (m_selectSprite->GetNum())
			{
			case 1:
				m_coms[0] = stage->AddGameObject<Sprite>(300, 300, L"StatusMoji1-3", Vec3(450.0f, 70.0f, 0.0f));
				m_moveStick = true;
				if (!m_moveCheck) {
				}
				break;
			case 2:
				m_coms[1] = stage->AddGameObject<Sprite>(300, 300, L"StatusMoji1-2", Vec3(450.0f, 70.0f, 0.0f));
				m_moveStick = true;
				break;
			case 3:
				m_coms[2] = stage->AddGameObject<Sprite>(300, 300, L"StatusMoji1-1", Vec3(450.0f, 70.0f, 0.0f));
				m_moveStick = true;
				break;
			case 4:
				m_coms[3] = stage->AddGameObject<Sprite>(300, 300, L"StatusMoji1-6", Vec3(450.0f, 70.0f, 0.0f));
				m_moveStick = true;
				break;
			case 5:
				m_coms[4] = stage->AddGameObject<Sprite>(300, 300, L"StatusMoji1-4", Vec3(450.0f, 70.0f, 0.0f));
				m_moveStick = true;
				break;
			case 6:
				m_coms[5] = stage->AddGameObject<Sprite>(300, 300, L"StatusMoji1-5", Vec3(450.0f, 70.0f, 0.0f));
				m_moveStick = true;
				break;
			default:
				m_moveStick = true;
				break;
			}
		}

		//ステータスを確定
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

	//画面上に映るSpriteなど
	void StatusManager::Displays() {
		float sizeX = 200;
		float sizeY = 200;
		Col4 green = Col4(0.1640f, 0.8632f, 0.2109f, 1.0f);
		auto stage = GetStage();
		auto& scene = App::GetApp()->GetScene<Scene>();

		//選択できるスプライト
		m_selectSprite = stage->AddGameObject<StageSelectSprite>(Vec3(-450, 170, 0.0f),
			sizeX, sizeY, 300, 300, 3, 2, 40, L"White_2", L"White_2", false, false);
		//ステータスのスプライト
		auto dashButton = stage->AddGameObject<Sprite>(sizeX, sizeY, L"DashButton", m_selectSprite->GetSpritePostion(1, 1));
		auto bulletLenght = stage->AddGameObject<Sprite>(sizeX, sizeY, L"BulletButton", m_selectSprite->GetSpritePostion(2, 1));
		auto pieceButton = stage->AddGameObject<Sprite>(sizeX, sizeY, L"GageButton", m_selectSprite->GetSpritePostion(3, 1));
		auto chainRarge = stage->AddGameObject<Sprite>(sizeX, sizeY, L"ScopeButton", m_selectSprite->GetSpritePostion(1, 2));
		auto bulletPower = stage->AddGameObject<Sprite>(sizeX, sizeY, L"PowerButton", m_selectSprite->GetSpritePostion(2, 2));
		auto bulletTime = stage->AddGameObject<Sprite>(sizeX, sizeY, L"ChargeButton", m_selectSprite->GetSpritePostion(3, 2));

		m_score = scene->GetAchievementPoint();
		//説明コメントの枠
		auto frame = stage->AddGameObject<Sprite>(350, 300, L"CommentFrame", Vec3(450.0f, 100.0f, 0.0f));
		//補足説明
		auto levelSetumei = stage->AddGameObject<Sprite>(256, 256, L"StatusSetumei2", Vec3(450.0f, -200.0f, 0.0f));
		levelSetumei->SetColor(green);
		//ポイントの表示
		auto pos = Vec3(430.0f, 350.0f, 0.0f);
		for (int i = 0; i < 4; i++) {
			float p = pow(10, 4 - (i + 1));
			int num = (m_score / (int)p) % 10;
			m_pointNum[i] = stage->AddGameObject<UITime>(num, Vec3(pos.x + i * 40, pos.y, pos.z));
		}
		auto pointTex = stage->AddGameObject<Sprite>(50, 50, L"PointTexture", Vec3(pos.x - 30, pos.y - 30, pos.z));
		pointTex->SetColor(green);

	}

	//ポイントの表示　レベルの表示等
	void StatusManager::PointLevelDis() {
		auto& scene = App::GetApp()->GetScene<Scene>();
		//ポイントとレベル
		Vec3 pointPos(-530.0f, 50.0f, 0.0f);
		Vec3 levelPos(-380.0f, 50.0f, 0.0f);
		int dash = scene->GetDashStatus();
		int bullet_l = scene->GetBulletLengthStatus();
		int bigPiece = scene->GetBigPieceUpStatus();
		int chain = scene->GetChainRangeStatus();
		int bullet_p = scene->GetBulletPowerStatus();
		int bullet_t = scene->GetBulletTimeStatus();

		NumDisplay(2, 25, Vec3(pointPos.x, pointPos.y, 0.0f));
		NumDisplay(1, dash, Vec3(levelPos.x, levelPos.y, 0.0f), false, true);
		NumDisplay(2, 25, Vec3(pointPos.x + 300, pointPos.y, 0.0f));
		NumDisplay(1, bullet_l, Vec3(levelPos.x + 300, levelPos.y, 0.0f), false, true);
		NumDisplay(2, 25, Vec3(pointPos.x + 300 * 2, pointPos.y, 0.0f));
		NumDisplay(1, bigPiece, Vec3(levelPos.x + 300 * 2, levelPos.y, 0.0f), false, true);
		NumDisplay(2, 50, Vec3(pointPos.x, pointPos.y - 300, 0.0f));
		NumDisplay(1, chain, Vec3(levelPos.x, levelPos.y - 300, 0.0f), false, true);
		NumDisplay(2, 75, Vec3(pointPos.x + 300, pointPos.y - 300.0f, 0.0f));
		NumDisplay(1, bullet_p, Vec3(levelPos.x + 300, levelPos.y - 300, 0.0f), false, true);
		NumDisplay(3, 100, Vec3(pointPos.x + 300 * 2, pointPos.y - 300.0f, 0.0f));
		NumDisplay(1, bullet_t, Vec3(levelPos.x + 300 * 2, levelPos.y - 300, 0.0f), false, true);

		if (dash >= 3) {
			m_selectSprite->SetCloseNum(0);
		}
		if (bullet_l >= 3) {
			m_selectSprite->SetCloseNum(1);
		}
		if (bigPiece >= 3) {
			m_selectSprite->SetCloseNum(2);
		}
		if (chain >= 3) {
			m_selectSprite->SetCloseNum(3);
		}
		if (bullet_p >= 3) {
			m_selectSprite->SetCloseNum(4);
		}
		if (bullet_t >= 3) {
			m_selectSprite->SetCloseNum(5);
		}

	}

	void StatusManager::NumDisplay(int digit, int num,Vec3 pos,bool pointFlag,bool levelFlag) {
		auto stage = GetStage();
		for (int i = 0; i < digit; i++) {
			float p = pow(10, digit - (i + 1));
			int n = (num / (int)p) % 10;
			auto numSprite = stage->AddGameObject<UITime>(n, Vec3(pos.x + i * 30, pos.y, pos.z),40,60,L"NumbersWhite");
			if (pointFlag) {
				auto pointTex = stage->AddGameObject<Sprite>(50, 50, L"PointTexture", Vec3(pos.x - 10, pos.y - 25, pos.z));
				pointTex->SetColor(Col4(0.1640f, 0.8632f, 0.2109f, 1.0f));
			}
			if (levelFlag) {
				auto levelTex = stage->AddGameObject<Sprite>(40, 40, L"LevelTexture", Vec3(pos.x - 10, pos.y - 25, pos.z));
				levelTex->SetColor(Col4(0.1640f, 0.8632f, 0.2109f, 1.0f));
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