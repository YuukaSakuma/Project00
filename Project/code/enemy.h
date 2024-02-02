//==============================================================
//
//�e�w�b�_�[[bullet.h]
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
//�e�N���X
//==============================================================
class CEnemy : public CObject
{
public:

	//�G�̎��
	typedef enum
	{
		ENEMY_WITCH = 0,		//��1
		ENEMY_SWORDMAN,			//��2
		ENEMY_BOSS,				//�{�X
		ENEMY_MAX
	}ENEMY;

	CEnemy();													//�R���X�g���N�^
	~CEnemy();													//�f�X�g���N�^

	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,ENEMY nType);	//�e�̐���

	virtual HRESULT Init(void);						//����������
	virtual void Uninit(void);						//�I������
	virtual void Update(void);						//�X�V����
	virtual void Draw(void);						//�`�揈��

	D3DXVECTOR3 GetPosition(void) const { return m_pos; }
	D3DXVECTOR3 GetRotation(void) const { return m_rot; }
	D3DXVECTOR3 GetMove(void) const { return m_move; }
	D3DXVECTOR3 GetSizeMin(void) { return m_min; }			//�ŏ��T�C�Y�̎擾
	D3DXVECTOR3 GetSizeMax(void) { return m_max; }			//�ő�T�C�Y�̎擾

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }

protected:
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

	STATE m_state;			//���


private:
	static LPD3DXMESH m_pMesh;			//���b�V���i���_���j�ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMat;		//�}�e���A���ւ̃|�C���^
	static DWORD m_dwNumMat;			//�}�e���A���̐�
	D3DXMATRIX m_mtxWorld;				//���[���h�}�g���b�N�X

	int m_nIdxTexture;			//�e�N�X�`���̔ԍ�
	static int m_nNumAll;		//�G�̑���
	int m_nID;					//�G�̔ԍ�

	//ENEMY m_type;			//�G�̎��

	
};


//class CEnemySwordsman :public CEnemy
//{
//public:
//
//	CEnemySwordsman();													//�R���X�g���N�^
//	~CEnemySwordsman();													//�f�X�g���N�^
//
//	HRESULT Init(void);						//����������
//	void Uninit(void);						//�I������
//	void Update(void);						//�X�V����
//	void Draw(void);						//�`�揈��
//
//private:
//
//
//};
class CEnemyWitch :public CEnemy
{
public:

	CEnemyWitch();													//�R���X�g���N�^
	~CEnemyWitch();													//�f�X�g���N�^

	HRESULT Init(void);						//����������
	void Uninit(void);						//�I������
	void Update(void);						//�X�V����
	void Draw(void);						//�`�揈��

	void SetModel(const char * c_FileName);
	void SetState(void);

private:
#define NUM_MODEL_BIRD1		(8)			//�G1�̃��f����

	CModelHier *m_apModel[NUM_MODEL_BIRD1];		//���f��(�p�[�c)�ւ̃|�C���^
	static char *m_apFileName[NUM_MODEL_BIRD1];	//�t�@�C����
	CMotion *m_pMotion;		//���[�V�������

};

//class CEnemyBoss : public CEnemy
//{
//public:
//	CEnemyBoss();
//	~CEnemyBoss();
//
//	HRESULT Init(void);						//����������
//	void Uninit(void);						//�I������
//	void Update(void);						//�X�V����
//	void Draw(void);						//�`�揈��
//
//private:
//
//};
#endif // !_BULLET_H_
