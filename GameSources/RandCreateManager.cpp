/*!
@file RandCreateManager.cpp
@brief ランダムなかけらの配置
担当：三瓶裕太
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	RandCreateManager::RandCreateManager(shared_ptr<Stage>& stagePtr,wstring objMapDataName,int mapSize,int num) :
		GameObject(stagePtr),
		m_ObjMapDataName(objMapDataName),
		m_MapSize(mapSize),
		m_Num(num)
	{

	}
	
	RandCreateManager::~RandCreateManager()
	{

	}

	void RandCreateManager::OnCreate()
	{
		auto& app = App::GetApp();
		auto path = app->GetDataDirWString();
		auto levelPath = path + L"Levels/";

		vector<vector<int>> kakeraMap;//マップの2次元座標を表す変数

		ifstream ifs(levelPath + m_ObjMapDataName);//ここのcsvの名前メンバ変数にする
		if (ifs)
		{
			string line;
			while (getline(ifs, line))
			{
				vector<int> datas;

				string data;
				istringstream ss(line);
				while (getline(ss, data, ','))
				{
					int cellData = atoi(data.c_str());//読み取ったデータをint型に変換する
					datas.push_back(cellData);//マップデータにCSVのデータをコピーする
				}

				kakeraMap.push_back(datas);//マップデータを一行一行入れていく
			}
		}

		int count = 0;//どれくらい生成したか数える
		while (count < m_Num)
		{
			int charkX = (rand() % m_MapSize+1)-1;
			int charkZ = (rand() % m_MapSize+1)-1;
			int a = 0;//デバック用

			int kakeraPosX = charkX - (m_MapSize / 2);
			float fKakeraPosX = (float)kakeraPosX;
			int kakeraPosZ = (m_MapSize / 2) - charkZ;
			float fKakeraPosZ = (float)kakeraPosZ;

			Vec3 Pos(fKakeraPosX, 0.1f, fKakeraPosZ);//かけらの場所

			switch (kakeraMap[charkZ][charkX])
			{
			case 0:
			{	
				auto& piece = GetStage()->AddGameObject<EnemyPiece>(Pos, Vec3(), Vec3(2.0f, 2.0f, 2.0f));//オブジェクト生成
				count++;//カウント
				PieceManager::enemyPieces.push_back(piece);
				break;
			}
			default:
				int a = 0;
				break;
			}
		}

	}
}