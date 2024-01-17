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
#include"playermodel.h"
#include"game.h"

//�}�N����`
#define LENGTH	(2500.0f)			//����
#define POSVX	(0.0f)				//���_X
#define POSVY	(0.0f)				//���_Y
#define POSVZ	(0.0f)			//���_Z
#define POSRX	(0.0f)			//�����_X
#define POSRY	(0.0f)			//�����_X
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
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	m_posV = D3DXVECTOR3(POSVX, POSVY, POSVZ);		//���_�̏�����
	m_posR = D3DXVECTOR3(POSRX, POSRY, POSRZ);		//�����_�̏�����
	m_vecU = D3DXVECTOR3(VECUX, VECUY, VECUZ);		//������x�N�g���̏�����
	m_rot = D3DXVECTOR3(1.5f, D3DX_PI * -0.5f, atan2f(m_posR.x - m_posV.x, m_posR.z - m_posV.z));			//�����̏�����

	m_posV.x = m_posR.x + (sinf(m_rot.x) * cosf(m_rot.y))* LENGTH;
	m_posV.y = m_posR.y + cosf(m_rot.x) * LENGTH;
	m_posV.z = m_posR.z + (sinf(m_rot.x) * sinf(m_rot.y))* LENGTH;

	m_posR.x = m_posV.x - (sinf(m_rot.x) * cosf(m_rot.y))* LENGTH;
	m_posR.y = m_posV.y - cosf(m_rot.x) * LENGTH;
	m_posR.z = m_posV.z - (sinf(m_rot.x) * sinf(m_rot.y))* LENGTH;

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
	CPlayerModel *pPlayer = CGame::GetPlayerModel();			//�v���C���[�̏��擾


	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		if (pPlayer->GetPosition().x <= 69000.0f)
		{
			//�Ǐ]
			Move();
		}
		/*else if (pPlayer->GetPosition().x > 70000.0f)
		{
			m_posV.y = pPlayer->GetPosition().y + 200.0f + sinf(pPlayer->GetRotation().y + D3DX_PI) * 0.0f;
			m_posV.x = 70000.0f + sinf(pPlayer->GetRotation().y + D3DX_PI);

			m_posR.y = pPlayer->GetPosition().y + 200.0f + sinf(pPlayer->GetRotation().y + D3DX_PI) * 0.0f;
			m_posR.x = 70000.0f + sinf(pPlayer->GetRotation().y + D3DX_PI);
		}*/

		
	}

	////�L�[�������ꂽ�Ƃ�
	//if (pInputKeyboard->GetPress(DIK_J) == true)
	//{//A�L�[�������ꂽ
	//	if (pInputKeyboard->GetPress(DIK_I) == true)
	//	{//����ړ�
	//		m_posV.x += cosf(m_rot.y + -D3DX_PI * CURVE4) * MOVE;
	//		m_posV.z += sinf(m_rot.y + -D3DX_PI * CURVE4) * MOVE;
	//		m_posR.x += cosf(m_rot.y + -D3DX_PI * CURVE4) * MOVE;
	//		m_posR.z += sinf(m_rot.y + -D3DX_PI * CURVE4) * MOVE;
	//	}
	//	else if (pInputKeyboard->GetPress(DIK_K) == true)
	//	{//�����ړ�
	//		m_posV.x += cosf(m_rot.y + -D3DX_PI * CURVE2) * MOVE;
	//		m_posV.z += sinf(m_rot.y + -D3DX_PI * CURVE2) * MOVE;
	//		m_posR.x += cosf(m_rot.y + -D3DX_PI * CURVE2) * MOVE;
	//		m_posR.z += sinf(m_rot.y + -D3DX_PI * CURVE2) * MOVE;
	//	}
	//	else
	//	{//���ړ�			
	//		m_posV.x += cosf(m_rot.y + -D3DX_PI * CURVE3) * MOVE;
	//		m_posV.z += sinf(m_rot.y + -D3DX_PI * CURVE3) * MOVE;
	//		m_posR.x += cosf(m_rot.y + -D3DX_PI * CURVE3) * MOVE;
	//		m_posR.z += sinf(m_rot.y + -D3DX_PI * CURVE3) * MOVE;
	//	}
	//}
	//else if (pInputKeyboard->GetPress(DIK_L) == true)
	//{//D�L�[�������ꂽ

	//	if (pInputKeyboard->GetPress(DIK_I) == true)
	//	{//�E��ړ�
	//		m_posV.x += cosf(m_rot.y + D3DX_PI * CURVE4) * MOVE;
	//		m_posV.z += sinf(m_rot.y + D3DX_PI * CURVE4) * MOVE;
	//		m_posR.x += cosf(m_rot.y + D3DX_PI * CURVE4) * MOVE;
	//		m_posR.z += sinf(m_rot.y + D3DX_PI * CURVE4) * MOVE;
	//	}
	//	else if (pInputKeyboard->GetPress(DIK_K) == true)
	//	{//�E���ړ�
	//		m_posV.x += cosf(m_rot.y + D3DX_PI * CURVE2) * MOVE;
	//		m_posV.z += sinf(m_rot.y + D3DX_PI * CURVE2) * MOVE;
	//		m_posR.x += cosf(m_rot.y + D3DX_PI * CURVE2) * MOVE;
	//		m_posR.z += sinf(m_rot.y + D3DX_PI * CURVE2) * MOVE;
	//	}
	//	else
	//	{//�E�ړ�
	//		m_posV.x += cosf(m_rot.y + D3DX_PI * CURVE3) * MOVE;
	//		m_posV.z += sinf(m_rot.y + D3DX_PI * CURVE3) * MOVE;
	//		m_posR.x += cosf(m_rot.y + D3DX_PI * CURVE3) * MOVE;
	//		m_posR.z += sinf(m_rot.y + D3DX_PI * CURVE3) * MOVE;
	//	}
	//}
	//else if (pInputKeyboard->GetPress(DIK_I) == true)
	//{//W�L�[�������ꂽ
	//	m_posV.x += cosf(m_rot.y + -D3DX_PI * CURVE1) * MOVE;
	//	m_posV.z += sinf(m_rot.y + -D3DX_PI * CURVE1) * MOVE;
	//	m_posR.x += cosf(m_rot.y + -D3DX_PI * CURVE1) * MOVE;
	//	m_posR.z += sinf(m_rot.y + -D3DX_PI * CURVE1) * MOVE;

	//}
	//else if (pInputKeyboard->GetPress(DIK_K) == true)
	//{//S�L�[�������ꂽ
	//	m_posV.x += cosf(m_rot.y + D3DX_PI * CURVE) * MOVE;
	//	m_posV.z += sinf(m_rot.y + D3DX_PI * CURVE) * MOVE;
	//	m_posR.x += cosf(m_rot.y + D3DX_PI * CURVE) * MOVE;
	//	m_posR.z += sinf(m_rot.y + D3DX_PI * CURVE) * MOVE;
	//}

	////���_
	//if (pInputKeyboard->GetPress(DIK_Z) == true)
	//{//Z�L�[�������ꂽ
	//	m_rot.y += MOVE1;
	//}
	//else if (pInputKeyboard->GetPress(DIK_C) == true)
	//{//C�L�[�������ꂽ
	//	m_rot.y -= MOVE1;
	//}
	//else if (pInputKeyboard->GetPress(DIK_Y) == true)
	//{//Y�L�[�������ꂽ
	//	m_rot.x -= MOVE1;
	//}
	//else if (pInputKeyboard->GetPress(DIK_N) == true)
	//{//N�L�[�������ꂽ
	//	m_rot.x += MOVE1;
	//}

	////�����_
	//if (pInputKeyboard->GetPress(DIK_Q) == true)
	//{//Q�L�[�������ꂽ
	//	m_rot.y += MOVE1;
	//}
	//else if (pInputKeyboard->GetPress(DIK_E) == true)
	//{//E�L�[�������ꂽ
	//	m_rot.y -= MOVE1;
	//}
	//else if (pInputKeyboard->GetPress(DIK_T) == true)
	//{//T�L�[�������ꂽ
	//	m_rot.x += MOVE1;
	//}
	//else if (pInputKeyboard->GetPress(DIK_B) == true)
	//{//B�L�[�������ꂽ
	//	m_rot.x -= MOVE1;
	//}

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;

	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}

	if (m_rot.x > D3DX_PI)
	{
		m_rot.x = -D3DX_PI;
	}
	else if (m_rot.x < -D3DX_PI)
	{
		m_rot.x = D3DX_PI;
	}

	//�J�����̏㉺��]�̏��
	if (m_rot.x > D3DX_PI * 0.95f)
	{//��
		m_rot.x = D3DX_PI * 0.95f;
	}
	else if (m_rot.x < D3DX_PI * 0.05f)
	{//��
		m_rot.x = D3DX_PI * 0.05f;
	}

	//���_
	if (pInputKeyboard->GetPress(DIK_Z) == true
		|| pInputKeyboard->GetPress(DIK_C) == true
		|| pInputKeyboard->GetPress(DIK_Y) == true
		|| pInputKeyboard->GetPress(DIK_N) == true)
	{
		m_posV.x = m_posR.x + (sinf(m_rot.x) * cosf(m_rot.y))* LENGTH;
		m_posV.y = m_posR.y + cosf(m_rot.x) * LENGTH;
		m_posV.z = m_posR.z + (sinf(m_rot.x) * sinf(m_rot.y))* LENGTH;
	}

	//�����_
	if (pInputKeyboard->GetPress(DIK_Q) == true
		|| pInputKeyboard->GetPress(DIK_E) == true
		|| pInputKeyboard->GetPress(DIK_T) == true
		|| pInputKeyboard->GetPress(DIK_B) == true)
	{
		m_posR.x = m_posV.x - (sinf(m_rot.x) * cosf(m_rot.y))* LENGTH;
		m_posR.y = m_posV.y - cosf(m_rot.x) * LENGTH;
		m_posR.z = m_posV.z - (sinf(m_rot.x) * sinf(m_rot.y))* LENGTH;
	}

	pDebugProc->Print("�J�����̎��_�ʒu : [%f %f %f] \n", m_posR.x, m_posR.y, m_posR.z);

	pDebugProc->Print("�J�����̒����_�ʒu : [%f %f %f] \n", m_posV.x, m_posV.y, m_posV.z);
}

//==============================================================
//�J�����̕`�揈��
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
		500.0f,
		10000.0f);

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
//�J�����̕`�揈��
//==============================================================
void CCamera::Move(void)
{
	CPlayerModel *pPlayer = CGame::GetPlayerModel();			//�v���C���[�̏��擾

	D3DXVECTOR3 VDiff;
	D3DXVECTOR3 RDiff;
	//�ړI�̒����_��ݒ�

	m_posRDest.x = (pPlayer->GetPosition().x + 1000.0f) + sinf(pPlayer->GetRotation().y + D3DX_PI) * 0.0f;
	m_posRDest.y = (pPlayer->GetPosition().y + 200.0f) + sinf(pPlayer->GetRotation().y + D3DX_PI) * 0.0f;
	m_posRDest.z = pPlayer->GetPosition().z + cosf(pPlayer->GetRotation().y + D3DX_PI) * 0.0f;

	//�ړI�̎��_��ݒ�
	m_posVDest.x = pPlayer->GetPosition().x + sinf(GetRotation().y + D3DX_PI) * LENGTH;
	m_posVDest.y = pPlayer->GetPosition().y + sinf(GetRotation().y + D3DX_PI) * LENGTH;
	m_posVDest.z = pPlayer->GetPosition().z + cosf(GetRotation().y + D3DX_PI) * LENGTH;

	RDiff = m_posRDest - m_posR;
	VDiff = m_posVDest - m_posV;

	m_posR += RDiff * 0.4f;
	m_posV += RDiff * 0.4f;
	 
}