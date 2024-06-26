/*!
@file PieceManager.cpp
@brief ウイルスを管理
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	vector<weak_ptr<EnemyPiece>> PieceManager::enemyPieces;
	map<int, vector<shared_ptr<EnemyPiece>>> PieceManager::breakPieces;

	void PieceManager::PieceDistance(const shared_ptr<EnemyPiece>& myPiece,const shared_ptr<Bullet>& bullet) {
		auto& pieces = PieceManager::enemyPieces;
		auto& breakPiece = PieceManager::breakPieces;
		//shared_ptr<EnemyPiece> p;
		auto bulletLeve = bullet->GetBulletLevel();
		float chainRange = App::GetApp()->GetScene<Scene>()->GetChainRange();

		for (auto& wp_piece : pieces) {
			auto piece = wp_piece.lock();
			if (piece == myPiece) {
				continue;
			}
			else if (piece) {
				auto otherPos = piece->GetComponent<Transform>()->GetPosition();
				auto pos = myPiece->GetComponent<Transform>()->GetPosition();
				Vec3 distance = otherPos - pos;
				auto dis = distance.length();

				if (0.0 <= dis && dis < 5.0f* chainRange && bulletLeve >= 1) {
					piece->DelDamage(6, 0.5f);
				}
				else if (dis < 10.0f* chainRange && bulletLeve >= 2) {
					piece->DelDamage(6, 1.0f);

				}
				else if (dis < 15.0f* chainRange && bulletLeve >= 3) {
					piece->DelDamage(6, 1.5f);

				}
			}


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