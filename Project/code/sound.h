//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 佐久間優香
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//サウンドクラス
class CSound
{
public:

	//*****************************************************************************
	// サウンド一覧
	//*****************************************************************************
	typedef enum
	{
		SOUND_LABEL_TITLE = 0,		// BGM0
		SOUND_LABEL_GAME,			// BGM0
		SOUND_LABEL_RESULT,			// BGM0
		SOUND_LABEL_SE_JUMP,		// ジャンプ
		SOUND_LABEL_SE_COIN,		// コイン
		SOUND_LABEL_SE_PICK,		// 選択
		SOUND_LABEL_SE_EXPLOSION,	// 爆発音
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	CSound();
	~CSound();

	//*****************************************************************************
	// プロトタイプ宣言
	//*****************************************************************************
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	static HRESULT Play(SOUND_LABEL label);
	static void Stop(SOUND_LABEL label);
	static void Stop(void);

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

private:

	//*****************************************************************************
	// サウンド情報の構造体定義
	//*****************************************************************************
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} SOUNDINFO;

	IXAudio2 *m_pXAudio2;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;			// マスターボイス
	static IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	static BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	static DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ
	static SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX];
};



#endif
