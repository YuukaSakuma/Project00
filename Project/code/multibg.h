//==============================================================
//
//多重背景ヘッダー[multibg.h]
//Author:佐久間優香
//
//==============================================================
#ifndef _MULTIBG_H_						//このマクロが定義されていなかったら
#define _MULTIBG_H_						//2重インクルード防止のマクロを定義する

#include"object.h"

//前方宣言
class CObject2D;

//==============================================================
//多重背景のクラス
//==============================================================
class CMultiBg : public CObject
{
public:
	CMultiBg();					//コンストラクタ
	~CMultiBg();				//デストラクタ

	//背景の種類
	typedef enum 
	{
		TYPE_BG_FIRST,	//背景1
		TYPE_BG_SECOND,	//背景2
		TYPE_BG_FINAL,	//背景3
		TYPE_BG_MAX

	}BG_TYPE;	

	HRESULT Init(void);			//初期化処理
	void Uninit(void);			//終了処理
	void Update(void);			//更新処理
	void Draw(void);			//描画処理

	static CMultiBg *Create(void);		//多重背景の生成処理

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }		//位置の設定
	D3DXVECTOR3 GetPosition(void) { return m_pos; }			//位置の取得

private:
	 
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_BG_MAX];		//共有テクスチャ
	static const char *apTexture[TYPE_BG_MAX];				//ファイル名

	CObject2D *m_apObject2D[TYPE_BG_MAX];		//オブジェクト2Dのテクスチャ
	D3DXVECTOR3 m_pos;							//位置
	float m_fTexV[TYPE_BG_MAX];					//テクスチャ座標の開始位置(V値)
	float m_fTexU[TYPE_BG_MAX];					//テクスチャ座標の開始位置(U値)
	float m_fmoveV[TYPE_BG_MAX];				//テクスチャ座標の移動量V
	float m_fmoveU[TYPE_BG_MAX];				//テクスチャ座標の移動量V

	int m_aldxTexture[TYPE_BG_MAX];				//テクスチャ番号
};			
#endif // !_MULTIBG_H_
