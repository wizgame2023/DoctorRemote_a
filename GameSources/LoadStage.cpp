/*!
@file ClearStage.cpp
@brief クリアステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void LoadStage::CreateViewLight() {
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

		m_comX = -580.0f;
		m_flag = false;
	}
	void LoadStage::OnCreate() {
		try {
			App::GetApp()->GetScene<Scene>()->SetGameStage(-1);

			//ビューとライトの作成
			CreateViewLight();
			AddGameObject<Sprite>(1280, 800, L"LoadScene", Vec3(0, 0, 0), -1);
			m_sprite = AddGameObject<Sprite>(70, 50, L"Sensuikan", Vec3(m_comX, -300, 0));
			m_comment = AddGameObject<Comment>(6, 0, 0.2f, 400, 100, 200, 50, 6, 1,
				Vec3(400.0f, -335.0f, 0.0f), L"LoadMoji2", true); // 「移動中...」

			m_blackBoard = AddGameObject<Sprite>(1280, 800, L"Black", Vec3(0, 0, 0), 4);
			m_blackBoard->SetColor(Col4(1, 1, 1, 0));

		}
		catch (...) {
			throw;
		}
	}
	void LoadStage::OnUpdate() {
		StageChange();

		float delta = App::GetApp()->GetElapsedTime();
		m_countUp += 1 * delta;
		StageChange();

		if (m_count == 0)
		{
			//スコアステージが生成されてから1秒後に、コメントを表示
			if (m_countUp >= 1.0f && m_timeCount == 0)
			{
				auto moji1 = AddGameObject<Comment>(4, 0, 0.2f, 512, 128, 220, 60, 4, 1,
					Vec3(340.0f, 200.0f, 0.0f), L"LoadMoji"); // 「正体不明」
				m_timeCount++;
			}
			//スコアステージが生成されてから2秒後に、コメントを表示
			else if (m_countUp >= 2.0f && m_timeCount == 1) //
			{
				auto moji2 = AddGameObject<CommentManager>(13, 0, 0.2f, 400, 128, 250, 80, 8, 2,
					Vec3(-555.0f, -95.0f, 0.0f), L"LoadMoji1"); // 「体内に住みつき徐々に蝕んでいく」
				m_timeCount++;
			}
			m_moveCount = -400;

			// 潜水艦を右に動かす
			auto spritetrans = m_sprite->GetComponent<Transform>();
			Vec3 spritepos = spritetrans->GetPosition();
			if (!m_flag)
			{
				m_comX += 3.0f;
				spritetrans->SetPosition(m_comX, -300.0f, 0.0f);
			}
			if (m_comX >= 700)
			{
				m_comment->ThisDestroy();
				auto moji = AddGameObject<Comment>(7, 0, 0.2f, 256, 64, 200, 50, 7, 1, // Bボタンで次へ
					Vec3(400.0f, -335.0f, 0.0f), L"LoadMoji3");
					m_flag = true;
			}
		}
		if (m_onFade)
		{
			float fadeSpeed = 1.0f;
			m_anCollar += fadeSpeed* delta;
			m_blackBoard->SetColor(Col4(1, 1, 1, m_anCollar));
		}

		//wstringstream wss(L"");
		//auto scene = App::GetApp()->GetScene<Scene>();
		//wss << m_countUp << endl;

		//scene->SetDebugString(wss.str());

	}
	void LoadStage::StageChange() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto& scene = App::GetApp()->GetScene<Scene>();
		if (m_countUp >= 7.5f && cntlVec[0].bConnected) {
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
				m_onFade = true;
			}
		}
		if (m_anCollar>=1)
		{
			m_onFade = false;
			if (scene->GetNextStage() == 0) {
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTutorialStage");
			}
			else {
				auto stage = scene->GetNextStage();
				wstring stageNum = to_wstring(stage);
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage" + stageNum);

			}
		}
	}

}