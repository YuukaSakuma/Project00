//==============================================================
//
//�����w�b�_�[[explosion.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _EXPLOSION_H_						//���̃}�N������`����Ă��Ȃ�������
#define _EXPLOSION_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "billboard.h"

//==============================================================
//�����N���X
//==============================================================
class CExplosion : public CBillboard
{
public:

	CExplosion();								//�R���X�g���N�^
	CExplosion(D3DXVECTOR3 pos, TYPE type);		//�R���X�g���N�^(�I�[�o�[���[�h)
	~CExplosion();								//�f�X�g���N�^

	static CExplosion *Create(D3DXVECTOR3 pos, TYPE type);			//�����̐���

	HRESULT Init(void);						//����������
	void Uninit(void);						//�I������
	void Update(void);						//�X�V����
	void Draw(void);						//�`�揈��

private:

	int m_nLife;							//����
	D3DXVECTOR3 m_move;						//�ړ���
	D3DXVECTOR3 m_rot;						//����	
	int m_nCounterAnim;						//�A�j���[�V�����J�E���^�[
	int m_nPatternAnim;						//�p�^�[��No.�J�E���^�[
	int m_nldxTexture;						//�e�N�X�`���ԍ�
	
};
#endif // !_EXPLOSION_H_
