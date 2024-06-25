/*!
@file ClearStage.cpp
@brief スコアステージ実体
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
			PieceManager::enemyPieces.clear();
			//App::GetApp()->GetScene<Scene>()->SetGameStage(-1);
			App::GetApp()->GetScene<Scene>()->SetPlayFlag(false);


			//何回クリアしたか
			auto& scene = App::GetApp()->GetScene<Scene>();
			m_stageCount = scene->GetGameStage();
			scene->SetGameStage(m_stageCount);

			CreateViewLight();

			AddGameObject<Sprite>(1280, 800, L"ScoreWaku", Vec3(), -1);
			auto moji = AddGameObject<Comment>(9, 0, 0.1f, 270, 40, 270, 40, 9, 1,
				Vec3(325.0f, 360.0f, 0.0f), L"ResultMoji4"); //「Aボタンでスキップ」を表示
			m_time = App::GetApp()->GetScene<Scene>()->GetTime();
		}
		catch (...) {
			throw;
		}
	}

	void ScoreStage::OnUpdate()
	{
		auto scene = App::GetApp()->GetScene<Scene>();
		float delta = App::GetApp()->GetElapsedTime();//デルタタイムを取得
		m_countUp += 1 * delta;
		StageChange();

		if (m_control == 0)
		{			
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) //Aボタンが押されたらスキップ(カウントを10秒プラス)する
			{
				m_mojispeed = 0.0f;
				m_mojispeed1 = 0.0f;
				m_countUp+= 10;
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

			//スコアステージが生成されてから4秒後で、文字を表示
			else if (m_countUp >= 4.0f && m_timeCount == 3)
			{
				auto moji = AddGameObject<Comment>(11, 0, m_mojispeed1, 420, 40, 420, 40, 11, 1,
					Vec3(-570.0f, 150.0f, 0.0f), L"ResultMoji5"); // 「壊した大きいウイルス」を表示
				m_timeCount++;
			}

			//スコアステージが生成されてから6秒後で、大きい欠片を何個壊したかを表示
			else if (m_countUp >= 6.0f && m_timeCount == 4)
			{
				int count = scene->GetBigPieceCount();
				auto moji = AddGameObject<Comment>(1, count, m_mojispeed1, 40, 420, 55, 600, 1, 9,
					Vec3(-150.0f, 160.0f, 0.0f), L"CountMoji");
				m_timeCount++;
			}

			//スコアステージが生成されてから7秒後で、枠を表示
			else if (m_countUp >= 7.0f && m_timeCount == 5)
			{
				AddGameObject<Sprite>(500, 430, L"ResultWaku", Vec3(-345, -135.0f, 0.0f)); // 枠を表示
				m_timeCount++;
			}			

			//スコアステージが生成されてから8秒後で、評価の文字を表示
			else if (m_countUp >= 8.0f && m_timeCount == 6)
			{
				auto moji2 = AddGameObject<CommentManager>(27, 0, m_mojispeed, 512, 512, 340, 370, 9, 5, //評価の文字を表示
					Vec3(-576.0f, 59.0f, 0.0f), L"IfClear");
				m_timeCount++;
			}

			//スコアステージが生成されてから9秒後で、ステージクリアした時の残りタイムが50秒以上だったら表示
			else if (m_time >= 50 && m_countUp >= 9.0f && m_timeCount == 7)
			{
				auto moji3 = AddGameObject<CommentManager>(16, 0, m_mojispeed1, 512, 512, 450, 450, 5, 5, //チェックを4つ表示
					Vec3(-208.0f, 80.0f, 0.0f), L"CheckMark");
				m_timeCount++;
			}
			//スコアステージが生成されてから9秒後で、ステージクリアした時の残りタイムが40秒以上だったら表示
			else if (m_time >= 40 && m_time < 50 && m_countUp >= 9.0f && m_timeCount == 7)
			{
				auto moji3 = AddGameObject<CommentManager>(16, 1, m_mojispeed1, 512, 512, 450, 450, 5, 5, //チェックを3つ表示
					Vec3(-208.0f, 162.0f, 0.0f), L"CheckMark");
				m_timeCount++;
			}
			//スコアステージが生成されてから9秒後で、ステージクリアした時の残りタイムが25秒以上だったら表示
			else if (m_time >= 25 && m_time < 40 && m_countUp >= 9.0f && m_timeCount == 7)
			{
				auto moji3 = AddGameObject<CommentManager>(14, 2, m_mojispeed1, 512, 512, 450, 450, 5, 5, //チェックを2つ表示
					Vec3(-208.0f, 82.0f, 0.0f), L"CheckMark");
				m_timeCount++;
			}
			//スコアステージが生成されてから9秒後で、ステージクリアしたら表示
			else if (m_time < 25 && m_countUp >= 9.0f && m_timeCount == 7)
			{
				auto moji3 = AddGameObject<Comment>(16, 3, m_mojispeed1, 512, 512, 450, 450, 5, 5, //チェックを1つ表示
					Vec3(-208.0f, 80.0f, 0.0f), L"CheckMark");
				m_timeCount++;
			}

			//スコアステージが生成されてから10秒後で、合計を表示
			else if (m_countUp >= 10.0f && m_timeCount == 8)
			{
				auto moji3 = AddGameObject<Comment>(2, 0, 0.1f, 256, 64, 200, 55, 4, 1, //合計を表示
					Vec3(-450.0f, -278.0f, 0.0f), L"ResultMoji3");
				m_timeCount++;
			}

			//スコアステージが生成されてから11秒後で、ステージクリアした時の残りタイムが50秒以上だったらポイント「100」を表示
			else if (m_countUp >= 11.0f && m_timeCount == 9) //m_time >= 50 && 
			{
				auto rank = AddGameObject<Sprite>(100, 100, L"Point", Vec3(-160.0f, -297.0f, 0.0f));//「100」を表示
				rank->UpdateIfClear(0);
				m_timeCount++;
			}
			//スコアステージが生成されてから11秒後で、ステージクリアした時の残りタイムが40秒以上だったらポイント「75」を表示
			else if (m_time >= 40 && m_time < 50 && m_countUp >= 11.0f && m_timeCount == 9)
			{
				auto rank = AddGameObject<Sprite>(100, 100, L"Point", Vec3(-162.0f, -304.0f, 0.0f));//「75」を表示
				rank->UpdateIfClear(1);
				m_timeCount++;
			}
			//スコアステージが生成されてから11秒後で、ステージクリアした時の残りタイムが25秒以上だったらポイント「50」を表示
			else if (m_time >= 25 && m_time < 40 && m_countUp >= 11.0f && m_timeCount == 9)
			{
				auto rank = AddGameObject<Sprite>(100, 100, L"Point", Vec3(-160.0f, -304.0f, 0.0f));//「50」を表示 
				rank->UpdateIfClear(2);
				m_timeCount++;
			}
			//スコアステージが生成されてから11秒後で、ステージクリアしたらポイント「25」を表示
			else if (m_time < 25 && m_countUp >= 11.0f && m_timeCount == 9)
			{
				auto rank = AddGameObject<Sprite>(100, 100, L"Point", Vec3(-160.0f, -301.0f, 0.0f));//「25」を表示
				rank->UpdateIfClear(3);
				m_timeCount++;
			}

			//スコアステージが生成されてから12秒後で、ステージクリアした時の残り時間が50秒以上だったら「S」を表示
			else if (m_time >= 50 && m_countUp >= 12.0f && m_timeCount == 10)
			{
				auto rank = AddGameObject<Sprite>(400, 400, L"Rank", Vec3(270, 0, 0));
				rank->UpdateRank(0);
				m_timeCount++;
				m_achievementPoint += 100;//100成果(achievement)ポイント獲得
				m_control++;
			}
			//スコアステージが生成されてから12秒後で、ステージクリアした時の残り時間が40秒以上だったら「A」を表示
			else if (m_time >= 40 && m_time < 50 && m_countUp >= 12.0f && m_timeCount == 10)
			{
				auto rank = AddGameObject<Sprite>(400, 400, L"Rank", Vec3(350, 0, 0));
				rank->UpdateRank(1);
				m_timeCount++;
				m_achievementPoint += 75;//75成果(achievement)ポイント獲得
				m_control++;
			}
			//スコアステージが生成されてから12秒後で、ステージクリアした時の残り時間が25秒以上だったら「B」を表示
			else if (m_time >= 25 && m_time < 40 && m_countUp >= 12.0f && m_timeCount == 10)
			{
				auto rank = AddGameObject<Sprite>(400, 400, L"Rank", Vec3(350, 0, 0));
				rank->UpdateRank(2);
				m_timeCount++;
				m_achievementPoint += 50;;//50成果(achievement)ポイント獲得
				m_control++;
			}
			//スコアステージが生成されてから12秒後で、ステージクリアしたら「C」を表示
			else if (m_time < 25 && m_countUp >= 12.0f && m_timeCount == 10)
			{
				auto rank = AddGameObject<Sprite>(400, 400, L"Rank", Vec3(350, 0, 0));
				rank->UpdateRank(3);
				m_timeCount++;
				m_achievementPoint += 25;;//25成果(achievement)ポイント獲得
				m_control++;
			}
			scene->SetAchievementPoint(m_achievementPoint);
		}
		//スコアステージが生成されてから6秒後に「Bボタンで次へ」を表示
		else if (m_control == 1 && m_countUp >= 13.0f)
		{
			auto moji3 = AddGameObject<Comment>(7, 0, 0.1f, 256, 64, 256, 64, 7, 1, // Bボタンで次へ
			Vec3(340.0f, -300.0f, 0.0f), L"ResultMoji2");
			m_timeCount++;
			m_control++;
		}
		//int test = scene->GetAchievementPoint();//デバック用変数
		//wstringstream wss(L"");
		//wss << m_countUp << "\n" << test << endl;

		//scene->SetDebugString(wss.str());
	}

	void ScoreStage::OnDestroy()
	{
		auto scene = App::GetApp()->GetScene<Scene>();
		m_count = scene->GetBigPieceCount();
		scene->SetBigPieceCount(-m_count);
		scene->GetBigPieceCount();
	}

	void ScoreStage::StageChange() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].bConnected)
		{
			if (m_countUp >= 14.0f && cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
			{
				switch (m_stageCount)
				{
				case 0:
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStartStage");
					break;
				case 1:
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStatusStage");
					break;
				case 2:
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStartStage");
					break;
				case 3:
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStartStage");
					break;
				default:
					break;
				}
			}
		}
	}
}