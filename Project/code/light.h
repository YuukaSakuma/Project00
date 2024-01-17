//==============================================================
//
//ライトヘッダー[light.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _LIGHT_H_							//このマクロ定義がされていなかったら
#define _LIGHT_H_							//2重インクルード防止のマクロを定義する

#include"main.h"

//ライトクラス
class CLight
{
public:
	CLight();		//コンストラクタ
	~CLight();		//デストラクタ

	HRESULT Init(void);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理

private:

	D3DLIGHT9 m_light[3];				//ライトの情報

};
#endif
