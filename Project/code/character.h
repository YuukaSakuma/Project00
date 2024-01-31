//==============================================================
//
//�v���C���[�w�b�_�[[player.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _CHARACTER_H_						//���̃}�N������`����Ă��Ȃ�������
#define _CHARACTER_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "object.h"

//==============================================================
//�v���C���[�N���X
//==============================================================
class CCharacter 
{
public:

	CCharacter();								//�R���X�g���N�^
	~CCharacter();								//�f�X�g���N�^

	static CCharacter *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			//�v���C���[�̐���

	HRESULT Init(void);						//�v���C���[�̏���������
	void Uninit(void);						//�v���C���[�̏I������
	void Update(void);						//�v���C���[�̍X�V����
	void Draw(void);						//�v���C���[�̕`�揈��

private:


};
#endif // !_PLAYER_H_
