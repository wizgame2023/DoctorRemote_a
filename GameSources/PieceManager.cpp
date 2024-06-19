/*!
@file PieceManager.cpp
@brief ウイルスを管理
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	vector<shared_ptr<EnemyPiece>> PieceManager::enemyPieces;
	map<int, vector<shared_ptr<EnemyPiece>>> PieceManager::breakPieces;


	void PieceManager::PieceDistance(shared_ptr<EnemyPiece>& myPiece,shared_ptr<EnemyPiece>& otherPiece) {
		auto& piece = PieceManager::enemyPieces;
		auto& breakPiece = PieceManager::breakPieces;
		
		int i = 0;
		while (i<piece.size())
		{
			otherPiece = piece[i];
			if (otherPiece == myPiece) {
				piece.erase(piece.begin() + i);
				if (piece.size() == 0) continue;

				otherPiece = piece[i];
			}

			auto otherPos = otherPiece->GetComponent<Transform>()->GetPosition();
			auto pos = myPiece->GetComponent<Transform>()->GetPosition();
			Vec3 distance = otherPos - pos;
			auto dis = distance.length();

			if (dis >= 0.0f && dis < 5.0f) {
				breakPieces[0].push_back(otherPiece);
			}
			else if (dis >= 5.0f && dis < 10.0f) {
				breakPieces[1].push_back(otherPiece);
			}
			else if (dis >= 10.0f && dis < 20.0f) {
				breakPieces[2].push_back(otherPiece);

			}
			
			if (dis >= 20.0f) {
				i++;
			}
			else {
				piece.erase(piece.begin() + i);

			}

		}
		for (int i = 0; i < piece.size(); i++) {
		}
	}

	void PieceManager::PieceDestroy() {
		auto& piece = PieceManager::enemyPieces;
		auto& breakPiece = PieceManager::breakPieces;

		for (int i = 0; i < breakPiece.size(); i++) {
			if (breakPiece.find(i)!=breakPiece.end()) {
				breakPieces.erase(i);
			}
		}
	}

}
//end namespace basecross