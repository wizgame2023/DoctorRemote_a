/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

    //--------------------------------------------------------------------------------------
    ///    ゲームシーン
    //--------------------------------------------------------------------------------------
    void Scene::CreateResourses() {
		auto& app = App::GetApp();

		auto path = app->GetDataDirWString();
		auto texPath = path + L"Textures/";
		auto modPath = path + L"Models/";
		auto SoundPath = path + L"Sounds/";

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
		strTexture = texPath + L"BarFrame2.png";
		app->RegisterTexture(L"BarFrame", strTexture);


		strTexture = texPath + L"Clear.png";
		app->RegisterTexture(L"Clear", strTexture);
		strTexture = texPath + L"GameOver.png";
		app->RegisterTexture(L"GameOver", strTexture);
		strTexture = texPath + L"Start.png";
		app->RegisterTexture(L"Start", strTexture);


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
		strTexture = texPath + L"numbernoten.png";
		app->RegisterTexture(L"NumbersTen", strTexture);
		strTexture = texPath + L"WallSkin1.png";
		app->RegisterTexture(L"WallSkin", strTexture);
		strTexture = texPath + L"WallSkin2.png";
		app->RegisterTexture(L"WallSkin2", strTexture);
		strTexture = texPath + L"WallSkin3.png";
		app->RegisterTexture(L"WallBreak", strTexture);
		strTexture = texPath + L"WallSkin4.png";
		app->RegisterTexture(L"WallRecovery", strTexture);


		//スタティックモデル(マルチメッシュ)の通常リソース
		auto staticMultiModelMesh = MultiMeshResource::CreateStaticModelMultiMesh(modPath, L"Sensuikan.bmf");
		app->RegisterResource(L"Sensuikan_Mesh", staticMultiModelMesh);

		staticMultiModelMesh = MultiMeshResource::CreateStaticModelMultiMesh(modPath, L"Baikin.bmf");
		app->RegisterResource(L"Baikin_Mesh", staticMultiModelMesh);

		staticMultiModelMesh = MultiMeshResource::CreateStaticModelMultiMesh(modPath, L"Obstacle3-1.bmf");
		app->RegisterResource(L"Obstacle_Mesh3", staticMultiModelMesh);


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

		//サウンド
		//SE
		wstring soundWav = SoundPath + L"ShotSE.wav";
		App::GetApp()->RegisterWav(L"ShotSE", soundWav);
		soundWav = SoundPath + L"GetPiece.wav";
		App::GetApp()->RegisterWav(L"GetPieceSE", soundWav);
		soundWav = SoundPath + L"Recovery.wav";
		App::GetApp()->RegisterWav(L"RecoveryWallSE", soundWav);
		soundWav = SoundPath + L"BreakWall.wav";
		App::GetApp()->RegisterWav(L"BreakWallSE", soundWav);
		//BGM
		soundWav = SoundPath + L"ScaryBGM.wav";
		App::GetApp()->RegisterWav(L"ScaryBGM", soundWav);




    }

    void Scene::OnCreate() {
        try {
            // 背景色を設定
            SetClearColor(Col4(0.0f, 0.11328125f, 0.2578125, 1.0f)); // ミッドナイトブルー

            //リソース作成
            CreateResourses();

            //自分自身にイベントを送る
            //これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
            PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToStartStage");
        }
        catch (...) {
            throw;
        }
    }

    Scene::~Scene() {
    }

    void Scene::OnEvent(const shared_ptr<Event>& event) {
        if (event->m_MsgStr == L"ToGameStage") {
            //ゲームステージの設定
			ResetActiveStage<GameStage>();

        }
        else if (event->m_MsgStr == L"ToStartStage") {
            ResetActiveStage<StartStage>();
        }
        else if (event->m_MsgStr == L"ToClearStage") {
            ResetActiveStage<ClearStage>();
        }
        else if (event->m_MsgStr == L"ToGameOverStage") {
            ResetActiveStage<GameOverStage>();

        }
    }


}
//test
//end basecross
