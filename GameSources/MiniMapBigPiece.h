/*!
@file PieceGarge.h
@brief ミニマップにビックピースの位置を表示
担当：三瓶裕太
*/

#pragma once
#include "stdafx.h"
#include "BigPiece.h"


namespace basecross {
	class MiniMapBigPiece :public Sprite
	{
	private:
		wstring m_ObjName;
		bool m_Existence;//対応するオブジェクトがあるかを表す
	public:
		MiniMapBigPiece(const shared_ptr<Stage>& stagePtr, float width, float height, wstring meshResName, Vec3 pos, int layer,wstring objName);
		~MiniMapBigPiece()override;

		void OnCreate()override;
		void OnUpdate()override;
		void SetExistence(bool Existence);
	};
}