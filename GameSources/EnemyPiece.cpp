/*!
@file EnemyPiece.cpp
@brief 敵の欠片実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	EnemyPiece::EnemyPiece(const shared_ptr<Stage>& StagePtr,
		const Vec3& position,
		const Vec3& rotate,
		const Vec3& scale,
		const bool littlePieceFlag
	) :
		GameObject(StagePtr),
		m_position(position),
		m_rotate(rotate),
		m_scale(scale),
		m_pieceDeletFlag(0),
		m_otherPieceFlag(false),
		m_pieceDeleteTime(scale.x * 0.15f),
		m_littlePieceFlag(littlePieceFlag),
		m_hp(3),
		m_breakCount(1.0f),
		m_meshResName(L"Kakera_Mesh")

	{}

	void EnemyPiece::OnCreate() {
		auto stage = GetStage();
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_scale);
		ptrTrans->SetRotation(m_rotate);
		ptrTrans->SetPosition(m_position);

		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.5f, 0.5f, 0.5f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.2f, 0.0f)
		);

		//オブジェクトの描画
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		//ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(m_meshResName);
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->AddAnimation(L"Default", 0, 90, true, 30.0f);
		ptrDraw->ChangeCurrentAnimation(L"Default");



		//オブジェクトの影の描画
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(m_meshResName);
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//コライダー
		auto colPtr = AddComponent<CollisionSphere>();
		colPtr->SetDrawActive(true);
		colPtr->SetAfterCollision(AfterCollision::None);
		colPtr->SetFixed(false);


		AddTag(L"EnemyPiece");
		vector<shared_ptr<EnemyPiece>> breakedObject;
		//中心破壊

		//しゅとくしたvector配列の中身を破壊
	}

	void EnemyPiece::OnUpdate() {
		auto stage = GetStage();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		ptrDraw->UpdateAnimation(elapsedTime);
		m_trans = GetComponent<Transform>();
		m_trans->SetScale(m_scale);

		if (m_otherPieceFlag) {
			

			auto& piece = PieceManager::enemyPieces;
			auto& breakPiece = PieceManager::breakPieces;
			bool isBreaked = true;
			m_breakCount -= elapsedTime;
			if (m_breakCount < 0) {
				isBreaked = false;
				for (int i = 0; i < PieceManager::breakPieces.size(); i++) {
					if (breakPiece[i].size() > 0)
					{
						for (auto& bp : breakPiece[i]) {
							GetStage()->RemoveGameObject<EnemyPiece>(bp);
							bp->ScatterLittlePiece(3);
							m_breakCount = 1.0f;
						}
						PieceManager::breakPieces.erase(i);
						isBreaked = true;
						break;
					}
				}
			}


			if (/*PieceManager::breakPieces.empty()*/!isBreaked) {
				m_otherPieceFlag = false;
				stage->RemoveGameObject<EnemyPiece>(GetThis<EnemyPiece>());

				m_pieceDeletFlag = 0;
			}
		}
		////時間差で自分自身を消す
		//if (m_hp <= 0) {
		//	m_pieceDeleteTime -= elapsedTime;
		//	m_scale -= 2.0f * elapsedTime * 3.0f;
		//	if (m_pieceDeleteTime < 0) {

		//		//自分自身を廃棄する
		//		stage->RemoveGameObject<EnemyPiece>(GetThis<EnemyPiece>());

		//		m_pieceDeletFlag = 0;

		//	}
		//}

		wstringstream wss;//デバック用文字列
		wss << L"brekPiece[0] :" << PieceManager::breakPieces[0].size() << endl;
		wss << L"brekPiece[1] :" << PieceManager::breakPieces[1].size() << endl;
		wss << L"brekPiece[2] :" << PieceManager::breakPieces[2].size() << endl;
		wss << L"brekPiece :" << PieceManager::breakPieces.size() << endl;
		wss << L"Piece :" << PieceManager::enemyPieces.size() << endl;
		wss << L"Count :" << m_breakCount << endl;







		auto scene = App::GetApp()->GetScene<Scene>();//シーン取得
		scene->SetDebugString(L"a\n" + wss.str());


	}

	void EnemyPiece::OnCollisionEnter(shared_ptr<GameObject>& other) {
		auto stage = GetStage();
		auto player = stage->GetSharedGameObject<Player>(L"GamePlayer");
		auto stageManager = stage->GetSharedGameObject<StageManager>(L"StageManager");
		if (other->FindTag(L"Bullet")){
			m_bullet = dynamic_pointer_cast<Bullet>(other);
			//欠片の体力
			if (m_hp > 0) {
				m_hp -= m_bullet.lock()->GetAttack();
			}
			if (m_hp <= 0) {
				m_pieceDeletFlag ++;
			}
			//欠片をばらまく
			if (m_pieceDeletFlag == 1) {
				if (m_littlePieceFlag) {
					ScatterLittlePiece(3);
					m_otherPieceFlag = true;
					PieceManager::PieceDistance(GetThis<EnemyPiece>(), m_otherPiece);
					
					
				}
			}
			//m_pieceDeletFlag = true;
			//m_pieceDeletFlag++;
			
			//効果音
			auto pieceSE = App::GetApp()->GetXAudio2Manager();
			pieceSE->Start(L"PieceDownSE", 0, 0.5f);//SEはじめ
		}
		if (other->FindTag(L"Player")) {
			stageManager->SetHp(-10.0f);
		}
		if (other->FindTag(L"Ground")) {
			m_ground = true;
		}
	}

	//小さい欠片を散らばせる
	void EnemyPiece::ScatterLittlePiece(int little) {
		auto stage = GetStage();
		auto player = stage->GetSharedGameObject<Player>(L"GamePlayer");

		for (int i = 0; i < little; i++) {
			stage->AddGameObject<PieceLittle>(GetThis<EnemyPiece>(), player, (360 / little) * i);

			auto effect = stage->AddGameObject<EffectPiece>();
			auto effectTrans = effect->GetComponent<Transform>();
			effectTrans->SetPosition(m_position);
		}

	}

	//ボスのイベント
	void EnemyPiece::Event(float deg) {
		auto grav = AddComponent<Gravity>();
		auto ptrTrans = GetComponent<Transform>();
		Vec3 pos = ptrTrans->GetPosition();

		//auto bossTrans = m_boss->GetComponent<Transform>();
		//auto bossPos = bossTrans->GetPosition();

		//pos = bossPos;
		//落ちてくる高さ
		pos.y += 6.0f;
		Quat qt = ptrTrans->GetQuaternion();
		float rad = XMConvertToRadians(deg);

		Vec3 velo(sin(rad), 1.0f, cos(rad));
		velo *= 7.0f;
		m_velocity = velo;
		ptrTrans->SetPosition(pos);

	}

	//ボスのイベントの更新処理
	void EnemyPiece::UpdateEvent() {
		//auto grav = GetComponent<Gravity>();
		auto elapsed = App::GetApp()->GetElapsedTime();
		auto ptrTrans = GetComponent<Transform>();
		if (!m_ground) {
			auto pos = ptrTrans->GetPosition();
			pos += m_velocity * elapsed;
			ptrTrans->SetPosition(pos);
		}
		else if (m_ground) {
			auto grav = GetComponent<Gravity>();
			grav->SetGravityZero();
		}

	}

	Vec3 EnemyPiece::GetPos() {
		return m_position;
	}
	Vec3 EnemyPiece::GetRot() {
		return m_rotate;
	}
	int EnemyPiece::GetDeletFlag() {
		return m_pieceDeletFlag;
	}
	
}

//end basecross
