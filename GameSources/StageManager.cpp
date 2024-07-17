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
		m_enemyFlag(false),
		m_StartDestoryFlag(false),
		m_startSEFlag(false)

	{}


	void StageManager::OnCreate() {
		auto stage = GetStage();

		auto uiManager = stage->AddGameObject<UIManager>();//UIを管理するマネージャー
		stage->SetSharedGameObject(L"UIManager", uiManager);	

		m_blackout = GetStage()->AddGameObject<Sprite>(1280, 800, L"Black", Vec3(0, 0, 0));//暗転生成
		m_blackout->SetColor(Col4(0.0f, 0.0f, 0.0f, 0.0f));
		m_outCol = m_blackout->GetColor();


	}
	void StageManager::OnUpdate() {
		App::GetApp()->GetScene<Scene>()->ResetButton();
		auto stage = GetStage();
		auto& scene = App::GetApp()->GetScene<Scene>();
		float elapsedTime = App::GetApp()->GetElapsedTime();

		m_currentHp;//デバック用
		int a = 0;//デバック用のコード
		//体力が0になったらGameOver
		if (m_currentHp <= 0.0f) {
			dynamic_pointer_cast<MainCamera>(OnGetDrawCamera())->SetMove(false);//カメラを操作できるようになる
			GetStage()->GetSharedGameObject<Player>(L"GamePlayer")->SetSpeed(0.0f);//Playerの慣性を消す
			stage->GetSharedGameObject<StageManager>(L"StageManager")->SetStartFlag(false);//Playerの操作を効かなくさせる

			m_outCol.w += elapsedTime * 0.4f;//暗転する
			m_blackout->SetColor(m_outCol);
			if (m_outCol.w >= 1)
			{
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");
				int test = m_currentHp;
				int s = 0;
			}
		}

		if (m_countFlag)
		{
			if (scene->GetGameStage() > 0) {
				//カウントダウンの表示
				if (!m_StartDestoryFlag)
				{
					m_count -= elapsedTime;

				}
				else
				{
					m_count = 4.0f;
				}
				if (m_count > 1) {
					if (!m_countNumFlag) {
						m_num = stage->AddGameObject<UITime>((int)m_count, Vec3(-120.0f, 120.0f, 0.0f), 240.0f, 480.0f, Col4(1.0f));
						m_num->SetColor(Col4(1.0f, 1.0f, 1.0f, 1.0f));
						m_countNumFlag = true;//１回しか通らないようにする
						m_stageSprite = stage->AddGameObject<Sprite>(300, 300, L"Stage", Vec3(0.0f,200.0f,0.0f));
						m_stageNum = stage->AddGameObject<UITime>(scene->GetGameStage(), Vec3(120.0f, 250.0f, 0.0f), 60, 120, L"Numbers10", Col4(1.0f));
					}
					m_num->UpdateValue((int)m_count);

					if (!m_startSEFlag) {
						auto soundE = App::GetApp()->GetXAudio2Manager();
						soundE->Start(L"CountDownSE", 0, 0.8f);
						m_startSEFlag = true;
					}

				}
				if (m_count < 1) {
					m_num->ThisDestroy();
					m_stageSprite->ThisDestroy();
					m_stageNum->ThisDestroy();
					if (!m_start && m_stageFlag <= 1) {
						m_startSprite = GetStage()->AddGameObject<Sprite>(500, 500, L"Start", Vec3());		
						m_StartDestoryFlag = false;
					}
					m_start = true;

					if (m_count < 0.1f && !m_StartDestoryFlag) {
						m_startSprite->ThisDestroy();
						m_StartDestoryFlag = true;
					}
				}

			}

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