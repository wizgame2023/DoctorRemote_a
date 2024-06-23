/*!
@file EffectPiece.h
@brief ウイルスが連鎖する時のエフェクト
担当：逸見
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class EffectPiece :public GameObject {
	private:
		float m_height;
		float m_topRadius;
		float m_unberRadius;
		float m_effectLoop;
		int m_square;
		bool m_isUpdate;
		bool m_effectLoopFlag;
		bool m_colFlag;
		bool m_spreadFlag;

		Vec2 m_loops;
		Vec2 m_scrollVelocity;
		Vec3 m_pos;
		Vec3 m_rot;
		Vec3 m_velocity;
		Col4 m_topCol;
		Col4 m_underCol;

		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;
		shared_ptr<BcPCTStaticDraw> m_draw;
		shared_ptr<Transform> m_trans;
		wstring m_meshResName;

		void InitializeVertices();


	public:
		EffectPiece(const shared_ptr<Stage>& stage);
		EffectPiece(const shared_ptr<Stage>& stage,
			const float height,      //高さ
			const float topRadius,   //上の円の大きさ
			const float underRadius, //下の円の大きさ
			const int square,        //何角形か
			const Vec2 loops,        //画像を縦横何回ループさせるか
			const Col4 topCol,       //上の頂点の色
			const Col4 underCol,     //下の頂点の色
			const wstring meshResname,//テクスチャ
			const Vec2 scrollVec,    //X軸,Y軸方向に動かす
			const Vec3 pos,
			const float effectLoop = 0.0f		
			);
		virtual ~EffectPiece(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		
		void ThihDestroy();
		void SetScrollSpeed(float x,float y);
		void SetTopRadius(float radius);
		void SetUnderRadius(float radius);
		void SetDeleteTime(float time);
		void SetBlendState(const BlendState state);
	};
}
//end namespace basecross
