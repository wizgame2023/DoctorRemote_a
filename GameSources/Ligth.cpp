/*!
@file Ligth.cpp
@brief 光、光源などの実体
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
			//{Vec3(-wide * 0.5f, +height * 0.5f, 0), WhiteColor, Vec2(0.0f, 0.0f)}, // 0
			//{Vec3(+wide * 0.5f, +height * 0.5f, 0), WhiteColor, Vec2(1.0f, 0.0f)}, // 1
			//{Vec3(-wide * 0.5f, -height * 0.5f, 0), WhiteColor, Vec2(0.0f, 1.0f)}, // 2
			//{Vec3(+wide * 0.5f, -height * 0.5f, 0), WhiteColor, Vec2(1.0f, 1.0f)}, // 3
			{Vec3(-640.0f, 480.0f, 0), WhiteColor, Vec2(0.0f, 0.0f)}, // 0
			{Vec3(-640.0f, 400.0f, 0), WhiteColor, Vec2(0.0f, 0.0f)}, // 1
			{Vec3(-640.0f, -480.0f, 0), WhiteColor, Vec2(0.0f, 0.0f)}, // 2
			{Vec3(-80.0f, -80.0f, 0), WhiteColor, Vec2(0.0f, 0.0f)}, // 3
			{Vec3(-0.0f, -480.0f, 0), WhiteColor, Vec2(0.0f, 0.0f)}, // 4
			{Vec3(0.0f, -80.0f, 0), WhiteColor, Vec2(0.0f, 0.0f)}, // 5
			{Vec3(640.0f, 480.0f, 0), WhiteColor, Vec2(0.0f, 0.0f)}, // 6
			{Vec3(640.0f, 400.0f, 0), WhiteColor, Vec2(0.0f, 0.0f)}, // 7
			{Vec3(640.0f, -480.0f, 0), WhiteColor, Vec2(0.0f, 0.0f)}, // 8
			{Vec3(80.0f, -80.0f, 0), WhiteColor, Vec2(0.0f, 0.0f)}, // 9




		};

		vector<uint16_t> indices = // 頂点インデックス（頂点のつなげ順）
		{ 
		0, 1, 2, // ←これで一つのポリゴン(三角形)A
		1, 3, 2,  // ←こっちもB
		2, 3, 4,//C
		4, 5, 3,//D
		6, 7, 8,//E
		8, 7, 9,//F
		9, 8, 4,//G
		4, 5, 9//H

		};

		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices); // スプライト用のドローコンポーネント
		drawComp->SetTextureResource(L"Black");
		drawComp->SetSamplerState(SamplerState::LinearWrap); // テクスチャを繰り返して貼り付ける設定
		drawComp->SetDiffuse(Col4(1, 1, 1, 0.7f)); // ポリゴンを色を設定する

		// アルファブレンド(透過処理)を有効にする
		SetAlphaActive(true); // true:透過を有効、false:透過を無効

	}

}
//end basecross
