/*!
@file Sprite.h
@brief スプライト
担当：逸見
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Sprite :public GameObject {
	private:
		//画像の大きさ
		
		//画像の表示サイズ
		float m_width;
		float m_heigth;
		int m_layer;

		bool m_OnOff;//透明状態かを示す変数

		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;
		shared_ptr<PCTSpriteDraw> m_draw;
		wstring m_meshResName;

		shared_ptr<Transform> m_trans;

		Vec3 m_pos;
		Vec3 m_rot;
		Col4 m_color;

	protected:
		int m_numPtr;//何番目の配列にポインタを入れたかを表す変数

	public:
		Sprite(const shared_ptr<Stage>& stagePtr,float width, float heigth,
			wstring meshResName, Vec3 pos);
		Sprite(const shared_ptr<Stage>& stagePtr, float width, float heigth,
			wstring meshResName, Vec3 pos, int layer);
		Sprite(const shared_ptr<Stage>& stagePtr, float width, float heigth,
			wstring meshResName, Vec3 pos,Vec3 rot, int layer = 1);
		virtual ~Sprite(){}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void UpdateRank(int value);
		void UpdateIfClear(int value);
		void UpdateCount(int value);
		void UpdatePoint(int value);
		void ThisDestroy();
		void Blinking(float count);

		Col4 GetColor();
		void SetColor(Col4 color);
		int GetNumPtr();//自分の登録されている配列の番号を返す
		void SetNumPtr(int afterNum);//自分の配列の番号を入れる
		void OnClear(bool OnOff);//透明になる関数
		//bool SetOnOff(bool OnOff);//透明になっているか教える
		bool GetOnOff();
	};

}
//end namespace basecross