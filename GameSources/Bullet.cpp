/*!
@file Bullet.cpp
@brief 弾の実体
担当　逸見、（三瓶）
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//enum BULLETLEVEL {
	//	NORMAL,
	//	LEVEL1,
	//	LEVEL2,
	//	LEVEL3,
	//};

	//コンストラクタ
	Bullet::Bullet(const shared_ptr<Stage>& stagePtr, const Vec3& position, const Vec3& scale, float speed, float angle, float attack) :
		GameObject(stagePtr),
		m_position(position),
		m_scale(scale),
		m_speed(speed),
		m_angle(angle),//角度はRad（弧度法）
		m_attack(attack),
		m_statusFlag(0),
		m_shotRange(20.0f),
		m_meshResName(L"Bullet"),
		m_velocity(0),
		m_bulletLevel(0)
	{
	}
	//デストラクタ
	Bullet::~Bullet()
	{

	}
	//初期化
	void Bullet::OnCreate()
	{

		auto ptrTransform = GetComponent<Transform>();//toransformを取得

		ptrTransform->SetPosition(m_position);//位置を設定
		ptrTransform->SetScale(m_scale);//大きさを設定
		ptrTransform->SetQuaternion(Quat());//クトーニアン（回転）を設定
		m_allStartPosition = ptrTransform->GetPosition();//初期化時点の位置を取得

		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.5f, 0.5f, 0.5f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		//描画コンポーネント
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(m_meshResName);
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->SetOwnShadowActive(true);

		//オブジェクトの影の描画
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(m_meshResName);
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//球体のコリジョンを追加
		auto ptrcollider = AddComponent<CollisionSphere>();
		ptrcollider->SetAfterCollision(AfterCollision::None);

		AddTag(L"Bullet");//Bulletタグを追加

		m_effect = GetStage()->AddGameObject<EffectPiece>(1.0f, 0.25f * m_scale.length(), 0.25f * m_scale.length(), 150 * m_scale.length(), Vec2(1.0f, 1.0f),
			Col4(0.0f, 1.0f, 1.0f, 0.5f), Col4(0.0f, 1.0f, 1.0f, 0.5f), L"BulletEffect", Vec2(1.0f, 0.0f), m_position);
		m_effect.lock()->SetBlendState(BlendState::Opaque);
		m_effect2 = GetStage()->AddGameObject<EffectPiece>(1.0f, 0.18f*m_scale.length(), 0.18f * m_scale.length(), 150 * m_scale.length(), Vec2(1.0f, 1.0f),
			Col4(0.0f, 1.0f, 1.0f, 0.5f), Col4(0.0f, 1.0f, 1.0f, 0.5f), L"BulletEffect", Vec2(-1.0f, 0.0f), m_position);


		//m_effect.lock()->GetComponent<Transform>()->SetRotation(Vec3(0.0f, 0.0f, XMConvertToRadians(90)));
		//m_effect.lock()->GetComponent<Transform>()->SetQuaternion(Quat(Vec3(1, 0, 0), XM_PIDIV2));
		//auto player = GetStage()->GetSharedGameObject<Player>(L"GamePlayer");
		//auto playerAngle = player->FrontVec();

		//Quat SpanQt = Quat(Vec3(1, 0, 1), XM_PIDIV2);
		//Quat bulletAngle = (Quat)playerAngle;
		//SpanQt *= bulletAngle;
		//m_effect.lock()->GetComponent<Transform>()->SetQuaternion(SpanQt);


		m_statusFlag = App::GetApp()->GetScene<Scene>()->GetBulletStatus();
		switch (m_statusFlag)
		{
		case 0:
			m_shotRange = 20.0f;
			break;
		case 1:
			m_shotRange = 30.0f;
			break;
		case 2:
			m_shotRange = 40.0f;
			break;
		default:
			break;
		}
	}
	void Bullet::OnUpdate()
	{		
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();//デルタタイムを取得

		auto player = GetStage()->GetSharedGameObject<Player>(L"GamePlayer");
		auto playerAngle = player->FrontVec();
		auto& ptrPlayer = GetStage()->GetSharedObject(L"GamePlayer");//GamePlayerというオブジェクトを取得
		auto ptrTransform = GetComponent<Transform>();//toransformを取得

		auto effect = m_effect.lock();
		auto effect2 = m_effect2.lock();
		auto& effectTrans = effect->GetComponent<Transform>();
		auto& effectTrans2 = effect2->GetComponent<Transform>();

		//delta = floor(delta * 100) / 100;
		m_velocity.x = cos(m_angle);
		m_velocity.y = 0;
		m_velocity.z = sin(m_angle);
		m_velocity.normalize();

		m_position.x += m_velocity.x * m_speed * delta;//移動
		m_position.z += m_velocity.z * m_speed * delta;//移動
		ptrTransform->SetPosition(m_position);//移動を反映させる
		Vec3 UpdatePosition = ptrTransform->GetPosition();//移動を反映させたpositionを取得

		//弾の後ろにエフェクト
		m_effectPos = m_position;
		m_effectPos.x -= m_velocity.x * 1.0f;
		m_effectPos.z -= m_velocity.z * 1.0f;
		if (effect) {
			//エフェクトの向き
			//エフェクトを回転させるための軸
			auto effectShaft = m_velocity.cross(Vec3(0.0f,1.0f,0.0f));
			Quat SpanQt = Quat(effectShaft, XMConvertToRadians(90));
			Quat bulletAngle = (Quat)playerAngle;
			bulletAngle *= SpanQt;
			effectTrans->SetQuaternion(bulletAngle);
			effectTrans->SetPosition(m_effectPos);

			if (effect2) {
				effectTrans2->SetQuaternion(bulletAngle);
				effectTrans2->SetPosition(m_effectPos);

			}
		}


		//auto& Vec = GetStage()->GetGameObjectVec();//ゲームオブジェクトの配列を取得
		//for (auto V : Vec)
		//{
		//	bool chack = V->FindTag(L"Bullet");
		//	if (chack)
		//	{

		//	}
		//}

		
		Vec3 PositionVec = Vec3(m_allStartPosition.x - UpdatePosition.x,m_allStartPosition.y - UpdatePosition.y,m_allStartPosition.z - UpdatePosition.z);
		float AllPosition = abs(PositionVec.x)+abs(PositionVec.y)+abs(PositionVec.z);

		// 初期位置から20.0f離れた弾は破棄する
		if (AllPosition >= m_shotRange)//ちょっと計算違うから直しておく
		{
			// ステージから自身を破棄する
			ThisDestroy();
		}
		wstringstream wss;//デバック用文字列
		//wss << L"m_effectPos.x :" << m_effectPos.x << endl;
		//wss << L"m_effectPos.y :" << m_effectPos.y << endl;
		//wss << L"m_effectPos.z :" << m_effectPos.z << endl;
		//wss << L"m_bulletPos.y :" << m_Position.y << endl;
		//wss << L"angle:" << XMConvertToDegrees(m_angle) << endl;

		//auto scene = app->GetScene<Scene>();//シーン取得
		//scene->SetDebugString(L"a\n" + wss.str());


	}
	//コリジョンがぶつかったら
	void Bullet::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		//もしぶつかったコリジョンがEnemyのものだったら
		if (other->FindTag(L"Enemy"))
		{			
			GetStage()->AddGameObject<EffectBullet>(L"DamageBullet", 3, 2, GetComponent<Transform>()->GetPosition(), 0.1f);
			//DestroyGameObject();//自分は消える
			ThisDestroy();

		}
		if (other->FindTag(L"BreakWall"))
		{
			DestroyGameObject();//自分は消える
			ThisDestroy();
			m_hit = 1;//壊れる壁に当たった
			auto& ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"GamePlayer");//GamePlayerというオブジェクトを取得
			ptrPlayer->EffectFlag(2);//これでPlayerからエフェクトを出す

		}
		if (other->FindTag(L"Obj"))
		{
			DestroyGameObject();//自分は消える
			ThisDestroy();
		}
		if (other->FindTag(L"EnemyPiece")) {
			ThisDestroy();
		}
	}

	//自分自身と自分についているエフェクトを消す関数
	void Bullet::ThisDestroy() {
		GetStage()->RemoveGameObject<Bullet>(GetThis<Bullet>());
		m_effect.lock()->ThihDestroy();
		m_effect2.lock()->ThihDestroy();
		
	}

	float Bullet::GetSpeed()
	{
		return m_speed;
	}
	int Bullet::GetAttack()
	{
		return m_attack;
	}

	int Bullet::GetBulletLevel() {
		return m_bulletLevel;
	}
	void Bullet::SetBulletLevel(int level) {
		m_bulletLevel = level;
	}
}
//end basecross
