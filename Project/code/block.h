//==============================================================
//
//�u���b�N�w�b�_�[[block.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _BLOCK_H_						//���̃}�N������`����Ă��Ȃ�������
#define _BLOCK_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"object2D.h"

//==============================================================
//�u���b�N�N���X
//==============================================================
class CBlock : public CObject2D
{
public:

	CBlock();									//�R���X�g���N�^
	CBlock(TYPE type, D3DXVECTOR3 pos);			//�R���X�g���N�^(�I�[�o�[���[�h)
	~CBlock();									//�f�X�g���N�^

	static CBlock *Create(TYPE type, D3DXVECTOR3 pos);	//�e�̐���

	HRESULT Init(void);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��

	static bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight);		//�G�Ƃ̓����蔻��

private:

	static LPDIRECT3DTEXTURE9 m_pTexture;	//���L�e�N�X�`��

	D3DXVECTOR3 m_move;						//�ړ���
	D3DXVECTOR3 m_rot;						//����	

	static float m_fWidth;					//����
	static float m_fHeight;					//�c��

	int m_nldxTexture;						//�e�N�X�`���ԍ�

};
#endif // !_BLOCK_H_
