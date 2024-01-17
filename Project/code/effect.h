//==============================================================
//
//�G�t�F�N�g�w�b�_�[[effect.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _EFFECT_H_						//���̃}�N������`����Ă��Ȃ�������
#define _EFFECT_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"billboard.h"

//==============================================================
//�G�t�F�N�g�N���X
//==============================================================
class CEffect : public CBillboard
{
public:

	CEffect();																					//�R���X�g���N�^
	CEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife);		//�R���X�g���N�^(�I�[�o�[���[�h)
	~CEffect();																					//�f�X�g���N�^

	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife);			//�G�t�F�N�g�̐���

	HRESULT Init(void);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��

private:

	D3DXVECTOR3 m_move;		//�ړ���
	D3DXCOLOR m_col;		//�F
	float m_fRadius;		//���a(�傫��)
	int m_nLife;			//����(�\������)
	int m_nldxTexture;		//�e�N�X�`���ԍ�
};
#endif // !_EFFECT_H_
