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
		m_dashCount(m_dashCoolTime),
		m_dashCoolTime(8.0f),
		m_lastAngle(0.0f,0.0f,0.0f),
		m_dashCool(m_dashCoolTime),
		m_dashCheck(false),
		m_dashCooldown(false),
		m_startFlag(false),
		m_radarFlag(false),
		m_statusFlag(2),
		m_enemyPieceFlag(false),
		m_meshResName(L"Sensuikan_Mesh")
	{}


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

	float Player::PlayerAngle() const{

		//進行方向の向きを計算
		auto ptrCamera = OnGetDrawCamera();
		auto front = m_trans->GetPosition() - ptrCamera->GetEye();
		front.y = 0;
		front.normalize();
		//進行方向の向きからの角度を算出
		float frontAngle = atan2(front.z, front.x);

		return frontAngle;
	}

	Vec3 Player::GetMoveVector() {
		Vec3 angle(0, 0, 0);
		//入力を取得
		auto inPut = GetInputState();//コントローラーの入力の傾きを入れている
		float moveX = inPut.x;
		float moveZ = inPut.y;
		if (moveX != 0 || moveZ != 0){//コントローラー(アナログステック)を動かしたら
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
				m_speed += (input.y * 6.5f) * elapsedTime;//ステックを縦に傾けば傾くほど加速する
			}

			if (!m_dashCheck)//ダッシュ効果適応外
			{
				if(m_maxSpeed <= m_speed)//限界のスピードを超えたとき
				{
					m_speed = m_maxSpeed;//限界のスピードまでに制限
				}
				if (-m_maxSpeed/2 >= m_speed)//バックの限界のスピードを超えたとき
				{
					m_speed = -m_maxSpeed/2;//バックの限界のスピードまでに制限
				}

			}

			//if (m_dashCheck)//ダッシュ効果適応中
			//{
			//	//if (m_maxSpeed >= m_speed)
			//	//{
			//	//	m_speed += (input.y * 2.0f) * elapsedTime;
			//	//}
			//	if(m_dashSpeed <= m_speed)
			//	{
			//		//m_speed = m_dashSpeed;
			//	}
			//}

		}
		if(input.x == 0 && input.y == 0)//アナログスティックを動かしていない場合
		{
			if (m_speed < 0)//現在のスピードが０より小さかった時
			{	
				m_speed += elapsedTime * 5.0f;//スピードがどんどん落ちてくる
				if (m_speed >= -0.5f)//スピードが０に近くなったら
				{
					m_speed = 0;//スピードを０とみなす
				}
			}
			if (m_speed > 0)//現在のスピードが０より大きかった時
			{
				m_speed -= elapsedTime*6.8f;//スピードがどんどん落ちてくる
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

	void Player::Dash() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		Vec2 input = GetInputState();//入力を取得
		
		if (cntlVec[0].bRightTrigger >= 0.8f) {//RTボタンを押したら
			m_dashCheck = true;
			m_dashCooldown = true;
			if (m_dashCount > 0) {
				if (input.x != 0 || input.y != 0)
				{
					m_speed = m_dashSpeed;//スピードをダッシュ用のスピードに変更する
				}
			}
		}
		else {
			//m_speed = m_maxSpeed;
		}
	}


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
		ptrDraw->SetMultiMeshResource(m_meshResName);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->AddAnimation(L"Default", 0, 90, true, 30.0f);
		ptrDraw->ChangeCurrentAnimation(L"Default");

		//影をつける
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMultiMeshResource(m_meshResName);
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

		m_statusFlag = App::GetApp()->GetScene<Scene>()->GetPlayerStatus();

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
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
					auto bullet = stage->AddGameObject<Bullet>(Vec3(ptrPos.x,ptrPos.y-0.3f,ptrPos.z),Vec3(0.2f), 30.0f, frontAngle, 1);
					//stage->SetSharedGameObject(L"Bullet", bullet);

					auto soundE = App::GetApp()->GetXAudio2Manager();
					soundE->Start(L"ShotSE",0,0.5f);
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

		//アニメーションの更新
		auto drawComp = GetComponent<PNTBoneModelDraw>();
		drawComp->UpdateAnimation(elapsedTime);

		//ダッシュ
		switch (m_statusFlag)
		{
		case 0:
			break;
		case 1:
			Dash();
			if (m_dashCooldown) {
				m_dashCount -= elapsedTime;
				//ダッシュの効果時間が過ぎたらダッシュを出来なくなる
				if (m_dashCount <= 0) {
					//m_speed = m_maxSpeed;
					m_dashCheck = false;
				}
				//ダッシュのクールタイムが過ぎたらダッシュを再使用できるようになる
				m_dashCool -= elapsedTime;
				if (m_dashCool <= 0) {
					m_dashCooldown = false;
					m_dashCount = m_dashCountTime;
					m_dashCool = m_dashCoolTime;
				}
			}
			break;
		case 2:
			Dash();
			if (m_dashCooldown) {
				m_dashCount -= elapsedTime * 0.7;
				if (m_dashCount <= 0) {
					m_speed = m_maxSpeed;
					m_dashCheck = false;
				}
				m_dashCool -= elapsedTime * 1.5f;
				if (m_dashCool <= 0) {
					m_dashCooldown = false;
					m_dashCount = m_dashCountTime;
					m_dashCool = m_dashCoolTime;
				}
			}
			break;

		default:
			break;
		}

		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();//デバック用です


		auto trans = GetComponent<Transform>();
		//デバック用
		wstringstream wss(L"");
		auto scene = App::GetApp()->GetScene<Scene>();
		auto gameStage = scene->GetGameStage();
		wss << L"transform : "
			<< L"\n"
			<< L"postion : ("
			<< L"\nx."
			<< trans->GetPosition().x
			<< L","
			<< "\ny."
			<< trans->GetPosition().y
			<< L","
			<< "\nz."
			<< trans->GetPosition().z
			<< L")"
			<< "\ngameStage"
			<< gameStage
			<< "\nVectorX"
			<< m_lastAngle.x
			<< "\nVectorY"
			<< m_lastAngle.y
			<< "\nVectorZ"
			<< m_lastAngle.z
			<< "\nSpeed"
			<< m_speed
			<< "\ncntlVec[0].bRightTrigger"
			<< cntlVec[0].bRightTrigger
			<<"\nm_dashCheck"
			<< (bool)m_dashCheck
			<<"\nelapsedTime"
			<< elapsedTime
			<< endl;
		scene->SetDebugString(wss.str());

	}

	//衝突判定
	void Player::OnCollisionEnter(shared_ptr<GameObject>& other){
		auto ptrTrans = GetComponent<Transform>();

		if (other->FindTag(L"PieceLittle")) {
			if(!m_radarFlag){
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
				AddPiece(m_onePiece*3);

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
			auto bigPieceSE = App::GetApp()->GetXAudio2Manager();
			bigPieceSE->Start(L"GetPieceSE", 0, 0.5f);

		}
		if (other->FindTag(L"EnemyPiece")) {
			EffectFlag(2);
			m_enemyPieceFlag = true;
			SetObj(other);
		}
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
			//	break;
		case 2:
			//ブレイクウォールの場合
			if (PtrEffect) {
				PtrEffect = GetStage()->GetSharedGameObject<EffectChase>(L"EffectChase", false);
				PtrEffect->InsertEffect(GetComponent<Transform>()->GetPosition());
			}
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
