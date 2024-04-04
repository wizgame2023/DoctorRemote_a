/*!
@file HemmiStage.cpp
@brief サンプルステージ
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------

	//ビューとライトの作成
	void HemmiStage::CreateViewLight() {
		// カメラの設定
		auto camera = ObjectFactory::Create<MainCamera>();
		camera->SetEye(Vec3(0.0f, 10.0f, -10.0f));
		camera->SetAt(Vec3(0.0f, 0.0f, 0.0f));

		// ビューにカメラを設定
		auto view = CreateView<SingleView>();
		view->SetCamera(camera);

		//マルチライトの作成
		auto light = CreateLight<MultiLight>();
		light->SetDefaultLighting(); //デフォルトのライティングを指定
	}

	//敵の欠片を作成
	void HemmiStage::CreateEnemyPiece() {

		vector<vector<Vec3>> vec = {
			{
				Vec3(0.5f,0.5f,0.5f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(5.0f,0.5f,0.0f)
			},
			{
				Vec3(0.5f,0.5f,0.5f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(-5.0f,0.0f,5.0f)
			},
		};
		//オブジェクトの作成
		for (auto v : vec) {
			AddGameObject<EnemyPiece>(v[0], (Quat)v[1], v[2]);
		}
	}

	void HemmiStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();

			CreateEnemyPiece();
			auto ptrPlayer = AddGameObject<Player>();

			//ビューからカメラを取得
			auto camera = GetView()->GetTargetCamera();
			auto mainCamera = dynamic_pointer_cast<MainCamera>(camera);
			mainCamera->SetTarget(ptrPlayer);

		}
		catch (...) {
			throw;
		}
	}

}
//end namespace basecross