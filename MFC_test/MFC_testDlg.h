
// MFC_testDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxsock.h"
#include <Winsock2.h>
#include "stdint.h"


// CMFCtestDlg dialog
//typedef long 				nint64_t;
//typedef int 				nint32_t;
//typedef short 			nint16_t;
//typedef char 				nint8_t;



//定义用户使用ID
#define  WM_NET_SENDSignalINFO (WM_USER + 101)


//高八位和低八位互换宏定义
#define SW_16(x) ((short)((((short)(x)&(short)0x00ffU)<<8)|(((short)(x)&(short)0xff00U)>>8)))
#define SW_32(x)  ((((x)&(0x00ffU))<<24)|(((x)&(0xff00U))<<8)|(((x>>16)&(0x00ffU))<<8)|(((x>>16)&(0xff00U))>>8))


UINT ReceiveDataThread(LPVOID pParam);

class CMFCtestDlg : public CDialogEx
{
// Construction
public:
	CMFCtestDlg(CWnd* pParent = nullptr);	// standard constructor

	typedef struct _PARTICIPANTINFORMATION
	{
		uint16_t  ParticipantID;
		uint8_t   ParticipantType;
		uint8_t   ParticipantConfidence;
		uint8_t   ParticipantColor;
		uint8_t   ParticipantInformationSource;
		uint8_t   ParticipantReserved1[2];
		int32_t  ParticipantLongitude;
		int32_t  ParticipantLatitude;
		int16_t  ParticipantAltitude;
		uint16_t  ParticipantSpeed;
		uint16_t  ParticipantCourseAngle;
		uint16_t  ParticipantLength;
		uint16_t  ParticipantWidth;
		uint16_t  ParticipantHeight;
		int16_t  ParticipantPositionX;
		int16_t  ParticipantPosotionY;
		int16_t  ParticipantPosotionZ;
		uint8_t   ParticipantReserved2[2];

	}PARTICIPANTINFORMATION;

	typedef struct _MESSAGECONTNET
	{
		uint16_t  FacilityID;
		uint16_t  Reserved1;
		uint32_t  DataFrameNumber;
		uint64_t  TimeStamp;
		uint32_t  LidarLongitude;
		uint32_t  LidarLatitude;
		uint16_t  LidarAngle;
		uint8_t   TrafficParticipantNumber;
		uint8_t   Reserved2[5];
		PARTICIPANTINFORMATION *m_ParticipantInformation;
		uint8_t   Reserved3[4];

	}MESSAGECONTNET;

	typedef struct _UDPSENDRSM
	{
		uint16_t StartBit;
		uint8_t  SerialNumber;
		uint8_t  MasterNumber;
		uint8_t  SlaveNumber;
		uint8_t  StatusBit;
		uint16_t MessageLength;
		MESSAGECONTNET m_MessageContent;
		uint8_t  ParityBit;
		uint8_t  EndBit;
	}UdpSendRSM;

	UdpSendRSM g_UdpSendRSM;
	PARTICIPANTINFORMATION g_ParticipantInformation;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_TEST_DIALOG };
#endif

	static UINT SendDataThread(LPVOID pParam);

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	//添加发送数据函数
	LRESULT CMFCtestDlg::OnSendData(WPARAM wParam, LPARAM lParam);

	//添加接收数据函数
	//LRESULT CMFCtestDlg::OnReceiveData(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_CmbNumber;
	CComboBox m_CmbInfoSource;
	CComboBox m_CmbType1;
	CComboBox m_CmbType2;
	CComboBox m_CmbType3;
	CComboBox m_CmbColor1;
	CComboBox m_CmbColor2;
	CComboBox m_CmbColor3;
	uint8_t   m_TextConfidence1;
	int32_t  m_TextLongitude1;
	int32_t  m_TextLatitude1;
	uint32_t  m_TextSpeed1;
	uint32_t  m_TextCourseAngle1;
	int32_t  m_TextPositionX1;
	int32_t  m_TextPositionY1;
	int32_t  m_TextPositionZ1;
	uint8_t   m_TextConfidence2;
	int32_t  m_TextLongitude2;
	int32_t  m_TextLatitude2;
	uint32_t  m_TextSpeed2;
	uint32_t  m_TextCourseAngle2;
	int32_t  m_TextPositionX2;
	int32_t  m_TextPositionY2;
	int32_t  m_TextPositionZ2;
	uint8_t   m_TextConfidence3;
	int32_t  m_TextLongitude3;
	int32_t  m_TextLatitude3;
	uint32_t  m_TextSpeed3;
	uint32_t  m_TextCourseAngle3;
	int32_t  m_TextPositionX3;
	int32_t  m_TextPositionY3;
	int32_t  m_TextPositionZ3;
	uint32_t  m_TextLidarLongitude;
	uint32_t  m_TextLidarLatitude;

	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
};
