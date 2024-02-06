//==============================================================
//
//�v���C���[����[player.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include"player.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"
#include"sound.h"
#include"model.h"
#include"motion.h"
#include"camera.h"
#include"objectX.h"
#include"modelHierarchy.h"
#include <stdio.h>
#include"debugproc.h"
#include"particle.h"
#include"life.h"
#include"game.h"
#include"score.h"
#include"bullet.h"
 
//�}�N����`
#define WIDTH (50.0f)	//����
#define HEIGHT (80.0f)	//����
#define LIFE (10000000)		//�̗�
#define SPEED (0.8f)		//�f����
#define PLAYER_JUMP (25.0f)
#define PLAYER_GRAVITY (-2.0f)

//�ÓI�����o�ϐ�
char *CPlayer::m_apFileName[9] =
{
	"data\\MODEL\\player\\00_waist.x",
	"data\\MODEL\\player\\01_body.x",
	"data\\MODEL\\player\\02_head.x",
	"data\\MODEL\\player\\03_arm_L.x",
	"data\\MODEL\\player\\04_arm_R.x",
	"data\\MODEL\\player\\05_foot_L.x",
	"data\\MODEL\\player\\06_foot_R.x",
	"data\\MODEL\\player\\07_tail.x",
	"data\\MODEL\\player\\sword.x",
};

//==============================================================
//�R���X�g���N�^
//==============================================================
CPlayer::CPlayer()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�O��̈ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
	m_max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���f���̍ő�l
	m_min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���f���̍ŏ��l

	m_nCntDamage = 0;		//�_���[�W�J�E���^�[

	m_state = CObjectX::STATE_NONE;		//�ʏ��Ԃɂ���

	for (int nCntPlayer = 0; nCntPlayer < 9; nCntPlayer++)
	{
		m_apModel[nCntPlayer] = NULL;		//�v���C���[(�p�[�c)�ւ̃|�C���^
	}

	m_nNumModel = 0;		//�v���C���[(�p�[�c)�̑���
	m_bJump = false;		//�W�����v������
	m_pMotion = NULL;
	m_bMove = false;		//�����Ă邩
	m_bLand = true;			//���n����
	m_fRotDest = 0.0f;		//�ڕW
	m_fRotDiff = 0.0f;		//����

	m_nLife = LIFE;
}

//==============================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//==============================================================
CPlayer::CPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;		//�ʒu
	m_rot = rot;		//����
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�O��̈ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړ���
	m_max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���f���̍ő�l
	m_min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���f���̍ŏ��l

	m_nCntDamage = 0;		//�_���[�W�J�E���^�[

	m_state = CObjectX::STATE_NONE;		//�ʏ��Ԃɂ���


	for (int nCntPlayer = 0; nCntPlayer < 9; nCntPlayer++)
	{
		m_apModel[nCntPlayer] = NULL;		//�v���C���[(�p�[�c)�ւ̃|�C���^
	}

	m_nNumModel = 0;		//�v���C���[(�p�[�c)�̑���
	m_bJump = false;		//�W�����v������
	m_pMotion = NULL;
	m_bMove = false;		//�����Ă邩
	m_bLand = true;			//���n����
	m_fRotDest = 0.0f;		//�ڕW
	m_fRotDiff = 0.0f;		//����
	//m_pCamera = nullptr;
	
	m_nLife = LIFE;

	m_bHit = false;
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CPlayer::~CPlayer()
{

}

//==============================================================
//�v���C���[���f���̐�������
//==============================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer *pPlayerModel = NULL;

	if (pPlayerModel == NULL)
	{//���������g�p����ĂȂ�������

	 //�v���C���[�̐���
		pPlayerModel = new CPlayer(pos, rot);
	}

	//����������
	pPlayerModel->Init();

	//��ނ̐ݒ�
	pPlayerModel->SetType(CObject::TYPE_PLAYER);

	return pPlayerModel;
}

//==============================================================
//�v���C���[���f���̏���������
//==============================================================
HRESULT CPlayer::Init(void)
{
	//CLife *pLife = CGame::GetLife();

	//�v���C���[�̐����i�S�p�[�c���j
	for (int nCntModel = 0; nCntModel < 9; nCntModel++)
	{
		m_apModel[nCntModel] = m_apModel[nCntModel]->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apFileName[nCntModel]);
	}

	//���f���̃t�@�C���ǂݍ���
	CPlayer::SetModel("data\\TXT\\player.txt");

	m_pMotion = NULL;

	if (m_pMotion == NULL)
	{
		m_pMotion = m_pMotion->Create();

		if (m_pMotion != NULL)
		{
			//���[�V�����̏������E����
			m_pMotion->SetModel(&m_apModel[0], 9);
			m_pMotion->Init("data\\TXT\\player.txt",9);
		}
	}

	//�ő�l�E�ŏ��l���
	for (int nCntPlayer = 0; nCntPlayer < 9; nCntPlayer++)
	{
		//�ő�lY
		if ((nCntPlayer <= 0 && nCntPlayer <= 1) ||
			(nCntPlayer <= 5 && nCntPlayer <= 6))
		{
			m_max.y += m_apModel[nCntPlayer]->GetSizeMax().y;		//�ő�l���Z
		}

		//�ő�l����ւ�
		if (m_max.x < m_apModel[nCntPlayer]->GetSizeMax().x)
		{
			m_max.x = m_apModel[nCntPlayer]->GetSizeMax().x;		//�ŏ��lX
		}
		if (m_max.z < m_apModel[nCntPlayer]->GetSizeMax().z)
		{
			m_max.z = m_apModel[nCntPlayer]->GetSizeMax().z;		//�ŏ��lZ

		}

		//�ŏ��l����ւ�
		if (m_min.x > m_apModel[nCntPlayer]->GetSizeMin().x)
		{
			m_min.x = m_apModel[nCntPlayer]->GetSizeMin().x;		//�ŏ��lX
		}
		if (m_min.y > m_apModel[nCntPlayer]->GetSizeMin().y)
		{
			m_min.y = m_apModel[nCntPlayer]->GetSizeMin().y;		//�ŏ��lY
		}
		if (m_min.z > m_apModel[nCntPlayer]->GetSizeMin().z)
		{
			m_min.z = m_apModel[nCntPlayer]->GetSizeMin().z;		//�ŏ��lZ

		}
	}

	CObject::SetType(CObject::TYPE_PLAYER);

	m_max.y += 10.0f;

	//if (CManager::GetMode() == CScene::MODE_GAME)
	//{
	//	//�����ݒ�
	//	pLife->SetMax(LIFE);
	//}

	return S_OK;
}

//==============================================================
//�v���C���[���f���̏I������
//==============================================================
void CPlayer::Uninit(void)
{
	for (int nCntPlayer = 0; nCntPlayer < 9; nCntPlayer++)
	{
		if (m_apModel[nCntPlayer] != NULL)
		{//�g�p����Ă�Ƃ�

		 //�I������
			m_apModel[nCntPlayer]->Uninit();
			m_apModel[nCntPlayer] = NULL;
		}
	}

	if (m_pMotion != NULL)
	{//�g�p����Ă�Ƃ�

	 //���[�V�����̔j��
		delete m_pMotion;
		m_pMotion = NULL;
	}

	//�I�u�W�F�N�g�i�������g�̔j���j
	CObject::Release();
}

//==============================================================
//�v���C���[���f���̍X�V����
//==============================================================
void CPlayer::Update(void)
{
	CDebugProc *pDebugProc = CManager::Get()->GetDebugProc();

	//�ʒu�̎擾
	m_pos = GetPosition();

	//�O��̈ʒu�ɑ��
	m_posOld = m_pos;

	//�v���C���[�̑���
	CPlayer::Control();

	//if (m_pCamera != nullptr) {
	//	// �Ǐ]����
	//	m_pCamera->Update();
	//}

	//�d��
	m_move.y += PLAYER_GRAVITY;

	//�ړ��ʂ��X�V
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;
	m_move.y += (0.0f - m_move.y) * 0.1f;

	//�ʒu���X�V
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

	//�����蔻��
	if (CObjectX::Collision(&m_pos, &m_posOld, &m_move, m_min, m_max) == true)
	{
		m_bJump = false;	//�W�����v���ĂȂ���Ԃɂ���
		m_bLand = true;		//���n������Ԃɂ���
	}

	//if (m_pCamera != nullptr) {
	//	// �Ǐ]����	
	//	m_pCamera->Move(GetPosition(), GetRotation());
	//}

	//��ʐ���
	CPlayer::Screen();

 	SetState();

	//���[�V�����̍X�V����
	m_pMotion->Update();

	pDebugProc->Print("�v���C���[�̈ʒu : [%f %f %f] \n", m_pos.x, m_pos.y, m_pos.z);

	pDebugProc->Print("�̗� : [%d] \n", m_nLife);
}

//==============================================================
////�v���C���[���f���̕`�揈��
//==============================================================
void CPlayer::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;						//�v�Z�p�}�g���b�N�X

	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::Get()->GetRenderer();

	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mxtWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mxtWorld, &m_mxtWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mxtWorld, &m_mxtWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mxtWorld);

	for (int nCntMat = 0; nCntMat < 9; nCntMat++)
	{
		m_apModel[nCntMat]->Draw();
	}
}

//==============================================================
//�v���C���[���f���̑���
//==============================================================
void CPlayer::Control(void)
{
	D3DXVECTOR3 pos = GetPosition();	// ���W���擾
	D3DXVECTOR3 rot = GetRotation();	// �������擾

	CInputKeyboard *pInputKeyboard = CManager::Get()->GetInputKeybard();

	m_fRotMove = rot.y;

	Walk();

	//if (pInputKeyboard->GetTrigger(DIK_O) == true)
	//{
	//	m_pMotion->Set(m_pMotion->MOTOIN_ATTACK);
	//}

	//�����̕␳����
	RotCorrection();

	//���[�V�����̐ݒ�
	SetMotion();

	if ((m_move.x <= 0.8f && m_move.x >= -0.8f) && (m_move.y <= 0.8f && m_move.y >= -0.8f) && (m_move.z <= 0.8f && m_move.z >= -0.8f))
	{//�����Ă��Ȃ��Ƃ�

		m_bMove = false;		//�����Ă��Ȃ���Ԃɂ���
	}

	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true && m_bJump == false)
	{

		//�W�����v����
		m_move.y = PLAYER_JUMP;

		//�W�����v������Ԃɂ���
		m_bJump = true;
		m_bLand = false;
	}

	Adjust();
}

//===============================================
// ����
//===============================================
void CPlayer::Adjust(void)
{
	while (1)
	{
		if (m_fRotDest > D3DX_PI || m_fRotDest < -D3DX_PI)
		{//-3.14�`3.14�͈̔͊O�̏ꍇ
			if (m_fRotDest > D3DX_PI)
			{
				m_fRotDest += (-D3DX_PI * 2);
			}
			else if (m_fRotDest < -D3DX_PI)
			{
				m_fRotDest += (D3DX_PI * 2);
			}
		}
		else
		{
			break;
		}
	}

	m_fRotDiff = m_fRotDest - m_fRotMove;	//�ڕW�܂ł̈ړ������̍���

	while (1)
	{
		if (m_fRotDiff > D3DX_PI || m_fRotDiff < -D3DX_PI)
		{//-3.14�`3.14�͈̔͊O�̏ꍇ
			if (m_fRotDiff > D3DX_PI)
			{
				m_fRotDiff += (-D3DX_PI * 2);
			}
			else if (m_fRotDiff < -D3DX_PI)
			{
				m_fRotDiff += (D3DX_PI * 2);
			}
		}
		else
		{
			break;
		}
	}

	m_rot.y += m_fRotDiff;

	while (1)
	{
		if (m_rot.y > D3DX_PI || m_rot.y < -D3DX_PI)
		{//-3.14�`3.14�͈̔͊O�̏ꍇ
			if (m_rot.y > D3DX_PI)
			{
				m_rot.y += (-D3DX_PI * 2);
			}
			else if (m_rot.y < -D3DX_PI)
			{
				m_rot.y += (D3DX_PI * 2);
			}
		}
		else
		{
			break;
		}
	}
}

//==============================================================
//�v���C���[���f���̉�ʐ���
//==============================================================
void CPlayer::Screen(void)
{
	if (m_pos.y <= 0.0f)
	{//��ʉ��ɏo����
		//if (m_bJump == true)
		//{//�W�����v���Ă���

		// //���n
		//	m_pMotion->Set(m_pMotion->MOTION_LAND);
		//}

		//if (m_pMotion->IsFinish() == true)
		//{//�I��������

			m_bLand = true;		//���n����
		//}

		m_pos.y = 0.0f;
		m_move.y = 0.0f;

		m_bJump = false;
	}

}

//==============================================================
//�v���C���[���f���̃��[�V�����̐ݒ�
//==============================================================
void CPlayer::SetMotion(void)
{
	if (m_bMove == true && m_pMotion->GetType() == m_pMotion->MOTION_NEUTRAL)
	{//�����Ă� && �ҋ@���

	 //��������
		m_pMotion->Set(m_pMotion->MOTION_WALK);
	}
	else if ((m_pMotion->GetType() != m_pMotion->MOTION_NEUTRAL&& m_pMotion->IsFinish() == true) ||
		(m_pMotion->GetType() != m_pMotion->MOTION_NEUTRAL && m_bMove == false && m_bJump == false && m_bLand == true))
	{//���[�V�������I��������

	 //�ҋ@��Ԃɖ߂�
		m_pMotion->Set(m_pMotion->MOTION_NEUTRAL);
	}
}

//==============================================================
//�v���C���[���f���̈ړ�(����)
//==============================================================
void CPlayer::Walk(void)
{
	m_bMove = false;

	CInputKeyboard *pInputKeyboard = CManager::Get()->GetInputKeybard();

	//CCamera *pCamera = m_pCamera;		// �J�����̃|�C���^

	CCamera *pCamera = CManager::Get()->GetCamera();

	/*if (m_pCamera == nullptr) {
		pCamera = CManager::Get()->GetCamera();
	}*/
	D3DXVECTOR3 CamRot = pCamera->GetRotation();	// �J�����̊p�x

	float fSpeed = SPEED;	// �ړ���

	//�L�[�������ꂽ�Ƃ�
	if (pInputKeyboard->GetPress(DIK_A) == true)
	{//A�L�[�������ꂽ
		if (pInputKeyboard->GetPress(DIK_W) == true)
		{//����ړ�
			m_move.x += cosf(CamRot.y + (-D3DX_PI * 0.75f)) * fSpeed;
			m_move.z += sinf(CamRot.y + (-D3DX_PI * 0.75f)) * fSpeed;
			m_fRotDest = (-CamRot.y + D3DX_PI * 0.25f);

		}
		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{//�����ړ�
			m_move.x += cosf(CamRot.y + (-D3DX_PI * 0.25f)) * fSpeed;
			m_move.z += sinf(CamRot.y + (-D3DX_PI * 0.25f)) * fSpeed;
			m_fRotDest = (-CamRot.y + -D3DX_PI * 0.25f);
		}
		else
		{//���ړ�
			m_move.x += cosf(CamRot.y + (-D3DX_PI * 0.5f)) * fSpeed;
			m_move.z += sinf(CamRot.y + (-D3DX_PI * 0.5f)) * fSpeed;
			m_fRotDest = -CamRot.y;
		}
		m_bMove = true;			//�����Ă邩�̔���
	}
	else if (pInputKeyboard->GetPress(DIK_D) == true)
	{//D�L�[�������ꂽ

		if (pInputKeyboard->GetPress(DIK_W) == true)
		{//
			m_move.x += cosf(CamRot.y + (D3DX_PI * 0.75f)) * fSpeed;
			m_move.z += sinf(CamRot.y + (D3DX_PI * 0.75f)) * fSpeed;

			m_fRotDest = (-CamRot.y + D3DX_PI * 0.75f);
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{//
			m_move.x += cosf(CamRot.y + (D3DX_PI * 0.25f)) * fSpeed;
			m_move.z += sinf(CamRot.y + (D3DX_PI * 0.25f)) * fSpeed;

			m_fRotDest = (-CamRot.y + -D3DX_PI * 0.75f);
		}
		else
		{//
			m_move.x += cosf(CamRot.y + (D3DX_PI * 0.5f)) * fSpeed;
			m_move.z += sinf(CamRot.y + (D3DX_PI * 0.5f)) * fSpeed;
			m_fRotDest = (-CamRot.y + D3DX_PI * 1.0f);
		}
		m_bMove = true;			//�����Ă邩�̔���
	}
	else if (pInputKeyboard->GetPress(DIK_W) == true)
	{//W�L�[�������ꂽ
		m_move.x += -cosf(CamRot.y) * fSpeed;
		m_move.z += -sinf(CamRot.y) * fSpeed;
		m_fRotDest = (-CamRot.y + D3DX_PI * 0.5f);

		m_bMove = true;			//�����Ă邩�̔���
	}
	else if (pInputKeyboard->GetPress(DIK_S) == true)
	{//S�L�[�������ꂽ
		m_move.x += cosf(CamRot.y) * fSpeed;
		m_move.z += sinf(CamRot.y) * fSpeed;
		m_fRotDest = (-CamRot.y + -D3DX_PI * 0.5f);

		m_bMove = true;			//�����Ă邩�̔���
	}

	if (pInputKeyboard->GetTrigger(DIK_O) == true)
	{
		m_pMotion->Set(m_pMotion->MOTOIN_ATTACK);
	}

	D3DXVECTOR3 move = D3DXVECTOR3(-sinf(m_rot.y) * 10.0f, 0.0f, -cosf(m_rot.y) * 10.0f);

	if (pInputKeyboard->GetTrigger(DIK_H) == true)
	{
		CBullet::Create(m_pos, m_rot, move, CBullet::TYPE_A,CObject::TYPE_PLAYER);
	}
	else if (pInputKeyboard->GetTrigger(DIK_J) == true)
	{
		CBullet::Create(m_pos, m_rot, move, CBullet::TYPE_B,CObject::TYPE_PLAYER);
	}
	
}

//==============================================================
//�v���C���[���f���̃q�b�g����
//==============================================================
void CPlayer::Hit(void)
{
	m_nLife--;

	if (m_nLife > 0)
	{
		//m_state = CObject::STATE_DAMAGE;

		for (int nCntEnemy = 0; nCntEnemy < 9; nCntEnemy++)
		{
			//m_apModel[nCntEnemy]->SetState(m_state);		//�_���[�W��Ԃɂ���
		}

		//m_nCntDamage = 5;
	}
	else if (m_nLife <= 0)
	{
		
		m_bHit = true;
		//�p�[�e�B�N������
		CParticle::Create(m_pos, D3DXCOLOR(0.1f, 0.4f, 0.5f, 1.0f), TYPE_PLAYER, 30, 40);

		////�I������
		//Uninit();

	}
}

//==============================================================
//��Ԑݒ�
//==============================================================
void CPlayer::SetState(void)
{
	CInputKeyboard *pInputKeyboard = CManager::Get()->GetInputKeybard();
	CSound *pSound = CManager::Get()->GetSound();

	switch (m_state)
	{
	case STATE_NONE:		//�ʏ���

		break;

	case STATE_ATTACK:		//�U�����

		break;

	case STATE_DAMAGE:		//�_���[�W���

		m_nCntDamage--;

		if (m_nCntDamage <= 0)
		{
			m_state = STATE_NONE;

			//��Ԑݒ�
			for (int nCntEnemy = 0; nCntEnemy < 9; nCntEnemy++)
			{
				m_apModel[nCntEnemy]->SetState(m_state);		//�ʏ��Ԃɂ���
			}
		}
		break;

	case STATE_F_JUMP :		//1��ڂ̃W�����v���


	
			m_bLand = false;

			//��Ԑݒ�
			for (int nCntEnemy = 0; nCntEnemy < 9; nCntEnemy++)
			{
				m_apModel[nCntEnemy]->SetState(m_state);		//�ʏ��Ԃɂ���
			}
		break;

	case STATE_S_JUMP:		//2��ڂ̃W�����v���


		break;
	}
}

//==============================================================
//�����̕␳����
//==============================================================
void CPlayer::RotCorrection(void)
{

	//CCamera *pCamera = m_pCamera;		// �J�����̃|�C���^

	//if (m_pCamera == nullptr) {
	//	pCamera = CManager::Get()->GetCamera();
	//}

	//D3DXVECTOR3 CamRot = pCamera->GetRotation();	// �J�����̊p�x

	CInputKeyboard *pInputKey = CManager::Get()->GetInputKeybard();	// �L�[�{�[�h�̃|�C���^

	if (nullptr == pInputKey) {
		return;
	}

	//if (pInputKey->GetPress(DIK_W))
	//{
	//	if (pInputKey->GetPress(DIK_A))
	//	{
	//		m_fRotDest = -D3DX_PI * 0.25f;
	//	}
	//	else if (pInputKey->GetPress(DIK_D))
	//	{
	//		m_fRotDest = D3DX_PI * 0.25f;
	//	}
	//	else
	//	{
	//		m_fRotDest = D3DX_PI * 0.0f;
	//	}
	//}
	//else if (pInputKey->GetPress(DIK_S))
	//{
	//	if (pInputKey->GetPress(DIK_A))
	//	{
	//		m_fRotDest = -D3DX_PI * 0.75f;
	//	}
	//	else if (pInputKey->GetPress(DIK_D))
	//	{
	//		m_fRotDest = D3DX_PI * 0.75f;
	//	}
	//	else
	//	{
	//		m_fRotDest = D3DX_PI * 1.0f;
	//	}
	//}
	//else if (pInputKey->GetPress(DIK_A))
	//{
	//	m_fRotDest = -D3DX_PI * 0.5f;
	//}
	//else if (pInputKey->GetPress(DIK_D))
	//{
	//	m_fRotDest = D3DX_PI * 0.5f;
	//}
}

//=============================================================
//���f���̓ǂݍ���
//=============================================================
void CPlayer::SetModel(const char * c_FileName)
{
	FILE *pFile;				//�t�@�C���|�C���^
	char aString[126];		//�����ǂݍ���
	int nIndex = 0, nParent = 0;	//�p�[�cNo.,�e�ԍ�
	D3DXVECTOR3 pos, rot;

	//�t�@�C���J��
	pFile = fopen(c_FileName, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

		while (strcmp(&aString[0], "CHARACTERSET") != 0)
		{//[CHARACTERSET]����܂ł̊�

			fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���
		}

		if (strcmp(&aString[0], "CHARACTERSET") == 0)
		{//[CHARACTERSET]��������

			while (strcmp(&aString[0], "END_CHARACTERSET") != 0)
			{//[END_CHARACTERSET]������܂ł̊�

				fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���

				if (strcmp(&aString[0], "PARTSSET") == 0)
				{//[PARTSSET]��������

					while (strcmp(&aString[0], "END_PARTSSET") != 0)
					{//[END_PARTSSET]������܂ł̊�

						fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���

						if (strcmp(&aString[0], "INDEX") == 0)
						{//�p�[�cNo.

							fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���
							fscanf(pFile, "%d", &nIndex);			//�p�[�cNo.�ǂݍ���

						}
						else if (strcmp(&aString[0], "PARENT") == 0)
						{//�e���

							fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���
							fscanf(pFile, "%d", &nParent);			//�e�ԍ��ǂݍ���

							if (nParent == -1)
							{//�e�����Ȃ�������

								m_apModel[nIndex]->SetParent(NULL);		//NULL������
							}
							else
							{//�e��������

								m_apModel[nIndex]->SetParent(m_apModel[nParent]);		//�e�ԍ������
							}
						}
						else if (strcmp(&aString[0], "POS") == 0)
						{//�ʒu���

							fscanf(pFile, "%s", &aString[0]);	//�����ǂݍ���

							fscanf(pFile, "%f", &pos.x);		//�ʒu�ǂݍ���
							fscanf(pFile, "%f", &pos.y);		//�ʒu�ǂݍ���
							fscanf(pFile, "%f", &pos.z);		//�ʒu�ǂݍ���

							m_apModel[nIndex]->SetPosition(pos);		//�ʒu�ݒ�
							m_apModel[nIndex]->SetDefaultPosition(pos);	//�����ʒu�ݒ�

						}
						else if (strcmp(&aString[0], "ROT") == 0)
						{//�������

							fscanf(pFile, "%s", &aString[0]);	//�����ǂݍ���

							fscanf(pFile, "%f", &rot.x);		//�����ǂݍ���
							fscanf(pFile, "%f", &rot.y);		//�����ǂݍ���
							fscanf(pFile, "%f", &rot.z);		//�����ǂݍ���

							m_apModel[nIndex]->SetRotation(rot);		//�����ݒ�
							m_apModel[nIndex]->SetDefaultRotation(rot);	//���������ݒ�
						}
					}
				}
			}
		}

		//�t�@�C������
		fclose(pFile);
	}
}