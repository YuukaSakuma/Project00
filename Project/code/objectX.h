//==============================================================
//
//�I�u�W�F�N�gX����[objectX.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _OBJECTX_H_							//���̃}�N����`������Ă��Ȃ�������
#define _OBJECTX_H_							//2�d�C���N���[�h�h�~�̃}�N�����`����v

#include"object.h"

//==============================================================
//�I�u�W�F�N�gX�N���X
//==============================================================
class CObjectX : public CObject
{
public:

	CObjectX();		//�R���X�g���N�^
	~CObjectX();	//�f�X�g���N�^

	static CObjectX *Create(void);			//�I�u�W�F�N�gX�̐���
	static HRESULT Load(void);				//�e�N�X�`���̓ǂݍ���
	static void Unload(void);				//�e�N�X�`���̔j��


	virtual HRESULT Init(void);		//����������
	virtual void Uninit(void);		//�I������
	virtual void Update(void);		//�X�V����
	virtual void Draw(void);		//�`�揈��

	void BindMaterial(int nIdx);		//�O������}�e���A���w��
	void BindXFile(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD dwNumMat);		//�t�@�C���̐ݒ�

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }		//�ʒu�̐ݒ�
	D3DXVECTOR3 GetPosition(void) { return m_pos; }			//�ʒu�̎擾

	void SetRotation(TYPE type, D3DXVECTOR3 rot) { m_rot = rot; }			//�����ݒ�
	D3DXVECTOR3 GetRotation(void) { return m_rot; }							//�����̎擾

	void SetSize(D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax) { m_vtxMin = vtxMin;  m_vtxMax = vtxMax; }		//���f���̑傫���ݒ�
	D3DXVECTOR3 GetSizeMin(void) { return m_vtxMin; }		//�ŏ��̑傫���擾
	D3DXVECTOR3 GetSizeMax(void) { return m_vtxMax; }		//�ő�̑傫���擾

	void SetState(STATE state) { m_state = state; }		//�G�̏�Ԑݒ�
	STATE GetState(void) { return m_state; }			//�G�̏�Ԏ擾

	void SetObject(void);
	static bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 Min, D3DXVECTOR3 Max);
	static bool CollisionHit(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 Min, D3DXVECTOR3 Max);

private:

	LPD3DXMESH m_pMesh;					//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;			//�}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat;					//�}�e���A���̐�

	D3DXMATRIX m_mtxWorld;				//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_vtxMin;				//�ŏ�
	D3DXVECTOR3 m_vtxMax;				//�ő�

	D3DXVECTOR3 m_pos;					//�ʒu
	D3DXVECTOR3 m_rot;					//�ړ���
	D3DXVECTOR3 m_move;					//�ړ���
	TYPE m_type;						//�^�C�v�̐ݒ�
	STATE m_state;						//���

	int m_nIdxParent;				//�e���f���̃C���f�b�N�X
	D3DXMATERIAL m_matColor;		//�}�e���A���f�[�^�ւ̃|�C���^

	int m_nIdxModel;		//���f���̔ԍ�
};
#endif