/*!
@file EnemyMovieManager.h
@brief Enemyに出会ったときの演出
担当：三瓶裕太
*/

#pragma once
#include "stdafx.h"
#include"SelectSprite.h"
#include"UIScroll.h"

namespace basecross {
	class EnemyMovieManager :public GameObject
	{
	private:
		Vec3 m_Scale;
		Vec3 m_Position;
		Vec3 m_Rotate;
		Vec3 m_MoviePos;//カメラの目標の地点
		Vec3 m_MovieAt;//カメラの目標の視点
		Vec3 m_AfterPlayerScale;//ムービー用にする前のPlayerの大きさ
		Mat4x4 m_AfterPlayerMat;//ムービー用にする前のPlayerの差分行列の数値
		shared_ptr<Transform> m_Trans;
		shared_ptr<Camera> m_MovieCamera;//ムービー用のカメラ
		weak_ptr<MainCamera> m_StageCamera;//ステージのカメラ(ゲームプレイ用)
		weak_ptr<ViewBase> m_StageView;//ステージのビュー(ゲームプレイ用)
		shared_ptr<Sprite> m_MovieBand;//ムービー用の帯
		shared_ptr<Sprite> m_BossMoji;//Bossを表すための文字
		shared_ptr<Sprite> m_SkipMoji;//Bossを表すための文字
		weak_ptr<Player> m_Player;//プレイヤー
		shared_ptr<UIScroll> m_scroll;
		bool m_MovieCheck;

		int m_Count;//フラグ管理
		float m_Time;
	public:
		EnemyMovieManager(shared_ptr<Stage>& stage,Vec3 Pos, Vec3 scale,Vec3 moviePos,Vec3 m_MovieAt);
		~EnemyMovieManager();

		void OnCreate()override;
		void OnUpdate()override;

		Vec3 MoveVec(float speed, Vec3 Pos, Vec3 tagetPos);//移動ベクトルを求める関数

		void MyRemove();//自分自身を消去する

		void OnCollisionEnter(shared_ptr<GameObject>& Other) override;//コリジョンが入った時

		void MovieStart();
		int GetCount();

	};

	//EnemyMovieManagerのコリジョンを追加する(２つ目以降)
	class EnemyMovieLittle :public GameObject
	{
	private:
		Vec3 m_Scale;
		Vec3 m_Position;
		Vec3 m_Rotate;
	public:
		EnemyMovieLittle(shared_ptr<Stage>& stage,Vec3 Pos,Vec3 Scale);
		~EnemyMovieLittle();

		void OnCreate()override;
		void OnUpdate()override;

		void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
	};
}