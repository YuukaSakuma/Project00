//==============================================================
//
//ブロックX処理[blockX.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _BLOCKX_H_							//このマクロ定義がされていなかったら
#define _BLOCKX_H_							//2重インクルード防止のマクロを定義するv

#include"object.h"

//前方宣言
class CModel;

//==============================================================
//ブロックXクラス
//==============================================================
class CBlockX : public CObject
{
public:

	CBlockX();										//コンストラクタ
	CBlockX(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//コンストラクタ(オーバーロード)
	~CBlockX();										//デストラクタ

	static CBlockX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//ブロックXの生成

	HRESULT Init(void);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }		//位置の設定
	D3DXVECTOR3 GetPosition(void) { return m_pos; }			//位置の取得

private:

	LPDIRECT3DTEXTURE9 *m_pTexture;		//テクスチャへのポインタ
	LPD3DXMESH m_pMesh;					//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER m_pBuffMat;			//マテリアルへのポインタ
	DWORD m_dwNumMat;					//マテリアルの数

	D3DXVECTOR3 m_pos;					//位置
	D3DXVECTOR3 m_posOld;
	D3DXVECTOR3 m_rot;					//移動量
	D3DXVECTOR3 m_max;					//最大値
	D3DXVECTOR3 m_min;					//最小値
	D3DXVECTOR3 m_move;					//最小値

	D3DXMATRIX m_mtxWorld;				//ワールドマトリックス

	CModel *m_apModel[256];				//モデルのポインタ

	 int m_nNumModel;					//モデル数

	//int nldxShadow;
};
#endif