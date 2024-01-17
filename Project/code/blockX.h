//==============================================================
//
//�u���b�NX����[blockX.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _BLOCKX_H_							//���̃}�N����`������Ă��Ȃ�������
#define _BLOCKX_H_							//2�d�C���N���[�h�h�~�̃}�N�����`����v

#include"object.h"

//�O���錾
class CModel;

//==============================================================
//�u���b�NX�N���X
//==============================================================
class CBlockX : public CObject
{
public:

	CBlockX();										//�R���X�g���N�^
	CBlockX(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//�R���X�g���N�^(�I�[�o�[���[�h)
	~CBlockX();										//�f�X�g���N�^

	static CBlockX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//�u���b�NX�̐���

	HRESULT Init(void);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }		//�ʒu�̐ݒ�
	D3DXVECTOR3 GetPosition(void) { return m_pos; }			//�ʒu�̎擾

private:

	LPDIRECT3DTEXTURE9 *m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	LPD3DXMESH m_pMesh;					//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;			//�}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat;					//�}�e���A���̐�

	D3DXVECTOR3 m_pos;					//�ʒu
	D3DXVECTOR3 m_posOld;
	D3DXVECTOR3 m_rot;					//�ړ���
	D3DXVECTOR3 m_max;					//�ő�l
	D3DXVECTOR3 m_min;					//�ŏ��l
	D3DXVECTOR3 m_move;					//�ŏ��l

	D3DXMATRIX m_mtxWorld;				//���[���h�}�g���b�N�X

	CModel *m_apModel[256];				//���f���̃|�C���^

	 int m_nNumModel;					//���f����

	//int nldxShadow;
};
#endif