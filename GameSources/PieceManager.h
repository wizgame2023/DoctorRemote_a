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
		static vector<shared_ptr<EnemyPiece>> enemyPieces;
		static map<int, vector<shared_ptr<EnemyPiece>>> breakPieces;


		static void PieceDistance(shared_ptr<EnemyPiece>& myPiece, 
			shared_ptr<EnemyPiece>& otherPiece);
		static void PieceDestroy();


	};
}
//end namespace basecross
