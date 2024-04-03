/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class HemmiStage : public Stage {
		void CreateViewLight(); //ビューの作成

	public:
		//構築と破棄
		HemmiStage() :Stage() {}
		virtual ~HemmiStage() {}

		virtual void OnCreate()override; //初期化

		void CreateEnemyPiece();
	};
}
//end namespace basecross

