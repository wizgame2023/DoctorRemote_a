/*!
@file Radar.cpp
@brief レーダー実体
担当　三瓶裕太
これでやりたいこと　EnemyとPlayerの一人称視点の角度で見るとどの方向なのかわかるようにする
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//コンストラクタ
	Radar::Radar(const shared_ptr<Stage>& StagePtr):
		GameObject(StagePtr)
	{

	}
	//デストラクタ
	Radar::~Radar()
	{

	}

	//初期化
	void Radar::OnCreate()
	{
		//auto ptrTransform = GetComponent<Transform>();//toransformを取得

		//ptrTransform->SetPosition(m_Position);//ポジションを決定
		//ptrTransform->SetScale(m_Scale);//大きさを決める
		//auto a = GetComponent<GameObject>();

		// ポリゴンの自作

		Col4 color(1, 1, 1, 1); // ポリゴンの色
		const float w = 100.0f; // ポリゴンの幅
		const float h = 100.0f; // ポリゴンの高さ
		vector<VertexPositionColorTexture> vertices = { // 頂点データ
			//             座標           ,頂点色,        UV座標
			{Vec3(-w * 0.5f, +h * 0.5f, 0), color, Vec2(0.0f, 0.0f)}, // 0
			{Vec3(+w * 0.5f, +h * 0.5f, 0), color, Vec2(1.0f, 0.0f)}, // 1
			{Vec3(-w * 0.5f, -h * 0.5f, 0), color, Vec2(0.0f, 1.0f)}, // 2
			{Vec3(+w * 0.5f, -h * 0.5f, 0), color, Vec2(1.0f, 1.0f)}, // 3
		};

		vector<uint16_t> indices = { // 頂点インデックス（頂点のつなげ順）
			0, 1, 2, // ←これで一つのポリゴン(三角形)
			2, 1, 3  // ←こっちも
		};

		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices); // スプライト用のドローコンポーネント
		drawComp->SetTextureResource(L"Arrow");//白のテクスチャが欲しいときはHAKUSIを選択してください
		drawComp->SetSamplerState(SamplerState::LinearWrap); // テクスチャを繰り返して貼り付ける設定
		drawComp->SetDiffuse(Col4(1, 1, 1, 1.0f)); // ポリゴンを色を設定する

		// アルファブレンド(透過処理)を有効にする
		SetAlphaActive(true); // true:透過を有効、false:透過を無効


	}

	void Radar::OnUpdate()
	{
		auto transform = AddComponent<Transform>();		
		m_angle += 0.1f;
		transform->SetRotation(0.0f,0.0f,m_angle);//回転を初期化

	}
}