/*!
@file EffectBullet.cpp
@brief 弾の当たった時のエフェクト
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	EffectBullet::EffectBullet(const shared_ptr<Stage>& StagePtr,const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec2& StartPos, uint32_t PieceXCount, uint32_t PieceYCount, float AnimeTime) :
	    GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_TotalTime(0.0f),
		m_PieceXCount(PieceXCount),
		m_PieceYCount(PieceYCount),
		m_PieceIndex(0),
		m_AnimeTime(AnimeTime)
	{
	}

	EffectBullet::~EffectBullet()
	{
	}

	void EffectBullet::OnCreate()
	{
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
		drawComp->SetTextureResource(L"Radar");//白のテクスチャが欲しいときはHAKUSIを選択してください
		drawComp->SetSamplerState(SamplerState::LinearWrap); // テクスチャを繰り返して貼り付ける設定
		drawComp->SetDiffuse(Col4(1, 1, 1, 1.0f)); // ポリゴンを色を設定する

		// アルファブレンド(透過処理)を有効にする
		SetAlphaActive(true); // true:透過を有効、false:透過を無効

	}

	void EffectBullet::OnUpdate()
	{
		float DeltaTime = App::GetApp()->GetElapsedTime();//デルタタイムを取得
		
		uint16_t pieceX = m_PieceIndex % m_PieceXCount;
		uint16_t pieceY = m_PieceIndex / m_PieceXCount;
	}


}
//end namespace basecross