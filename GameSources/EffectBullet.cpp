/*!
@file EffectBullet.cpp
@brief 弾の当たった時のエフェクト
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	EffectBullet::EffectBullet(const shared_ptr<Stage>& StagePtr,const wstring& TextureKey,
		uint32_t PieceXCount, uint32_t PieceYCount,const Vec3 Bulletpos, float AnimeTime) :
	    GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_displayTime(0.0f),
		m_PieceXCount(PieceXCount),
		m_PieceYCount(PieceYCount),
		m_PieceIndex(0),
		m_Bullet(Bulletpos),
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
		m_Vertices = { // 頂点データ
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

		auto drawComp = AddComponent<PCTSpriteDraw>(m_Vertices, indices); // スプライト用のドローコンポーネント
		drawComp->SetTextureResource(m_TextureKey);//白のテクスチャが欲しいときはHAKUSIを選択してください
		drawComp->SetSamplerState(SamplerState::LinearWrap); // テクスチャを繰り返して貼り付ける設定
		drawComp->SetDiffuse(Col4(1, 1, 1, 1.0f)); // ポリゴンを色を設定する


		auto Trans = GetComponent<Transform>();
		Trans->SetPosition(Vec3(10.0f,0.0f,5.0f));

		// アルファブレンド(透過処理)を有効にする
		SetAlphaActive(true); // true:透過を有効、false:透過を無効

	}

	void EffectBullet::OnUpdate()
	{
		float DeltaTime = App::GetApp()->GetElapsedTime();//デルタタイムを取得
		m_displayTime += DeltaTime;
		if (m_displayTime >= m_AnimeTime)//テクスチャの表示時間が過ぎたら更新する
		{
			m_PieceIndex++;
			if (m_PieceIndex >= m_PieceXCount * m_PieceYCount)
			{	

				m_PieceIndex = 0;
				//GetStage()->RemoveGameObject<EffectBullet>(GetThis<EffectBullet>());

			}				

			m_displayTime = 0.0f;

		}

		vector<VertexPositionColorTexture> newVertices;
		uint32_t pieceX = m_PieceIndex % m_PieceXCount;
		uint32_t pieceY = m_PieceIndex / m_PieceXCount;//１行目の横の枚数を過ぎないと２行目に行けない
		float pieceWidth = 1.0f / (float)m_PieceXCount;//１つのテクスチャの長さ
		float pieceHeight = 1.0f / (float)m_PieceYCount;//１つのテクスチャの高さ

		float pieceStartX = (float)pieceX * pieceWidth;
		float pieceEndX = pieceStartX + pieceWidth;

		float pieceStartY = (float)pieceY * pieceHeight;
		float pieceEndY = pieceStartY + pieceHeight;

		for (size_t i = 0; i < m_Vertices.size(); i++)
		{
			Vec2 UvVertices = m_Vertices[i].textureCoordinate;
			switch (i)
			{
			case 0:
				UvVertices.x = pieceStartX;
				UvVertices.y = pieceStartY;
				break;
			case 1:
				UvVertices.x = pieceEndX;
				UvVertices.y = pieceStartY;
				break;
			case 2:
				UvVertices.x = pieceStartX;
				UvVertices.y = pieceEndY;
				break;
			case 3:
				UvVertices.x = pieceEndX;
				UvVertices.y = pieceEndY;
				break;
			default:
				break;
			}
			auto Update = VertexPositionColorTexture
			(
				m_Vertices[i].position,
				m_Vertices[i].color,
				UvVertices
			);
			newVertices.push_back(Update);
		}
		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		ptrDraw->UpdateVertices(newVertices);

	}


}
//end namespace basecross