//==============================================================
//
//�}�l�[�W������[manager.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include"manager.h"
#include "object2D.h"
#include"bg.h"
#include"multibg.h"
#include"score.h"
#include"block.h"
#include"object3D.h"
#include"polygon.h"
#include"billboard.h"
#include"objectX.h"
#include"texture.h"
#include"renderer.h"
#include"input.h"
#include"light.h"
#include"sound.h"
#include"camera.h"
#include"blockX.h"
#include"player.h"
#include"field.h"
#include"model.h"
#include"title.h"
#include"tutorial.h"
#include"game.h"
#include"result.h"
#include"ranking.h"
#include"fade.h"
#include"Xfile.h"

//�ÓI�����o�ϐ�

CScene *CManager::m_pScene = NULL;
CFade *CManager::m_pFade = NULL;

//CTitle *CScene::m_pTitle = NULL;
//CTutorial *CScene::m_pTutorial = NULL;
//CGame *CScene::m_pGame = NULL;
//CResult *CScene::m_pResult = NULL;
//CRanking *CScene::m_pRanking = NULL;
CManager *CManager::m_pManager = NULL;


//==============================================================
//�R���X�g���N�^
//==============================================================
CScene::CScene()
{
	m_mode = MODE_TITLE;
}

//==============================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//==============================================================
CScene::CScene(MODE mode)
{
	m_mode = mode;
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CScene::~CScene()
{

}

//==============================================================
// �V�[���̐���
//==============================================================
CScene *CScene::Create(MODE mode)
{
	CScene *pScene = NULL;

	if (pScene == NULL)
	{
		switch (mode)
		{
		case MODE_TITLE:			//�^�C�g�����
			pScene = new CTitle;
			break;

		case MODE_TUTORIAL:			//�`���[�g���A�����
			pScene = new CTutorial;
			break;

		case MODE_GAME:				//�Q�[�����
			pScene = new CGame;
			break;

		case MODE_RESULT:			//���U���g���
			pScene = new CResult;
			break;

		case MODE_RANKING:			//�����L���O���
			pScene = new CRanking;
			break;
		}
	}

	if (pScene != NULL)
	{// �������̊m�ۂ��o���Ă�����

	 // ���[�h�̐ݒ�
		pScene->m_mode = mode;

		// ����������
		pScene->Init();
	}

	return pScene;
}

//==============================================================
// �V�[���̏���������
//==============================================================
HRESULT CScene::Init(void)
{
	
	return S_OK;
}

//==============================================================
// �V�[���̏I������
//==============================================================
void CScene::Uninit(void)
{
	
}

//==============================================================
// �V�[���̍X�V����
//==============================================================
void CScene::Update(void)
{
	

}

//==============================================================
// �V�[���̕`�揈��
//==============================================================
void CScene::Draw(void)
{

}

//==============================================================
//�R���X�g���N�^
//==============================================================
CManager::CManager()
{
	m_pCamera = NULL;
	m_pDebugProc = NULL;
	m_pFade = NULL;
	m_pInputKeyboard = NULL;
	m_pLight = NULL;
	m_pMaterial = NULL;
	m_pPlayerModel = NULL;
	m_pRenderer = NULL;
	m_pScene = NULL;
	m_pSound = NULL;
	m_pTexture = NULL;
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CManager::~CManager()
{ 

}

//==============================================================
//�}�l�[�W���̏���������
//==============================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL hWindow)
{
	CNumber * pNum = NULL;

	m_pRenderer = NULL;
	m_pCamera = NULL;
	m_pDebugProc = NULL;
	m_pFade = NULL;
	m_pInputKeyboard = NULL;
	m_pLight = NULL;
	m_pMaterial = NULL;
	m_pPlayerModel = NULL;
	
	m_pScene = NULL;
	m_pSound = NULL;
	m_pTexture = NULL;

	//�����_���[�̐����E����������
	if (m_pRenderer == NULL)
	{//�g�p���Ă��Ȃ��Ƃ�	
		m_pRenderer = new CRenderer;
	}

	if (m_pRenderer != NULL)
	{//�g�p���Ă���Ƃ�
		if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
		{//���������������s�����ꍇ
			return -1;
		}
	}

	//�f�o�b�O�\���̐���
	if (m_pDebugProc == NULL)
	{//���������g�p����ĂȂ��Ƃ�

		m_pDebugProc = new CDebugProc;
	}

	if (m_pDebugProc != NULL)
	{//���������m�ۂ��ꂽ�Ƃ�

	 //�f�o�b�O�\���̏���������
		m_pDebugProc->Init();
	}

	//�L�[�{�[�h�̐����E����������
	if (m_pInputKeyboard == NULL)
	{//�g�p���Ă��Ȃ��Ƃ�
		m_pInputKeyboard = new CInputKeyboard;
	}

	if (m_pInputKeyboard != NULL)
	{//�g�p���Ă���Ƃ� 
		if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
		{//���������������s�����ꍇ
			return -1;
		}
	}

	//�T�E���h�̐����E����������
	if (m_pSound == NULL)
	{//�g�p���Ă��Ȃ��Ƃ�
		m_pSound = new CSound;
	}

	if (m_pSound != NULL)
	{//�g�p���Ă���Ƃ�
		if (FAILED(m_pSound->Init(hWnd)))
		{//���������������s�����ꍇ
			return -1;
		}
	}

	//�T�E���h�̐����E����������
	if (m_pCamera == NULL)
	{//�g�p���Ă��Ȃ��Ƃ�
		m_pCamera = new CCamera;
	}

	if (m_pCamera != NULL)
	{//�g�p���Ă���Ƃ�
		if (FAILED(m_pCamera->Init()))
		{//���������������s�����ꍇ
			return -1;
		}
	}

	//�T�E���h�̐����E����������
	if (m_pLight == NULL)
	{//�g�p���Ă��Ȃ��Ƃ�
		m_pLight = new CLight;
	}

	if (m_pLight != NULL)
	{//�g�p���Ă���Ƃ�
		if (FAILED(m_pLight->Init()))
		{//���������������s�����ꍇ
			return -1;
		}
	}

	//�T�E���h�̐����E����������
	if (m_pTexture == NULL)
	{//�g�p���Ă��Ȃ��Ƃ�
		m_pTexture = new CTexture;
	}
	m_pTexture->Load();

	//�}�e���A���̐���
	if (m_pMaterial == NULL)
	{
		m_pMaterial = new CXFile;
	}

	if (m_pMaterial != NULL)
	{//�������m�ۂł��Ă���

	 //�}�e���A���̓ǂݍ���
		if (FAILED(m_pMaterial->Load()))
		{//�ǂݍ��݂����s�����ꍇ

			return E_FAIL;
		}
	}

	//���[�h�ݒ�
	SetMode(CScene::MODE_TITLE);

	////�T�E���h�̍Đ�
	//CSound::Play(CSound::SOUND_LABEL_BGM000);

	return S_OK;
}

//==============================================================
//�}�l�[�W���̏I������
//==============================================================
void CManager::Uninit(void)
{
	//�S�Ẵe�N�X�`���̔j��
	if (m_pMaterial != NULL)
	{
		//�e�N�X�`���̏I������
		m_pMaterial->Unload();

		delete m_pMaterial;
		m_pMaterial = NULL;
	}

	//�S�Ẵe�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		//�e�N�X�`���̏I������
		m_pTexture->Unload();

		delete m_pTexture;
		m_pTexture = NULL;
	}

	//�S�Ă̐���
	CObject::ReleseAll();

	////�T�E���h�̒�~
	//CSound::Stop();

	//�J�����̏I������
	if (m_pCamera != NULL)
	{//�g�p���Ă�����	
		m_pCamera->Uninit();

		delete m_pCamera;
		m_pCamera = NULL;
	}

	//�J�����̏I������
	if (m_pLight != NULL)
	{//�g�p���Ă�����	
		m_pLight->Uninit();

		delete m_pLight;
		m_pLight = NULL;
	}

	//�T�E���h�̏I������
	if (m_pSound != NULL)
	{//�g�p���Ă�����	
		m_pSound->Uninit();

		delete m_pSound;
		m_pSound = NULL;
	}

	//�f�o�b�O�\���̔j��
	if (m_pDebugProc != NULL)
	{
		//�f�o�b�O�\���̏I������
		m_pDebugProc->Uninit();

		//�������J��
		delete m_pDebugProc;
		m_pDebugProc = NULL;
	}

	//�����_���[�̏I������
	if (m_pRenderer != NULL)
	{//�g�p���Ă�����	
		m_pRenderer->Uninit();

		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//�L�[�{�[�h�̏I������
	if (m_pRenderer != NULL)
	{//�g�p���Ă�����
		m_pInputKeyboard->Uninit();

		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}
}

//==============================================================
//�}�l�[�W���̍X�V����
//==============================================================
void CManager::Update(void)
{
	//�L�[�{�[�h�̍X�V����
	m_pInputKeyboard->Update();
	m_pCamera->Update();

	//�f�o�b�O�\���̍X�V����
	m_pDebugProc->Update();

	m_pLight->Update();

	//�}�b�v�̍Đ���
	CManager::ResetMap();

	//�����_���[�̍X�V����
	m_pRenderer->Update();
}

//==============================================================
//�}�l�[�W���̕`�揈��
//==============================================================
void CManager::Draw(void)
{
	//�����_���[�̕`�揈��
	m_pRenderer->Draw();
}

//==============================================================
// ���[�h�̐ݒ�
//==============================================================
void CManager::SetMode(CScene::MODE mode)
{
	Get()->m_pSound->Stop();

	if (m_pScene != NULL)
	{
		m_pScene->Uninit();

		//delete m_pScene;
		m_pScene = NULL;
	}

	//���ׂĔj������
	CObject::ReleseAll();

	m_pFade = NULL;

	//�T�E���h�̐����E����������
	if (Get()->m_pTexture == NULL)
	{//�g�p���Ă��Ȃ��Ƃ�
		Get()->m_pTexture = new CTexture;

		if (Get()->m_pTexture != NULL)
		{
			Get()->m_pTexture->Load();
		}
	}

	// �V�������[�h�̐���
	m_pScene = CScene::Create(mode);
	m_pScene->SetMode(mode);


	if (m_pScene == NULL)
	{
		m_pScene = CScene::Create(mode);
	}

	// �t�F�[�h�̐���
	if (m_pFade == NULL)
	{
		m_pFade = CFade::Create(mode);
	}
}

//==============================================================
// ���[�h�̎擾
//==============================================================
CScene::MODE CManager::GetMode(void)
{
	return m_pScene->GetMode();
}

//==============================================================
//��������
//==============================================================
void CManager::CreateAll(void)
{
	////�X�R�A�̐���
	//CScore::Create(D3DXVECTOR3(800.0f, 50.0f, 0.0f));
}

//==============================================================
//���Z�b�g
//==============================================================
void CManager::ResetMap(void)
{
	////���Z�b�g
	//if (m_pInputKeyboard->GetPress(DIK_F2) == true)
	//{//F2���������Ƃ�

	//	//�}�b�v�̃I�u�W�F�N�g�̃��Z�b�g
	//	CObject::ResetMapAll();

	//	//�I�u�W�F�N�g�̐���
	//	CManager::CreateAll();
	//}
}

//==============================================================
//�����_���[�̃f�o�C�X�̎擾
//==============================================================
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//==============================================================
//�L�[�{�[�h�̃f�o�C�X�̎擾
//==============================================================
CInputKeyboard *CManager::GetInputKeybard(void)
{
	return m_pInputKeyboard;
}

//==============================================================
//�v���C���[�̃f�o�C�X�̎擾
//==============================================================
CPlayer *CManager::GetPlayerModel(void)
{
	return m_pPlayerModel;
}

//==============================================================
//�J�����̎擾
//==============================================================
CCamera *CManager::GetCamera(void)
{
	return m_pCamera;
}

//==============================================================
//�e�N�X�`���̎擾
//==============================================================
CTexture * CManager::GetTexturet(void)
{
	return m_pTexture;
}

//===================================================
// �f�o�b�O�\���̎擾
//===================================================
CDebugProc *CManager::GetDebugProc(void)
{
	return m_pDebugProc;
}

//===================================================
// �f�o�b�O�\���̎擾
//===================================================
CFade *CManager::GetFade(void)
{
	return m_pFade;
}

//===================================================
// �f�o�b�O�\���̎擾
//===================================================
CSound *CManager::GetSound(void)
{
	return m_pSound;
}

//===================================================
// �f�o�b�O�\���̎擾
//===================================================
CManager *CManager::Get(void)
{
	if (m_pManager == NULL)
	{
		return m_pManager = new CManager;
	}
	else
	{
		return m_pManager;
	}

}

//===================================================
// �f�o�b�O�\���̎擾
//===================================================
HRESULT CManager::Release(void)
{
	if (m_pManager != NULL)
	{//�g�p���Ă�����

	 //�����_���[�̏I������
		m_pManager->Uninit();

		delete m_pManager;
		m_pManager = NULL;
	}

	return S_OK;

}