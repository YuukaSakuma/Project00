//==============================================================
//
//���C���w�b�_�[[main.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _MAIN_H_						//���̃}�N������`����Ă��Ȃ�������
#define _MAIN_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

// �r���h���̌x���Ώ��p�}�N��
#define  DIRECTINPUT_VERSION	(0x0800)

#include<windows.h>
#include <time.h>
#include "d3dx9.h"						//�`�揈���ɕK�v
#include "dinput.h"						//���͏����ɕK�v
#include "xaudio2.h"					//�T�E���h�����ɕK�v
#include<stdio.h>

//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")			//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")		//[d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")		//DirectX�R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")		//�V�X�e�������̎擾�ɕK�v
#pragma comment(lib,"dinput8.lib")		//���͏����ɕK�v

//�}�N����`
#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//���_���[2D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;					//���_���W
	float rhw;							//���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;						//���_�J���[
	D3DXVECTOR2 tex;					//�e�N�X�`���̍��W
}VERTEX_2D;

//���_���[3D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;			//���_���W
	D3DXVECTOR3 nor;			//�@���x�N�g��
	D3DCOLOR col;				//���_�J���[
	D3DXVECTOR2 tex;			//�e�N�X�`�����W
}VERTEX_3D;

//�v���g�^�C�v�錾
int GetFPS(void);

#endif // !_MAIN_H_