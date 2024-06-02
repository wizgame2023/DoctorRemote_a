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
		auto comPath = path + L"Comments/";
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
		strTexture = texPath + L"GageBar.png";
		app->RegisterTexture(L"GargeBar", strTexture);
		strTexture = texPath + L"Gage.png";
		app->RegisterTexture(L"Garge", strTexture);
		strTexture = texPath + L"Hearts.png";
		app->RegisterTexture(L"Hearts", strTexture);
		strTexture = texPath + L"HeartsFrame.png";
		app->RegisterTexture(L"HeartsFrame", strTexture);

		//背景など1280x800
		strTexture = texPath + L"Clear.png";
		app->RegisterTexture(L"Clear", strTexture);
		strTexture = texPath + L"GameOver.jpg";
		app->RegisterTexture(L"GameOver", strTexture);
		strTexture = texPath + L"Start.png";
		app->RegisterTexture(L"Start", strTexture);
		strTexture = texPath + L"Load.png";
		app->RegisterTexture(L"Load", strTexture);
		strTexture = texPath + L"Title_3.jpg";
		app->RegisterTexture(L"Title", strTexture);
		strTexture = texPath + L"Score.jpg";
		app->RegisterTexture(L"Score", strTexture);
		strTexture = texPath + L"Ligth.png";
		app->RegisterTexture(L"Ligth", strTexture);
		strTexture = texPath + L"Ligth2.png";
		app->RegisterTexture(L"Ligth2", strTexture);
		strTexture = texPath + L"Ligth3.png";
		app->RegisterTexture(L"Ligth3", strTexture);
		strTexture = texPath + L"Back.png";
		app->RegisterTexture(L"Back", strTexture);
		strTexture = texPath + L"GameScreen.png";
		app->RegisterTexture(L"GameScreen", strTexture);
		strTexture = texPath + L"Frame.png";
		app->RegisterTexture(L"Frame", strTexture);
		strTexture = texPath + L"triDot.png";
		app->RegisterTexture(L"TriDot", strTexture);
		strTexture = texPath + L"Button.png";
		app->RegisterTexture(L"Bbutton", strTexture);


		strTexture = texPath + L"MiniMapDataVer3.0.png";
		app->RegisterTexture(L"MiniMap", strTexture);
		strTexture = texPath + L"Triangle.png";
		app->RegisterTexture(L"MiniMapPlayer", strTexture);
		strTexture = texPath + L"Red.png";
		app->RegisterTexture(L"MiniMapBigPiece", strTexture);

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

		strTexture = texPath + L"kaihuku.png";
		app->RegisterTexture(L"PlayerEffectGreen", strTexture);
		strTexture = texPath + L"PlayerEffectRed.png";
		app->RegisterTexture(L"PlayerEffectRed", strTexture);
		strTexture = texPath + L"EffectWhite.png";
		app->RegisterTexture(L"PlayerEffectWhite", strTexture);

		strTexture = texPath + L"DashMode.png";
		app->RegisterTexture(L"DashButton", strTexture);
		strTexture = texPath + L"BulletMode.png";
		app->RegisterTexture(L"BulletButton", strTexture);
		strTexture = texPath + L"PieceButton.png";
		app->RegisterTexture(L"PieceButton", strTexture);
		strTexture = texPath + L"LightMode.png";
		app->RegisterTexture(L"LigthButton", strTexture);
		strTexture = texPath + L"SelectMoji.png";
		app->RegisterTexture(L"SelectTutorial", strTexture);
		strTexture = texPath + L"SelectMoji1.png";
		app->RegisterTexture(L"SelectGameStage", strTexture);
		strTexture = texPath + L"SelectMoji2.png";
		app->RegisterTexture(L"SelectGameStage2", strTexture);
		strTexture = texPath + L"SelectMoji3.png";
		app->RegisterTexture(L"SelectGameStage3", strTexture);
		strTexture = texPath + L"SelectWhite.png";
		app->RegisterTexture(L"SelectWhite", strTexture);

		//文字の表示等
		strTexture = texPath + L"Rank.png";
		app->RegisterTexture(L"Rank", strTexture);
		strTexture = texPath + L"StatusMoji.png";
		app->RegisterTexture(L"StatusMoji", strTexture);
		strTexture = texPath + L"StatusMoji2.png";
		app->RegisterTexture(L"StatusMoji2", strTexture);
		strTexture = texPath + L"comment2.png";
		app->RegisterTexture(L"comment", strTexture);
		strTexture = texPath + L"SousaCom.png";
		app->RegisterTexture(L"SousaCom", strTexture);
		strTexture = texPath + L"CommentFrame.png";
		app->RegisterTexture(L"CommentFrame", strTexture);
		strTexture = texPath + L"ResultMoji1.png";
		app->RegisterTexture(L"ResultMoji1", strTexture);
		strTexture = texPath + L"ResultMoji2.png";
		app->RegisterTexture(L"ResultMoji2", strTexture);
		strTexture = texPath + L"GameClear.jpg";
		app->RegisterTexture(L"GameClear", strTexture);
		strTexture = texPath + L"IfClear.png";
		app->RegisterTexture(L"IfClear", strTexture);
		strTexture = texPath + L"MapSetumei.png";
		app->RegisterTexture(L"MapSetumei", strTexture);



		//コメントファイルの文字テクスチャ
		strTexture = comPath + L"AIaisatu.png";
		app->RegisterTexture(L"AIaisatu", strTexture);
		strTexture = comPath + L"Comment_s.png";
		app->RegisterTexture(L"Comment_s", strTexture);
		strTexture = comPath + L"Garge_s.png";
		app->RegisterTexture(L"Garge_s", strTexture);
		strTexture = comPath + L"Hp_s.png";
		app->RegisterTexture(L"Hp_s", strTexture);
		strTexture = comPath + L"Map_s.png";
		app->RegisterTexture(L"Map_s", strTexture);
		strTexture = comPath + L"Map_s2.png";
		app->RegisterTexture(L"Map_s2", strTexture);
		strTexture = comPath + L"Time_s.png";
		app->RegisterTexture(L"Time_s", strTexture);
		strTexture = comPath + L"SetumeiStart.png";
		app->RegisterTexture(L"SetumeiStart", strTexture);
		strTexture = comPath + L"Dassyutu.png";
		app->RegisterTexture(L"Dassyutu", strTexture);
		strTexture = comPath + L"Sousa.png";
		app->RegisterTexture(L"Sousa", strTexture);
		strTexture = comPath + L"UISetumeiEnd.png";
		app->RegisterTexture(L"UISetumeiEnd", strTexture);
		strTexture = comPath + L"Setumei_1.png";
		app->RegisterTexture(L"Setumei1", strTexture);
		strTexture = comPath + L"Setumei_2.png";
		app->RegisterTexture(L"Setumei2", strTexture);
		strTexture = comPath + L"Setumei_3.png";
		app->RegisterTexture(L"Setumei3", strTexture);
		strTexture = comPath + L"WallSetumei.png";
		app->RegisterTexture(L"WallSetumei", strTexture);


		//ボーンマルチモデル(マルチメッシュ)の通常リソース
		auto boneMultiModelMesh = MultiMeshResource::CreateBoneModelMultiMesh(modPath, L"NewSensuikan.bmf");
		app->RegisterResource(L"Sensuikan_Mesh", boneMultiModelMesh);

		boneMultiModelMesh = MultiMeshResource::CreateBoneModelMultiMesh(modPath, L"NewBaikin.bmf");
		app->RegisterResource(L"Baikin_Mesh", boneMultiModelMesh);

		//スタティックマルチモデル
		auto staticMultiModelMesh = MultiMeshResource::CreateStaticModelMultiMesh(modPath, L"Obstacle3-1.bmf");
		app->RegisterResource(L"Obstacle_Mesh3", staticMultiModelMesh);

		staticMultiModelMesh = MultiMeshResource::CreateStaticModelMultiMesh(modPath, L"Pillar.bmf");
		app->RegisterResource(L"Obstacle_Gate", staticMultiModelMesh);

		//ボーンモデル
		auto boneModelMesh = MeshResource::CreateBoneModelMesh(modPath, L"Newkakera.bmf");
		app->RegisterResource(L"Kakera_Mesh", boneModelMesh);

		boneModelMesh = MeshResource::CreateBoneModelMesh(modPath, L"Newkakera2.bmf");
		app->RegisterResource(L"Kakera_Mesh3", boneModelMesh);

		//スタティックモデル
		auto staticModelMesh = MeshResource::CreateStaticModelMesh(modPath, L"kakera1.bmf");
		app->RegisterResource(L"Kakera_Mesh2", staticModelMesh);

		staticModelMesh = MeshResource::CreateStaticModelMesh(modPath, L"Obstacle1-1.bmf");
		app->RegisterResource(L"Obstacle_Mesh1", staticModelMesh);

		staticModelMesh = MeshResource::CreateStaticModelMesh(modPath, L"Obstacle2-1.bmf");
		app->RegisterResource(L"Obstacle_Mesh2", staticModelMesh);

		staticModelMesh = MeshResource::CreateStaticModelMesh(modPath, L"Littlekakera.bmf");
		app->RegisterResource(L"LittleKakera", staticModelMesh);

		staticModelMesh = MeshResource::CreateStaticModelMesh(modPath, L"Sphere.bmf");
		app->RegisterResource(L"Bullet", staticModelMesh);


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
		soundWav = SoundPath + L"BossBGM.wav";
		App::GetApp()->RegisterWav(L"BossBGM", soundWav);

		
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
		if (event->m_MsgStr == L"ToGameStage2") {
			//ゲームステージの設定
			ResetActiveStage<GameStage2>();
		}
        else if (event->m_MsgStr == L"ToStartStage") {
            ResetActiveStage<TitleStage>();
        }
		else if (event->m_MsgStr == L"ToTutorialStage") {
			ResetActiveStage<TutorialStage>();
		}
        else if (event->m_MsgStr == L"ToClearStage") {
            ResetActiveStage<ScoreStage>();
        }
        else if (event->m_MsgStr == L"ToGameOverStage") {
            ResetActiveStage<GameOverStage>();
        }
		else if (event->m_MsgStr == L"ToStatusStage") {
			ResetActiveStage<StatusStage>();
		}
		else if (event->m_MsgStr == L"ToScoreStage") {
			ResetActiveStage<ScoreStage>();
		}
		else if (event->m_MsgStr == L"ToLoadStage") {
			ResetActiveStage<LoadStage>();
		}



    }

	int Scene::GetPlayerStatus() {
		return m_playerStatus;
	}
	void Scene::SetPlayerStatus(int status) {
		m_playerStatus = status;
	}
	void Scene::AddPlayerStatus(int status) {
		m_playerStatus += status;
	}

	int Scene::GetBulletStatus() {
		return m_bulletStatus;
	}
	void Scene::SetBulletStataus(int status) {
		m_bulletStatus = status;
	}
	void Scene::AddBulletStatus(int status) {
		m_bulletStatus += status;
	}

	int Scene::GetLigthStatus() {
		return m_ligthStatus;
	}
	void Scene::SetLigthStatus(int status) {
		m_ligthStatus = status;
	}
	void Scene::AddLigthStatus(int status) {
		m_ligthStatus += status;
	}

	int Scene::GetTime() {
		return m_time;
	}
	void Scene::SetTime(int time) {
		m_time = time;
	}
	int Scene::GetGameStage() {
		return m_gameStage;
	}
	void Scene::SetGameStage(int gameStage) {
		m_gameStage = gameStage;
	}
}
//test
//end basecross
