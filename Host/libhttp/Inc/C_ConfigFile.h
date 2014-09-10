#ifndef C_CONFIGFILE_H
#define C_CONFIGFILE_H

/* ����pcSegmentָ���Ķζ�ȡ�ļ����ݣ��������һ��������,
** ��������ÿ���ڵ�Ԫ��ΪNAMEDSTRING_T(Name,Value��)����
eg: ʾ���ļ�config.ini����(������---------------------)��
-------------------------------
#This is file config.ini
[Test Segment]
name1=test1
name2=test2

name3=test3

	[New Segment]
name1=new1
#new2, this line won't be read
name2=new2
--------------------------------
�κ���#��ͷ���ж�����Ϊע�ⲻ�ƣ��հ��в��ƣ�ǰ���հײ��ơ�
ʹ������Ҫ����DeleteConfigSegmentList(..)�Է��ص������ͷ� */
#ifdef HTTP_SDIO
LIST *httpReadConfigSegment(const char *pcFileName, const char *pcSegName);
BOOL httpWriteConfigSegment(const char *pcFileName, const char *pcSegName, LIST *pListConfigItem);
#else
LIST *httpReadConfigSegment(const int *piReadAddr, const int iReadLen, const char *pcSegName);
BOOL httpWriteConfigSegment(const int *pWriteAddr, const int iWriteLen, const char *pcSegName, LIST *pListConfigItem);
#endif
void httpDeleteConfigSegmentList(LIST *pList);

#ifdef HTTP_SDIO
BOOL httpReadConfigValue(const char *pcFileName, const char *pcSegName, const char *pcVarName, char *pcVarValue, int iMaxReadSize);
BOOL httpWriteConfigValue(const char *pcFileName, const char *pcSegName, const char *pcVarName, const char *pcVarValue);
#else
BOOL httpReadConfigValue(const int *piReadAddr, const int iReadLen, const char *pcSegName, 
					const char *pcVarName, char *pcVarValue, int iMaxReadSize);
BOOL httpWriteConfigValue(const int *piWriteAddr, const int iWriteLen, const char *pcSegName, 
					const char *pcVarName, const char *pcVarValue);
#endif

/* �������ļ�����ppFileBuf�У�����Ҫfree */
#ifdef HTTP_SDIO
BOOL httpReadWholeFile(const char *pcFileName, char **ppcFileBuf, int *piFileLength);
#else
BOOL httpReadWholeFile(const int *piReadAddr, const int iReadLen, char **ppcFileBuf, int *piFileLength);
#endif

/* ���ļ�buffer(pFileBuf)�е�pcThisLinePos���õ�һ�У���ָ����һ�е�����ָ��*ppcNextLinePos
** ���û����һ���ˣ�*ppcNextLinePos��ָ���ļ���β�ַ�+1��
** �����pcThisLinePos���Ժ�û�����ˣ�����FALSE; ��֮����TRUE */
BOOL httpReadLineFromFileBuf(char *pcFileBuf, int iFileLength, char *pcThisLinePos, char **ppcNextLinePos);
#endif
