//==============================================================
//
//�e�N�X�`������[texture.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _XFILE_H_
#define _XFILE_H_

#include "main.h"

//�}�N����`
#define MAX_TEX	(256)	//�e�N�X�`���̍ő吔

//==============================================================
//�e�N�X�`���N���X
//==============================================================
class CXFile
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

	CXFile();		//�R���X�g���N�^
	~CXFile();	//�f�X�g���N�^

	HRESULT Load(void);		//�e�N�X�`���ǂݍ��ݏ���
	void Unload(void);		//�e�N�X�`���j������

	int Regist(const char *pFilename);				//�e�N�X�`���̔ԍ��w��
	LPDIRECT3DTEXTURE9 GetTexAddress(int nIdx, int nMat);		//�e�N�X�`���̏��擾
	LPD3DXBUFFER GetMatAddress(int nIdx);		//�}�e���A���̏��擾
	DWORD GetNumMatAddress(int nIdx);			//�}�e���A���̐��̏��擾
	LPD3DXMESH GetMeshAddress(int nIdx);		//���b�V���̏��擾

private:

	static int m_nNumAll;		//�e�N�X�`���̐�
	static const char *m_apFilename[MAX_TEX];		//���f���̃e�L�X�g�t�@�C����
	static Material m_Material[MAX_TEX];			//�}�e���A���̏��
};

////==============================================================
////�e�N�X�`���N���X
////==============================================================
//class CXFile
//{
//
//private:
//	const static int MAX_FILE = 256;
//	const static int MAX_NAME = 256;
//
//public:
//
//	//X�t�@�C�����
//	struct FileData
//	{
//		LPD3DXMESH pMesh;					//���b�V���i���_���j�ւ̃|�C���^
//		LPD3DXBUFFER pBuffMat;				//�}�e���A���ւ̃|�C���^
//		int *pIdexTexture;					//�e�N�X�`���ԍ�
//		DWORD dwNumMat;						//�}�e���A���̐�
//		D3DXVECTOR3 vtxMin;					//�ŏ�
//		D3DXVECTOR3 vtxMax;					//�ő�
//		LPDIRECT3DTEXTURE9 *pTexture;
//	};
//
//private:
//	// �t�@�C���ǂݍ��ݏ��
//	struct FileInfo
//	{
//		char aFileName[MAX_NAME];	// �t�@�C����
//		FileData filedata;			// �t�@�C�����
//	};
//
//public:
//
//	CXFile();		//�R���X�g���N�^
//	~CXFile();	//�f�X�g���N�^
//
//	// �����o�֐�
//	int Regist(const char *pFileName);
//	void Unload(void);
//	void SetSizeVtxMax(int nIdx, D3DXVECTOR3 vtxMax) { m_apModelFileData[nIdx]->filedata.vtxMax = vtxMax; }
//	void SetSizeVtxMin(int nIdx, D3DXVECTOR3 vtxMin) { m_apModelFileData[nIdx]->filedata.vtxMin = vtxMin; }
//
//	// �����o�֐�(�擾)
//	FileData *SetAddress(int nIdx);
//	static int GetNumAll(void) { return m_nNumAll; }
//	D3DXVECTOR3 GetMax(int nIdx) { return m_apModelFileData[nIdx]->filedata.vtxMax; }
//	D3DXVECTOR3 GetMin(int nIdx) { return m_apModelFileData[nIdx]->filedata.vtxMin; }
//	char *GetFileName(int nIdx) { return &m_apModelFileData[nIdx]->aFileName[0]; }
//
//private:
//
//	HRESULT FileLoad(int nIdx);
//
//	FileInfo *m_apModelFileData[MAX_FILE];	// ���f���̃t�@�C�����̃|�C���^
//	static int m_nNumAll;	// �ǂݍ��ݑ���
//};
#endif