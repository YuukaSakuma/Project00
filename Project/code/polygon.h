//==============================================================
//
//�|���S���w�b�_�[[polygon.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _POLYGON_H_						//���̃}�N������`����Ă��Ȃ�������
#define _POLYGON_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "object3D.h"

//==============================================================
//�|���S���N���X
//==============================================================
class CPolygon : public CObject3D
{
public:

	CPolygon();									//�R���X�g���N�^
	CPolygon(TYPE type,D3DXVECTOR3 pos);		//�R���X�g���N�^(�I�[�o�[���[�h)
	~CPolygon();								//�f�X�g���N�^

	static CPolygon *Create(TYPE type, D3DXVECTOR3 pos);			//�G�l�~�[�̐���

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

	static LPDIRECT3DTEXTURE9 m_pTexture;				//���L�e�N�X�`��

	int m_nldxTexture;
};
#endif // !_ENEMY_H_
