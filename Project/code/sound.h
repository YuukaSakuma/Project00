//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : ���v�ԗD��
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//�T�E���h�N���X
class CSound
{
public:

	//*****************************************************************************
	// �T�E���h�ꗗ
	//*****************************************************************************
	typedef enum
	{
		SOUND_LABEL_TITLE = 0,		// BGM0
		SOUND_LABEL_GAME,			// BGM0
		SOUND_LABEL_RESULT,			// BGM0
		SOUND_LABEL_SE_JUMP,		// �W�����v
		SOUND_LABEL_SE_COIN,		// �R�C��
		SOUND_LABEL_SE_PICK,		// �I��
		SOUND_LABEL_SE_EXPLOSION,	// ������
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	CSound();
	~CSound();

	//*****************************************************************************
	// �v���g�^�C�v�錾
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
	// �T�E���h���̍\���̒�`
	//*****************************************************************************
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDINFO;

	IXAudio2 *m_pXAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;			// �}�X�^�[�{�C�X
	static IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	static BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	static DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
	static SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX];
};



#endif
