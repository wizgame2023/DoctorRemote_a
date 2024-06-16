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

		int m_widthNum;
		int m_heightNum;
		int m_stageNum;

		bool m_checkU;
		bool m_checkD;
		bool m_checkR;
		bool m_checkL;
		bool m_moveCheck;

		Vec3 m_pos;

		shared_ptr<UITime> m_numberSprites[10];
		shared_ptr<Sprite> m_selectSprite;
		shared_ptr<Transform> m_trans;


	public:
		StageSelectSprite(const shared_ptr<Stage>& stagePtr);
		virtual ~StageSelectSprite(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}
