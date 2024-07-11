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

			auto moji = AddGameObject<Comment>(16, 0, 0.2f, 512, 256, 700 * 1.2, 350 * 1.2, 26, 8, Vec3(-250, 350.0f, 0.0f), L"StatusMoji");
			m_moji2 = AddGameObject<Sprite>(150,75, L"DecisionButton",Vec3(500, -350.0f, 0.0f));
			SetSharedGameObject(L"Moji2", m_moji2);

			auto aButton = AddGameObject<CommentManager>(11, 1, 0.0f, 512, 256, 512*1.5, 256*1.5, 13 * 2, 8, Vec3(-580, -300.0f, 0.0f), L"StatusMoji");

			auto black = AddGameObject<Sprite>(1280, 800, L"Black", Vec3(), -3);
			auto back = AddGameObject<Sprite>(1280,800,L"Back",Vec3(),-1);
			back->SetColor(Col4(1.0f, 1.0f, 1.0f, 0.6f));
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

		if (m_blinking > 0) {
			m_blinking -= elapsed;
		}
		else {
			m_blinking = 2.0f;
		}
		m_moji2->SetColor(Col4(0.0f, 1.0f, 0.0f, m_blinking));

		//デバック用
		//wstringstream wss(L"");
		//auto scene = App::GetApp()->GetScene<Scene>();
		//wss << status
		//	<<"\n"
		//	<< endl;
		//scene->SetDebugString(wss.str());

		
	}

}