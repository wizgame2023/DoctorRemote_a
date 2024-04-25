/*!
@file Player.cpp
@brief プレイヤー実体
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Data::Data(shared_ptr<Stage>& stagePtr):
	GameObject(stagePtr)
	{
	}

	void Data::OnCreate() {

		//サンプルのためアセットディレクトリを取得
		//App::GetApp()->GetAssetsDirectory(dataDir);//今仮で使っているので実際に実装するときは下のを使う
		auto& app = App::GetApp();

		auto path = app->GetDataDirWString();
		auto texPath = path + L"Textures/";
		auto modPath = path + L"Models/";

		//テクスチャ
		wstring strTexture = texPath + L"hakusi.jpg";
		app->RegisterTexture(L"White", strTexture);
		strTexture = texPath + L"arrow2.png";
		app->RegisterTexture(L"Arrow", strTexture);
		strTexture = texPath + L"Black.jpg";
		app->RegisterTexture(L"Black", strTexture);
		strTexture = texPath + L"InternalSkin.png";
		app->RegisterTexture(L"Internal", strTexture);
		strTexture = texPath + L"Bar2.png";
		app->RegisterTexture(L"Bar", strTexture);	
		strTexture = texPath + L"BarYoko2.png";
		app->RegisterTexture(L"BarSide", strTexture);

		strTexture = texPath + L"RadarBar.png";		
		app->RegisterTexture(L"RadarBar", strTexture);
		strTexture = texPath + L"RadarCover.png";
		app->RegisterTexture(L"RaderCover", strTexture);
		strTexture = texPath + L"Radar.png";
		app->RegisterTexture(L"Radar", strTexture);
		strTexture = texPath + L"Radaryoko1.png";
		app->RegisterTexture(L"Radar", strTexture);
		strTexture = texPath + L"RadarBlueYoko.png";
		app->RegisterTexture(L"RadarBlue", strTexture);
		strTexture = texPath + L"RadarOrangeYoko.png";
		app->RegisterTexture(L"RadarOrange", strTexture);
		strTexture = texPath + L"RadarRedYoko.png";
		app->RegisterTexture(L"RadarRed", strTexture);
		strTexture = texPath + L"DamageEffect.png";
		app->RegisterTexture(L"DamageBullet", strTexture);
		strTexture = texPath + L"numbers.png";
		app->RegisterTexture(L"NumbersBlack", strTexture);
		strTexture = texPath + L"numbers_w.png";
		app->RegisterTexture(L"NumbersWhite", strTexture);
		strTexture = texPath + L"WallSkin1.png";
		app->RegisterTexture(L"WallSkin", strTexture);
		strTexture = texPath + L"WallSkin2.png";
		app->RegisterTexture(L"WallSkin2", strTexture);


		//スタティックモデル(マルチメッシュ)の通常リソース
		auto staticMultiModelMesh = MultiMeshResource::CreateStaticModelMultiMesh(modPath, L"Sensuikan.bmf");
		app->RegisterResource(L"Sensuikan_Mesh", staticMultiModelMesh);

		staticMultiModelMesh = MultiMeshResource::CreateStaticModelMultiMesh(modPath, L"Baikin1.bmf");
		app->RegisterResource(L"Baikin_Mesh", staticMultiModelMesh);
		
		auto staticModelMesh = MeshResource::CreateStaticModelMesh(modPath, L"kakera.bmf");
		app->RegisterResource(L"Kakera_Mesh", staticModelMesh);
		
		staticModelMesh = MeshResource::CreateStaticModelMesh(modPath, L"kakera1.bmf");
		app->RegisterResource(L"Kakera_Mesh2", staticModelMesh);
		
		staticModelMesh = MeshResource::CreateStaticModelMesh(modPath, L"kakera2.bmf");
		app->RegisterResource(L"Kakera_Mesh3", staticModelMesh);
		
		staticModelMesh = MeshResource::CreateStaticModelMesh(modPath, L"Obstacle1-1.bmf");
		app->RegisterResource(L"Obstacle_Mesh1", staticModelMesh);
		
		staticModelMesh = MeshResource::CreateStaticModelMesh(modPath, L"Obstacle2-1.bmf");
		app->RegisterResource(L"Obstacle_Mesh2", staticModelMesh);


		//staticMultiModelMesh = MultiMeshResource::CreateStaticModelMultiMesh(modPath, L"kakera.bmf");
		//app->RegisterResource(L"Kakera_Mesh", staticMultiModelMesh);

	}
}