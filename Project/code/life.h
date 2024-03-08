//==============================================================
//
//�e�w�b�_�[[bullet.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _LIFE_H_						//���̃}�N������`����Ă��Ȃ�������
#define _LIFE_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"object2D.h"
#include"billboard.h"

//==============================================================
//�e�N���X
//==============================================================
class CLife : public CBillboard
{
public:

	CLife();													//�R���X�g���N�^
	~CLife();													//�f�X�g���N�^

	static CLife *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, TYPE type);	//�e�̐���

	virtual HRESULT Init(void);						//����������
	virtual void Uninit(void);						//�I������
	virtual void Update(void);						//�X�V����
	virtual void Draw(void);						//�`�揈��

	D3DXVECTOR3 GetPosition(void) const { return m_pos; }
	D3DXVECTOR3 GetRotation(void) const { return m_rot; }
	D3DXVECTOR3 GetMove(void) const { return m_move; }

	TYPE GetType(void) { return m_type; }

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetType(TYPE type) {m_type = type;}
private:

	int m_nLife;			//����
	D3DXVECTOR3 m_move;		//�ړ���
	D3DXVECTOR3 m_rot;		//����	
	TYPE m_type;			//���
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_posOld;	//�ʒu(�O��)

	//BulletType m_BType;		//�e�̎��
};
#endif // !_BULLET_H_
