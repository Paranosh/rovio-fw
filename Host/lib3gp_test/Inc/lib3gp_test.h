#ifndef __THREEGP_H_
#define  __THREEGP_H_

#include "wbtypes.h"
#include "MediaFileLib.h"
#include "cyg/kernel/kapi.h"

typedef struct _ThrGP
{
	UCHAR *pucInBuf;    		//��ͨ������ĺ���ָ���ȡ���ݵ�ʱ������ָ����ȡ�Ŀռ�
	int   iInBufSize; 			//������ȡ�ռ�Ĵ�С(iInBufSize >= MAX video packet size )

	CHAR OutMediaFile[128];
	CHAR OutMetaFile[128];
	
	UCHAR *pucOutBuf;				//ָ����¼�����memory
	int   iOutBufSize;			//���memory �Ĵ�С��iOutBufSize >=uOutMediaBufSize + uOutMetaBufSize��

	UINT32 *ucOutMediaBuf;	//��¼����(audio and video)����Ŀռ�
	UINT32	uOutMediaBufSize;	//��¼����(audio and video)����Ŀռ�Ĵ�С

	UINT32 *ucOutMetaBuf;			//��¼������������Ŀռ�
	UINT32	uOutMetaBufSize;	//��¼������������Ŀռ�Ĵ�С

	//UINT32  uiOut3GPSize;			//�����¼���ݵ��ܴ�С��uiOut3GPSize <=iOutBufSize��
	unsigned short sVidRecWidth;	//video �Ŀ��
	unsigned short sVidRecHeight; //video �ĸ߶�

//ͨ���ṩ����ָ���ȡ video and audio 
	INT  (*tgpGetVideoFrame)(struct _ThrGP *ptgp,UINT8 **pucFrameBuff, UINT32 *puFrameSize);
	INT  (*tgpGetAudioFrame)(struct _ThrGP *ptgp,UINT8 **pucFrameBuff, UINT32 *puFrameSize);
	//�ṩ��������
	void (*ap_time)(struct _ThrGP *ptgp);
  	UINT32 data_rec_action;       //��¼��־ 
 
	int     device_fd;   //open device ID
	void* pMvCfg;				//����
	
	cyg_tick_count_t tgpStartTime;
}THREEGP_t;

int tgpRecorderVideoTrack(THREEGP_t *ptgp,UINT8 *pucInBuf,UINT32 uiSize);
int tgpRecorderAudioTrack(THREEGP_t *ptgp,UINT8 *pucInBuf,UINT32 uiSize);
int tgpIsRecorderEnd(THREEGP_t *ptgp);
int tgpInitVideoAudioFormat(THREEGP_t *ptgp);
int  tgpInitMovieConfig(THREEGP_t *ptgp);
unsigned int tgpMergeTGP(THREEGP_t *ptgp);
void tgpGetRecorderSize(THREEGP_t *ptgp,UINT32 *uOutMediaSize);
void tgpRecorderEnd(THREEGP_t *ptgp);

#endif

