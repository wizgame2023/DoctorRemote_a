/*!
@file Radar.cpp
@brief レーダー実体
担当　三瓶裕太
これでやりたいこと　EnemyとPlayerの一人称視点の角度で見るとどの方向なのかわかるようにする
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//コンストラクタ
	Radar::Radar(const shared_ptr<Stage>& StagePtr, const Vec3 PlayerPosition, const Vec3 EnemyPosition) :
		GameObject(StagePtr),
		m_PlayerPosition(PlayerPosition),
		m_EnemyPosition(EnemyPosition)
	{

	}
	//デストラクタ
	Radar::~Radar()
	{

	}

	//初期化
	void Radar::OnCreate()
	{
		//auto ptrTransform = GetComponent<Transform>();//toransformを取得

		//ptrTransform->SetPosition(m_Position);//ポジションを決定
		//ptrTransform->SetScale(m_Scale);//大きさを決める
		//auto a = GetComponent<GameObject>();

		// ポリゴンの自作

		Col4 color(1, 1, 1, 1); // ポリゴンの色
		const float w = 100.0f; // ポリゴンの幅
		const float h = 100.0f; // ポリゴンの高さ
		vector<VertexPositionColorTexture> m_vertices = { // 頂点データ
			//             座標           ,頂点色,        UV座標
			{Vec3(-w * 0.5f, +h * 0.5f, 0), color, Vec2(0.0f, 0.0f)}, // 0
			{Vec3(+w * 0.5f, +h * 0.5f, 0), color, Vec2(1.0f, 0.0f)}, // 1
			{Vec3(-w * 0.5f, -h * 0.5f, 0), color, Vec2(0.0f, 1.0f)}, // 2
			{Vec3(+w * 0.5f, -h * 0.5f, 0), color, Vec2(1.0f, 1.0f)}, // 3
		};

		vector<uint16_t> m_indices = { // 頂点インデックス（頂点のつなげ順）
			0, 1, 2, // ←これで一つのポリゴン(三角形)
			2, 1, 3  // ←こっちも
		};

		m_drawComp = AddComponent<PCTSpriteDraw>(m_vertices, m_indices); // スプライト用のドローコンポーネント
		m_drawComp->SetTextureResource(L"Arrow");//白のテクスチャが欲しいときはHAKUSIを選択してください
		m_drawComp->SetSamplerState(SamplerState::LinearWrap); // テクスチャを繰り返して貼り付ける設定
		m_drawComp->SetDiffuse(Col4(1, 1, 1, 0.0f)); // ポリゴンを色を設定する

		// アルファブレンド(透過処理)を有効にする
		SetAlphaActive(true); // true:透過を有効、false:透過を無効


	}

	void Radar::OnUpdate()
	{
		auto& app = App::GetApp(); // アプリケーションオブジェクトを取得する

		wstringstream wss;//デバック用文字列
		//wss << "test" << endl;
		auto scene = app->GetScene<Scene>();//シーン取得


		float degConvert = 180.0f / 3.14f;//radからdegに変換するための変数
		auto transform = AddComponent<Transform>();

		//auto& Stage = GetStage()->GetSharedObject(L");

		auto& ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"GamePlayer");//GamePlayerというオブジェクトを取得
		auto PlayerTrans = ptrPlayer->GetComponent<Transform>();//そのオブジェクトのTransformを取得
		m_PlayerPosition = PlayerTrans->GetPosition();//Positionを取得
		float PlayerAngle = ptrPlayer->PlayerAngle();//Playerの向いている角度を取得する

		//PlayerとEnemyの距離を取得
		Vec3 RadarVec3 = Vec3((m_EnemyPosition.x - m_PlayerPosition.x),
			0.0f,
			(m_EnemyPosition.z - m_PlayerPosition.z));

		float rad = atan2f(RadarVec3.z, RadarVec3.x);//ベクトルをラジアンに変換
		float deg = (rad * degConvert);//ラジアンをディグリーに変換
		m_angle = rad - PlayerAngle+ 1.57f;

		if (m_angle < 0.0f)//もし回転する方向が下方面だったら
		{
			m_angle = -m_angle;//上方面に直す
		}
		if (m_angle > 3.14f)
		{
			m_angle = 6.28f - m_angle;
		}


		wss << m_angle << endl;//デバック用文字列を作成

		transform->SetRotation(0.0f, 0.0f, m_angle);//回転を初期化
		transform->SetPosition(0.0f, -300.0f, 0.0f);

		auto& ptrGarge = GetStage()->GetSharedGameObject<PieceGarge>(L"Garge");
		float GargeLength = ptrGarge->GetLength();
		float GargeMaxLength = ptrGarge->GetMaxLength();
		int test=0;
		if (GargeLength >= GargeMaxLength)
		{
			m_drawComp->SetDiffuse(Col4(1, 1, 1, 1.0f)); // ポリゴンを色を設定する
			test = 1;
		}

		//デバック用
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeyState.m_bPressedKeyTbl[VK_SPACE]) {
			float a = 1.0f;
		}
		//デバック用文字列を生成
		scene->SetDebugString(L"a\n" + wss.str());

	}
}