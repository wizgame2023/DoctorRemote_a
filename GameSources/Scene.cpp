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
		strTexture = texPath + L"GargeLight.png";
		app->RegisterTexture(L"GargeLight", strTexture);
		strTexture = texPath + L"DashIcon.png";
		app->RegisterTexture(L"DashIcon", strTexture);
		strTexture = texPath + L"CommentWaku.png";
		app->RegisterTexture(L"CommentWaku", strTexture);
		strTexture = texPath + L"MapWaku.png";
		app->RegisterTexture(L"MapWaku", strTexture);
		strTexture = texPath + L"HPWaku.png";
		app->RegisterTexture(L"HPWaku", strTexture);
		strTexture = texPath + L"ChargeWaku.png";
		app->RegisterTexture(L"ChargeWaku", strTexture);
		strTexture = texPath + L"GageWaku.png";
		app->RegisterTexture(L"GageWaku", strTexture);
		strTexture = texPath + L"TimeWaku.png";
		app->RegisterTexture(L"TimeWaku", strTexture);
		strTexture = texPath + L"Map_sWaku.png";
		app->RegisterTexture(L"Map_sWaku", strTexture);
		strTexture = texPath + L"kakera.png";
		app->RegisterTexture(L"Kakera", strTexture);
		strTexture = texPath + L"triDot.png";
		app->RegisterTexture(L"TriDot", strTexture);
		strTexture = texPath + L"Button.png";
		app->RegisterTexture(L"Bbutton", strTexture);
		strTexture = texPath + L"Abutton.png";
		app->RegisterTexture(L"Abutton", strTexture);
		strTexture = texPath + L"Bbutton2.png";
		app->RegisterTexture(L"Bbutton2", strTexture);
		strTexture = texPath + L"DecisionButton.png";
		app->RegisterTexture(L"DecisionButton", strTexture);
		strTexture = texPath + L"RetrunButton.png";
		app->RegisterTexture(L"RetrunButton", strTexture);
		strTexture = texPath + L"White_2.png";
		app->RegisterTexture(L"White_2", strTexture);
		strTexture = texPath + L"PointTexture.png";
		app->RegisterTexture(L"PointTexture", strTexture);
		strTexture = texPath + L"GameCleraRogo.png";
		app->RegisterTexture(L"GameCleraRogo", strTexture);
		strTexture = texPath + L"GameOverRogo.png";
		app->RegisterTexture(L"GameOverRogo", strTexture);
		strTexture = texPath + L"OverButton.png";
		app->RegisterTexture(L"OverButton", strTexture);
		strTexture = texPath + L"Clear.png";
		app->RegisterTexture(L"Clear", strTexture);
		strTexture = texPath + L"Stage.png";
		app->RegisterTexture(L"Stage", strTexture);
		strTexture = texPath + L"CAUTION.png";
		app->RegisterTexture(L"CAUTION", strTexture);
		strTexture = texPath + L"Easy.png";
		app->RegisterTexture(L"Easy", strTexture);
		strTexture = texPath + L"Normal.png";
		app->RegisterTexture(L"Normal", strTexture);
		strTexture = texPath + L"Hard.png";
		app->RegisterTexture(L"Hard", strTexture);
		strTexture = texPath + L"ReStart.png";
		app->RegisterTexture(L"ReStart", strTexture);
		strTexture = texPath + L"TitleMoji.png";
		app->RegisterTexture(L"TitleMoji", strTexture);
		strTexture = texPath + L"GameOverBackSpace.png";
		app->RegisterTexture(L"GameOverBackSpace", strTexture);
		strTexture = texPath + L"GameOverSpace.png";
		app->RegisterTexture(L"GameOverSpace", strTexture);		
		strTexture = texPath + L"GameOverComment1.png";
		app->RegisterTexture(L"GameOverComment1", strTexture);
		strTexture = texPath + L"GameOverComment2.png";
		app->RegisterTexture(L"GameOverComment2", strTexture);
		strTexture = texPath + L"GameOverCommentName1.png";
		app->RegisterTexture(L"GameOverCommentName1", strTexture);
		strTexture = texPath + L"GameOverCommentName2.png";
		app->RegisterTexture(L"GameOverCommentName2", strTexture);
		strTexture = texPath + L"ClearTitle.png";
		app->RegisterTexture(L"ClearTitle", strTexture);
		strTexture = texPath + L"GameClearAButton.png";
		app->RegisterTexture(L"GameClearAButton", strTexture);
		strTexture = texPath + L"GameClearSpace.png";
		app->RegisterTexture(L"GameClearSpace", strTexture);

		

		//背景など1280x800//////////////////////////////////////////////////////////////
		strTexture = texPath + L"GameOver.jpg";
		app->RegisterTexture(L"GameOver", strTexture);
		strTexture = texPath + L"Start.png";
		app->RegisterTexture(L"Start", strTexture);
		strTexture = texPath + L"Load.png";
		app->RegisterTexture(L"Load", strTexture);
		strTexture = texPath + L"Title_3.jpg";
		app->RegisterTexture(L"Title", strTexture);
		strTexture = texPath + L"Score.png";
		app->RegisterTexture(L"Score", strTexture);
		strTexture = texPath + L"ScoreWaku.jpg";
		app->RegisterTexture(L"ScoreWaku", strTexture);
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
		strTexture = texPath + L"LoadScene.png";
		app->RegisterTexture(L"LoadScene", strTexture);
		strTexture = texPath + L"LoadStageWaku.png";
		app->RegisterTexture(L"LoadStageWaku", strTexture);
		strTexture = texPath + L"GameOver BackBoard.jpg";
		app->RegisterTexture(L"GameOverBackBoard", strTexture);
		strTexture = texPath + L"Thank.png";
		app->RegisterTexture(L"Thank", strTexture);
		strTexture = texPath + L"ClearButton.png";
		app->RegisterTexture(L"ClearButton", strTexture);
		strTexture = texPath + L"Credit.jpg";
		app->RegisterTexture(L"Credit", strTexture);
		
		
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//ミニマップ関連///////////////////////////////////////////////////////////////////////////////////////////////
		strTexture = texPath + L"MiniMapStage1.png";//ミニマップStage1
		app->RegisterTexture(L"MiniMapStage1", strTexture);
		strTexture = texPath + L"MiniMapStage2.png";//ミニマップStage2
		app->RegisterTexture(L"MiniMapStage2", strTexture);
		strTexture = texPath + L"MiniMapStage3.png";//ミニマップStage3
		app->RegisterTexture(L"MiniMapStage3", strTexture);
		strTexture = texPath + L"MiniMapStage4Ver5.0.png";//ミニマップStage4
		app->RegisterTexture(L"MiniMapStage4", strTexture);
		strTexture = texPath + L"MiniMapStage5ver2.0.png";//ミニマップStage5
		app->RegisterTexture(L"MiniMapStage5", strTexture);
		strTexture = texPath + L"MiniMapStage6.png";//ミニマップStage6
		app->RegisterTexture(L"MiniMapStage6", strTexture);
		strTexture = texPath + L"MiniMapStage7.png";//ミニマップStage7
		app->RegisterTexture(L"MiniMapStage7", strTexture);
		strTexture = texPath + L"MiniMapStage8Ver2.0.png";//ミニマップStage8
		app->RegisterTexture(L"MiniMapStage8", strTexture);
		strTexture = texPath + L"MiniMapStage9Ver2.0.png";//ミニマップStage9
		app->RegisterTexture(L"MiniMapStage9", strTexture);
		strTexture = texPath + L"MiniMapStage10Ver3.0.png";//ミニマップStage10
		app->RegisterTexture(L"MiniMapStage10", strTexture);
		strTexture = texPath + L"MiniMapStage11ver2.0.png";//ミニマップStage11
		app->RegisterTexture(L"MiniMapStage11", strTexture);
		strTexture = texPath + L"MiniMapStage12ver3.0.png";//ミニマップStage12
		app->RegisterTexture(L"MiniMapStage12", strTexture);
		strTexture = texPath + L"MiniMapDataTutorialVer2.0.png";//ミニマップチュートリアル
		app->RegisterTexture(L"MiniMapTutorial", strTexture);

		strTexture = texPath + L"Triangle.png";
		app->RegisterTexture(L"MiniMapPlayer", strTexture);
		strTexture = texPath + L"Red.png";
		app->RegisterTexture(L"MiniMapBigPiece", strTexture);
		strTexture = texPath + L"Red.png";
		app->RegisterTexture(L"MiniMapBigPiece", strTexture);
		strTexture = texPath + L"MiniMapBrearkWall.png";
		app->RegisterTexture(L"MiniMapBrearkWall", strTexture);
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
		strTexture = texPath + L"RadarYellowYoko.png";
		app->RegisterTexture(L"RadarYellow", strTexture);
		strTexture = texPath + L"RadarRedYoko.png";
		app->RegisterTexture(L"RadarRed", strTexture);
		strTexture = texPath + L"DamageEffect.png";
		app->RegisterTexture(L"DamageBullet", strTexture);
		strTexture = texPath + L"RadarWaku.png";//レーダーの枠組み
		app->RegisterTexture(L"RaderFrame", strTexture);
		strTexture = texPath + L"numbers.png";
		app->RegisterTexture(L"NumbersBlack", strTexture);
		strTexture = texPath + L"numbers_w.png";
		app->RegisterTexture(L"NumbersWhite", strTexture);
		strTexture = texPath + L"numbernoten.png";
		app->RegisterTexture(L"NumbersTen", strTexture);
		strTexture = texPath + L"Numbers10.png";
		app->RegisterTexture(L"Numbers10", strTexture);
		strTexture = texPath + L"Numbers12.png";
		app->RegisterTexture(L"Numbers12", strTexture);
		strTexture = texPath + L"WallSkin1.png";
		app->RegisterTexture(L"WallSkin", strTexture);
		strTexture = texPath + L"WallSkin2.png";
		app->RegisterTexture(L"WallSkin2", strTexture);
		strTexture = texPath + L"WallSkin3.png";
		app->RegisterTexture(L"WallBreak", strTexture);
		strTexture = texPath + L"WallSkin4.png";
		app->RegisterTexture(L"WallRecovery", strTexture);
		strTexture = texPath + L"ResultWaku.png";
		app->RegisterTexture(L"ResultWaku", strTexture);
		strTexture = texPath + L"CheckMark.png";
		app->RegisterTexture(L"CheckMark", strTexture);
		strTexture = texPath + L"Sensuikan.png";
		app->RegisterTexture(L"Sensuikan", strTexture);
		strTexture = texPath + L"SpaceButton.png";
		app->RegisterTexture(L"SpaceButton", strTexture);
		strTexture = texPath + L"BackSpaceButton.png";
		app->RegisterTexture(L"BackSpaceButton", strTexture);
		strTexture = texPath + L"SButton.png";
		app->RegisterTexture(L"SButton", strTexture);
		strTexture = texPath + L"YButton.png";
		app->RegisterTexture(L"YButton", strTexture);
		strTexture = texPath + L"DeleteButton.png";
		app->RegisterTexture(L"DeleteButton", strTexture);
		strTexture = texPath + L"GameOverAButton.png";
		app->RegisterTexture(L"GameOverAButton", strTexture);
		strTexture = texPath + L"GameOverBButton.png";
		app->RegisterTexture(L"GameOverBButton", strTexture);



		//ムービーの枠組み
		strTexture = texPath + L"MovieBand.png";
		app->RegisterTexture(L"MovieBand", strTexture);

		//エフェクト関連
		strTexture = texPath + L"kaihuku.png";
		app->RegisterTexture(L"PlayerEffectGreen", strTexture);
		strTexture = texPath + L"PlayerEffectRed.png";
		app->RegisterTexture(L"PlayerEffectRed", strTexture);
		strTexture = texPath + L"EffectWhite.png";
		app->RegisterTexture(L"PlayerEffectWhite", strTexture);
		strTexture = texPath + L"RecoveryEffect.png";
		app->RegisterTexture(L"RecoveryEffect", strTexture);
		strTexture = texPath + L"GetEffect.png";
		app->RegisterTexture(L"GetEffect", strTexture);
		strTexture = texPath + L"DashMode.png";
		app->RegisterTexture(L"DashButton", strTexture);
		strTexture = texPath + L"BulletMode.png";
		app->RegisterTexture(L"BulletButton", strTexture);
		strTexture = texPath + L"GageMode.png";
		app->RegisterTexture(L"GageButton", strTexture);
		strTexture = texPath + L"ScopeMode.png";
		app->RegisterTexture(L"ScopeButton", strTexture);
		strTexture = texPath + L"ChargeMode.png";
		app->RegisterTexture(L"ChargeButton", strTexture);
		strTexture = texPath + L"PowerMode.png";
		app->RegisterTexture(L"PowerButton", strTexture);
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
		strTexture = texPath + L"EffectPiece.png";
		app->RegisterTexture(L"EffectPiece", strTexture);
		strTexture = texPath + L"BulletEffect.png";
		app->RegisterTexture(L"BulletEffect", strTexture);
		strTexture = texPath + L"Smoke.png";//煙	
		app->RegisterTexture(L"SmokeEffect", strTexture);
		strTexture = texPath + L"EnemyDamage.png";
		app->RegisterTexture(L"EnemyDamageEffect", strTexture);
		strTexture = texPath + L"EnemyPiece.png";
		app->RegisterTexture(L"EnemyPieceEffect", strTexture);
		strTexture = texPath + L"BigPiece2.png";
		app->RegisterTexture(L"BigPieceEffect2", strTexture);
		strTexture = texPath + L"BigPiece2-1.png";
		app->RegisterTexture(L"BigPieceEffect2-1", strTexture);
		strTexture = texPath + L"BigPiece2-2.png";
		app->RegisterTexture(L"BigPieceEffect2-2", strTexture);
		//文字の表示等
		strTexture = texPath + L"Rank.png";
		app->RegisterTexture(L"Rank", strTexture);
		strTexture = texPath + L"Point.png";
		app->RegisterTexture(L"Point", strTexture);
		strTexture = texPath + L"KakeraPoint.png";
		app->RegisterTexture(L"KakeraPoint", strTexture);
		strTexture = texPath + L"Plus.png";
		app->RegisterTexture(L"Plus", strTexture);
		strTexture = texPath + L"StatusMoji.png";
		app->RegisterTexture(L"StatusMoji", strTexture);
		strTexture = texPath + L"StatusMoji2.png";
		app->RegisterTexture(L"StatusMoji2", strTexture);
		strTexture = texPath + L"comment2.png";
		app->RegisterTexture(L"comment", strTexture);
		strTexture = texPath + L"SousaCom.png";
		app->RegisterTexture(L"SousaCom", strTexture);
		strTexture = texPath + L"SousaCom2.png";
		app->RegisterTexture(L"SousaCom2", strTexture);
		strTexture = texPath + L"CommentFrame.png";
		app->RegisterTexture(L"CommentFrame", strTexture);
		strTexture = texPath + L"ResultMoji1.png";
		app->RegisterTexture(L"ResultMoji1", strTexture);
		strTexture = texPath + L"ResultMoji2.png";
		app->RegisterTexture(L"ResultMoji2", strTexture);
		strTexture = texPath + L"ResultMoji3.png";
		app->RegisterTexture(L"ResultMoji3", strTexture);
		strTexture = texPath + L"ResultMoji4.png";
		app->RegisterTexture(L"ResultMoji4", strTexture);
		strTexture = texPath + L"ResultMoji5.png";
		app->RegisterTexture(L"ResultMoji5", strTexture);
		strTexture = texPath + L"GameClear.jpg";
		app->RegisterTexture(L"GameClear", strTexture);
		strTexture = texPath + L"IfClear.png";
		app->RegisterTexture(L"IfClear", strTexture);
		strTexture = texPath + L"MapSetumei.png";
		app->RegisterTexture(L"MapSetumei", strTexture);
		strTexture = texPath + L"StatusMoji1-1.png";
		app->RegisterTexture(L"StatusMoji1-1", strTexture);
		strTexture = texPath + L"StatusMoji1-2.png";
		app->RegisterTexture(L"StatusMoji1-2", strTexture);
		strTexture = texPath + L"StatusMoji1-3.png";
		app->RegisterTexture(L"StatusMoji1-3", strTexture);
		strTexture = texPath + L"StatusMoji1-4.png";
		app->RegisterTexture(L"StatusMoji1-4", strTexture);
		strTexture = texPath + L"StatusMoji1-5.png";
		app->RegisterTexture(L"StatusMoji1-5", strTexture);
		strTexture = texPath + L"StatusMoji1-6.png";
		app->RegisterTexture(L"StatusMoji1-6", strTexture);
		strTexture = texPath + L"ScoreTime.png";
		app->RegisterTexture(L"ScoreComment", strTexture);
		strTexture = texPath + L"LoadMoji.png";
		app->RegisterTexture(L"LoadMoji", strTexture);
		strTexture = texPath + L"LoadMoji1.png";
		app->RegisterTexture(L"LoadMoji1", strTexture);
		strTexture = texPath + L"LoadMoji2.png";
		app->RegisterTexture(L"LoadMoji2", strTexture);
		strTexture = texPath + L"LoadMoji3.png";
		app->RegisterTexture(L"LoadMoji3", strTexture);
		strTexture = texPath + L"LoadMoji4.png";
		app->RegisterTexture(L"LoadMoji4", strTexture);
		strTexture = texPath + L"BossMoji.png";
		app->RegisterTexture(L"BossMoji", strTexture);
		strTexture = texPath + L"CountMoji.png";
		app->RegisterTexture(L"CountMoji", strTexture);
		strTexture = texPath + L"StatusSetumei2.png";
		app->RegisterTexture(L"StatusSetumei2", strTexture);
		strTexture = texPath + L"LevelTexture.png";
		app->RegisterTexture(L"LevelTexture", strTexture);	
		strTexture = texPath + L"Skip_pad.png";
		app->RegisterTexture(L"Skip_pad", strTexture);
		strTexture = texPath + L"Skip.png";
		app->RegisterTexture(L"Skip", strTexture);
		strTexture = texPath + L"Space.png";
		app->RegisterTexture(L"Space", strTexture);

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
		app->RegisterTexture(L"Charge_s", strTexture);
		strTexture = comPath + L"Charge_s.png";
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
		strTexture = comPath + L"Sousa2.png";
		app->RegisterTexture(L"Sousa2", strTexture);
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
		//auto boneMultiModelMesh = MultiMeshResource::CreateBoneModelMultiMesh(modPath, L"NewBaikin.bmf");
		//app->RegisterResource(L"Baikin_Mesh", boneMultiModelMesh);

		//スタティックマルチモデル
		auto staticMultiModelMesh = MultiMeshResource::CreateStaticModelMultiMesh(modPath, L"Obstacle3-2.bmf");
		app->RegisterResource(L"Obstacle_Mesh3", staticMultiModelMesh);

		staticMultiModelMesh = MultiMeshResource::CreateStaticModelMultiMesh(modPath, L"Pillar.bmf");
		app->RegisterResource(L"Obstacle_Gate", staticMultiModelMesh);

		//ボーンモデル
		auto boneModelMesh = MeshResource::CreateBoneModelMesh(modPath, L"Newkakera.bmf");
		app->RegisterResource(L"Kakera_Mesh", boneModelMesh);

		boneModelMesh = MeshResource::CreateBoneModelMesh(modPath, L"Boss.bmf");
		app->RegisterResource(L"Boss_Mesh", boneModelMesh);


		boneModelMesh = MeshResource::CreateBoneModelMesh(modPath, L"Newkakera2.bmf");
		app->RegisterResource(L"Kakera_Mesh3", boneModelMesh);

		boneModelMesh = MeshResource::CreateBoneModelMesh(modPath, L"Newkakera2-1.bmf");
		app->RegisterResource(L"Kakera_Mesh4", boneModelMesh);

		boneModelMesh = MeshResource::CreateBoneModelMesh(modPath, L"Newkakera2-2.bmf");
		app->RegisterResource(L"Kakera_Mesh5", boneModelMesh);	
		
		boneModelMesh = MeshResource::CreateBoneModelMesh(modPath, L"NewSensuikan.bmf");
		app->RegisterResource(L"Sensuikan_Mesh", boneModelMesh);

		boneModelMesh = MeshResource::CreateBoneModelMesh(modPath, L"Wall.bmf");
		app->RegisterResource(L"Wall", boneModelMesh);


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
		soundWav = SoundPath + L"PieceDown.wav";
		App::GetApp()->RegisterWav(L"PieceDownSE", soundWav);
		soundWav = SoundPath + L"TitleSE.wav";
		App::GetApp()->RegisterWav(L"TitleSE", soundWav);
		soundWav = SoundPath + L"ScoreSE.wav";
		App::GetApp()->RegisterWav(L"ScoreSE", soundWav);
		soundWav = SoundPath + L"LampSE.wav";
		App::GetApp()->RegisterWav(L"LampSE", soundWav);
		soundWav = SoundPath + L"DeadSE.wav";
		App::GetApp()->RegisterWav(L"DeadSE", soundWav);
		soundWav = SoundPath + L"DamageSE.wav";
		App::GetApp()->RegisterWav(L"DamageSE", soundWav);
		soundWav = SoundPath + L"CountDownSE.wav";
		App::GetApp()->RegisterWav(L"CountDownSE", soundWav);
		soundWav = SoundPath + L"CommentSE.wav";
		App::GetApp()->RegisterWav(L"CommentSE", soundWav);
		soundWav = SoundPath + L"ChoiceSE.wav";
		App::GetApp()->RegisterWav(L"ChoiceSE", soundWav);
		soundWav = SoundPath + L"BreakSE.wav";
		App::GetApp()->RegisterWav(L"BreakSE", soundWav);
		soundWav = SoundPath + L"AttackSE.wav";
		App::GetApp()->RegisterWav(L"AttackSE", soundWav);
		soundWav = SoundPath + L"Charge1.wav";
		App::GetApp()->RegisterWav(L"Charge1", soundWav);
		soundWav = SoundPath + L"Charge2.wav";
		App::GetApp()->RegisterWav(L"Charge2", soundWav);
		soundWav = SoundPath + L"Charge3.wav";
		App::GetApp()->RegisterWav(L"Charge3", soundWav);
		soundWav = SoundPath + L"PlayerbreakSE.wav";
		App::GetApp()->RegisterWav(L"PlayerbreakSE", soundWav);

		//BGM
		soundWav = SoundPath + L"ScaryBGM.wav";
		App::GetApp()->RegisterWav(L"ScaryBGM", soundWav);
		soundWav = SoundPath + L"BossBGM.wav";
		App::GetApp()->RegisterWav(L"BossBGM", soundWav);
		soundWav = SoundPath + L"GameOverBGM.wav";
		App::GetApp()->RegisterWav(L"GameOverBGM", soundWav);
		soundWav = SoundPath + L"ScoreBGM.wav";
		App::GetApp()->RegisterWav(L"ScoreBGM", soundWav);
		soundWav = SoundPath + L"GameClearBGM.wav";
		App::GetApp()->RegisterWav(L"GameClearBGM", soundWav);
		soundWav = SoundPath + L"TutorialBGM.wav";
		App::GetApp()->RegisterWav(L"TutorialBGM", soundWav);
		soundWav = SoundPath + L"TitleBGM.wav";
		App::GetApp()->RegisterWav(L"TitleBGM", soundWav);

	}

	void Scene::OnCreate() {
		try {
			m_gameStage = -1;
			// 背景色を設定
			SetClearColor(Col4(1.0f, 0.5625f, 0.582031f, 1.0f)); // ミッドナイトブルー

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
		if (event->m_MsgStr == L"ToGameStage1") {
			//ゲームステージの設定
			ResetActiveStage<GameStage1>();
		}
		else if (event->m_MsgStr == L"ToGameStage2") {
			//ゲームステージの設定
			ResetActiveStage<GameStage2>();
		}
		else if (event->m_MsgStr == L"ToGameStage3") {
			//ゲームステージの設定
			ResetActiveStage<GameStage3>();
		}
		else if (event->m_MsgStr == L"ToGameStage4") {
			//ゲームステージの設定
			ResetActiveStage<GameStage4>();
		}
		else if (event->m_MsgStr == L"ToGameStage5") {
			//ゲームステージの設定
			ResetActiveStage<GameStage5>();
		}
		else if (event->m_MsgStr == L"ToGameStage6") {
			//ゲームステージの設定
			ResetActiveStage<GameStage6>();
		}
		else if (event->m_MsgStr == L"ToGameStage7") {
			//ゲームステージの設定
			ResetActiveStage<GameStage7>();
		}
		else if (event->m_MsgStr == L"ToGameStage8") {
			//ゲームステージの設定
			ResetActiveStage<GameStage8>();
		}
		else if (event->m_MsgStr == L"ToGameStage9") {
			//ゲームステージの設定
			ResetActiveStage<GameStage9>();
		}
		else if (event->m_MsgStr == L"ToGameStage10") {
			//ゲームステージの設定
			ResetActiveStage<GameStage10>();
		}
		else if (event->m_MsgStr == L"ToGameStage11") {
			//ゲームステージの設定
			ResetActiveStage<GameStage11>();
		}
		else if (event->m_MsgStr == L"ToGameStage12") {
			//ゲームステージの設定
			ResetActiveStage<GameStage12>();
		}
		else if (event->m_MsgStr == L"ToStartStage") {
			ResetActiveStage<TitleStage>();
		}
		else if (event->m_MsgStr == L"ToTutorialStage") {
			ResetActiveStage<TutorialStage>();
		}
		else if (event->m_MsgStr == L"ToClearStage") {
			ResetActiveStage<ClearStage>();
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
		else if (event->m_MsgStr == L"ToMovieStage") {
			ResetActiveStage<MyMovieStage>();
		}
	}

	void Scene::SetPlayFlag(bool flag){
		m_PlayFlag = flag;
	}
	bool Scene::GetPlayFlag(){
		return m_PlayFlag;
	}

	int Scene::GetDashStatus() {
		return m_dashStatus;
	}
	void Scene::SetDashStatus(int status) {
		m_dashStatus = status;
	}
	void Scene::AddDashStatus(int status) {
		m_dashStatus += status;
	}
	//弾の射程
	float Scene::GetBulletLength() {
		auto bulletLength = 20.0f;
		switch (m_bulletLengthStatus)
		{
		case 0:
			bulletLength = 20.0f;
			break;
		case 1:
			bulletLength = 25.0f;
			break;
		case 2:
			bulletLength = 30.0f;
			break;
		case 3:
			bulletLength = 40.0f;
			break;
		default:
			bulletLength = 40.0f;
			break;
		}

		return bulletLength;
	}
	int Scene::GetBulletLengthStatus() {
		return m_bulletLengthStatus;
	}
	void Scene::SetBulletLengthStatus(int status) {
		m_bulletLengthStatus = status;
	}
	void Scene::AddBulletLengthStatus(int status) {
		m_bulletLengthStatus += status;
	}
	//大きなウイルスの取得率
	int Scene::GetBigPieceUp() {
		auto littlePiecce = 6;
		switch (m_PieceStatus)
		{
		case 0:
			littlePiecce = 6;
			break;
		case 1:
			littlePiecce = 8;
			break;
		case 2:
			littlePiecce = 10;
			break;
		case 3:
			littlePiecce = 12;
			break;
		default:
			littlePiecce = 12;
			break;
		}

		return littlePiecce;
	}
	int Scene::GetBigPieceUpStatus() {
		return m_PieceStatus;
	}
	void Scene::SetBigPieceUpStatus(int status) {
		m_PieceStatus = status;
	}
	void Scene::AddBigPieceUpStatus(int status) {
		m_PieceStatus += status;
	}
	//欠片の取得範囲
	float Scene::GetChainRange() {
		float chainRange = 1.0f;
		switch (m_chainRangeStatus)
		{
		case 0:
			chainRange = 1.0f;
			break;
		case 1:
			chainRange = 1.25f;
			break;
		case 2:
			chainRange = 1.5f;
			break;
		case 3:
			chainRange = 2.0f;
			break;
		default:
			chainRange = 2.0f;
			break;
		}
		return chainRange;
	}
	int Scene::GetChainRangeStatus() {
		return m_chainRangeStatus;
	}
	void Scene::SetChainRargeStatus(int status) {
		m_chainRangeStatus = status;
	}
	void Scene::AddChainRargeStatus(int status) {
		m_chainRangeStatus += status;
	}
	//弾の火力
	float Scene::GetBulletPower() {
		float bulletPower = 1.0f;
		switch (m_bulletPowerStatus)
		{
		case 0:
			bulletPower = 1.0f;
			break;
		case 1:
			bulletPower = 1.5f;
			break;
		case 2:
			bulletPower = 2.0f;
			break;
		case 3:
			bulletPower = 3.0f;
			break;
		default:
			bulletPower = 3.0f;
			break;
		}
		return bulletPower;
	}
	int Scene::GetBulletPowerStatus() {
		return m_bulletPowerStatus;
	}
	void Scene::SetBulletPowerStatus(int status) {
		m_bulletPowerStatus = status;
	}
	void Scene::AddBulletPowerStatus(int status) {
		m_bulletPowerStatus += status;
	}
	//弾のチャージ時間
	float Scene::GetBulletTime() {
		float bulletTime = 1.0f;
		switch (m_bulletTimeStatus)
		{
		case 0:
			bulletTime = 1.0f;
			break;
		case 1:
			bulletTime = 0.8f;
			break;
		case 2:
			bulletTime = 0.6f;
			break;
		case 3:
			bulletTime = 0.4f;
			break;
		default:
			bulletTime = 0.4f;
			break;
		}
		return bulletTime;
	}
	int Scene::GetBulletTimeStatus() {
		return m_bulletTimeStatus;
	}
	void Scene::SetBulletTimeStatus(int status) {
		m_bulletTimeStatus = status;
	}
	void Scene::AddBulletTimeStatus(int status) {
		m_bulletTimeStatus += status;
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

	int Scene::GetNextStage() {
		return m_nextStage;
	}
	void Scene::SetNextStage(int stage) {
		m_nextStage = stage;
	}

	int  Scene::GetAchievementPoint()
	{
		return m_achievementPoint;
	}

	void Scene::SetAchievementPoint(int achievementPoint)
	{
		m_achievementPoint = achievementPoint;
	}

	void Scene::AddAchievementPoint(int achievementPoint)
	{
		m_achievementPoint += achievementPoint;
	}
	void Scene::MinusAchievementPoint(int achievementPoint) {
		m_achievementPoint -= achievementPoint;
	}

	int Scene::GetBigPieceCount()
	{
		return m_count;
	}
	void Scene::AddBigPieceCount(int count)
	{
		m_count += count;
	}

	void Scene::SetBigPieceCount(int count)
	{
		m_count = count;
    }

	bool Scene::GetFirstTimeStage(int num) {		
		return m_firstTimeStage[num];
	}
	void Scene::SetFirstTimeStage(int num,bool firstTime) {
		m_firstTimeStage[num] = firstTime;
	}

	//リセットボタン
	void Scene::ResetButton() {
		auto& cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto& keyState = App::GetApp()->GetInputDevice().GetKeyState();

		if ((cntlVec[0].wButtons & XINPUT_GAMEPAD_START && cntlVec[0].wButtons & XINPUT_GAMEPAD_BACK)||
			(keyState.m_bPressedKeyTbl[VK_DELETE] && keyState.m_bLastKeyTbl[VK_SHIFT])) {
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToStartStage");
			//ポイント類のリセット
			SetAchievementPoint(0);
			SetDashStatus(0);
			SetBulletLengthStatus(0);
			SetBigPieceUpStatus(0);
			SetChainRargeStatus(0);
			SetBulletPowerStatus(0);
			SetBulletTimeStatus(0);
			//ステージアンロックリセット
			for (int i = 0; i < 12; i++) {
				SetFirstTimeStage(i, false);
			}

		}
	}
}
//end basecross
