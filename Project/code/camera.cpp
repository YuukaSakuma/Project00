//==============================================================
//
//�J��������[camera.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include "camera.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"
#include"player.h"
#include"game.h"

//�}�N����`
#define LENGTH	(800.0f)			//����
#define POSVX	(0.0f)				//���_X
#define POSVY	(100.0f)				//���_Y
#define POSVZ	(-100.0f)			//���_Z
#define POSRX	(0.0f)			//�����_X
#define POSRY	(100.0f)			//�����_X
#define POSRZ	(0.0f)				//�����_X
#define VECUX	(0.0f)				//������x�N�g��X
#define VECUY	(1.0f)				//������x�N�g��Y
#define VECUZ	(0.0f)				//������x�N�g��Z
#define ROTX	(0.0f)				//����X
#define ROTY	(1.0f)				//����Y
#define ROTZ	(0.0f)				//����Z
#define MOVE	(1.0f)				//�ړ���
#define MOVE1	(0.05f)				//�ړ���
#define CURVE	(0.0f)				//�p�x
#define CURVE1	(1.0f)				//�p�x
#define CURVE2	(0.25f)				//�p�x
#define CURVE3	(0.5f)				//�p�x
#define CURVE4	(0.75f)				//�p�x

//==============================================================
//�R���X�g���N�^
//==============================================================
CCamera::CCamera()
{
	/*m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);*/
}

//==============================================================
//�R���X�g���N�^
//==============================================================
CCamera::~CCamera()
{

}

//==============================================================
//�J�����̏���������
//==============================================================
HRESULT CCamera::Init(void)
{
	m_posV = D3DXVECTOR3(0.0f, 100.0f, 2200.0f);		//���_�̏�����
	m_posR = D3DXVECTOR3(0.0f, 200.0f, 0.0f);		//�����_�̏�����
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//������x�N�g���̏�����
	m_rot = D3DXVECTOR3(0.0f, atan2f(m_posR.x - m_posV.x, m_posR.z - m_posV.z), 1.56f);			//�����̏�����

	SetV();

	return S_OK;

}

//==============================================================
//�J�����̏I������
//==============================================================
void CCamera::Uninit(void)
{
	
}

//==============================================================
//�J�����̍X�V����
//==============================================================
void CCamera::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::Get()->GetInputKeybard();	//�L�[�{�[�h�̎擾
	CDebugProc *pDebugProc = CManager::Get()->GetDebugProc();
	CPlayer *pPlayer = CGame::GetPlayerModel();			//�v���C���[�̏��擾


	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		//�Ǐ]
		Move();	
	}

	//�S���_�̈ړ�
	//MoveA();

	//���_�̈ړ�
	MoveV();

	//�����_�̈ړ�
	MoveR();

	pDebugProc->Print("�J�����̎��_�ʒu : [%f %f %f] \n", m_posR.x, m_posR.y, m_posR.z);

	pDebugProc->Print("�J�����̒����_�ʒu : [%f %f %f] \n", m_posV.x, m_posV.y, m_posV.z);
}

//==============================================================
//�J�����̑S�ړ�
//==============================================================
void CCamera::MoveA(void)
{
	CInputKeyboard *pInputKeyboard = CManager::Get()->GetInputKeybard();	//�L�[�{�[�h�̎擾

																			//�L�[�������ꂽ�Ƃ�
	if (pInputKeyboard->GetPress(DIK_J) == true)
	{//A�L�[�������ꂽ
		if (pInputKeyboard->GetPress(DIK_I) == true)
		{//����ړ�
			m_posV.x += cosf(m_rot.y + (-D3DX_PI * 0.75f)) * MOVE;
			m_posV.z += sinf(m_rot.y + (-D3DX_PI * 0.75f)) * MOVE;
		}
		else if (pInputKeyboard->GetPress(DIK_K) == true)
		{//�����ړ�
			m_posV.x += cosf(m_rot.y + (-D3DX_PI * 0.25f)) * MOVE;
			m_posV.z += sinf(m_rot.y + (-D3DX_PI * 0.25f)) * MOVE;		
		}
		else
		{//���ړ�	
			m_posV.x += cosf(m_rot.y + (-D3DX_PI * 0.5f)) * MOVE;
			m_posV.z += sinf(m_rot.y + (-D3DX_PI * 0.5f)) * MOVE;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_L) == true)
	{//D�L�[�������ꂽ

		if (pInputKeyboard->GetPress(DIK_I) == true)
		{//�E��ړ�
			m_posV.x += cosf(m_rot.y + (D3DX_PI * 0.75f)) * MOVE;
			m_posV.z += sinf(m_rot.y + (D3DX_PI * 0.75f)) * MOVE;	
		}
		else if (pInputKeyboard->GetPress(DIK_K) == true)
		{//�E���ړ�
			m_posV.x += cosf(m_rot.y + (D3DX_PI * 0.25f)) * MOVE;
			m_posV.z += sinf(m_rot.y + (D3DX_PI * 0.25f)) * MOVE;
		}
		else
		{//�E�ړ�
			m_posV.x += cosf(m_rot.y + (D3DX_PI * 0.5f)) * MOVE;
			m_posV.z += sinf(m_rot.y + (D3DX_PI * 0.5f)) * MOVE;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_I) == true)
	{//W�L�[�������ꂽ
		m_posV.x += -cosf(m_rot.y) * MOVE;
		m_posV.z += -sinf(m_rot.y) * MOVE;
	}
	else if (pInputKeyboard->GetPress(DIK_K) == true)
	{//S�L�[�������ꂽ
		m_posV.x += cosf(m_rot.y) * MOVE;
		m_posV.z += sinf(m_rot.y) * MOVE;
	}

	SetR();
}

//==============================================================
//�J�����̒����_�ړ�
//==============================================================
void CCamera::MoveV(void)
{
	CInputKeyboard *pInputKeyboard = CManager::Get()->GetInputKeybard();	//�L�[�{�[�h�̎擾

	if (pInputKeyboard->GetPress(DIK_Z) == true && pInputKeyboard->GetPress(DIK_C) != true)
	{//Z�L�[����
		m_rot.y += -D3DX_PI * 0.0154f;
		if (m_rot.y < -D3DX_PI)
		{//�p�x�����𒴂����ꍇ
			m_rot.y += D3DX_PI * 2;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_C) == true && pInputKeyboard->GetPress(DIK_Z) != true)
	{//C�L�[����
		m_rot.y += D3DX_PI * 0.0154f;
	}

	if (pInputKeyboard->GetPress(DIK_Y) == true && pInputKeyboard->GetPress(DIK_N) != true)
	{//Y�L�[����
	 //�p�x�̕ύX
		m_rot.z += -D3DX_PI * 0.0154f;
		if (m_rot.z < MIN_CAMERA_ROTZ)
		{//�p�x�����E�𒴂����ꍇ
			m_rot.z = MIN_CAMERA_ROTZ;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_N) == true && pInputKeyboard->GetPress(DIK_Y) != true)
	{//N�L�[����
	 //�p�x�̕ύX
		m_rot.z += D3DX_PI * 0.0154f;

		if (m_rot.z > MAX_CAMERA_ROTZ)
		{//�p�x�����E�𒴂����ꍇ
			m_rot.z = MAX_CAMERA_ROTZ;
		}
	}

	SetV();
}

//==============================================================
//�J�����̎��_�ړ�
//==============================================================
void CCamera::MoveR(void)
{
	CInputKeyboard *pInputKeyboard = CManager::Get()->GetInputKeybard();	//�L�[�{�[�h�̎擾

	if (pInputKeyboard->GetPress(DIK_Q) == true && pInputKeyboard->GetPress(DIK_E) != true)
	{//Q�L�[����
	 //�p�x�̕ύX
		m_rot.y += D3DX_PI * 0.0154f;
		if (m_rot.y > D3DX_PI)
		{//�p�x�����𒴂����ꍇ
			m_rot.y += -D3DX_PI * 2;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_E) == true && pInputKeyboard->GetPress(DIK_Q) != true)
	{//E�L�[����
	 //�p�x�̕ύX
		m_rot.y += -D3DX_PI * 0.0154f;

		if (m_rot.y < -D3DX_PI)
		{//�p�x�����𒴂����ꍇ
			m_rot.y += D3DX_PI * 2;
		}
	}

	if (pInputKeyboard->GetPress(DIK_T) == true && pInputKeyboard->GetPress(DIK_B) != true)
	{//T�L�[����
	 //�p�x�̕ύX
		m_rot.z += D3DX_PI * 0.0154f;

		if (m_rot.z > MAX_CAMERA_ROTZ)
		{//�p�x�����E�𒴂����ꍇ
			m_rot.z = MAX_CAMERA_ROTZ;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_B) == true && pInputKeyboard->GetPress(DIK_T) != true)
	{//B�L�[����
	 //�p�x�̕ύX
		m_rot.z += -D3DX_PI * 0.0154f;
		if (m_rot.z < MIN_CAMERA_ROTZ)
		{//�p�x�����E�𒴂����ꍇ
			m_rot.z = MIN_CAMERA_ROTZ;
		}
	}

	SetR();
}

//==============================================================
//�J�����̐ݒ菈��
//==============================================================
void CCamera::Set(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer *pRenderer = CManager::Get()->GetRenderer();

	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		40000.0f);

	//D3DXMatrixOrthoLH(&m_mtxProjection,
	//	SCREEN_WIDTH ,
	//	SCREEN_HEIGHT,
	//	100.0f,
	//	10000.0f);

	//�v���W�F�N�g�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

}

//==============================================================
//�J�����̒Ǐ]
//==============================================================
void CCamera::Move(void)
{

	CPlayer *pPlayer = CGame::GetPlayerModel();			//�v���C���[�̏��擾

	D3DXVECTOR3 posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ڕW�̒����_
	D3DXVECTOR3 posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ڕW�̎��_
	D3DXVECTOR3 RDiff = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �����_�̍���
	D3DXVECTOR3 VDiff = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ���_�̍���

	//�ړI�̒����_��ݒ�
	//posRDest = D3DXVECTOR3(pos.x - sinf(rot.y) * 30.0f, pos.y + 50.0f + 40.0f , pos.z - cosf(rot.y) * 30.0f);

	m_posRDest.x = pPlayer->GetPosition().x  - sinf(pPlayer->GetRotation().y) * 30.0f;
	m_posRDest.y = pPlayer->GetPosition().y + 200.0f;
	m_posRDest.z = pPlayer->GetPosition().z + cosf(pPlayer->GetRotation().y) * 30.0f;

	//�ړI�̎��_��ݒ�
	//posVDest = D3DXVECTOR3(
	//	m_posRDest.x + (sinf(m_rot.z) * cosf(m_rot.y)) * LENGTH,
	//	m_posRDest.y + cosf(m_rot.z) * LENGTH,
	//	m_posRDest.z + (sinf(m_rot.z) * sinf(m_rot.y)) * LENGTH);

	m_posVDest.x = m_posRDest.x + (sinf(GetRotation().z) * cosf(GetRotation().y)) * LENGTH;
	m_posVDest.y = m_posRDest.y + cosf(GetRotation().z)* LENGTH;
	m_posVDest.z = m_posRDest.z + (sinf(GetRotation().z) * sinf(GetRotation().y)) * LENGTH;


	RDiff = D3DXVECTOR3(m_posRDest.x - m_posR.x, m_posRDest.y - m_posR.y, m_posRDest.z - m_posR.z);
	m_posR.x += RDiff.x * 0.2f;
	m_posR.y += RDiff.y * 0.1f;
	m_posR.z += RDiff.z * 0.2f;

	VDiff = D3DXVECTOR3(m_posVDest.x - m_posV.x, m_posVDest.y - m_posV.y, m_posVDest.z - m_posV.z);
	m_posV.x += VDiff.x * 0.2f;
	m_posV.y += VDiff.y * 0.1f;
	m_posV.z += VDiff.z * 0.2f;



	//RDiff = D3DXVECTOR3(posRDest.x - m_posR.x, posRDest.y - m_posR.y, posRDest.z - m_posR.z);
	//m_posR.x += RDiff.x * 0.2f;
	//m_posR.y += RDiff.y * 0.1f;
	//m_posR.z += RDiff.z * 0.2f;

	//VDiff = D3DXVECTOR3(posVDest.x - m_posV.x, posVDest.y - m_posV.y, posVDest.z - m_posV.z);
	//m_posV.x += VDiff.x * 0.2f;
	//m_posV.y += VDiff.y * 0.1f;
	//m_posV.z += VDiff.z * 0.2f;

	//RDiff = m_posRDest - m_posR;
	//VDiff = m_posVDest - m_posV;

	//m_posR += RDiff * 0.4f;
	//m_posV += RDiff * 0.4f;
	 
}

//==============================================================
//���e�ꏊ�ݒ�
//==============================================================
void CCamera::Setting(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	m_rot.y = -rot.y + (D3DX_PI * 0.5f);

	//�ړI�̒����_�̍��W���擾
	m_posR = D3DXVECTOR3(pos.x - sinf(rot.y) * 30.0f, pos.y + 50.0f, pos.z - cosf(rot.y) * 30.0f);

	//�ړI�̎��_�̍��W���l��
	m_posV = D3DXVECTOR3(
		m_posR.x + (sinf(m_rot.z) * cosf(m_rot.y)) * m_fLength,
		m_posR.y + cosf(m_rot.z) * m_fLength,
		m_posR.z + (sinf(m_rot.z) * sinf(m_rot.y)) * m_fLength);
}

//==============================================================
//�J�����̎��_�ݒ菈��
//==============================================================
void CCamera::SetV(void)
{
	m_posV.x = m_posR.x + (sinf(m_rot.z) * cosf(m_rot.y))* LENGTH;
	m_posV.y = m_posR.y + cosf(m_rot.z) * LENGTH;
	m_posV.z = m_posR.z + (sinf(m_rot.z) * sinf(m_rot.y))* LENGTH;
}

//==============================================================
//�J�����̒����_�ݒ菈��
//==============================================================
void CCamera::SetR(void)
{
	m_posR.x = m_posV.x - (sinf(m_rot.z) * cosf(m_rot.y))* LENGTH;
	m_posR.y = m_posV.y - cosf(m_rot.z) * LENGTH;
	m_posR.z = m_posV.z - (sinf(m_rot.z) * sinf(m_rot.y))* LENGTH;
}

//==========================================================
// R���W�ݒ�
//==========================================================
void CCamera::SetPositionV(D3DXVECTOR3 pos)
{
	m_posV = pos;
	SetV();
}

//==========================================================
// R���W�ݒ�
//==========================================================
void CCamera::SetPositionR(D3DXVECTOR3 pos)
{
	m_posR = pos;
	SetR();
}