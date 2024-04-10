/*!
@file Ligth.cpp
@brief 光、光源などの実体
担当　三瓶裕太
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	MyLight::MyLight(const shared_ptr<Stage>& StagePtr):
		GameObject(StagePtr)
	{

	}
	MyLight::~MyLight()
	{
	}


	void MyLight::OnCreate()
	{
		//光の表現をするためのポリゴン作成
		Col4 WhiteColor(1, 1, 1, 1.0f);//色と透明度
		float wide = 200.0f;//ポリゴンの幅
		const float height = 200.0f; // ポリゴンの高さ
		vector<VertexPositionColorTexture> vertices = // 頂点データ
		{ 
			//             座標           ,頂点色,        UV座標
			{Vec3(-wide * 0.5f, +height * 0.5f, 0), WhiteColor, Vec2(0.0f, 0.0f)}, // 0
			{Vec3(+wide * 0.5f, +height * 0.5f, 0), WhiteColor, Vec2(1.0f, 0.0f)}, // 1
			{Vec3(-wide * 0.5f, -height * 0.5f, 0), WhiteColor, Vec2(0.0f, 1.0f)}, // 2
			{Vec3(+wide * 0.5f, -height * 0.5f, 0), WhiteColor, Vec2(1.0f, 1.0f)}, // 3
		};

		vector<uint16_t> indices = // 頂点インデックス（頂点のつなげ順）
		{ 
		0, 1, 2, // ←これで一つのポリゴン(三角形)
		2, 1, 3  // ←こっちも
		};

		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices); // スプライト用のドローコンポーネント
		drawComp->SetTextureResource(L"White");
		drawComp->SetSamplerState(SamplerState::LinearWrap); // テクスチャを繰り返して貼り付ける設定
		drawComp->SetDiffuse(Col4(1, 1, 1, 0.3f)); // ポリゴンを色を設定する

		// アルファブレンド(透過処理)を有効にする
		SetAlphaActive(true); // true:透過を有効、false:透過を無効

	}

}
//end basecross
