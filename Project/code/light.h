//==============================================================
//
//���C�g�w�b�_�[[light.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _LIGHT_H_							//���̃}�N����`������Ă��Ȃ�������
#define _LIGHT_H_							//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"main.h"

//���C�g�N���X
class CLight
{
public:
	CLight();		//�R���X�g���N�^
	~CLight();		//�f�X�g���N�^

	HRESULT Init(void);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����

private:

	D3DLIGHT9 m_light[3];				//���C�g�̏��

};
#endif
