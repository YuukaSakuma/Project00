//==============================================================
//
//�u���b�NX����[blockX.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _ITEMX_H_							//���̃}�N����`������Ă��Ȃ�������
#define _ITEMX_H_							//2�d�C���N���[�h�h�~�̃}�N�����`����v

#include"objectX.h"

//==============================================================
//�u���b�NX�N���X
//==============================================================
class CItemX : public CObjectX
{
public:

	CItemX();										//�R���X�g���N�^
	CItemX(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//�R���X�g���N�^(�I�[�o�[���[�h)
	~CItemX();										//�f�X�g���N�^

	static CItemX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//�u���b�NX�̐���

	HRESULT Init(void);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��
	void Hit(void);


	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }		//�ʒu�̐ݒ�
	D3DXVECTOR3 GetPosition(void) { return m_pos; }			//�ʒu�̎擾

private:

	static int m_nNumAll;			//���f���̎��

	static LPD3DXMESH m_pMesh;			//���b�V���i���_���j�ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMat;		//�}�e���A���ւ̃|�C���^
	static DWORD m_dwNumMat;			//�}�e���A���̐�

	D3DXVECTOR3 m_pos;			//�ʒu
	D3DXVECTOR3 m_rot;			//����
	int m_nMaxModel;			//���f���̐ݒu��
	int m_nIdx;					//���f���̔ԍ�

	int m_type;			//�A�C�e���̎��
};
#endif