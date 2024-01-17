//==============================================================
//
//�I�u�W�F�N�g�w�b�_�[[object.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _OBJECT_H_						//���̃}�N������`����Ă��Ȃ�������
#define _OBJECT_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

//�}�N����`
#define MAX_OBJECT (1024)

//==============================================================
//�I�u�W�F�N�g�N���X
//==============================================================
class CObject
{
public:

	//���
	typedef enum
	{
		TYPE_NONE = 0,	//�Ȃ�
		TYPE_PLAYER,	//�v���C���[
		TYPE_ENEMY,		//�G
		TYPE_BULLET,	//�e
		TYPE_EXPLOSION,	//����
		TYPE_EFFECT,	//�G�t�F�N�g
		TYPE_PARTICLE,	//�p�[�e�B�N��
		TYPE_SCORE,		//�X�R�A
		TYPE_BLOCK,		//�u���b�N
		TYPE_ITEM,		//�A�C�e��
		TYPE_MODEL,
		TYPE_MAX
	}TYPE;

	//�I�u�W�F�N�g�̏��
	typedef enum
	{
		STATE_NONE = 0,		//�ʏ���
		STATE_ATTACK,		//�U�����
		STATE_DAMAGE,		//�_���[�W���
		STATE_APPEAR,		//�������
		STATE_F_JUMP,		//1��ڂ̃W�����v���
		STATE_S_JUMP,		//2��ڂ̃W�����v���
		STATE_DEATH,		//���S���

	} STATE;

	CObject();				//�R���X�g���N�^
	CObject(TYPE type);		//�R���X�g���N�^(�I�[�o�[���[�h)
	virtual ~CObject();		//�f�X�g���N�^

	virtual HRESULT Init(void) = 0;		//����������
	virtual void Uninit(void) = 0;		//�I������
	virtual void Update(void) = 0;		//�X�V����
	virtual void Draw(void) = 0;		//�`�揈��

	virtual void Hit(void) {};		//�q�b�g����

	virtual void SetRotation(D3DXVECTOR3 rot) {};										//�ʒu�̐ݒ�
	virtual D3DXVECTOR3 GetRotation(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }		//�ʒu�̎擾

	virtual void SetPosition(D3DXVECTOR3 pos) {};										//�ʒu�̐ݒ�
	virtual D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }		//�ʒu�̎擾
																						
	virtual D3DXVECTOR3 GetSizeMin(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }		//�ŏ��T�C�Y�̎擾
	virtual D3DXVECTOR3 GetSizeMax(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }		//�ő�T�C�Y�̎擾

	static void ReleseAll(void);										//
	static void UpdateAll(void);										//�S�Ă̍X�V
	static void DrawAll(void);											//�S�Ă̕`��
	static void ResetMapAll(void);										//
	static CObject * GetObject(int nIdx) { return m_apObject[nIdx]; }	//�I�u�W�F�N�g���̎擾

	void SetType(TYPE type) { m_type = type; }	//�^�C�v�̐ݒ�
	TYPE GetType(void) { return m_type; }		//�^�C�v�̎擾

	virtual void SetState(STATE state) {}					//�I�u�W�F�N�g�̏�Ԑݒ�
	virtual STATE GetState(void) { return STATE_NONE; }		//�I�u�W�F�N�g�̏�Ԏ擾
	
protected:

	void Release(void);

private:
	static CObject * m_apObject[MAX_OBJECT];	//�I�u�W�F�N�g�̃|�C���^
	static int m_nNumAll;						//�I�u�W�F�N�g�̑���
	int m_nID;									//�������g�̃N���X
	TYPE m_type;								//���
	STATE m_state;								//�I�u�W�F�N�g�̏��

};
#endif // !_MAIN_H_

