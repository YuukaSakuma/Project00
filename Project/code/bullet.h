//==============================================================
//
//�e�w�b�_�[[bullet.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _BULLET_H_						//���̃}�N������`����Ă��Ȃ�������
#define _BULLET_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"object2D.h"
#include"billboard.h"

//==============================================================
//�e�N���X
//==============================================================
class CBullet : public CBillboard
{
public:

	typedef enum
	{
		TYPE_A = 0,
		TYPE_B,
		TYPE_C,
		TYPE_MAX
	}BulletType;

	CBullet();													//�R���X�g���N�^
	~CBullet();													//�f�X�g���N�^

	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move,BulletType btype, TYPE type);	//�e�̐���

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

	bool Collision(D3DXVECTOR3 pos);								//�G�Ƃ̓����蔻��
	bool ColisionLeft(D3DXVECTOR3 pos, D3DXVECTOR3 posBlock);		//�u���b�N�̓����蔻��(���S�F[����])
	bool ColisionCenter(D3DXVECTOR3 pos, D3DXVECTOR3 posBlock);		//�u���b�N�̓����蔻��(���S�F[����])
	bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld);	//���f���Ƃ̓����蔻��
	bool CollisionData(D3DXVECTOR3 pos);							//���f���Ƃ̓����蔻��

private:

	int m_nLife;			//����
	D3DXVECTOR3 m_move;		//�ړ���
	D3DXVECTOR3 m_rot;		//����	
	TYPE m_type;			//���
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_posOld;	//�ʒu(�O��)

	BulletType m_BType;		//�e�̎��
};

class CBulletA :public CBullet
{
public:

	CBulletA();													//�R���X�g���N�^
	~CBulletA();													//�f�X�g���N�^

	HRESULT Init(void);						//����������
	void Uninit(void);						//�I������
	void Update(void);						//�X�V����
	void Draw(void);						//�`�揈��

private:

	int m_nldxTexture;		//�e�N�X�`���ԍ�

};

class CBulletB :public CBullet
{
public:

	CBulletB();													//�R���X�g���N�^
	~CBulletB();													//�f�X�g���N�^

	HRESULT Init(void);						//����������
	void Uninit(void);						//�I������
	void Update(void);						//�X�V����
	void Draw(void);						//�`�揈��

private:

	int m_nldxTexture;		//�e�N�X�`���ԍ�

};

class CBulletC :public CBullet
{
public:

	CBulletC();													//�R���X�g���N�^
	~CBulletC();													//�f�X�g���N�^

	HRESULT Init(void);						//����������
	void Uninit(void);						//�I������
	void Update(void);						//�X�V����
	void Draw(void);						//�`�揈��

private:

	int m_nldxTexture;		//�e�N�X�`���ԍ�

};
#endif // !_BULLET_H_
