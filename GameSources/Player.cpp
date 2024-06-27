/*!
@file Player.cpp
@brief プレイヤー実体
担当：逸見、（三瓶）
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
		m_piece(0),
		m_onePiece(15.0f),
		m_maxPiece(100.0f),
		m_speed(0.0f),
		m_maxSpeed(5.0f),
		m_dashSpeed(8.0f),
		m_startFlag(false),
		m_radarFlag(false),
		m_statusFlag(0),
		m_meshResName(L"Sensuikan_Mesh")
	{}
	Player::Player(const shared_ptr<Stage>& StagePtr, const Vec3& pos,const Vec3& rot,float onePiece):
		GameObject(StagePtr),
		m_pos(pos),
		m_rot(rot),
		m_piece(0),
		m_onePiece(onePiece),
		m_maxPiece(150.0f),
		m_speed(0.0f),
		m_maxSpeed(7.0f),
		m_dashSpeed(15.0f),
		m_dashCountTime(1.0f),
		m_dashCount(1.0f),
		m_dashCoolTime(8.0f),
		m_lastAngle(0.0f,0.0f,0.0f),
		m_dashCool(8.0f),
		m_bulletTime(0.0f),
		m_bulletChargeTime(1.0f),
		m_bulletRatio(0.0f),
		m_bulletPower(1.0f),
		m_dashCheck(false),
		m_dashCooldown(false),
		m_startFlag(false),
		m_radarFlag(false),
		m_statusFlag(2),
		m_enemyPieceFlag(false),
		m_bulletFlag(false),
		m_bulletLevel(0),
		m_chargeBulletSE{ false },
		m_meshResName(L"Sensuikan_Mesh")
	{}



	void Player::OnCreate(){
		//STATUSPLAYER = 0;
		//初期位置などの設定
		m_trans = GetComponent<Transform>();
		m_trans->SetScale(1.5f, 2.0f, 8.5f);
		m_trans->SetRotation(m_rot);
		m_trans->SetPosition(m_pos);

		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.75f, 0.5f, 0.25f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XM_PI, 0.0f),
			Vec3(0.0f, -0.5f, -0.05f)
		);


		//描画コンポーネント
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		ptrDraw->SetMeshResource(m_meshResName);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->AddAnimation(L"Default", 0, 90, true, 30.0f);
		ptrDraw->ChangeCurrentAnimation(L"Default");

		//影をつける
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(m_meshResName);
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto colPtr = AddComponent<CollisionObb>();
		colPtr->SetDrawActive(false);
		colPtr->SetAfterCollision(AfterCollision::Auto);

		AddTag(L"Player");

		//カメラオブジェクトを取得する
		auto ptrCamera = dynamic_pointer_cast<MainCamera>(OnGetDrawCamera());
		if (ptrCamera) {
			ptrCamera->SetTarget(GetThis<GameObject>());
		}
		
		auto& scene = App::GetApp()->GetScene<Scene>();
		m_statusFlag = scene->GetDashStatus();
		DashCoolManager(m_statusFlag);//これでダッシュの効果時間やクールタイムを決める
		m_bulletPower = scene->GetBulletPower();
		m_bulletChargeTime = scene->GetBulletTime();
	}

	void Player::OnUpdate(){
		m_position = m_trans->GetPosition();
		m_trans->SetPosition(Vec3(m_position.x, m_pos.y, m_position.z));
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto stage = GetStage();
		m_startFlag = stage->GetSharedGameObject<StageManager>(L"StageManager")->GetStartFlag();
		//導入などが終わりフラグが踏まれたら操作できるようにする
		if (m_startFlag) {
			MovePlayer();
			auto frontAngle = PlayerAngle();
			auto ptrPos = m_trans->GetPosition();
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

			//Ｂボタンで弾を発射
			if (cntlVec[0].bConnected) {
				auto soundE = App::GetApp()->GetXAudio2Manager();

				if (cntlVec[0].wButtons & XINPUT_GAMEPAD_B) {
					if (m_bulletTime <= m_bulletChargeTime*3) {
						m_bulletTime += elapsedTime;
						if (m_bulletTime >= 1) {
							if (!m_chargeBulletSE[0]) {
								soundE->Start(L"Charge1", 0, 0.5f);
								m_chargeBulletSE[0] = true;
							}
						}
						if (m_bulletTime >= 2) {
							if (!m_chargeBulletSE[1]) {
								soundE->Start(L"Charge2", 0, 0.5f);
								m_chargeBulletSE[1] = true;
							}
						}
						if (m_bulletTime >= 3) {
							if (!m_chargeBulletSE[2]) {
								soundE->Start(L"Charge3", 0, 0.5f);
								m_chargeBulletSE[2] = true;
							}
						}


					}
					else {
						m_bulletTime = m_bulletChargeTime*3;
					}
					m_bulletRatio = m_bulletTime / (m_bulletChargeTime * 3);
				}
				else {
					m_bulletFlag = false;
				}

				if (cntlVec[0].wReleasedButtons & XINPUT_GAMEPAD_B) {
					if (m_bulletTime >= m_bulletChargeTime*3) {
						auto bullet = stage->AddGameObject<Bullet>(Vec3(ptrPos.x, ptrPos.y - 0.3f, ptrPos.z), Vec3(0.7f), 50.0f, frontAngle, 20.0f);
						bullet->SetBulletLevel(3);
						BulletSE();
					}
					else if (m_bulletTime >= m_bulletChargeTime*2) {
						auto bullet = stage->AddGameObject<Bullet>(Vec3(ptrPos.x, ptrPos.y - 0.3f, ptrPos.z), Vec3(0.5f), 45.0f, frontAngle, 12.0f);
						bullet->SetBulletLevel(2);
						BulletSE();
					}
					else if (m_bulletTime >= m_bulletChargeTime) {
						auto bullet = stage->AddGameObject<Bullet>(Vec3(ptrPos.x, ptrPos.y - 0.3f, ptrPos.z), Vec3(0.3f), 40.0f, frontAngle, 6.0f);
						bullet->SetBulletLevel(1);
						BulletSE();
					}
					else {
						auto bullet = stage->AddGameObject<Bullet>(Vec3(ptrPos.x, ptrPos.y - 0.3f, ptrPos.z), Vec3(0.2f), 30.0f, frontAngle, 2.0f * m_bulletPower);
						bullet->SetBulletLevel(0);
						BulletSE();
					}
					m_bulletTime = 0.0f;
					m_bulletRatio = 0.0f;

					for (int i = 0; i < 3; i++) {
						if (m_chargeBulletSE[i]) {
							m_chargeBulletSE[i] = false;
						}
					}
				}
				else {
					//m_bulletTime = 0.0f;
				}
			}

			//EnemyPieceに触れたら押し出し
			if (m_enemyPieceFlag) {
				auto obj = GetObj();
				auto objTrans = obj->GetComponent<Transform>();
				auto pullTrans = objTrans->GetPosition() - ptrPos;
				float range = sqrt(pullTrans.x * pullTrans.x + pullTrans.z * pullTrans.z);
				if (range < 7.0f) {
					auto pos = ptrPos;
					pos.x += -pullTrans.x * 0.15f + elapsedTime;
					pos.z += -pullTrans.z * 0.15f + elapsedTime;
					m_trans->SetPosition(Vec3(pos.x, pos.y, pos.z));
					m_startFlag = false;
				}
				else {
					m_enemyPieceFlag = false;
					m_startFlag = true;
				}
			}

		}
		if (!m_startFlag) {//プレイヤーが動けないとき
				m_bulletRatio = 0.0f;//弾のチャージをリセットする
		}

		//アニメーションの更新
		auto drawComp = GetComponent<PNTBoneModelDraw>();
		drawComp->UpdateAnimation(elapsedTime);

		Dash();//これでダッシュの動きをする


		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();//デバック用です


		auto trans = GetComponent<Transform>();
		//デバック用
		wstringstream wss(L"");
		auto scene = App::GetApp()->GetScene<Scene>();
		auto gameStage = scene->GetGameStage();
		//wss << L"transform : "
		//	<< L"\n"
		//	<< L"postion : ("
		//	<< L"\nx."
		//	<< trans->GetPosition().x
		//	<< L","
		//	<< "\ny."
		//	<< trans->GetPosition().y
		//	<< L","
		//	<< "\nz."
		//	<< trans->GetPosition().z
		//	<< L")"
		//	<< "\ngameStage"
		//	<< gameStage
		//	<< "\nVectorX"
		//	<< m_lastAngle.x
		//	<< "\nVectorY"
		//	<< m_lastAngle.y
		//	<< "\nVectorZ"
		//	<< m_lastAngle.z
		//	<< "\nSpeed"
		//	<< m_speed
		//	<< "\ncntlVec[0].bRightTrigger"
		//	<< cntlVec[0].bRightTrigger
		//	<<"\nm_dashCheck"
		//	<< (bool)m_dashCheck
		//	<<"\nelapsedTime"
		//	<< elapsedTime
		//	<<"\nChain : "
		//	<<scene->GetBulletPower()
		//	<< endl;

		scene->SetDebugString(wss.str());

	}

	//衝突判定
	void Player::OnCollisionEnter(shared_ptr<GameObject>& other) {
		auto ptrTrans = GetComponent<Transform>();

		if (other->FindTag(L"PieceLittle")) {
			if (!m_radarFlag) {
				AddPiece(m_onePiece);

			}
			if (m_maxPiece < m_piece) {
				m_radarFlag = true;
			}

			EffectFlag(3);
			auto pieceSE = App::GetApp()->GetXAudio2Manager();
			pieceSE->Start(L"GetPieceSE", 0, 0.5f);

		}
		if (other->FindTag(L"BigPieceLittle")) {
			if (!m_radarFlag) {
				AddPiece(m_onePiece * 3);

			}
			if (m_maxPiece < m_piece) {
				m_radarFlag = true;
			}

			EffectFlag(3);
			auto pieceSE = App::GetApp()->GetXAudio2Manager();
			pieceSE->Start(L"GetPieceSE", 0, 0.5f);

		}
		if (other->FindTag(L"BigPiece")) {

			m_enemyPieceFlag = true;
			SetObj(other);

			EffectFlag(2);
			auto damegeSE = App::GetApp()->GetXAudio2Manager();
			damegeSE->Start(L"DamageSE", 0, 0.5f);

		}
		if (other->FindTag(L"EnemyPiece")) {
			EffectFlag(2);
			m_enemyPieceFlag = true;
			SetObj(other);

			auto damegeSE = App::GetApp()->GetXAudio2Manager();
			damegeSE->Start(L"DamageSE", 0, 0.5f);
		}
	}

	Vec2 Player::GetInputState() {
		Vec2 ret;
		ret.x = 0.0f;
		ret.y = 0.0f;
		//コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].bConnected)
		{
			ret.x = cntlVec[0].fThumbLX;
			ret.y = cntlVec[0].fThumbLY;
			if (ret.x != 0 || ret.y != 0) {//コントローラー(アナログステック)を動かしたら
				m_PadLastAngle = ret;

			}
		}

		return ret;
	}

	float Player::PlayerAngle() const {

		//進行方向の向きを計算
		auto ptrCamera = OnGetDrawCamera();
		auto front = m_trans->GetPosition() - ptrCamera->GetEye();
		front.y = 0;
		front.normalize();
		//進行方向の向きからの角度を算出
		float frontAngle = atan2(front.z, front.x);

		return frontAngle;
	}
	//飛ばす方向ベクトル
	Vec3 Player::FrontVec() {
		auto ptrCamera = OnGetDrawCamera();
		auto front = m_trans->GetPosition() - ptrCamera->GetEye();
		front.y = 0;
		return front;
	}

	Vec3 Player::GetMoveVector() {
		Vec3 angle(0, 0, 0);
		//入力を取得
		auto inPut = GetInputState();//コントローラーの入力の傾きを入れている
		float moveX = inPut.x;
		float moveZ = inPut.y;
		if (moveX != 0 || moveZ != 0) {//コントローラー(アナログステック)を動かしたら
			float moveLength = 0;

			float frontAngle = PlayerAngle();

			//コントローラの向きを計算
			Vec2 moveVec(moveX, moveZ);
			//角度からベクトルを作成
			angle = Vec3(cos(frontAngle), 0.0f, sin(frontAngle));
			//正規化
			angle.normalize();

			//移動サイズ
			//float moveSize = moveVec.length();
			//angle *= moveSize;

			//wstringstream wss(L"");
			//auto scene = App::GetApp()->GetScene<Scene>();
			//auto gameStage = scene->GetGameStage();
			//wss << L"angle.x : " << moveVec.x << L"angle.z : " << moveVec.y
			//	<< endl;
			//scene->SetDebugString(wss.str());

			//Y軸は変化させない
			angle.y = 0.0f;
			//最後に傾けた値を保存する
			m_lastAngle = angle;

		}
		return angle;
	}

	void Player::SpeedCalculation()//Playerの進むスピードを計算する
	{
		Vec2 input = GetInputState();//入力を取得
		input.length();
		float elapsedTime = App::GetApp()->GetElapsedTime();



		if (input.x != 0 || input.y != 0)//アナログステックが傾けられた場合
		{
			if (m_maxSpeed >= m_speed)
			{
				m_speed += (input.y * 9.0f) * elapsedTime;//ステックを縦に傾けば傾くほど加速する
			}

			if (!m_dashCheck)//ダッシュ効果適応外
			{
				if (m_maxSpeed <= m_speed)//限界のスピードを超えたとき
				{
					m_speed = m_maxSpeed;//限界のスピードまでに制限
				}
				if (-m_maxSpeed + 2 >= m_speed)//バックの限界のスピードを超えたとき
				{
					m_speed = -m_maxSpeed + 2;//バックの限界のスピードまでに制限
				}

			}

			if (m_dashCheck)//ダッシュ効果適応中
			{
				if (input.y > 0)//前に傾けたら
				{
					m_speed = m_dashSpeed;//ダッシュの速度になる
				}
				if (input.y < 0)//後ろに傾けたら
				{
					m_speed = -m_maxSpeed + 2;//ダッシュの速度になる
				}
			}

		}
		if (input.x == 0 && input.y == 0)//アナログスティックを動かしていない場合
		{
			if (m_speed < 0)//現在のスピードが０より小さかった時
			{
				m_speed += elapsedTime * 6.8f;//スピードがどんどん落ちてくる
				if (m_speed >= -0.5f)//スピードが０に近くなったら
				{
					m_speed = 0;//スピードを０とみなす
				}
			}
			if (!m_dashCheck && m_speed > 0)//現在のスピードが０より大きかった時
			{
				m_speed -= elapsedTime * 6.8f;//スピードがどんどん落ちてくる
				if (m_speed <= 0.5)//スピードが０に近くなったら
				{
					m_speed = 0;//スピードを０とみなす
				}

			}
			if (m_dashCheck && m_speed > 0)//現在のスピードが０より大きかった時(ダッシュ時)
			{
				m_speed -= elapsedTime * 12.8f;//スピードがどんどん落ちてくる
				if (m_speed <= 0.5)//スピードが０に近くなったら
				{
					m_speed = 0;//スピードを０とみなす
				}

			}

		}



	}

	void Player::MovePlayer() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		//角度を計算している関数を代入	
		auto angle = m_lastAngle;
		if (GetMoveVector() != Vec3(0.0f, 0.0f, 0.0f))
		{
			angle = GetMoveVector();
		}
		//auto cntl = GetInputState();
		SpeedCalculation();//スピードの計算
		if (angle.length() >= 0.0f) {

			Vec3 moveAngle = angle;
			//if (m_PadLastAngle.y < 0.0f) {//yの数値がマイナスの場合バックする
			//	auto subAngle = atan2(moveAngle.z, moveAngle.x);
			//	subAngle += XM_PI;
			//	moveAngle = Vec3(cos(subAngle), 0.0f, sin(subAngle));
			//}

			auto pos = GetComponent<Transform>()->GetPosition();
			pos += moveAngle * elapsedTime * m_speed;//ここで進む距離を決めている
			GetComponent<Transform>()->SetPosition(pos);

		}

		//回転の計算
		if (angle.length() > 0.0f) {
			auto unilPtr = GetBehavior<UtilBehavior>();
			//補間処理を行う回転
			unilPtr->RotToHead(angle, 0.7f);
		}
	}

	void Player::DashCoolManager(int count)
	{
		switch (count)
		{
		case 0:
			m_dashCooldown = true;//そもそもダッシュできないようにする
			break;
		case 1:
			//ダッシュの効果時間
			m_dashCount = 1.0f;
			m_dashCountTime = 1.0f;
			//クールタイム
			m_dashCoolTime = 8.0f;
			m_dashCool = 8.0f;
			break;
		case 2:
			//ダッシュの効果時間
			m_dashCount = 1.5f;
			m_dashCountTime = 1.5f;
			//クールタイム
			m_dashCoolTime = 7.0f;
			m_dashCool = 7.0f;
			break;
		case 3:
			//ダッシュの効果時間
			m_dashCount = 2.0f;
			m_dashCountTime = 2.0f;
			//クールタイム
			m_dashCoolTime = 6.0f;
			m_dashCool = 6.0f;
			break;
		default:
			m_dashCooldown = true;//そもそもダッシュできないようにする
			break;
		}

	}

	void Player::Dash() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		Vec2 input = GetInputState();//入力を取得
		float elapsedTime = App::GetApp()->GetElapsedTime();

		if (cntlVec[0].bRightTrigger >= 0.8f && !m_dashCooldown) //RTボタンを押したら
		{
			m_dashCheck = true;//ダッシュできるようになる
			m_dashCooldown = true;//クールタイムのフラグを入れる
		}

		if (m_dashCheck)//ダッシュのボタンが押されていたら
		{
			m_dashCountTime -= elapsedTime;
			if (m_dashCountTime < 0.0f)//ダッシュの制限時間が過ぎたら
			{
				m_dashCheck = false;//走れなくなる
				//m_dashCooldown = true;//クールダウンをカウントさせるフラグをONにする

			}
		}
		if (m_dashCountTime < 0.0f)//制限時間が過ぎたら
		{
			//クールタイムが発生する
			m_dashCoolTime -= elapsedTime;
			if (m_dashCoolTime <= 0.0f)//クールタイムが過ぎたら
			{
				m_dashCooldown = false;//再度走れるようになる
				m_dashCoolTime = m_dashCool;//クールタイムを元に戻す
				m_dashCountTime = m_dashCount;//ダッシュの制限時間を元に戻す
			}

		}


	}


	void Player::BulletSE() {
		auto soundE = App::GetApp()->GetXAudio2Manager();
		soundE->Start(L"ShotSE", 0, 0.5f);
	}

	void Player::EffectFlag(int Flag)
	{
		auto PtrEffect = GetStage()->GetSharedGameObject<Effect>(L"Effect", false);
		switch (Flag)
		{
			//case 1:
			//	//リカバリーウォールの場合
			//	if (PtrEffect) {
			//		PtrEffect = GetStage()->GetSharedGameObject<EffectChase>(L"PlayerEffectRecovery", false);
			//		PtrEffect->InsertEffect(GetComponent<Transform>()->GetPosition());
			//	}
				break;
		case 2:
			////ブレイクウォールの場合
			//if (PtrEffect) {
			//	PtrEffect = GetStage()->GetSharedGameObject<EffectChase>(L"EffectChase", false);
			//	PtrEffect->InsertEffect(GetComponent<Transform>()->GetPosition());
			//}
			break;
		case 3:
			//かけらを拾った場合
			if (PtrEffect)
			{
				PtrEffect = GetStage()->GetSharedGameObject<EffectMove>(L"PlayerEffectWhite", false);
				PtrEffect->InsertEffect(GetComponent<Transform>()->GetPosition());
			}
			break;
		default:
			break;
		}
	}

	Vec3 Player::GetAngle() {
		auto angle = GetMoveVector();
		return angle;
	}

	float Player::GetPiece() const {
		return m_piece;
	}
	float Player::GetMaxPiece() const {
		return m_maxPiece;
	}

	void Player::AddPiece(float piece){
		m_piece += piece;
	}

	float Player::GetPieceRatio() {
		auto ratio = m_piece / m_maxPiece;
		return ratio;
	}

	bool Player::GetRadarFlag() {
		return m_radarFlag;
	}
	void Player::SetRadarPiece(float piece) {
		m_piece = piece;
	}
	bool Player::GetEnemyFlag() {
		return m_enemyFlag;
	}
	shared_ptr<GameObject>Player::GetObj() {
		return m_obj;
	}
	void Player::SetObj(shared_ptr<GameObject>& obj) {
		m_obj = obj;
	}

	bool Player::GetDashFlag() {
		return m_dashCooldown;
	}

	int Player::GetBulletLevel() {
		return m_bulletLevel;
	}
	float Player::GetBulletRatio() {
		return m_bulletRatio;
	}
	void Player::SetSpeed(float speed){
		m_speed = speed;
	}

	//--------------------------------------------------------------------------------------
	//	class ChildSphere : public GameObject;
	//　当たり判定用のクラス
	//--------------------------------------------------------------------------------------
	ChildPlayer::ChildPlayer(const shared_ptr<Stage>& stagePtr,
		const shared_ptr<GameObject>& parent, 
		const Vec3& vecParent
	):
		GameObject(stagePtr),
		m_parent(parent),
		m_vecParent(vecParent)
	{}

	void ChildPlayer::OnCreate() {
		auto childTrans = GetComponent<Transform>();
		childTrans->SetScale(Vec3(1.0f));

		auto ptrDraw = AddComponent<BcPNStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetDrawActive(true);
		//コリジョン
		auto ptrCol = AddComponent<CollisionObb>();
		ptrCol->SetAfterCollision(AfterCollision::None);
		SetDrawActive(true);

		AddTag(L"Player");

	}
	void ChildPlayer::OnUpdate() {
		auto ptrTrans = GetComponent<Transform>();
		auto parentTrans = m_parent.lock()->GetComponent<Transform>();
		ptrTrans->SetPosition(parentTrans->GetPosition()+Vec3(3.0f,0.0f,0.0f));

	}
}

//end basecross
