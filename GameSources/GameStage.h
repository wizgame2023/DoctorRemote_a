namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {

		void CreateViewLight(); //ビューの作成
		void CreateBullet();//弾の作成
		void CreatePlayer();//プレイヤーの作成
		void CreateEnemyPiece();//敵のかけらの作成
		void CreateEnemyPiece2();//敵のかけらの作成（集まっているかけら何個出るか決める）
		void CerateBreakEnemyPiece();//壊れる壁の後ろに生成するかけら
		void CreateEnemy();//敵の作成
		void CreateRadar();//レーダーの作成
		void CreateWall();//壁の作成
		void CreateBlock();//障害物の作成
		void CreateBreakWall();//壊れる壁の作成
		void CreateRecoveryWall();//治す壁の作成
		void CreateBlockSecond();//障害物の作成２
		void RandamPiecePosition(Vec3 originPosition);//ランダムに
		shared_ptr<Transform> m_Trans;
	public:
		//構築と破棄
		GameStage() :Stage() {}
		virtual ~GameStage() {}

		virtual void OnCreate()override; //初期化
	};

}
//end basecross

