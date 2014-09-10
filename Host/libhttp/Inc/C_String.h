#ifndef C_STRING_H
#define C_STRING_H

#ifndef BOOL
#define BOOL char
#define TRUE 1
#define FALSE 0
#endif

typedef struct
{
	char *pcName;
	char *pcValue;
} NAMEDSTRING_T;

char *httpMyStrncpy(char *pcDest, const char *pcSrc, int iLength);

/* ��pcString��cSeparator��Ϊ�ָ�����һ��LIST�ṹ��˫�������� */
LIST *httpSplitString(const char *pcString, char cSeparator);

/* �ͷ�SplitString�������ɵ��������е��ַ�����Դ */
void httpDeleteSplitString(LIST *pList);

/* �õ�һ��ȥ��ǰ��հ׵��ַ�����������Ҫfree */
char *httpGetTrimString(const char *pcString);

/* �õ�һ����Cת�廯���ַ�����������Ҫfree
** ��ab"cd, ��õ�ab\"cd */
char *httpGetCStyleString(const char *pcString);
void httpDeleteCStyleString(char *pcString);

/* �õ�һ����webת�廯���ַ�����������Ҫfree
**   ab<cd, ��õ�ab&lt;cd */
char *httpGetWebStyleString(const char *pcString);

/* �õ�һ���Ⱦ�webת�廯���پ�C/javaת�廯���ַ���������Ҫfree */
char *httpGetWebInCString(const char *pcStr);
void httpDeleteWebInCString(char *pcStr);

/* ���ַ���ת��ΪIP��ַ */
unsigned long httpString2IP(const char *pcString);
/* ��IP��ַת��Ϊ�ַ���, pcStringOut�ռ����>=16, ����pcStringOut�ַ����ĳ��� */
int httpIP2String(unsigned long ulIP, char *pcStringOut);

/* ���ַ���ת��Ϊlong */
long httpString2Long(const char *pcString);
unsigned long httpString2ULong(const char *pcString);
/* ��longת��Ϊ�ַ���, pcStringOut�ռ����>=32, ����pcStringOut�ַ����ĳ��� */
int httpLong2String(long lVal, char *pcStringOut);

/* ���ַ���ת��ΪBOOL */
BOOL httpString2Bool(const char *pcString);
/* ��BOOLת��Ϊ�ַ���, pcStringOut�ռ����>=6("true"��"false"), ����pcStringOut�ַ����ĳ��� */
int httpBool2String(BOOL bVal, char *pcStringOut);

/* ��ʮ�������ַ���ת��Ϊ��Ӧ��ASC�ַ�,��"41"ת��ΪA */
char httpHex2Char(const char *str);
/* ��ASC�ַ�ת��Ϊʮ�������ַ���, ����2 */
int httpChar2Hex(char ch, char *pcRtHex);


/* ����һ���ֵ� */
LIST *httpCreateDict(void);

/* ����һ���ֵ� */
void httpDeleteDict(LIST *pList);

/* ���ֵ���ɾ��һ�� */
BOOL httpDelDictParam(LIST *pList, const char *pcName);

/* ���һ���ֵ�(NAMEDSTRING_T, Name,Value��)���������Ƿ���ָ������
** ���������,���溯���ķ���ֵΪ:
	httpGetString()	""
	httpGetIP()		0
	httpGetIP4()	0
	GetInt32()	0
	httpGetBool()	0
*/
LISTNODE *httpIsExistParam(const LIST *pList, const char *pcName);

/* �����ĺ�������pcName��list������ȡ��ֵ��
** ��������ÿ���ڵ�Ԫ��ΪNAMEDSTRING_T(Name,Value��)���� */
const char *httpGetString(const LIST *pList, const char *pcName);
unsigned long httpGetIP(const LIST *pList, const char *pcName);
unsigned long httpGetIP4(const LIST *pList, const char *pcName);
long httpGetLong(const LIST *pList, const char *pcName);
unsigned long httpGetULong(const LIST *pList, const char *pcName);
BOOL httpGetBool(const LIST *pList, const char *pcName);

/* �����ĺ�����������list��pcName��pcValue */
LISTNODE *httpSetString(LIST *pList, const char *pcName, const char *pcValue);
LISTNODE *httpSetIP(LIST *pList, const char *pcName, unsigned long ulValue);
LISTNODE *httpSetLong(LIST *pList, const char *pcName, long lValue);
LISTNODE *httpSetBool(LIST *pList, const char *pcName, BOOL bValue);


/* Define XML structure */
typedef struct tagXML
{
	struct tagXML *pParXML;
	LISTNODE *pParXMLNode;

	char *pcName;
	LIST *plAttrib;
	LIST *plSubXML;
} XML;

XML *httpCreateXML(const char *pcName);
XML *httpCreateXMLText(const char *pcText);
void httpDeleteXML(XML *pXML);
XML *httpInsertXMLBefore(XML *pXML, XML *pInsert);
XML *httpInsertXMLAfter(XML *pXML, XML *pInsert);
XML *httpAppendXML(XML *pXML, XML *pSubXML);
XML *httpDetachXML(XML *pXML, XML *pSubXML);
XML *httpGetParentXML(XML *pXML);
void httpDumpXML(XML *pXML, void (*Dumper)(const char *, void *), void *pParam);

#endif
