//==============================================================
//
//�e�w�b�_�[[bullet.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _COA_H_						//���̃}�N������`����Ă��Ȃ�������
#define _COA_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "object.h"

//�O���錾
class CModel;
class CModelHier;
class CMotion;

//==============================================================
//�R�A�N���X
//==============================================================
class CCOa
{
public:

	CCOa();													//�R���X�g���N�^
	~CCOa();													//�f�X�g���N�^

	static CCOa *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//�e�̐���

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

	void SetState(void);

private:
#define NUM_MODEL_BIRD1		(8)			//�G1�̃��f����

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

	//STATE m_state;			//���

	int m_nIdxTexture;			//�e�N�X�`���̔ԍ�
	static int m_nNumAll;		//�G�̑���
	int m_nID;					//�G�̔ԍ�

	CModel* m_pModel;
};
#endif // !_BULLET_H_
