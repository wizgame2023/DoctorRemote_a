/*!
@file MiniMapPlayer.cpp
@brief 
ミニマップに映るPlayerの表示
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	MiniMapPlayer::MiniMapPlayer(const shared_ptr<Stage>& StagePtr,Vec3 StartPos,float lenght,float mapSize,float MiniMapSize):
		GameObject(StagePtr),
		m_StartPos(StartPos),
		m_Lenght(lenght),
		m_MapSize(mapSize),
		m_MiniMapSize(MiniMapSize),
		m_MapMagnification(MiniMapSize/mapSize),
		m_color(1.0f,1.0f,1.0f,1.0f)
	{

	}
	MiniMapPlayer::~MiniMapPlayer()
	{
	}


	void MiniMapPlayer::OnCreate()
	{
		//光の表現をするためのポリゴン作成
		Col4 color(0, 1, 0, 1.0f);//色と透明度
		vector<VertexPositionColorTexture> vertices = // 頂点データ
		{
			{Vec3((m_Lenght * -0.5f),(m_Lenght * +0.5f), 0) * m_MapMagnification, color, Vec2(0.0f, 0.0f)}, // 0
			{Vec3((m_Lenght * +0.5f),(m_Lenght * +0.5f), 0) * m_MapMagnification, color, Vec2(1.0f, 0.0f)}, // 1
			{Vec3((m_Lenght * -0.5f),(m_Lenght * -0.5f), 0) * m_MapMagnification, color, Vec2(0.0f, 1.0f)}, // 2
			{Vec3((m_Lenght * +0.5f),(m_Lenght * -0.5f), 0) * m_MapMagnification, color, Vec2(1.0f, 1.0f)}, // 3

		};

		vector<uint16_t> indices = // 頂点インデックス（頂点のつなげ順）
		{ 
		0, 1, 2, // ←これで一つのポリゴン(三角形)A
		1, 3, 2,  // ←こっちもB
		};

		m_DrawComp = AddComponent<PCTSpriteDraw>(vertices, indices); // スプライト用のドローコンポーネント
		m_DrawComp->SetTextureResource(L"MiniMapPlayer");
		m_DrawComp->SetSamplerState(SamplerState::LinearWrap); // テクスチャを繰り返して貼り付ける設定
		m_DrawComp->SetDiffuse(m_color); // ポリゴンを色を設定する

		// アルファブレンド(透過処理)を有効にする
		SetAlphaActive(true); // true:透過を有効、false:透過を無効

		SetDrawLayer(6);//表示の優先度を決める

	}

	void MiniMapPlayer::OnUpdate()
	{
		auto trans = GetComponent<Transform>();//自分のトランスフォーム取得
		auto stage = GetStage();
		auto player = stage->GetSharedGameObject<Player>(L"GamePlayer");
		auto playerTrans = player->GetComponent<Transform>();//Playerのトランスフォーム取得
		auto playerPos = playerTrans->GetPosition();//Playerの位置を取得
		auto playerRad = stage->GetSharedGameObject<Player>(L"GamePlayer")->PlayerAngle();//Playerの角度を取得

		trans->SetPosition(Vec3((playerPos.x * m_MapMagnification) + m_StartPos.x, (playerPos.z * m_MapMagnification) + m_StartPos.y, 0.0f));//位置を更新
		trans->SetRotation(Vec3(0.0f, 0.0f, playerRad));//回転をPlayerに合わせて更新
		
	}

	void MiniMapPlayer::OnClear(bool OnOff)
	{
		if (OnOff == true)//オンなら
		{
			//m_color = Col4(1.0f, 1.0f, 1.0f, 0.0f);
			m_DrawComp->SetDiffuse(Col4(0.0f, 0.0f, 0.0f, 0.0f));//透明にする
		}
		if (OnOff == false)//オフなら
		{
			m_DrawComp->SetDiffuse(m_color);//透明でなかった時の色に戻る
		}

	}
}
//end basecross
