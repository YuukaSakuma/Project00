//==============================================================
//
//�^�C�g���w�b�_�[[title.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _TITLE_H_						//���̃}�N������`����Ă��Ȃ�������
#define _TITLE_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"manager.h"

#define NUM_LIFE_FRAME		(2)		//�g�g�݂̐�

//�O���錾
class CModel;
class CField;
class CObject2D;

//==============================================================
//�^�C�g���N���X
//==============================================================
class CLife : public CObject
{
public:
	CLife();								//�R���X�g���N�^
	CLife(D3DXVECTOR3 pos);					//�R���X�g���N�^
	~CLife();								//�f�X�g���N�^

	static CLife *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//��������

	HRESULT Init(void);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��

	void SetMax(int nMaxLife) { m_nMaxLife = nMaxLife; }			//�̗͐ݒ�
	void SetNum(int nNumBullet);		//�̗͏���ݒ�
	void SetNumCon(int nNumCon) { m_nNumCon = nNumCon; }			//������l�ݒ�
	int GetNum(void) { return m_nNumCon; }							//�̗͏���擾
	int GetMax(void) { return (m_nMaxLife - m_nNumCon); }


private:

	static CObject2D *m_apObject2D[NUM_LIFE_FRAME];		//�I�u�W�F�N�g2D�̏��
	int m_nIdxTexture[NUM_LIFE_FRAME];		//�e�N�X�`���̔ԍ�


	D3DXVECTOR3 m_pos;		//�ʒu
	int m_nNumCon;			//�̗͏��
	int m_nMaxLife;			//�ő�̗�

};
#endif // !_PLAYER_H_

