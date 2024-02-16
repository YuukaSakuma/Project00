//==============================================================
//
//�G�w�b�_�[[enemy.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _ENEMY_H_						//���̃}�N������`����Ă��Ȃ�������
#define _ENEMY_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "objectX.h"

//�O���錾
class CModel;
class CModelHier;
class CMotion;

//==============================================================
//�G�N���X
//==============================================================
class CEnemy : public CObject
{
public:

	CEnemy();													//�R���X�g���N�^
	~CEnemy();													//�f�X�g���N�^

	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//�e�̐���

	virtual HRESULT Init(void);						//����������
	virtual void Uninit(void);						//�I������
	virtual void Update(void);						//�X�V����
	virtual void Draw(void);						//�`�揈��

	//�擾
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	D3DXVECTOR3 GetMove(void) const { return m_move; }
	D3DXVECTOR3 GetSizeMin(void) { return m_min; }			//�ŏ��T�C�Y�̎擾
	D3DXVECTOR3 GetSizeMax(void) { return m_max; }			//�ő�T�C�Y�̎擾
	int GetLife(void) { return m_nLife; }

	//�ݒ�
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }

	void SetModel(const char * c_FileName);
	void SetState(void);
	void Hit(void);

private:
#define ENEMY_MODEL		(8)			//�G1�̃��f����

	static LPD3DXMESH m_pMesh;			//���b�V���i���_���j�ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMat;		//�}�e���A���ւ̃|�C���^
	static DWORD m_dwNumMat;			//�}�e���A���̐�
	D3DXMATRIX m_mtxWorld;				//���[���h�}�g���b�N�X

	int m_nLife;			//����
	D3DXVECTOR3 m_move;		//�ړ���
	D3DXVECTOR3 m_rot;		//����	
							//TYPE m_type;			//���
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_posOld;	//�ʒu(�O��)
	D3DXVECTOR3 m_max;		//�ő�l
	D3DXVECTOR3 m_min;		//�ŏ��l
	int m_nldxTexture;		//�e�N�X�`���ԍ�
	int m_nCntAttack;		//�A�^�b�N�J�E���^�[
	int m_nCntDamage;		//�_���[�W�J�E���^�[
	int m_nCntMove;			//�ړ�����܂�

	STATE m_state;			//���

	int m_nIdxTexture;			//�e�N�X�`���̔ԍ�
	static int m_nNumAll;		//�G�̑���
	int m_nID;					//�G�̔ԍ�

	CModelHier *m_apModel[ENEMY_MODEL];		//���f��(�p�[�c)�ւ̃|�C���^
	static char *m_apFileName[ENEMY_MODEL];	//�t�@�C����
	CMotion *m_pMotion;		//���[�V�������
};
#endif // !_BULLET_H_
