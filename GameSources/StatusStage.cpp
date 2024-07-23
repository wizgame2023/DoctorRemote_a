/*!
@file StatusStage.h
@brief ステータスステージ実体
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void StatusStage::CreateViewLight() {

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
	}
	void StatusStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			App::GetApp()->GetScene<Scene>()->SetPlayFlag(false);


			auto statusManager = AddGameObject<StatusManager>();
			SetSharedGameObject(L"StatusManager", statusManager);

			
			auto moji = AddGameObject<Comment>(16, 0, 0.2f, 512, 256, 700 * 1.2, 350 * 1.2, 26, 8, 
				Vec3(-250, 350.0f, 0.0f), L"StatusMoji"); //「ステータスを1つ選んでください」
			m_moji[0] = AddGameObject<Sprite>(150, 75, L"DecisionButton", Vec3(500, -350.0f, 0.0f)); //「B決定」
			m_moji[1] = AddGameObject<Sprite>(150, 75, L"SpaceButton", Vec3(500, -350.0f, 0.0f)); // 「Space」

			// 「選ばず次のステージへ」
			auto skipMoji = AddGameObject<CommentManager>(11, 1, 0.0f, 512, 256, 512 * 1.5, 256 * 1.5, 13 * 2, 8, 
				Vec3(-500, -300.0f, 0.0f), L"StatusMoji");
			m_moji[2] = AddGameObject<Sprite>(100,50,L"Abutton",Vec3(-500, -370.0f, 0.0f)); // Aボタン
			m_moji[3] = AddGameObject<Sprite>(150, 75, L"BackSpaceButton", Vec3(-540, -370.0f, 0.0f)); // BackSpaceキー

			// 「タイトルに戻る」
			auto titleMoji = AddGameObject <CommentManager>(8, 2, 0.0f, 512, 256, 512 * 1.5, 256 * 1.5, 13 * 2, 8,
				Vec3(50, -250.0f, 0.0f), L"StatusMoji");
			m_moji[4] = AddGameObject<Sprite>(100, 50, L"YButton", Vec3(50, -365.0f, 0.0f)); // Yボタン
			m_moji[5] = AddGameObject<Sprite>(150, 75, L"DeleteButton", Vec3(0, -370.0f, 0.0f)); // Deleteキー
			for (int i = 0; i < 6; i++) {
				m_moji[i]->SetColor(Col4(0.0f));
			}

			//背景
			auto back = AddGameObject<Sprite>(1280,800,L"Back",Vec3(),-1);
			back->SetColor(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		catch (...) {
			throw;
		}

	}
	void StatusStage::OnUpdate() {
		App::GetApp()->GetScene<Scene>()->ResetButton();
		auto statusManager = GetSharedGameObject<StatusManager>(L"StatusManager");
		auto status = statusManager->GetStatus();
		auto elapsed = App::GetApp()->GetElapsedTime();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		if (m_blinking > 0) {
			m_blinking -= elapsed;
		}
		else {
			m_blinking = 2.0f;
		}

		//操作文字の透明度の切り替え
		if (cntlVec[0].bConnected) {
			m_moji[0]->SetColor(Col4(0.0f, 1.0f, 0.0f, m_blinking));
			m_moji[2]->SetColor(Col4(1.0f, 1.0f, 1.0f, 1.0f));
			m_moji[4]->SetColor(Col4(1.0f, 1.0f, 1.0f, 1.0f));
			m_moji[1]->SetColor(Col4(0.0f));
			m_moji[3]->SetColor(Col4(0.0f));
			m_moji[5]->SetColor(Col4(0.0f));
		}
		else {
			m_moji[1]->SetColor(Col4(0.0f, 1.0f, 0.0f, m_blinking));
			m_moji[3]->SetColor(Col4(1.0f, 1.0f, 1.0f, 1.0f));
			m_moji[5]->SetColor(Col4(1.0f, 1.0f, 1.0f, 1.0f));
			m_moji[0]->SetColor(Col4(0.0f));
			m_moji[2]->SetColor(Col4(0.0f));
			m_moji[4]->SetColor(Col4(0.0f));

		}

		//デバック用
		//wstringstream wss(L"");
		//auto scene = App::GetApp()->GetScene<Scene>();
		//wss << status
		//	<<"\n"
		//	<< endl;
		//scene->SetDebugString(wss.str());

		
	}

}