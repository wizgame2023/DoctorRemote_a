/*!
@file TimeManager.cpp
@brief 時間の表示
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	TimeManager::TimeManager(const shared_ptr<Stage>& stagePtr):
		GameObject(stagePtr),
		m_time(300.0f),
		m_move(true),
		m_SEFlag(false),
		m_pos(-535, 85, 0.0f)
	{}
	TimeManager::TimeManager(const shared_ptr<Stage>& stagePtr,int time,Vec3 pos) :
		GameObject(stagePtr),
		m_time(time),
		m_move(false),
		m_pos(pos)
	{}


	void TimeManager::OnCreate() {
		auto stage = GetStage();

		float sw = App::GetApp()->GetGameWidth();
		float sh = App::GetApp()->GetGameHeight();
		//Vec3 screen(-105.0f, sh * 0.5, 0.0f);
		//Vec3 dis(15.0f, -10.0f, 0);
		//Vec3 pos = screen + dis;
		Vec3 pos1(m_pos.x + 40, m_pos.y, m_pos.z);
		Vec3 posTen(m_pos.x + 70, m_pos.y, m_pos.z);
		Vec3 pos2(m_pos.x + 100, m_pos.y, m_pos.z);
		Vec3 pos3(m_pos.x + 140, m_pos.y, m_pos.z);

		m_firstNum = stage->AddGameObject<UITime>(m_first,pos3);
		m_secondNum = stage->AddGameObject<UITime>(m_seconds, pos2);
		m_thirdNum = stage->AddGameObject<UITime>(m_third, pos1);
		m_fourthNum = stage->AddGameObject<UITime>(m_fourth, m_pos);
		m_ten = stage->AddGameObject<UITime>(m_fourth, posTen);

		m_blackout = GetStage()->AddGameObject<Sprite>(1280, 800, L"Black", Vec3(0, 0, 0));//スプライトを表示
		m_blackout->SetColor(Col4(0.0f, 0.0f, 0.0f, 0.0f));
		m_outCol = m_blackout->GetColor();
	}
	void TimeManager::OnUpdate() {
		auto lastCol = Col4(1.0f, 0.0f, 0.0f, 1.0f);

		if (m_move) {
			float elapsedTime = App::GetApp()->GetElapsedTime();
			bool start = GetStage()->GetSharedGameObject<StageManager>(L"StageManager")->GetStartFlag();
			auto a = start;
			if (start) {
				if (m_time >= 0)
				{
					m_time -= elapsedTime;

				}
				//if (m_time <= 0.0f) {
				//	PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");
				//}
			}
		}
		if (m_time <= 60.0f && App::GetApp()->GetScene<Scene>()->GetGameStage() != 0) {

			if (m_firstNum->GetOnOff() == true)return;//透明になっているとき強制的に赤にならないようにする

			m_firstNum->SetColor(lastCol);
			m_secondNum->SetColor(lastCol);
			m_thirdNum->SetColor(lastCol);
			m_fourthNum->SetColor(lastCol);
			m_ten->SetColor(lastCol);
			//効果音
			if (!m_SEFlag) {
				auto Keikoku = App::GetApp()->GetXAudio2Manager();
				Keikoku->Start(L"KeikokuSE", 0, 1.5f);
				m_SEFlag = true;
			}

		}

		if (m_time <= 0.0f) {
			float elapsedTime = App::GetApp()->GetElapsedTime();

			dynamic_pointer_cast<MainCamera>(OnGetDrawCamera())->SetMove(false);//カメラが動かないようにする
			GetStage()->GetSharedGameObject<Player>(L"GamePlayer")->SetSpeed(0.0f);//Playerの速度を0にする
			GetStage()->GetSharedGameObject<StageManager>(L"StageManager")->SetStartFlag(false);//Playerを動かないようにする
			if (m_outCol.w <= 0)//GameOver条件を達成した１回のみ発動させる(この条件式は１回しか使えないため使用)
			{
				auto pieceSE = App::GetApp()->GetXAudio2Manager();
				pieceSE->Start(L"PlayerbreakSE", 0, 1.5f);
			}

			m_outCol.w += elapsedTime * 0.4f;//だんだんと暗転する
			m_blackout->SetColor(m_outCol);
			if (m_outCol.w >= 1)
			{
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");
			}
		}

		int minutes = m_time / 60;
		int seconds = (int)m_time % 60;
		m_first = seconds % 10;
		m_second = (seconds / 10) % 10;
		m_third = minutes % 10;
		m_fourth = (minutes / 10) % 10;


		m_firstNum->UpdateValue(m_first);
		m_secondNum->UpdateValue(m_second);
		m_thirdNum->UpdateValue(m_third);
		m_fourthNum->UpdateValue(m_fourth);
		m_ten->UpdateValue(10);

		App::GetApp()->GetScene<Scene>()->SetTime(m_time);

		//デバック用
		//wstringstream wss(L"");
		//auto scene = App::GetApp()->GetScene<Scene>();

		//wss <<L"time : "
		//	<<m_time
		//	<<"\n"
		//	<< L"minutes : "
		//	<< minutes
		//	<< "\n"
		//	<< L"second : "
		//	<< seconds
		//	<<"\n"
		//	<<"Time : "
		//	<<m_fourth
		//	<<m_third
		//	<<L":"
		//	<<m_second
		//	<<m_first
		//	<< endl;


		//wss << m_time << endl;

		//auto dstr = scene->GetDebugString();
		//scene->SetDebugString(dstr + wss.str());

	}

	void TimeManager::UpdateNumber() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_time -= elapsedTime;

		int minutes = m_time / 60;
		int seconds = (int)m_time % 60;
		m_first = seconds % 10;
		m_second = (seconds / 10) % 10;
		m_third = minutes % 10;
		m_fourth = (minutes / 10) % 10;

	}

	void TimeManager::SetTimeFlag(bool timeFlag) {
		m_move = timeFlag;
	}
}
//end namespace basecross