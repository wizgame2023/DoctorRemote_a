/*!
@file Player.cpp
@brief プレイヤー実体
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class Player : public GameObject;
	//	用途: プレイヤー
	//--------------------------------------------------------------------------------------
	Player::Player(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_hp(0),
		m_speed(5.0f),
		m_meshResName(L"DEFAULT_CUBE")
	{}

	Vec2 Player::GetInputState()const {
		Vec2 ret;
		ret.x = 0.0f;
		ret.y = 0.0f;
		//コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].bConnected)
		{
			ret.x = cntlVec[0].fThumbLX;
			ret.y = cntlVec[0].fThumbLY;
		}
		return ret;
	}

	Vec3 Player::GetMoveVector()const {
		Vec3 angle(0, 0, 0);
		//入力を取得
		auto inPut = GetInputState();
		float moveX = inPut.x;
		float moveZ = inPut.y;
		if (moveX != 0 || moveZ != 0){
			float moveLength = 0; //動いた時のスピード
			auto ptrTrasform = GetComponent<Transform>();
			auto ptrCamera = OnGetDrawCamera();

			//進行方向の向きを計算
			auto front = ptrTrasform->GetPosition() - ptrCamera->GetEye();
			front.y = 0;
			front.normalize();

			//進行方向の向きからの角度を算出
			float frontAngle = atan2(front.z, front.x);
			
			//コントローラの向きを計算
			Vec2 moveVec(moveX, moveZ);
			//角度からベクトルを作成
			angle = Vec3(cos(frontAngle), 0.0f, sin(frontAngle));
			//正規化
			angle.normalize();

			//移動サイズ
			float moveSize = moveVec.length();
			angle *= moveSize;

			//Y軸は変化させない
			angle.y = 0.0f;
			
		}

			return angle;
	}

	void Player::MovePlayer() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		//角度を計算している関数を代入
		auto angle = GetMoveVector();
		auto cntl = GetInputState();

		if (angle.length() > 0.0f) {

			Vec3 moveAngle = angle;
			if (cntl.y < 0.0f) {
				auto subAngle = atan2(moveAngle.z, moveAngle.x);
				subAngle += XM_PI;
				moveAngle = Vec3(cos(subAngle), 0.0f, sin(subAngle));
			}


			auto pos = GetComponent<Transform>()->GetPosition();
			pos += moveAngle * elapsedTime * m_speed;
			GetComponent<Transform>()->SetPosition(pos);
		}

		//回転の計算
		if (angle.length() > 0.0f) {
			auto unilPtr = GetBehavior<UtilBehavior>();
			//補間処理を行う回転
			unilPtr->RotToHead(angle, 1.0f);
		}
	}


	void Player::OnCreate(){
		//初期位置などの設定
		m_trans = GetComponent<Transform>();
		m_trans->SetScale(1.0f, 1.0f, 2.0f);
		m_trans->SetRotation(0.0f, 30.0f, 0.0f);
		m_trans->SetPosition(0.0f, 0.5f, 0.0f);

		//描画コンポーネント
		auto draw_Comp = AddComponent<BcPNStaticDraw>();
		draw_Comp->SetMeshResource(m_meshResName);
		draw_Comp->SetOwnShadowActive(true);
		draw_Comp->SetFogEnabled(true);

		//影をつける
		auto shadowComp = AddComponent<Shadowmap>();
		shadowComp->SetMeshResource(m_meshResName);

		auto colPtr = AddComponent<CollisionObb>();
		colPtr->SetDrawActive(false);
		colPtr->SetAfterCollision(AfterCollision::None);

		AddTag(L"Player");

		//カメラオブジェクトを取得する
		auto ptrCamera = dynamic_pointer_cast<MainCamera>(OnGetDrawCamera());
		if (ptrCamera) {
			ptrCamera->SetTarget(GetThis<GameObject>());
		}

	}

	void Player::OnUpdate(){
		MovePlayer();
		auto stage = GetStage();

		//進行方向の向きを計算
		auto ptrTransform = GetComponent<Transform>();
		auto ptrPos = ptrTransform->GetPosition();
		auto ptrCamera = OnGetDrawCamera();
		auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();
		front.y = 0;
		front.normalize();
		//進行方向の向きからの角度を算出
		float frontAngle = atan2(front.z, front.x);

		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].bConnected) {
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
				auto bullet = stage->AddGameObject<Bullet>(ptrPos, Vec3(0.3f, 0.3f, 0.3f), 10.0f, frontAngle, 1);
			}
		}
	}

	Vec3 Player::GetAngle() {
		auto angle = GetMoveVector();
		return angle;
	}

	float Player::GetHp() const {
		return m_hp;
	}

	void Player::SetHp(float hp){
		m_hp += hp;
	}

	void Player::OnCollisionEnter(shared_ptr<GameObject>& other){
		if (other->FindTag(L"EnemyPiece")) {
			SetHp(100.0f);
		}
	}
}
//end basecross
