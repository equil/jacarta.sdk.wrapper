#ifndef JCPKCS11V_EXTENSIONS
#define JCPKCS11V_EXTENSIONS

#ifdef __cplusplus
extern "C" {
#endif

#ifdef JCPKCS11V_EXTENSIONS_EXPORT_FUNCTIONS
#define JCPKCS11V_EXTENSIONS_EXPORT __declspec(dllexport)
#else
#define JCPKCS11V_EXTENSIONS_EXPORT
#endif


#include "cryptoki.h"

	
	//! \brief Предварительный просмотр документа и формирование PKCS#7 сообщения типа signed data.
	//! Параметры:
	//! \param in session - PKCS#11 сессия.
	//! \param in	data - данные для подписи.
	//! \param in	dataLength - длина данных для подписи.
	//! \param in	signCertificate - сертификат создателя сообщения.
	//! \param out	envelope - указатель на указатель на буфер в который будет записано сообщение.
	//!		Буфер создается внутри функции. После окончания работы с ним необходимо освободить его, вызвав функцию freeBuffer().
	//! \param out	envelopeLength - указатель на длину созданного буфера с сообщением.
	//! \param in	privateKey - закрытый ключ создателя сообщения. Может устанавливаться в 0, тогда поиск закрытого ключа будет осуществляться по CKA_ID сертификата.
	//! \param in	certificates - указатель на массив сертификатов, которые следует добавить в сообщение.
	//! \param in	certificatesLength - количество сертификатов в параметре certificates.
	//! \param in	flags - флаги. Может принимать значение 0 или значения PKCS7_DETACHED_SIGNATURE или PKCS7_HARDWARE_HASH.
	//! \param in  extension - строковый параметр, содержит расширение для определения типа данных (например "txt", "html", "doc", "xls" ... ) 
	//! \return	код результата PKCS#11

	JCPKCS11V_EXTENSIONS_EXPORT CK_RV pkcs7ShowAndSign(
		CK_SESSION_HANDLE session,
		CK_BYTE_PTR data,
		CK_ULONG dataLength,
		CK_OBJECT_HANDLE signCertificate,
		CK_BYTE_PTR* envelope,
		CK_ULONG_PTR envelopeLength,
		CK_OBJECT_HANDLE privateKey,
		CK_OBJECT_HANDLE_PTR certificates,
		CK_ULONG certificatesLength,
		CK_ULONG flags,
		CK_BYTE_PTR extension);



	
	//! \brief Предварительный просмотр документа и проверка подписи в PKCS#7 сообщении типа signed data
	//!Параметры:
	//! \param in session - PKCS#11 сессия.
	//! \param in envelope - PKCS#7 сообщение.
	//! \param in envelopeLength - длина PKCS#7 сообщения.
	//! \param in data - если сообщение не содержит самих данных, то необходимо передать их в этот параметр.
	//! \param in dataLength - длина данных.
	//! \param in trustedSigner   	Буфер с доверенным сертификатом в DER формате.
	//! \param in trustedSignerLen	Длина буфера.
	//! \param in flags			 	Флаги. Может принимать значение 0 или PKCS7_HARDWARE_HASH.
	//! \param in extension - строковый параметр, содержит расширение для определения типа данных ("txt", "html", "doc", "xls" ... ) 
	//! \return	код результата PKCS#11
	
	JCPKCS11V_EXTENSIONS_EXPORT CK_RV pkcs7ShowAndVerify(
		CK_SESSION_HANDLE session,
		CK_BYTE_PTR envelope,
		CK_ULONG envelopeLength,
		CK_BYTE_PTR data,
		CK_ULONG dataLength,
		CK_BYTE_PTR trustedSigner,
		CK_ULONG	trustedSignerLen,
		CK_ULONG flags,
		CK_BYTE_PTR extension);


	typedef CK_RV (*PKCS7_SHOW_AND_SIGN)(
		CK_SESSION_HANDLE session,
		CK_BYTE_PTR data,
		CK_ULONG dataLength,
		CK_OBJECT_HANDLE signCertificate,
		CK_BYTE_PTR* envelope,
		CK_ULONG_PTR envelopeLength,
		CK_OBJECT_HANDLE privateKey,
		CK_OBJECT_HANDLE_PTR certificates,
		CK_ULONG certificatesLength,
		CK_ULONG flags,
		CK_BYTE_PTR extension);

	typedef CK_RV (*PKCS7_SHOW_AND_VERIFY)(
		CK_SESSION_HANDLE session,
		CK_BYTE_PTR envelope,
		CK_ULONG envelopeLength,
		CK_BYTE_PTR data,
		CK_ULONG dataLength,
		CK_BYTE_PTR trustedSigner,
		CK_ULONG trustedSignerLen,
		CK_ULONG flags,
		CK_BYTE_PTR extension);

#ifdef __cplusplus
}
#endif

#endif

