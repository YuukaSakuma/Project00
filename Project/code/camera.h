//==============================================================
//
//�J�����w�b�_�[[camera.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _CAMERA_H_							//���̃}�N����`������Ă��Ȃ�������
#define _CAMERA_H_							//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

//�O���錾
class CPlayer;

//==============================================================
//�J�����N���X
//==============================================================
class CCamera
{
public:
	CCamera();	//�R���X�g���N�^
	~CCamera();	//�f�X�g���N�^

	HRESULT Init(void);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V���e
	void Set(void);			//�ݒ菈��

	void SetPositionVY(float posY) { m_posV.y = posY; }		//���_�ʒuY�ݒ�
	void SetPositionRY(float posY) { m_posR.y = posY; }		//�����_�ʒuY�ݒ�
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }		//�����ݒ�
	D3DXVECTOR3 GetRotation(void) { return m_rot; }			//�����擾

	void Move(void);

private:
	D3DXMATRIX m_mtxView;					//�r���[�}�g���b�N�X
	D3DXMATRIX m_mtxProjection;				//�v���W�F�N�V�����}�g���b�N�X

	D3DXVECTOR3 m_posV;						//���_
	D3DXVECTOR3 m_posR;						//�����_
	D3DXVECTOR3 m_vecU;						//������x�N�g��
	D3DXVECTOR3 m_rot;						//����

	D3DXVECTOR3 m_posVDest;					//�ړI�̎��_
	D3DXVECTOR3 m_posRDest;					//�ړI�̒����_
	D3DXVECTOR3 m_moveV;					//���_�̈ړ���
	D3DXVECTOR3 m_moveR;					//�����_�̈ړ���

	float m_fRotMove;						//���݂̕���(�p�x)
	float m_fRotDest;						//�ڕW�̕���(�p�x)
	float m_fRotDiff;						//�ڕW�̕����܂ł̍���

};

#endif
