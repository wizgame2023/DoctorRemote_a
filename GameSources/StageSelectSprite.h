/*!
@file StageSelectSprite.h
@brief 動かすことができるスプライト
担当：逸見
*/

#pragma once
#include "stdafx.h"
#include "Sprite.h"
#include "UITime.h"

namespace basecross {
	class StageSelectSprite :public GameObject {
	private:
		float m_width;
		float m_widthUnit;
		float m_widthMax;
		float m_widthMin;
		float m_height;
		float m_heightUnit;
		float m_heightMax;
		float m_heightMin;
		float m_sizeX;
		float m_sizeY;
		float m_frameSize;
		float m_blinkTime;

		int m_widthNum;
		int m_heightNum;
		int m_stageNum;
		int m_limitNum;

		bool m_checkU;
		bool m_checkD;
		bool m_checkR;
		bool m_checkL;
		bool m_moveCheck;
		bool m_display;
		bool m_displayNumber;

		Vec3 m_pos;
		wstring m_spritesName;
		wstring m_frameName;

		shared_ptr<UITime> m_numberSprites[10];
		shared_ptr<Sprite> m_baseSprite[30];
		shared_ptr<Sprite> m_selectSprite;
		shared_ptr<Transform> m_trans;


	public:
		StageSelectSprite(const shared_ptr<Stage>& stagePtr,
			const wstring sprites = L"White",//選択する画像
			const wstring frame = L"White" //フレームの画像
			);
		StageSelectSprite(const shared_ptr<Stage>& stagePtr,
			const Vec3 pos,       //表示位置
			const float sizeX,    //画像の縦サイズ
			const float sizeY,    //画像の横サイズ
			const float widthUnit,//次の画像までの幅（横）
			const float heightUnit,//次の画像までの幅（縦）
			const float widthNum,  //横に何個表示させるか
			const float heightNum, //縦に何個表示させるか
			const float frameSize, //フレーム部分の大きさ
			const wstring sprites,//選択する画像
			const wstring frame,  //フレームの画像
			const bool displayNumber = false,//ステージ数を表示させるか
			const bool display = true //選択する画像の表示をさせるか
		);
		virtual ~StageSelectSprite(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;


		Vec3 GetSpritePostion(const int w, const int h);
		int GetNum();
		float GetBlinkTime();
		void SetLimitNum(int num);
		void ThisDestroy();
	};
}
