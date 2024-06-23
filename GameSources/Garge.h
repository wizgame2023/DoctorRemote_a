/*!
@file Garge.h
@brief ゲージ
担当：逸見
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Garge :public GameObject {
	protected:
		//表示する画像の大きさ
		const float m_sizeX;
		const float m_sizeY;

		//ゲージの単位
		float m_moveW;
		float m_moveH;

		//ゲージを表示する割合
		float m_ratio;

		//画像を表示する幅と高さ
		float m_height;
		float m_width;


		//頂点データ
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;
		shared_ptr<PCTSpriteDraw> m_draw;

		//頂点の色
		Col4 m_color;
		//画像の色
		Col4 m_color2;

		shared_ptr<Transform> m_trans;
		wstring m_meshResName;

		//表示する場所
		Vec3 m_screen;
		Vec3 m_distance;

	public:
		Garge(const shared_ptr<Stage>& stagePtr,
			const float sizeX, const float sizeY, wstring meshResName, //画像のサイズ
			float ratio, float width, float heigth, //ゲージの割合と表示するサイズ
			Col4 color, Col4 color2, Vec3 screen, Vec3 distance = Vec3(0.0));
		virtual ~Garge(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void OnClear(bool OnOff);

		void UpdateValue(float ratio);
		void SetColor(Col4 color);
		void ThisDestroy();

	};
}
//end namespace basecross
