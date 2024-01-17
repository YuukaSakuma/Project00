//==============================================================
//
//�e�N�X�`������[texture.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "main.h"
#include"object.h"

//�}�N����`
#define MAX_TEX	(256)	//�e�N�X�`���̍ő吔

//==============================================================
//�e�N�X�`���N���X
//==============================================================
class CMaterial
{
public:

	//�e�N�X�`���̎��
	typedef enum
	{
		TEX_MAX = 0

	} TEX;

	//���f���̍\���̂̒�`
	typedef struct
	{
		LPD3DXMESH pMesh;					//���b�V���i���_���j�ւ̃|�C���^
		LPD3DXBUFFER pBuffMat;				//�}�e���A���ւ̃|�C���^
		DWORD dwNumMat;						//�}�e���A���̐�
		LPDIRECT3DTEXTURE9 *pTexture;
	} Material;


	CMaterial();		//�R���X�g���N�^
	~CMaterial();	//�f�X�g���N�^

	HRESULT Load(void);		//�e�N�X�`���ǂݍ��ݏ���
	void Unload(void);		//�e�N�X�`���j������

	int Regit(const char *pFilename);				//�e�N�X�`���̔ԍ��w��
	LPDIRECT3DTEXTURE9 GetTexAddress(int nIdx, int nMat);		//�e�N�X�`���̏��擾
	LPD3DXBUFFER GetMatAddress(int nIdx);		//�}�e���A���̏��擾
	DWORD GetNumMatAddress(int nIdx);			//�}�e���A���̐��̏��擾
	LPD3DXMESH GetMeshAddress(int nIdx);		//���b�V���̏��擾

private:
	static int m_nNumAll;		//�e�N�X�`���̐�
	static const char *m_apFilename[MAX_TEX];		//���f���̃e�L�X�g�t�@�C����
	static Material m_Material[MAX_TEX];			//�}�e���A���̏��
};
#endif