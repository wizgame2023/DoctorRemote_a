/*!
@file StageManager.cpp
@brief ステージ全体の処理等
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"


namespace basecross {
	StageManager::StageManager(const shared_ptr<Stage>& stagePtr) :
		GameObject(stagePtr),
		m_currentHp(100.0f),
		m_maxHp(100.0f),
		m_hpSpeed(3.0f),
		m_ligthStatus(0),
		m_count(4.0f),
		m_stageFlag(0),
		m_comX(800.0f),
		m_start(false),
		m_countNumFlag(false),
		m_cfFlag(false),
		m_comFlag(false),
		m_comFlag2(false),
		m_countFlag(false),
		m_enemyFlag(false)

	{}


	void StageManager::OnCreate() {
		auto stage = GetStage();

		auto uiManager = stage->AddGameObject<UIManager>();//UIを管理するマネージャー
		stage->SetSharedGameObject(L"UIManager", uiManager);
		//画面上のライト
		//stage->AddGameObject<Sprite>(1280, 800, L"Ligth2", Vec3(), 0);

		//m_PieceStatus = App::GetApp()->GetScene<Scene>()->GetBigPieceUp();
		//switch (m_PieceStatus)
		//{
		//case 0:
		//	stage->AddGameObject<Sprite>(1280, 800, L"Ligth", Vec3(),0);
		//	break;
		//case 1:
		//	stage->AddGameObject<Sprite>(1280, 800, L"Ligth2", Vec3(),0);
		//	break;
		//case 2:
		//	stage->AddGameObject<Sprite>(1280, 800, L"Ligth3", Vec3(),0);
		//	break;
		//default:
		//	break;
		//}


	}
	void StageManager::OnUpdate() {
		auto stage = GetStage();
		auto& scene = App::GetApp()->GetScene<Scene>();
		float elapsedTime = App::GetApp()->GetElapsedTime();

		if (m_countFlag)
		{
			if (scene->GetGameStage() > 0) {
				//カウントダウンの表示
				m_count -= elapsedTime;
				if (m_count > 1) {
					if (!m_countNumFlag) {
						m_num = stage->AddGameObject<UITime>((int)m_count, Vec3(-120.0f, 120.0f, 0.0f), 240.0f, 480.0f);
						m_num->SetColor(Col4(1.0f, 1.0f, 1.0f, 1.0f));
						m_countNumFlag = true;
					}
					m_num->UpdateValue(m_count);

				}
				if (m_count < 1) {
					m_num->ThisDestory();
					if (!m_start && m_stageFlag <= 1) {
						m_startSprite = GetStage()->AddGameObject<Sprite>(500, 500, L"Start", Vec3());					
					}
					m_start = true;

					if (m_count <= 0) return;//カウントが０秒より少なかった場合リターンする
					if (m_count < 0.1f) {			
						m_startSprite->ThisDestory();
					}
				}

			}

		}


		//体力が0になったらGameOver
		if (m_currentHp <= 0.0f) {
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");
		}

		//デバック用
		//wstringstream wss(L"");
		//auto scene = App::GetApp()->GetScene<Scene>();
		//wss << L"currentHp : " <<
		//	m_currentHp <<
		//	"\n" <<
		//	endl;
		//auto dstr = scene->GetDebugString();
		//scene->SetDebugString(dstr + wss.str());
	}

	int StageManager::GetStageFlag()
	{
		return m_stageFlag;
	}
	float StageManager::GetHp() {
		return m_currentHp;
	}
	float StageManager::GetHpRatio() {
		auto ratio = m_currentHp / m_maxHp;
		return ratio;
	}
	void StageManager::SetHp(float hp) {
		m_currentHp += hp;
	}
	bool StageManager::GetCountFlag() {
		return m_countFlag;
	}
	void StageManager::SetCountFlag(bool OnOff) {
		m_countFlag = OnOff;
	}
	void StageManager::SetCareerFlag(int Flag)
	{
		m_stageFlag = Flag;
	}
	bool StageManager::GetStartFlag() {
		return m_start;
	}
	void StageManager::SetStartFlag(bool start) {
		m_start = start;
	}
	bool StageManager::GetComFrameFlag() {
		return m_cfFlag;
	}
	void StageManager::SetComFrameFlag(bool cfFlag){
		m_cfFlag = cfFlag;
	}
	bool StageManager::GetEnemyFlag() {
		return m_enemyFlag;
	}
	void StageManager::SetEnemyFlag(bool enemy) {
		m_enemyFlag = enemy;
	}
}
//end namespace basecross