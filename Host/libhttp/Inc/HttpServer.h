#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#define weak_alias(name, aliasname) \
extern __typeof (name) aliasname __attribute__ ((weak, alias (#name)));

typedef void *HTTPCONNECTION;
typedef int (*REQUEST_CALLBACK_PFUN)(HTTPCONNECTION hc, void *pParam);

typedef void *HTTPSERVER;

#ifndef ECOS
#include <sys/time.h>
#else
#include "time.h"
#include "../../../../SysLib/Inc/wb_syslib_addon.h"
#endif

#include "C_List.h"
#include "C_String.h"
#include "C_ConfigFile.h"
#include "C_HttpSupport.h"
#include "C_SendFile.h"
#include "C_MultiPart.h"
//#include "globals.h"

//#define HTTP_WITH_MALLOC
//#define HTTP_WITH_MALLOC_LEVEL1

/* ����һ��������, ���û��ύhttp://hostname/<cpAccessName>?[parameters]������ʱ��
** ת��ô�������
** ����������0��ʾ�����ٽ���ȱʡ�������ط�0��ʾ��Ҫ����ȱʡ���� */
int httpRegisterEmbedFun(const char *pcAccessName, REQUEST_CALLBACK_PFUN funRequestCallBack, void *pParam);
/* ����ô������Ĺ��� */
int httpUnregisterEmbedFun(const char *pcAccessName);
/* ��������Ѿ����صĺ��� */
void httpClearEmbedFun(void);


typedef int (*REQUEST_OVER_PFUN)(HTTPCONNECTION hConnection, void *pParam);
void httpSetRequestOverFun(HTTPCONNECTION hConnection, REQUEST_OVER_PFUN funOnRequestOver, void *pParam);

/* ���嵱���ݷ�����Ϻ�Ļص����� */
typedef int (*SEND_DATA_OVER_PFUN)(HTTPCONNECTION hConnection, time_t *tLastFill, void *pParam);
void httpSetSendDataOverFun(HTTPCONNECTION hConnection, SEND_DATA_OVER_PFUN funOnSendDataOver, void *pParam);

/* �����յ�POST������Ļص�����
** Return 0, �����������, ���رմ˴�����
** Return 1, ��������Ҫ��������, �����ִ˴�����
** Return -1, ������������, ���رմ˴����� */
typedef int (*POST_DATA_PFUN)(HTTPCONNECTION hConnection,
								int *piPostState,
								char **ppcPostBuf,
								int *piPostBufLen,
								int *piPostDataLen,
								char *pcFillData,
								int iFillDataLen,
								int iIsMoreData/*bool*/,
								void *pParam/*other parameter for extend use*/);

void httpSetPostDataFun(HTTPCONNECTION hConnection, POST_DATA_PFUN funPostDataGot, void *pParam);

void httpSetRequestOverFun(HTTPCONNECTION hConnection, REQUEST_OVER_PFUN funOnRequestOver, void *pParam);

void httpAddBody(HTTPCONNECTION hConnection, const char *pcBuf2Add, int iBufLen);
void httpAddBodyString(HTTPCONNECTION hConnection, const char *pcString);

void ClearHttpSendData(HTTPCONNECTION hConnection);
void SetExtraHeader(HTTPCONNECTION hConnection, char *pcExtraHeader);

/* ����Http KeepAlive����, must be called before httpSetHeader() */
void httpSetKeepAliveMode(HTTPCONNECTION hConnection, BOOL bIsKeepAlive);
void httpSetHeader(HTTPCONNECTION hConnection, int iStatus, const char *pcTitle, const char *pcEncodings, const char *pcExtraheads, const char *pcContentType, BOOL bShowLength);
void httpSetNullHeader(HTTPCONNECTION hConnection);

/* ȡ�ü���document root����ַ���, ������Ҫfree */
char *httpGetDocumentBasedPath(char *pcUriPath);
/* ����Http��������֧��ssl */
HTTPSERVER httpdStartEx3(char *pcServerRoot,
				int *piPort,
				int *piSSLPort,
				int iKeepAliveTimeout,
				int iKeepAliveMax,
				int iMaxConnections,
				int (*pOnListenSocketCreate)(int fd, int iPort),
				int (*pOnHttpInit)(HTTPSERVER hServer),
				REQUEST_CALLBACK_PFUN pOnRequestBegin);
/* ����Http������, ֧�ָ���listen socket�Ľ��� */
HTTPSERVER httpdStartEx2(char *pcServerRoot,
				int *piPort,
				int iKeepAliveTimeout,
				int iKeepAliveMax,
				int iMaxConnections,
				int (*pOnListenSocketCreate)(int fd, int iPort),
				int (*pOnHttpInit)(HTTPSERVER hServer),
				REQUEST_CALLBACK_PFUN pOnRequestBegin);
/* ����Http������, ֧�ֶ��port */
HTTPSERVER httpdStartEx(char *pcServerRoot,
				int *piPort,
				int iKeepAliveTimeout,
				int iKeepAliveMax,
				int iMaxConnections,
				int (*pOnHttpInit)(HTTPSERVER hServer),
				REQUEST_CALLBACK_PFUN pOnRequestBegin);
/* ����Http������ */
HTTPSERVER httpdStart(char *pcServerRoot,
				int iPort,
				int iKeepAliveTimeout,
				int iKeepAliveMax,
				int iMaxConnections,
				int (*pOnHttpInit)(HTTPSERVER hServer),
				REQUEST_CALLBACK_PFUN pOnRequestBegin);
#ifndef HTTP_WITH_MALLOC
int httpInitHashMemPool(void);
#endif

/****************** METHODS *****************/
#define	M_INVALID	-1
#define	M_SHORT	0
#define M_GET		1
#define M_HEAD		2
#define M_PUT		3
#define M_POST		4
#define M_DELETE	5
#define M_LINK		6
#define M_UNLINK	7
/* ȡ������ķ��� HEAD, GET, POST, ...*/
int httpGetMethod(HTTPCONNECTION hConnection);
/* ȡ��Client��ַ */
struct in_addr httpGetClientAddr(HTTPCONNECTION hConnection);
/* ȡ��Client MAC��ַ, ����һ������Ϊ6���ַ����� */
char *httpGetClientMac(HTTPCONNECTION hConnection);
/* ȡ���û���GET�����ύ����ʱ���ӵĲ���, δ���� */
char *httpGetQueryString(HTTPCONNECTION hConnection);
/* ȡ�ý���������·��, ip�Ժ�Ĳ���, ����query */
char *httpGetRequestPath(HTTPCONNECTION hConnection);
/* ȡ�������ʵ���ļ�·�� */
char *httpGetRequestFilePath(HTTPCONNECTION hConnection);
/* ȡ��Referer */
char *httpGetReferer(HTTPCONNECTION hConnection);
/* ȡ��Content-type */
char *httpGetContentType(HTTPCONNECTION hConnection);
/* ȡ��Content-length */
int httpGetContentLength(HTTPCONNECTION hConnection);
/* Get X_SESSIONCOOKIE */
char *httpGetXSessionCookie(HTTPCONNECTION hConnection);



/* ����Ȩ�޴ӵ͵��ߣ���Ҫ�ı���ֵ! */
#define AUTH_ANY -1
#define AUTH_USER 0
#define AUTH_ADMIN 1
#define AUTH_SYSTEM 2
int httpRegisterEmbedFunEx(const char *pcAccessName, REQUEST_CALLBACK_PFUN funRequestCallBack, int iPrivilegeRequired, void *pParam);
BOOL httpIsRegisterEmbedFunEx(const char *pcAccessName, REQUEST_CALLBACK_PFUN *pfunRequestCallBack, int *piPrivilegeRequired, void **ppParam);

char *httpGetCurrentUser(HTTPCONNECTION hConnection, char *pcUser, int iUserLen);
int httpGetAuthPrivilege(HTTPCONNECTION hConnection);
int httpSendAuthRequired(HTTPCONNECTION hConnection, int iPrivilege);
void httpSetAuthPrompt(const char *pcUserPrompt, const char *pcAdminPrompt, const char *pcSystemPrompt);
BOOL httpAuthGetUser(const char *pcUserName, char *pcPassword, int iMaxPassLen, int *piPrivilege);
int httpAuthSetUser(const char *pcUserName, const char *pcPassword, int iPrivilege);
int httpAuthDelUser(const char *pUserName);
LIST **httpGetAuthUserList(void);
void httpEnableUserCheck(BOOL bIsEnable);
BOOL httpIsEnableUserCheck(void);

int httpDisconnect(const char *pcPath, const char *pcQuery);
BOOL httpIsDisconnect(HTTPCONNECTION hConnection);
int httpSwapFD(HTTPCONNECTION hConnection, int fd);

#endif
