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
			int kakeraPosX = (rand() % (m_MapSize * 10)) - (m_MapSize * 10) / 2;//ランダムにかけらの場所を決める
			float fKakeraPosX = (float)kakeraPosX / 10;//floatに変更
			int kakeraPosZ = (rand() % (m_MapSize * 10)) - (m_MapSize * 10) / 2;//ランダムにかけらの場所を決める
			float fKakeraPosZ = (float)kakeraPosZ / 10;//floatに変更
			Vec3 Pos(fKakeraPosX, 0.1f, fKakeraPosZ);//かけらの場所

			int charkX = (int)fKakeraPosX + 75;//小数点切り捨て
			int charkZ = (int)fKakeraPosZ + 75;//小数点切り捨て

			switch (kakeraMap[charkZ][charkX])
			{
			case 0:
				GetStage()->AddGameObject<EnemyPiece>(Pos, Vec3(), Vec3(1.25f, 1.25f, 1.25f));//オブジェクト生成
				count++;//カウント
			default:
				break;
			}
		}

	}
}