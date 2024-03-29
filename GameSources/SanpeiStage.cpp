/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------

	//ビューとライトの作成
	void SanpeiStage::CreateViewLight() {
		// カメラの設定
		auto camera = ObjectFactory::Create<Camera>();
		camera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
		camera->SetAt(Vec3(0.0f, 0.0f, 0.0f));

		// ビューにカメラを設定
		auto view = CreateView<SingleView>();
		view->SetCamera(camera);

		//マルチライトの作成
		auto light = CreateLight<MultiLight>();
		light->SetDefaultLighting(); //デフォルトのライティングを指定
	}

	void SanpeiStage::CreateBullet()
	{
		AddGameObject<Bullet>(Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f),1.0f);
		//AddGameObject<Bullet>(Vec3(3.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f),-1.0f);

	}

	void SanpeiStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			//弾を作成
			CreateBullet();
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
