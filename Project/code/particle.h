//==============================================================
//
//�p�[�e�B�N���w�b�_�[[particle.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _PARTICLE_H_						//���̃}�N������`����Ă��Ȃ�������
#define _PARTICLE_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"object2D.h"

//==============================================================
//�p�[�e�B�N���N���X
//==============================================================
class CParticle : public CObject2D
{
public:

	CParticle();							//�R���X�g���N�^
	~CParticle();							//�f�X�g���N�^

	static CParticle *Create(D3DXVECTOR3 pos, D3DXCOLOR col, TYPE type, float fRadius, int nLife);			//�p�[�e�B�N���̐���

	HRESULT Init(void);						//�p�[�e�B�N���̏���������
	void Uninit(void);						//�p�[�e�B�N���̏I������
	void Update(void);						//�p�[�e�B�N���̍X�V����
	void Draw(void);						//�p�[�e�B�N���̕`�揈��

	void Set(D3DXVECTOR3 pos, D3DXCOLOR col, CObject::TYPE type, float fRadius, int nLife);

private:

	static LPDIRECT3DTEXTURE9 m_pTexture;	//���L�e�N�X�`��

	D3DXVECTOR3 m_pos;			//�ʒu(�J�n����)
	D3DXVECTOR3 m_move;			//�ړ���
	D3DXCOLOR m_col;			//�F
	float m_fRadius;			//���a(�傫��)
	int m_nLife;				//����(��������)							
	int m_nType;				//���
	float m_fAngle;				//
	float m_fMove;				//
	
};
#endif // !_PLAYER_H_
