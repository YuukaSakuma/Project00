//==============================================================
//
//パーティクルヘッダー[particle.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _PARTICLE_H_						//このマクロが定義されていなかったら
#define _PARTICLE_H_						//2重インクルード防止のマクロを定義する

#include"object2D.h"

//==============================================================
//パーティクルクラス
//==============================================================
class CParticle : public CObject2D
{
public:

	CParticle();							//コンストラクタ
	~CParticle();							//デストラクタ

	static CParticle *Create(D3DXVECTOR3 pos, D3DXCOLOR col, TYPE type, float fRadius, int nLife);			//パーティクルの生成

	HRESULT Init(void);						//パーティクルの初期化処理
	void Uninit(void);						//パーティクルの終了処理
	void Update(void);						//パーティクルの更新処理
	void Draw(void);						//パーティクルの描画処理

	void Set(D3DXVECTOR3 pos, D3DXCOLOR col, CObject::TYPE type, float fRadius, int nLife);

private:

	static LPDIRECT3DTEXTURE9 m_pTexture;	//共有テクスチャ

	D3DXVECTOR3 m_pos;			//位置(開始時間)
	D3DXVECTOR3 m_move;			//移動量
	D3DXCOLOR m_col;			//色
	float m_fRadius;			//半径(大きさ)
	int m_nLife;				//寿命(発生時間)							
	int m_nType;				//種類
	float m_fAngle;				//
	float m_fMove;				//
	
};
#endif // !_PLAYER_H_
