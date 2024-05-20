/*!
@file TitleStage.cpp
@brief タイトルステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void TitleStage::CreateViewLight() {
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
	void TitleStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			auto& scene = App::GetApp()->GetScene<Scene>();

			scene->SetPlayerStatus(0);
			scene->SetBulletStataus(0);
			scene->SetLigthStatus(0);
			//AddGameObject<Player>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
			AddGameObject<Sprite>(1280, 800, L"Title", Vec3(0, 0, 0),-1);
		}
		catch (...) {
			throw;
		}
	}
	void TitleStage::OnUpdate()
	{
		StageChange();
	}
	void TitleStage::StageChange() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].bConnected) {
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToLoadStage");
			}
		}
	}
}
