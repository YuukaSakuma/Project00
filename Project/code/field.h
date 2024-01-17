//==============================================================
//
//�t�B�[���h�w�b�_�[[field.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _FIELD_H_						//���̃}�N������`����Ă��Ȃ�������
#define _FIELD_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "object3D.h"

//==============================================================
//�t�B�[���h�N���X
//==============================================================
class CField : public CObject3D
{
public:

	CField();								//�R���X�g���N�^
	CField(TYPE type,D3DXVECTOR3 pos);		//�R���X�g���N�^(�I�[�o�[���[�h)
	~CField();								//�f�X�g���N�^

	static CField *Create(TYPE type, D3DXVECTOR3 pos);			//�t�B�[���h�̐���

	HRESULT Init(void);						//����������
	void Uninit(void);						//�I������
	void Update(void);						//�X�V����
	void Draw(void);						//�`�揈��

	//void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	//�ʒu�ݒ�
	//D3DXVECTOR3 GetPosition(void) { return m_pos; }		//�ʒu�̎擾

private:

	D3DXVECTOR3 m_move;						//�ړ���
	D3DXVECTOR3 m_rot;						//����
	D3DXVECTOR3 m_pos;						//�ʒu

	int m_nldxTexture;		//�e�N�X�`���ԍ�
};
#endif // !_ENEMY_H_
