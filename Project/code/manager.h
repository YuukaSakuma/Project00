//==============================================================
//
//�}�l�[�W���w�b�_�[[manager.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _MANAGER_H_						//���̃}�N������`����Ă��Ȃ�������
#define _MANAGER_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"input.h"
#include"sound.h"
#include"camera.h"
#include"light.h"
#include"renderer.h"
#include"texture.h"
#include"debugproc.h"

//�O���錾
class CPlayer;
class CMaterial;
class CTitle;			//�^�C�g�����
class CTutorial;		//�`���[�g���A�����
class CGame;			//�Q�[�����
class CResult;			//���U���g���
class CRanking;			//�����L���O���
class CFade;			//�t�F�[�h

class CEdit;

//==============================================================
//�V�[���N���X
//==============================================================
class CScene : public CObject
{
public:

	//���[�h�̎��
	typedef enum
	{
		MODE_TITLE = 0,		//�^�C�g��
		MODE_TUTORIAL,		//�`���[�g���A��
		MODE_GAME,			//�Q�[��
		MODE_RESULT,		//���U���g
		MODE_RANKING,
		MODE_MAX,
	}MODE;

	CScene();				//�R���X�g���N�^
	CScene(MODE mode);		//�R���X�g���N�^(�I�[�o�[���[�h)
	~CScene();				//�f�X�g���N�^

	static CScene *Create(MODE mode);	//�V�[���̐���

	virtual	HRESULT Init(void);		//����������
	virtual void Uninit(void);		//�I������
	virtual void Update(void);		//�X�V����
	virtual	void Draw(void);		//�`�揈��

	MODE GetMode(void) { return m_mode; }			//���[�h�擾
	void SetMode(MODE mode) { m_mode = mode; }

private:

	MODE m_mode;	//���[�h
};

//==============================================================
//�}�l�[�W���N���X
//==============================================================
class CManager
{
public:
	CManager();			//�R���X�g���N�^
	~CManager();		//�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL hWindow);	//�}�l�[�W���̏���������
	void Uninit(void);											//�}�l�[�W���̏I������
	void Update(void);											//�}�l�[�W���̍X�V����
	void Draw(void);											//�}�l�[�W���̕`�揈��

	static CManager *Get(void);
	static HRESULT Release(void);

	 CRenderer * GetRenderer(void);			//�����_���[�̎擾
	 CInputKeyboard *GetInputKeybard(void);	//�L�[�{�[�h�̎擾
	 CPlayer * GetPlayerModel(void);		//�v���C���[�̎擾
	 CCamera * GetCamera(void);				//�J�����̎擾
	 CLight * GetLight(void);					//���C�g�̎擾
	 CTexture * GetTexturet(void);			//�e�N�X�`���̎擾
	 CMaterial *GetMaterial(void) { return m_pMaterial; }		//�}�e���A���̎擾
	 CDebugProc *GetDebugProc(void);			//�f�o�b�O�v���b�N�̎擾
	 CFade *GetFade(void);
	 CSound *GetSound(void);

	static void SetMode(CScene::MODE mode);			//���[�h�̐ݒ�
	static CScene::MODE GetMode(void);				//���[�h�̎擾

	void LoadAll(void);		//�e�N�X�`���̓ǂݍ���
	void UnloadAll(void);	//�e�N�X�`���̔j��
	void CreateAll(void);	//��������
	void ResetMap(void);	//�Đ���

private:

	static CManager *m_pManager;

	 CRenderer *m_pRenderer;					//�����_���[�̃|�C���^
	 CInputKeyboard *m_pInputKeyboard;		//�L�[�{�[�h�̃|�C���^
	 CPlayer * m_pPlayerModel;			//�v���C���[�̃|�C���^
	 CSound * m_pSound;						//�T�E���h�̃|�C���^
	 CCamera * m_pCamera;						//�J�����̃|�C���^
	 CLight * m_pLight;						//�J�����̃|�C���^
	 CTexture * m_pTexture;					//�e�N�X�`���̃|�C���^
	 CMaterial *m_pMaterial;		//�}�e���A���̏��
	 CDebugProc *m_pDebugProc;				//�f�o�b�O�v���b�N�̃|�C���^

	static CScene *m_pScene;	//�V�[���̃|�C���^
	static CFade *m_pFade;
};

#endif // !_MANAGER_H_

