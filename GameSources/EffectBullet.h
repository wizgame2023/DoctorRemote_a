/*!
@file EffectBullet.h
@brief 弾の当たった時のエフェクト
担当：三瓶裕太
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class EffectBullet : public GameObject
	{
	private:
		bool m_Trace;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
		uint32_t m_PieceXCount;//一フレームにつきの座標
		uint32_t m_PieceYCount;//一フレームにつきの座標
		uint32_t m_PieceIndex;//おそらくこれはアニメが何フレーム目か数える奴
		float m_AnimeTime;
		wstring m_TextureKey;
		//トータル時間
		float m_TotalTime;
		//バックアップ頂点データ
		vector<VertexPositionColorTexture> m_BackupVertices;

	public:
		EffectBullet(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec2& StartPos, uint32_t PieceXCount, uint32_t PieceYCount,
			float AnimeTime);
		//破棄
		virtual ~EffectBullet();
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate()override;

	};

}
//end namespace basecross