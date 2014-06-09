#ifndef JC_CONTROL_H
#define JC_CONTROL_H
#include "pkcs11t.h"

/*! \typedef C_JCCTRL
* \brief ��������� �� �����, ����������� ��������� �������� �� SWYX-������������
* \param slotID - �������������(�����) �����. ��� ����� ����� �������� � ������� C_GetSlotList
* \param operation - ��� �������� (��. #C_JCCTRL_OPERATION_CODES)
* \param pData - ��������� �� ������ ���� � ������� ����� �������� �������� ������, ��� ��������� ��� �����������(� ������ �������� #JC_CTRL_SWYX_DISPLAY) 
* ��� ����������� �������� ��������� � ��������� ������ �������� ��. �������� ��������� #C_JCCTRL_OPERATION_CODES
* \param ulDataLen - ��������� �� ����� ������� � ��������� ��� �������� (� ������ �������� #JC_CTRL_SWYX_DISPLAY) �������
* ��� ����������� �������� ��������� � ��������� ������ �������� ��. �������� ��������� #C_JCCTRL_OPERATION_CODES
* \return ��� �������� � �������� PKCS11
**/
extern "C"
{
	CK_RV C_jcCtrl(CK_ULONG slotId, CK_ULONG operation, CK_BYTE_PTR pData, CK_ULONG_PTR ulDataLen);
}

// ���� �������� ��� ������ jc_ctrl
enum C_JCCTRL_OPERATION_CODES
{
	/// �������� �������� SWYX-�����������. ��������� #C_JCCTRL: � pData  ����� �������� �������� � ���� ��������� #_SWYX_PROPERTIES_RESPONSE (����� ���� � little endian), 
	/// ulDataLen ����� ��������� ������ ��������� �� ���������� (������ ���� 12 ����)
	JC_CTRL_GET_PROPERTIES = 0, 
	/// �������� SWYX-�����.  ��������� pData � ulDataLen � #C_JCCTRL �� ������������ 
	JC_CTRL_SWYX_START = 1,
	/// ��������� SWYX-����� � �������� ��� + �������.  ��������� #C_JCCTRL: � pData ����� ������� ��� � ������� xml + 64 ����� ������� � �����,
	/// ulDataLen ����� ��������� ��������� ������ ���� � �������
	JC_CTRL_SWYX_STOP = 2,
	/// ���������� ����� �� ������ SWYX-����������� � ���������� ������������ ��������� ���. ��������� #C_JCCTRL: �
	/// pData ������ ��������� ��������� #SWYX_DISPLAY_ARGUMENTS, ulDataLen - ������ ���� ���������.
	/// � ������ ���� ������������ ������� �������� �������, ����� C_JCCTRL ������ CKR_FUNCTION_REJECTED (0x00000200),
	/// � ������ ����-���� - CKR_FUNCTION_CANCELED (0x00000050)
	JC_CTRL_SWYX_DISPLAY = 3,
	/// ������������� ����� �������� ���� �� SWYX-�����������. ��������� pData � ulDataLen � #C_JCCTRL �� ������������.
	/// � ������, ���� ������������ ������� �������� ����� C_JCCTRL ������ CKR_FUNCTION_REJECTED (0x00000200)
	JC_CTRL_PERSONALIZE = 4,
	/// �������� �������� ���� SWYX-�����������. ��������� #C_JCCTRL: pData - ������ ��������� �������� ����, ulDataLen - ������ ����� ����� (������ ���� 64 �����)
	JC_CTRL_ENROLL = 5,
	/// �������� �������� ����� �������, ������������ ������ SWYX-�����������. ��������� #C_JCCTRL: pData ������ ��������� �������� �����, ulDataLen - ��� ����� (������ ���� 8 ����)
	JC_CTRL_SWYX_GET_APPLET_SN = 6,
	/// ��������� ���-��� ������������. ��������� pData � ulDataLen � #C_JCCTRL �� ������������.  � ������, ���� ������������ ������� ��������,
	/// ����� #C_JCCTRL ������ CKR_FUNCTION_REJECTED (0x00000200), � ������ �������� ����� (30 ������) - CKR_FUNCTION_CANCELED (0x00000050)
	JC_CTRL_PIN_VERIFY = 7
};

/// �������� SWYX-�����������
struct SWYX_PROPERTIES_RESPONSE
{
	/// ��� ������. 0 - ������ �����, 1 - �����������
	CK_BYTE bDisplayType;
	/// ������������ ���������� ��������, ������������ � ���� ������� �� ������
	CK_ULONG wLcdMaxCharacters;
	/// ������������ ���������� �����
	CK_ULONG wLcdMaxLines;
	/// ������ ������ � ������
	CK_ULONG wGraphicMaxWidth;
	/// ������ ������ � ������
	CK_ULONG wGraphicMaxHeight;
	/// ��������� ������. 1 - �����-�����, 2 - �������� ������ (4 ����), 4 - ������� (4 ����)
	CK_BYTE bGraphicColorDepth;   
	/// ������������ ���������� ��������� ��������, ������������ ������������ �� ������
	CK_ULONG wMaxVirtualSize;    
}; 

struct SWYX_DISPLAY_ARGUMENTS
{
	/// ����-��� ������������� �������. 1 ������� - 5 ������. 0 - ����� ����������
	CK_BYTE swyxDisplayTimeout;
	/// ����� ��� ����������� �� ������ ����������� � ��������� UTF8 ������ �� 5 �� 400 ��������
	CK_UTF8CHAR_PTR text;
	/// ����� ������
	CK_ULONG textLength;
};

#endif //JC_CONTROL_H