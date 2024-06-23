/*!
@file PieceManager.h
@brief ウイルスを管理する
担当：逸見
*/

#pragma once
#include "stdafx.h"
#include "EnemyPiece.h"

namespace basecross {
	class PieceManager{
		vector<EnemyPiece> m_otherPiece;
	public:
		static vector<weak_ptr<EnemyPiece>> enemyPieces;
		static map<int, vector<shared_ptr<EnemyPiece>>> breakPieces;


		static void PieceDistance(const shared_ptr<EnemyPiece>& myPiece, const shared_ptr<Bullet>& bullet);
		static void PieceDestroy();


	};
}
//end namespace basecross
