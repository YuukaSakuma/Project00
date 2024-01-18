//==============================================================
//
//�u���b�N���f������[blockX.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include"itemX.h"
#include"game.h"
#include "model.h"
#include "playerModel.h"
#include "material.h"
#include "sound.h"
#include "score.h"

//�ÓI�����o�ϐ��錾
LPD3DXMESH CItemX::m_pMesh = NULL;						//���b�V���i���_���j�ւ̃|�C���^
LPD3DXBUFFER CItemX::m_pBuffMat = NULL;					//�}�e���A���ւ̃|�C���^
DWORD CItemX::m_dwNumMat = NULL;

//==============================================================
//�R���X�g���N�^
//==============================================================
CItemX::CItemX()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
	m_nIdx = -1;				//���f���̔ԍ�
}

//==============================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//==============================================================
CItemX::CItemX(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;		//�ʒu
	m_rot = rot;		//����
	m_nIdx = -1;				//���f���̔ԍ�
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CItemX::~CItemX()
{

}

//==============================================================
//�u���b�N���f���̂̐�������
//==============================================================
CItemX *CItemX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CItemX *pItemX = NULL;

	if (pItemX == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pItemX = new CItemX(pos,rot);

		//����������
		pItemX->Init();

		pItemX->SetPosition(pos);

		pItemX->SetType(TYPE_ITEM);
	}

	return pItemX;
}

//==============================================================
//�u���b�N���f���̏���������
//==============================================================
HRESULT CItemX::Init(void)
{
	CMaterial *pMaterial = CManager::Get()->GetMaterial();

	//���f���̓ǂݍ���
	m_nIdx = pMaterial->Regit("data\\MODEL\\coin.x");

	//�}�e���A���̊��蓖��
	CObjectX::BindMaterial(m_nIdx);

	//�I�u�W�F�N�gX�̏���������
	CObjectX::Init();

	//��ނ̐ݒ�
	CObject::SetType(CObject::TYPE_ITEM);

	return S_OK;
}

//==============================================================
//�u���b�N���f���̏I������
//==============================================================
void CItemX::Uninit(void)
{
	//�I�u�W�F�N�gX�̏I������
	CObjectX::Uninit();
}

//==============================================================
//�u���b�N���f���̍X�V����
//==============================================================
void CItemX::Update(void)
{
	//�I�u�W�F�N�gX�̍X�V����
	CObjectX::Update();
}

//==============================================================
//�u���b�N���f���̕`�揈��
//==============================================================
void CItemX::Draw(void)
{
	//�I�u�W�F�N�gX�̕`�揈��
	CObjectX::Draw();
}

//==============================================================
//�A�C�e���̃q�b�g����
//==============================================================
void CItemX::Hit(void)
{
	CPlayerModel *pPlayer = CGame::GetPlayerModel();
	CScore *pScore = CGame::GetScore();
	CSound *pSound = CManager::Get()->GetSound();

	pSound->Play(pSound->SOUND_LABEL_SE_COIN);

	//�X�R�A���Z
	pScore->Add(700);

	//�I������
	CItemX::Uninit();
}