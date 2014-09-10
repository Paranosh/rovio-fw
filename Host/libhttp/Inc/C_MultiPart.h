#ifndef C_MULTIPART_H
#define C_MULTIPART_H

typedef struct
{
	LIST *plPartDiscription;	//LIST of MULTIPART_DESCRIPTION_T;
	char *pcPartBody;
	int	iPartBodyLength;
} INNERPART_T;

typedef struct
{
	char *pcSegStart;//������
	char *pcSegEnd;	//������
} SPLIT_ITEM_T;

/* �ָ�pcBuffer, (iBufferLength - pBuffer����)
   iMaxReturn, ���ķָ���Ŀ

	�ָ��ж�����
	char *pcSeperator(char *pcBeing, char *pcEnd, char *pcCur, void *pSeperatorParam);
		pcBegin - pBuffer
		pcEnd - pBuffer + iBufferLength
		pcCur - λ��[pcBegin, pcEnd)֮���ĳ��λ��
		���pcCur�����Ϸָ��ж�����, ������һ�ε�λ��
		����, ����NULL
*/

LIST *httpSplitBuffer(char *pcBuffer, int iBufferLength, int iMaxReturn, char *pcSeperator(char *pcBeing, char *pcEnd, char *pcCur, void *pSeperatorParam), void *pSeperatorParam);
void httpDeleteSplitBuffer(LIST *pList);

LIST *httpParseDescriptionLine(char *pcDescription, int iDescriptionLength);
void httpDeleteDescriptionLine(LIST *pList);

LIST *httpParseDescription(char *pcDescription, int iDescriptionLength);
void httpDeleteDescription(LIST *pList);

INNERPART_T *httpParseSinglePart(char *pcSinglePartSource, int iSinglePartSourceLength);
void httpDeleteSinglePart(INNERPART_T *pInnerPart);

LIST *httpParseMultiPart(char *pcMultiPartSource, int iMultiPartSourceLength, char *pcBoundary);
void httpDeleteMultiPart(LIST *pList);

#endif
