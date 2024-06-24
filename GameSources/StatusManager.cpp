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
		m_count(10.0f),
		m_status(1),
		m_score(100),
		m_control(0)
	{}

	void StatusManager::OnCreate() {
		auto stage = GetStage();
		auto& scene = App::GetApp()->GetScene<Scene>();
		m_selectSprite = stage->AddGameObject<StageSelectSprite>(Vec3(-300, 150, 0.0f), 
			200, 200, 300, 250, 3, 2, 30, L"White", L"White",false);

		auto dashButton = stage->AddGameObject<Sprite>(200, 200, L"DashButton", m_selectSprite->GetSpritePostion(1,1));
		auto bulletLenght = stage->AddGameObject<Sprite>(200, 200, L"BulletButton", m_selectSprite->GetSpritePostion(2, 1));
		auto pieceButton = stage->AddGameObject<Sprite>(200, 200, L"GageButton", m_selectSprite->GetSpritePostion(3, 1));
		auto chainRarge = stage->AddGameObject<Sprite>(200, 200, L"DashButton", m_selectSprite->GetSpritePostion(1, 2));
		auto bulletPower = stage->AddGameObject<Sprite>(200, 200, L"BulletButton", m_selectSprite->GetSpritePostion(2, 2));
		auto bulletTime = stage->AddGameObject<Sprite>(200, 200, L"GageButton", m_selectSprite->GetSpritePostion(3, 2));


		m_score = scene->GetAchievementPoint();
		//m_score = 1234;
		int first = (m_score / 1000);
		int second = (m_score / 100) % 10;
		int third = (m_score / 10) % 10;
		int fourth = (m_score) % 10;
		auto pos = Vec3(430.0f, 350.0f, 0.0f);
		Vec3 pos2(pos.x + 40, pos.y, pos.z);
		Vec3 pos3(pos.x + 80, pos.y, pos.z);
		Vec3 pos4(pos.x + 120,pos.y, pos.z);
		m_pointNum[0] = stage->AddGameObject<UITime>(first, pos);
		m_pointNum[1] = stage->AddGameObject<UITime>(second, pos2);
		m_pointNum[2] = stage->AddGameObject<UITime>(third, pos3);
		m_pointNum[3] = stage->AddGameObject<UITime>(fourth, pos4);


		if (m_score>=100) {
			m_selectSprite->SetLimitNum(6);
		}
		else if (m_score >= 75) {
			m_selectSprite->SetLimitNum(5);
		}
		else if (m_score >= 50) {
			m_selectSprite->SetLimitNum(4);
		}
		else if(m_score >= 25) {
			m_selectSprite->SetLimitNum(3);
		}
		else {
			m_selectSprite->SetLimitNum(2);
		}
	}

	void StatusManager::OnUpdate() {
		auto stage = GetStage();
		auto& scene = App::GetApp()->GetScene<Scene>();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		float elapsedTime = App::GetApp()->GetElapsedTime();

		
		switch (m_selectSprite->GetNum())
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		default:
			break;
		}


	

		if ( m_selectSprite->GetBlinkTime()<= 0) {

			//選択したステート
			switch (m_selectSprite->GetNum())
			{
			case 1:
				scene->AddDashStatus(1);
				break;
			case 2:
				scene->AddBulletLengthStatus(1);
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

			switch (1)
			{
			case 0:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStartStage");
				break;
			case 1:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage4");
				break;
			case 2:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStartStage");
				break;
			default:
				break;
			}
		}

		//コメントの表示
		//if (m_status == 1) {
		//	if (m_com[0]) {
		//		m_com[0]->ThisDestroy();
		//	}
		//	if (m_com[2]) {
		//		m_com[2]->ThisDestroy();
		//	}
		//	if (m_comFlag) return;
		//	m_com[1] = stage->AddGameObject<CommentManager>(3, 0, 0.05f, 512, 50, 300, 30, 9, 1, Vec3(-150.0f, -180.0f, 0.0f), L"StatusMoji1-2");
		//	m_comFlag = true;
		//}
		//if (m_status == 0) {
		//	if (m_com[1]) {
		//		m_com[1]->ThisDestroy();
		//	}
		//	if (m_com[2]) {
		//		m_com[2]->ThisDestroy();
		//	}
		//	if (m_comFlag) return;
		//	m_com[0] = stage->AddGameObject<CommentManager>(16, 0, 0.05f, 450, 195, 250, 120, 8, 3, Vec3(-525.0f, -180.0f, 0.0f), L"StatusMoji1-3");
		//	m_comFlag = true;
		//}
		//if (m_status == 2) {
		//	if (m_com[0]) {
		//		m_com[0]->ThisDestroy();
		//	}
		//	if (m_com[1]) {
		//		m_com[1]->ThisDestroy();
		//	}
		//	if (m_comFlag) return;
		//	m_com[2] = stage->AddGameObject<CommentManager>(17, 0, 0.05f, 512, 120, 300, 80, 9, 2, Vec3(250.0f, -180.0f, 0.0f), L"StatusMoji1-1");
		//	m_comFlag = true;
		//}
		
		//int test = scene->GetAchievementPoint();//デバック用変数
		//wstringstream wss(L"");
		//wss << test <<"\n" << m_score << endl;
		//scene->SetDebugString( wss.str());

	}
	int StatusManager::GetStatus() {
		return m_status;
	}
	int StatusManager::GetDecision() {
		return m_decision;
	}
}
//end namespace basecross