//==============================================================
//
//�e�w�b�_�[[bullet.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _BULLET_H_						//���̃}�N������`����Ă��Ȃ�������
#define _BULLET_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "objectX.h"
//==============================================================
//�e�N���X
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

	D3DXVECTOR3 GetPosition(void) const { return m_pos; }
	D3DXVECTOR3 GetRotation(void) const { return m_rot; }
	D3DXVECTOR3 GetMove(void) const { return m_move; }

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
private:

	int m_nLife;			//����
	D3DXVECTOR3 m_move;		//�ړ���
	D3DXVECTOR3 m_rot;		//����	
	TYPE m_type;			//���
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_posOld;	//�ʒu(�O��)
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
//
//class CEnemyWitch :public CEnemy
//{
//public:
//
//	CEnemyWitch();													//�R���X�g���N�^
//	~CEnemyWitch();													//�f�X�g���N�^
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
