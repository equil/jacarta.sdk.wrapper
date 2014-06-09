#ifndef JC_CONTROL_H
#define JC_CONTROL_H
#include "pkcs11t.h"

/*! \typedef C_JCCTRL
* \brief Указатель на метод, позволяющий выполнять операции со SWYX-считывателем
* \param slotID - идентификатор(номер) слота. Все слота можно получить с помощью C_GetSlotList
* \param operation - код операции (см. #C_JCCTRL_OPERATION_CODES)
* \param pData - указатель на массив байт в который будут записаны выходные данные, или сообщение для отображения(в случае операции #JC_CTRL_SWYX_DISPLAY) 
* Для конкретного значения параметра в контексте каждой операции см. описание структуры #C_JCCTRL_OPERATION_CODES
* \param ulDataLen - указатель на длину массива с выходными или входными (в случае операции #JC_CTRL_SWYX_DISPLAY) данными
* Для конкретного значения параметра в контексте каждой операции см. описание структуры #C_JCCTRL_OPERATION_CODES
* \return код операции в терминах PKCS11
**/
extern "C"
{
	CK_RV C_jcCtrl(CK_ULONG slotId, CK_ULONG operation, CK_BYTE_PTR pData, CK_ULONG_PTR ulDataLen);
}

// коды операций для метода jc_ctrl
enum C_JCCTRL_OPERATION_CODES
{
	/// Получить свойства SWYX-считывателя. Аргументы #C_JCCTRL: в pData  будут записаны свойства в виде структуры #_SWYX_PROPERTIES_RESPONSE (байты идут в little endian), 
	/// ulDataLen будет содержать размер структуры со свойствами (должно быть 12 байт)
	JC_CTRL_GET_PROPERTIES = 0, 
	/// Включить SWYX-режим.  Аргументы pData и ulDataLen в #C_JCCTRL не используются 
	JC_CTRL_SWYX_START = 1,
	/// Выключить SWYX-режим и получить лог + подпись.  Аргументы #C_JCCTRL: в pData будет записан лог в формате xml + 64 байта подписи в конце,
	/// ulDataLen будет содержать суммарный размер лога и подписи
	JC_CTRL_SWYX_STOP = 2,
	/// Отобразить текст на экране SWYX-считывателя и предложить пользователю подписать его. Аргументы #C_JCCTRL: в
	/// pData должен содержать структуру #SWYX_DISPLAY_ARGUMENTS, ulDataLen - размер этой структуры.
	/// В случае если пользователь отменит операцию подписи, метод C_JCCTRL вернет CKR_FUNCTION_REJECTED (0x00000200),
	/// в случае тайм-аута - CKR_FUNCTION_CANCELED (0x00000050)
	JC_CTRL_SWYX_DISPLAY = 3,
	/// Сгенерировать новую ключевую пару на SWYX-считывателе. Аргументы pData и ulDataLen в #C_JCCTRL не используются.
	/// В случае, если пользователь отменит операцию метод C_JCCTRL вернет CKR_FUNCTION_REJECTED (0x00000200)
	JC_CTRL_PERSONALIZE = 4,
	/// Получить открытый ключ SWYX-считывателя. Аргументы #C_JCCTRL: pData - должен содержать открытый ключ, ulDataLen - размер этого ключа (должно быть 64 байта)
	JC_CTRL_ENROLL = 5,
	/// Получить серийный номер апплета, находящегося внутри SWYX-считывателя. Аргументы #C_JCCTRL: pData должен содержать серийный номер, ulDataLen - его длину (должно быть 8 байт)
	JC_CTRL_SWYX_GET_APPLET_SN = 6,
	/// Запросить ПИН-код пользователя. Аргументы pData и ulDataLen в #C_JCCTRL не используется.  В случае, если пользователь отменит операцию,
	/// метод #C_JCCTRL вернет CKR_FUNCTION_REJECTED (0x00000200), в случае таймаута ввода (30 секунд) - CKR_FUNCTION_CANCELED (0x00000050)
	JC_CTRL_PIN_VERIFY = 7
};

/// Свойства SWYX-считывателя
struct SWYX_PROPERTIES_RESPONSE
{
	/// Тип экрана. 0 - только текст, 1 - графический
	CK_BYTE bDisplayType;
	/// Максимальное количество символов, помещающихся в одну строчку на экране
	CK_ULONG wLcdMaxCharacters;
	/// Максимальное количество строк
	CK_ULONG wLcdMaxLines;
	/// Ширина экрана в точках
	CK_ULONG wGraphicMaxWidth;
	/// Высота экрана в точках
	CK_ULONG wGraphicMaxHeight;
	/// Цветность экрана. 1 - черно-белый, 2 - градации серого (4 бита), 4 - цветной (4 бита)
	CK_BYTE bGraphicColorDepth;   
	/// Максимальное количество буквенных символов, одновременно помещающихся на экране
	CK_ULONG wMaxVirtualSize;    
}; 

struct SWYX_DISPLAY_ARGUMENTS
{
	/// тайм-аут подтверждения подписи. 1 единица - 5 секунд. 0 - ждать бесконечно
	CK_BYTE swyxDisplayTimeout;
	/// текст для отображения на экране считывателя в кодировке UTF8 длиной от 5 до 400 символов
	CK_UTF8CHAR_PTR text;
	/// длина текста
	CK_ULONG textLength;
};

#endif //JC_CONTROL_H