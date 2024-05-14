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

			auto statusManager = AddGameObject<StatusManager>();
			SetSharedGameObject(L"StatusManager", statusManager);
			auto dashButton = AddGameObject<Sprite>(300, 300, L"DashButton", Vec3(-400, 0, 0));
			auto bulletButton = AddGameObject<Sprite>(300, 300, L"BulletButton", Vec3(0, 0, 0));
			auto pieceButton = AddGameObject<Sprite>(300, 300, L"PieceButton", Vec3(400, 0, 0));


		}
		catch (...) {
			throw;
		}

	}
	void StatusStage::OnUpdate() {
		auto statusManager = GetSharedGameObject<StatusManager>(L"StatusManager");
		auto status = statusManager->GetStatus();

		//デバック用
		wstringstream wss(L"");
		auto scene = App::GetApp()->GetScene<Scene>();
		wss << status
			<<"\n"
			<< endl;
		scene->SetDebugString(wss.str());

		
	}

}