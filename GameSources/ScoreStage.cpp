/*!
@file ClearStage.cpp
@brief スコアステージ実体
担当:ちなみ
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void ScoreStage::CreateViewLight() {
		auto ptrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto ptrMyCamera = ObjectFactory::Create<Camera>();
		ptrView->SetCamera(ptrMyCamera);
		ptrMyCamera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
		ptrMyCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//マルチライトの作成
		auto ptrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		ptrMultiLight->SetDefaultLighting();

		m_mojispeed = 0.05f;
		m_mojispeed1 = 0.1f;
	}

	void ScoreStage::OnCreate() {
		try {
			//BGM
			BaseBGM();
			auto& scene = App::GetApp()->GetScene<Scene>();

			PieceManager::enemyPieces.clear();
			//前のステージを取得
			m_stageCount = scene->GetGameStage();
			scene->SetGameStage(0);
			scene->SetPlayFlag(false);


			CreateViewLight();
			auto stage = scene->GetGameStage();
			scene->SetFirstTimeStage(m_stageCount);

			AddGameObject<Sprite>(1280, 800, L"ScoreWaku", Vec3(), -1);

			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[0].bConnected) {
				auto moji = AddGameObject<Comment>(9, 0, 0.1f, 270, 40, 270, 40, 9, 1,
					Vec3(325.0f, 360.0f, 0.0f), L"ResultMoji4"); //「Aボタンでスキップ」を表示
			}
			else {
				auto moji = AddGameObject<Sprite>(100, 100, L"SButton", Vec3(440.0f, 330.0f, 0.0f)); //S
				auto moji2 = AddGameObject<Sprite>(100, 100, L"Skip", Vec3(520.0f, 330.0f, 0.0f)); // 「スキップ」
			}

			m_time = App::GetApp()->GetScene<Scene>()->GetTime();
		}
		catch (...) {
			throw;
		}
	}

	void ScoreStage::BaseBGM()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"ScoreBGM", XAUDIO2_LOOP_INFINITE, 0.2f);
	}

	void ScoreStage::OnUpdate()
	{
		App::GetApp()->GetScene<Scene>()->ResetButton();
		auto scene = App::GetApp()->GetScene<Scene>();
		float delta = App::GetApp()->GetElapsedTime();//デルタタイムを取得
		auto keyState = App::GetApp()->GetInputDevice().GetKeyState();
		m_countUp += 1 * delta;
		StageChange();

		if (m_control == 0)
		{
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A || keyState.m_bPressedKeyTbl['S']) //Aボタンが押されたらスキップ(カウントを10秒プラス)する
			{
				m_mojispeed = 0.0f;
				m_mojispeed1 = 0.0f;
				m_countUp += 12;
				auto choiceSE = App::GetApp()->GetXAudio2Manager();
				choiceSE->Start(L"ChoiceSE", 0, 0.4f);

			}

			//スコアステージが生成されてから1秒後に、「レコード」を表示
			if (m_countUp >= 1.0f && m_timeCount == 0)
			{
				auto moji = AddGameObject<Comment>(4, 0, m_mojispeed1, 400, 90, 400, 90, 4, 1,
					Vec3(-550.0f, 350.0f, 0.0f), L"ResultMoji1"); //「レコード」を表示
				m_timeCount++;
			}

			//スコアステージが生成されてから2秒後に、「タイム」を表示
			else if (m_countUp >= 2.0f && m_timeCount == 1)
			{
				auto moji = AddGameObject<Comment>(4, 0, m_mojispeed1, 512, 512, 450, 450, 7, 1,
					Vec3(-570.0f, 235.0f, 0.0f), L"ScoreComment"); // 「タイム：」を表示
				m_timeCount++;
			}

			//スコアステージが生成されてから3秒後で、ゴールするまでにかかった時間を表示
			else if (m_countUp >= 3.0f && m_timeCount == 2)
			{
				AddGameObject<TimeManager>(m_time, Vec3(-300, 243, 0));
				m_timeCount++;
			}

			//スコアステージが生成されてから4秒後で、枠を表示
			else if (m_countUp >= 4.0f && m_timeCount == 3)
			{
				AddGameObject<Sprite>(600, 430, L"ResultWaku", Vec3(-280, -60.0f, 0.0f)); // 枠を表示
				m_timeCount++;
			}			

			//スコアステージが生成されてから4秒後で、評価の文字を表示
			else if (m_countUp >= 4.0f && m_timeCount == 4)
			{
				auto moji2 = AddGameObject<CommentManager>(35, 0, m_mojispeed, 512, 512, 370, 370, 11, 5, //評価の文字を表示
					Vec3(-560.0f, 137.0f, 0.0f), L"IfClear");
				m_timeCount++;
			}

			//スコアステージが生成されてから7秒後で、ステージクリアした時の残りタイムが50秒以上だったら表示
			else if (m_time >= 180 && m_countUp >= 7.0f && m_timeCount == 5)
			{
				auto moji3 = AddGameObject<CommentManager>(16, 0, m_mojispeed1, 512, 512, 450, 450, 5, 5, //チェックを4つ表示
					Vec3(-112.0f, 155.0f, 0.0f), L"CheckMark");
				m_timeCount++;
			}
			//スコアステージが生成されてから7秒後で、ステージクリアした時の残りタイムが40秒以上だったら表示
			else if (m_time >= 120 && m_time < 180 && m_countUp >= 7.0f && m_timeCount == 5)
			{
				auto moji3 = AddGameObject<CommentManager>(16, 1, m_mojispeed1, 512, 512, 450, 450, 5, 5, //チェックを3つ表示
					Vec3(-112.0f, 155.0f, 0.0f), L"CheckMark");
				m_timeCount++;
			}
			//スコアステージが生成されてから7秒後で、ステージクリアした時の残りタイムが25秒以上だったら表示
			else if (m_time >= 90 && m_time < 120 && m_countUp >= 7.0f && m_timeCount == 5)
			{
				auto moji3 = AddGameObject<CommentManager>(14, 2, m_mojispeed1, 512, 512, 450, 450, 5, 5, //チェックを2つ表示
					Vec3(-112.0f, 155.0f, 0.0f), L"CheckMark");
				m_timeCount++;
			}
			//スコアステージが生成されてから7秒後で、ステージクリアしたら表示
			else if (m_time < 90 && m_countUp >= 7.0f && m_timeCount == 5)
			{
				auto moji3 = AddGameObject<Comment>(16, 3, m_mojispeed1, 512, 512, 450, 450, 5, 5, //チェックを1つ表示
					Vec3(-112.0f, 155.0f, 0.0f), L"CheckMark");
				m_timeCount++;
			}

			//スコアステージが生成されてから9秒後で、「合計」を表示
			else if (m_countUp >= 9.0f && m_timeCount == 6)
			{
				auto moji3 = AddGameObject<Comment>(2, 0, 0.1f, 120, 50, 120, 55, 2, 1, //「合計」を表示
					Vec3(-410.0f, -200.0f, 0.0f), L"ResultMoji3");
				m_timeCount++;
			}

			//スコアステージが生成されてから10秒後で、ステージクリアした時の残りタイムが3分以上だったらポイント「80」を表示
			else if (m_time >= 180 && m_countUp >= 10.0f && m_timeCount == 7)
			{
				auto rank = AddGameObject<Sprite>(100, 100, L"Point", Vec3(-58.0f, -223.0f, 0.0f));//「80」を表示
				rank->UpdateIfClear(0);
				m_achievementPoint += 80;//80成果(achievement)ポイント獲得  
				m_timeCount++;
			}
			//スコアステージが生成されてから10秒後で、ステージクリアした時の残りタイムが2分秒以上だったらポイント「60」を表示
			else if (m_time >= 120 && m_time < 180 && m_countUp >= 10.0f && m_timeCount == 7)
			{
				auto rank = AddGameObject<Sprite>(100, 100, L"Point", Vec3(-60.0f, -228.0f, 0.0f));//「60」を表示
				rank->UpdateIfClear(1);
				m_achievementPoint += 60;//60成果(achievement)ポイント獲得
				m_timeCount++;
			}
			//スコアステージが生成されてから10秒後で、ステージクリアした時の残りタイムが1分30秒以上だったらポイント「40」を表示
			else if (m_time >= 90 && m_time < 120 && m_countUp >= 10.0f && m_timeCount == 7)
			{
				auto rank = AddGameObject<Sprite>(100, 100, L"Point", Vec3(-59.0f, -230.0f, 0.0f));//「40」を表示 
				rank->UpdateIfClear(2);
				m_achievementPoint += 40;//40成果(achievement)ポイント獲得
				m_timeCount++;
			}
			//スコアステージが生成されてから10秒後で、ステージクリアしたらポイント「20」を表示
			else if (m_time < 90 && m_countUp >= 10.0f && m_timeCount == 7)
			{
				auto rank = AddGameObject<Sprite>(100, 100, L"Point", Vec3(-60.0f, -225.0f, 0.0f));//「20」を表示
				rank->UpdateIfClear(3);
				m_achievementPoint += 20;//20成果(achievement)ポイント獲得
				m_timeCount++;
			}

			//スコアステージが生成されてから11秒後で、文字を表示
			else if (m_countUp >= 11.0f && m_timeCount == 8)
			{
				auto moji = AddGameObject<Comment>(11, 0, m_mojispeed1, 420, 40, 340, 40, 11, 1,
					Vec3(-570.0f, -295.0f, 0.0f), L"ResultMoji5"); // 「壊した大きいウイルス」を表示
				m_timeCount++;
			}
			//スコアステージが生成されてから13秒後で、大きい欠片を何個壊したかを表示
			else if (m_countUp >= 13.0f && m_timeCount == 9)
			{
				int count = scene->GetBigPieceCount();
				auto rank = AddGameObject<Sprite>(65, 70, L"CountMoji", Vec3(-210.0f, -312.0f, 0.0f));
				rank->UpdateCount(count);
				m_timeCount++;
			}
			//スコアステージが生成されてから14秒後で、壊したウイルスの数に応じてポイントを表示
			else if (m_countUp >= 14.0f && m_timeCount == 10)
			{
				int kakeracount = scene->GetBigPieceCount();
				auto rank = AddGameObject<Sprite>(100, 100, L"KakeraPoint", Vec3(-60.0f, -315.0f, 0.0f));
				auto plus = AddGameObject<Sprite>(90, 130, L"Plus", Vec3(-115.0f, -315.0f, 0.0f));
				rank->UpdatePoint(kakeracount);

				if (kakeracount == 1) {
					m_achievementPoint += 5;
				}
				if (kakeracount == 2) {
					m_achievementPoint += 10;
				}
				if (kakeracount == 3) {
					m_achievementPoint += 15;
				}
				if (kakeracount == 4) {
					m_achievementPoint += 20;
				}
				if (kakeracount == 5) {
					m_achievementPoint += 25;
				}
				if (kakeracount == 6) {
					m_achievementPoint += 30;
				}

				//ゲームステージのみポイントを加算
				if (m_stageCount > 0) {
					scene->AddAchievementPoint(m_achievementPoint);
				}
				m_timeCount++;
			}

			//スコアステージが生成されてから15秒後で、ステージクリアした時の残り時間が3分以上だったら「S」を表示
			else if (m_time >= 180 && m_countUp >= 15.0f && m_timeCount == 11)
			{
				auto rank = AddGameObject<Sprite>(400, 400, L"Rank", Vec3(270, 0, 0));
				rank->UpdateRank(0);
				m_timeCount++;
				m_control++;

				ScoreSE();
			}
			//スコアステージが生成されてから15秒後で、ステージクリアした時の残り時間が2分以上だったら「A」を表示
			else if (m_time >= 120 && m_time < 180 && m_countUp >= 15.0f && m_timeCount == 11)
			{
				auto rank = AddGameObject<Sprite>(400, 400, L"Rank", Vec3(350, 0, 0));
				rank->UpdateRank(1);
				m_timeCount++;
				m_control++;

				ScoreSE();
				}
			//スコアステージが生成されてから15秒後で、ステージクリアした時の残り時間が1分30秒以上だったら「B」を表示
			else if (m_time >= 90 && m_time < 120 && m_countUp >= 15.0f && m_timeCount == 11)
			{
				auto rank = AddGameObject<Sprite>(400, 400, L"Rank", Vec3(350, 0, 0));
				rank->UpdateRank(2);
				m_timeCount++;
				m_control++;

				ScoreSE();
			}
			//スコアステージが生成されてから15秒後で、ステージクリアしたら「C」を表示
			else if (m_time < 90 && m_countUp >= 15.0f && m_timeCount == 11)
			{
				auto rank = AddGameObject<Sprite>(400, 400, L"Rank", Vec3(350, 0, 0));
				rank->UpdateRank(3);
				m_timeCount++;
				m_control++;

				ScoreSE();
			}
		}
		//スコアステージが生成されてから16秒後に「Bボタンで次へ」を表示
		else if (m_control == 1 && m_countUp >= 16.0f)
		{
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[0].bConnected) {
				auto moji3 = AddGameObject<Comment>(7, 0, 0.1f, 280, 64, 256, 64, 7, 1, // Bボタンで次へ
				Vec3(340.0f, -300.0f, 0.0f), L"ResultMoji2");
			}
			else {
				auto spaceMoji = AddGameObject<Sprite>(150, 75, L"SpaceButton", Vec3(530.0f, -330.0f, 0.0f)); // Space
			}
			m_timeCount++;
			m_control++;
		}
		//int test = scene->GetAchievementPoint();//デバック用変数
		//wstringstream wss(L"");
		//wss << test << "\n" << test << endl;

		//scene->SetDebugString(wss.str());
	}

	void ScoreStage::OnDestroy()
	{
		auto scene = App::GetApp()->GetScene<Scene>();
		m_count = scene->GetBigPieceCount();
		scene->SetBigPieceCount(0);
		scene->GetBigPieceCount();
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	void ScoreStage::StageChange() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto keyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (m_countUp >= 17.0f && cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B || m_countUp >= 17.0f && keyState.m_bPressedKeyTbl[VK_SPACE])
		{
			if (m_stageCount == 0) {
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStartStage");
			}
			else if (m_stageCount <= 11) {
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStatusStage");
			}
			else if (m_stageCount == 12) {
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToClearStage");
			}
			if (!m_SEFlag) {
				auto choiceSE = App::GetApp()->GetXAudio2Manager();
				choiceSE->Start(L"ChoiceSE", 0, 0.4f);
				m_SEFlag = true;
			}
		}
	}
	void ScoreStage::ScoreSE() {
		auto scoreSE = App::GetApp()->GetXAudio2Manager();
		scoreSE->Start(L"ScoreSE", 0, 0.3f);
	}
}