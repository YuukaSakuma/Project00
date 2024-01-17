//==============================================================
//
//�����_���[�w�b�_�[[renderer.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _RENDERER_H_						//���̃}�N������`����Ă��Ȃ�������
#define _RENDERER_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

//�O���錾
class CDebugProc;

//==============================================================
//�����_���[�N���X
//==============================================================
class CRenderer
{
public:
	CRenderer();			//�R���X�g���N�^
	~CRenderer();			//�f�X�g���N�^

	HRESULT Init( HWND hWnd, BOOL bWindow);	//����������
	void Uninit(void);						//�I������
	void Update(void);						//�X�V����
	void Draw(void);						//�`�揈��

	LPDIRECT3DDEVICE9 GetDevice(void);		//�f�o�C�X�̎擾
	
private:

	LPDIRECT3D9 m_pD3D;										//Direct3D�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECT3DDEVICE9 m_pD3DDevice;							//Direc3D�f�o�C�X�ւ̃|�C���^
};
#endif // !_MAIN_H_
