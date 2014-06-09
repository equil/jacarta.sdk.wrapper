#ifndef JCPKCS11_EXTENSIONS
#define JCPKCS11_EXTENSIONS

#ifdef __cplusplus
extern "C" {
#endif

#ifdef JCPKCS11_EXTENSIONS_EXPORT_FUNCTIONS
#define JCPKCS11_EXTENSIONS_EXPORT __declspec(dllexport)
#else
#define JCPKCS11_EXTENSIONS_EXPORT
#endif

#include "cryptoki.h"

#define CKR_NEED_MORE_DATA (CKR_VENDOR_DEFINED + 1)
#define CKR_CERT_SIGNATURE_INVALID (CKR_VENDOR_DEFINED + 2)

// Флаги
#define PKCS7_DETACHED_SIGNATURE		0x01 // Не включать данные в сообщение PKCS#7 подписи.
#define PKCS7_HARDWARE_HASH				0x02 // Вычислять значение хеш-функции на устройстве.
#define PKCS7_CHECK_CERT_VALIDITY		0x04 // Выполнять проверку срока действия сертификата

	/*
	Формированиe PKCS#7 сообщения типа signed data.
	Параметры:
	in session - PKCS#11 сессия.
	in	data - данные для подписи.
	in	dataLength - длина данных для подписи.
	in	signCertificate - сертификат создателя сообщения.
	out	envelope - указатель на указатель на буфер в который будет записано сообщение.
			Буфер создается внутри функции. После окончания работы с ним необходимо освободить его, вызвав функцию freeBuffer().
	out	envelopeLength - указатель на длину созданного буфера с сообщением.
	in	privateKey - закрытый ключ создателя сообщения. Может устанавливатся в 0, тогда поиск закрытого ключа будет осуществлятся по CKA_ID сертификата.
	in	certificates - указатель на массив сертификатов, которые следует добавить в сообщение.
	in	certificatesLength - количество сертификатов в параметре certificates.
	in	flags - флаги. Может принимать значение 0 или значения PKCS7_DETACHED_SIGNATURE или PKCS7_HARDWARE_HASH.
	*/
	JCPKCS11_EXTENSIONS_EXPORT CK_RV pkcs7Sign(
		CK_SESSION_HANDLE session,
		CK_BYTE_PTR data,
		CK_ULONG dataLength,
		CK_OBJECT_HANDLE signCertificate,
		CK_BYTE_PTR* envelope,
		CK_ULONG_PTR envelopeLength,
		CK_OBJECT_HANDLE privateKey,
		CK_OBJECT_HANDLE_PTR certificates,
		CK_ULONG certificatesLength,
		CK_ULONG flags);
	/*
	Проверка подписи в PKCS#7 сообщениии типа signed data. Используются программные реализации методов проверки подписи и хеширования.
	Параметры:
	in envelope - PKCS#7 сообщение.
	in envelopeLength - длина PKCS#7 сообщения.
	in data - если сообщение не содержит самих данных, то необходимо передать их в этот параметр.
	in dataLength - длина данных.
	*/
	JCPKCS11_EXTENSIONS_EXPORT CK_RV pkcs7Verify(
		CK_BYTE_PTR envelope,
		CK_ULONG envelopeLength,
		CK_BYTE_PTR data,
		CK_ULONG dataLength);


	/*
	Проверка подписи в PKCS#7 сообщениии типа signed data. Используется аппаратная реализация проверки подписи. 
	Параметры:
	in session - PKCS#11 сессия.
	in envelope - PKCS#7 сообщение.
	in envelopeLength - длина PKCS#7 сообщения.
	in data - Если сообщение не содержит данных (используется отсоединенная подпись), то необходимо передать их в этот параметр.
	in dataLength - длина данных.
	in flags - флаги. Может принимать значение 0 или PKCS7_HARDWARE_HASH.
	*/
	JCPKCS11_EXTENSIONS_EXPORT CK_RV pkcs7VerifyHW
	(
		CK_SESSION_HANDLE session,
		CK_BYTE_PTR envelope,
		CK_ULONG envelopeLength,
		CK_BYTE_PTR data,
		CK_ULONG dataLength,
		CK_ULONG flags
	);

//! \brief	Проверка подписи в PKCS#7 сообщениии типа signed data с дополнительной проверкой
//! 		на соответствие подписи ключа проверки ЭП открытому ключу доверенного сертификата. Используется аппаратная реализация проверки подписи.  
//!
//! \param	session			 	PKCS#11 сессия.
//! \param	envelope		 	PKCS#7 сообщение.
//! \param	envelopeLength   	Длина PKCS#7 сообщения.
//! \param	data			 	Если сообщение не содержит данных (используется отсоединенная подпись), то необходимо передать их в этот параметр.
//! \param	dataLength		 	Длина данных.
//! \param	trustedSigner   	Буфер с доверенным сертификатом в DER формате.
//! \param	trustedSignerLen	Длина буфера.
//! \param	flags			 	Флаги. Может принимать значение 0 или PKCS7_HARDWARE_HASH.
//!
//! \return	код результата PKCS#11
JCPKCS11_EXTENSIONS_EXPORT CK_RV pkcs7TrustedVerifyHW
	(
	CK_SESSION_HANDLE session,
	CK_BYTE_PTR envelope,
	CK_ULONG envelopeLength,
	CK_BYTE_PTR data,
	CK_ULONG dataLength,
	CK_BYTE_PTR trustedSigner,
	CK_ULONG trustedSignerLen,
	CK_ULONG flags
	);

//! \brief	Проверка подписи сертификата на соответствие ключу его подписанта. 
//! 		Проверка подписи выполняется аппаратно. Хеширование выполняется аппаратно, если 
//! 		была вызвана функция useHardwareHash(CK_TRUE).
//!
//! \param	session			 	PKCS11# сессия.
//! \param	certToCheck		 	Буфер с сертификатом в DER формате, проверка подписи по которому выполняется.
//! \param	certToCheckLength	Длина буфера.
//! \param	trustedSignerCert		 	Буфер с сертификатом доверенного подписанта проверяемого сертификата в DER формате.
//! \param	trustedSignerCertLength 	Длина буфера.
//!
//! \return	код результата PKCS#11
//! 		
JCPKCS11_EXTENSIONS_EXPORT CK_RV checkCertSignature
	(
	CK_SESSION_HANDLE session,
	CK_BYTE_PTR certToCheck,
	CK_ULONG certToCheckLength,
	CK_BYTE_PTR trustedSignerCert,
	CK_ULONG trustedSignerCertLength
	);

//! \brief	Извлечение данных и сертификата подписанта из PKCS#7 контейнера.
//!
//! \param	envelope	  	PKCS#7 контейнер.
//! \param	envelopeLength	Длина контейнера.
//! \param	signerCert	  	Буфер для записи сертификата.
//! \param	signerCertLen 	Длина буфера.
//! \param	data		  	Буфер для записи данных.
//! \param	dataLength	  	Длина буфера.
//!
//! \return	код результата PKCS#11

JCPKCS11_EXTENSIONS_EXPORT CK_RV pkcs7Parse
	(
	CK_BYTE_PTR envelope,
	CK_ULONG envelopeLength,
	CK_BYTE_PTR* signerCert,
	CK_ULONG_PTR signerCertLen,
	CK_BYTE_PTR* attachedData, 
	CK_ULONG_PTR dataLength 
	);

	/*
	Проверка пути сертификации.
	Параметры:
	in session - PKCS#11 сессия.
	in certificateToVerify - сертификат, который необходимо проверить.
	in trustedCertificates - массив доверенных сертификатов.
	in trustedCertificatesLength - количество сертификатов в trustedCertificates.
	in certificateChain - промежуточные сертификаты.
	in certificateChainLength - количество сертификатов в certificateChain.
	in crls - массив списков отозванных сертификатов.
	in crlsLengths - массив с длинами списков отозванных сертификатов.
	in crlsLength - количество списков отозванных сертификатов в clrs.
	*/
	JCPKCS11_EXTENSIONS_EXPORT CK_RV certVerify(
		CK_SESSION_HANDLE session,
		CK_OBJECT_HANDLE certificateToVerify,
		CK_OBJECT_HANDLE_PTR trustedCertificates,
		CK_ULONG trustedCertificatesLength,
		CK_OBJECT_HANDLE_PTR certificateChain,
		CK_ULONG certificateChainLength,
		CK_BYTE_PTR* crls,
		CK_ULONG_PTR crlsLengths, 
		CK_ULONG crlsLength);

	/*
	Сформировать запрос на сертификат.
	Параметры:
	in	session - PKCS#11 сессия.
	in	publicKey - открытый ключ для создания сертификата.
	in	dn - distinguished name. В параметр должен передаваться массив строк. В первой строке должен распологаться тип поля в текстовой форме, или
			OID, например, "CN". Во второй строке должно распологаться значение поля в UTF8.
			Последующие поля передаются в следующих строках. Количество строк должно быть четным.
	in	dnLength - количество строк в dn.
	out	csr - указатель на указатель на буфер в который будет записан запрос на сертификат.
			Буфер создается внутри функции. После окончания работы с ним необходимо освободить его, вызвав функцию freeBuffer().
	out	csrLength - длина буфера в который будет записан запрос на сертификат.
	in	privateKey - закрытый ключ, парный publicKey. Если значение установленно в 0, то поиск закрытого ключа будет осуществляться
		по CKA_ID открытого ключа.
	in	attributes - дополнительные атрибуты для включения в запрос. Формат аналогичен dn.
	in	attributesLength - количество строк в attributes.
	in	extensions - расширения для включения в запрос. Формат аналогичен dn.
	in	extensionsLength - количество строк в extensions.
	*/
	JCPKCS11_EXTENSIONS_EXPORT CK_RV createCSR(
		CK_SESSION_HANDLE session,
		CK_OBJECT_HANDLE publicKey,
		CK_CHAR_PTR* dn,
		CK_ULONG dnLength,
		CK_BYTE_PTR* csr,
		CK_ULONG_PTR csrLength,
		CK_OBJECT_HANDLE privateKey,
		CK_CHAR_PTR* attributes,
		CK_ULONG attributesLength,
		CK_CHAR_PTR* extensions,
		CK_ULONG extensionsLength);
	/*
	Проверить подпись в запросе на сертификат.
	Параметры:
	in	csr - запрос на сертификат.
	in  csrLength - длина запроса на сертификат
	*/
	JCPKCS11_EXTENSIONS_EXPORT CK_RV verifyReq(
		CK_BYTE_PTR csr,
		CK_ULONG csrLength);
	
	/*
	Создать сертификат из запроса.
	Параметры:
	in	session - PKCS#11 сессия.
	in	csr - запрос на сертификат.
	in  csrLength - длина запроса на сертификат
	in  privateKey - закрытый ключ издателя сетификата
	in  serial - серийный номер сертификата в строковом представлении
	in  issuerDN - distinguished name издателя сетификата. В параметр должнен переваваться массив строк. В первой строке должен распологаться тип поля в текстовой форме,
		или OID, например, "CN". Во второй строке должно распологаться значение поля в UTF8.
		Если issuerDN равно нулю, distinguished name издателя устанавливается равным distinguished namе субъекта.
	in  issuerDNLength - количество строк в issuerDN.
	in  days - срок действия сертификата в днях.
	out	certificate - указатель на указатель на буфер в который будет записан сертификат.
			Буфер создается внутри функции. После окончания работы с ним необходимо освободить его, вызвав функцию freeBuffer().
	out	certificateLength - длина буфера в который будет записан сертификат.
	*/
	JCPKCS11_EXTENSIONS_EXPORT CK_RV genCert(
		CK_SESSION_HANDLE session,
		CK_BYTE_PTR csr,
		CK_ULONG csrLength,
		CK_OBJECT_HANDLE privateKey,
		CK_CHAR_PTR serial,
		CK_CHAR_PTR* issuerDN,
		CK_ULONG issuerDNLength,
		CK_ULONG days,
		CK_BYTE_PTR* certificate,
		CK_ULONG_PTR certificateLength);

	/*
	Получить информацио о сертификате в текстовом виде.
	Параметры:
	in	session - PKCS#11 сессия.
	in	certificate - сертификат.
	out	certificateInfo - указатель на указатель на буфер в который будет записана информация о сертификате.
		Буфер создается внутри функции. После окончания работы с ним необходимо освободить его, вызвав функцию freeBuffer().
	out	certificateInfoLength - длина буфера в который будет записана информация о сертификате.
	*/
	JCPKCS11_EXTENSIONS_EXPORT CK_RV getCertificateInfo(
		CK_SESSION_HANDLE session,
		CK_OBJECT_HANDLE certificate,
		CK_CHAR_PTR* certificateInfo,
		CK_ULONG* certificateInfoLength);

	/*
	Формирование PKCS#7 сообщения типа signed data.
	Параметры:
	in session - PKCS#11 сессия.
	in	data - данные для подписи.
	in	dataLength - длина данных для подписи.
	in	signCertificate - сертификат создателя сообщения в DER кодировке (массив байт).
	in	signCertificateLength - длина signCertificate.
	out	envelope - указатель на указатель на буфер в который будет записано сообщение.
			Буфер создается внутри функции. После окончания работы с ним необходимо освободить его, вызвав функцию freeBuffer().
	out	envelopeLength - указатель на длину созданного буфера с сообщением.
	in	privateKey - закрытый ключ создателя сообщения. Может устанавливатся в 0, тогда поиск закрытого ключа будет осуществлятся по CKA_ID сертификата.
	in	certificates - указатель на массив сертификатов, которые следует добавить в сообщение.
	in	certificatesLength - количество сертификатов в параметре certificates.
	in	flags - флаги. Может принимать значение 0 и PKCS7_DETACHED_SIGNATURE.
	*/
	JCPKCS11_EXTENSIONS_EXPORT CK_RV pkcs7SignEx(
		CK_SESSION_HANDLE session,
		CK_BYTE_PTR data,
		CK_ULONG dataLength,
		CK_BYTE_PTR signCertificate,
		CK_ULONG signCertificateLength,
		CK_BYTE_PTR* envelope,
		CK_ULONG_PTR envelopeLength,
		CK_OBJECT_HANDLE privateKey,
		CK_OBJECT_HANDLE_PTR certificates,
		CK_ULONG certificatesLength,
		CK_ULONG flags);
	
	/*
	Получить информацио о сертификате в текстовом виде.
	Параметры:
	in	certificate - сертификат в DER кодировке (массив байт).
	in	certificateLength - длина certificate.
	out	certificateInfo - указатель на указатель на буфер в который будет записана информация о сертификате.
		Буфер создается внутри функции. После окончания работы с ним необходимо освободить его, вызвав функцию freeBuffer().
	out	certificateInfoLength - длина буфера в который будет записана информация о сертификате.
	*/
	JCPKCS11_EXTENSIONS_EXPORT CK_RV getCertificateInfoEx(
		CK_BYTE_PTR certificate,
		CK_ULONG certificateLength,
		CK_CHAR_PTR* certificateInfo,
		CK_ULONG* certificateInfoLength);

	/*
	Освободить буфер, выделенный в одной из других функций.
	Параметры:
	in	buffer - буфер.
	*/
	JCPKCS11_EXTENSIONS_EXPORT CK_RV freeBuffer(
		CK_BYTE_PTR buffer);

	/*
	Установить использование аппаратного вычисления значения хеш-функции в функциях расширения.
	Параметры:
	in	hardware - CK_TRUE - использовать аппаратное хеширование; CK_FALSE - использовать программное хеширование.
	*/
	JCPKCS11_EXTENSIONS_EXPORT CK_RV useHardwareHash(
		CK_BBOOL hardware);

	/*
	Начать установку ssl соединения. Функция может возвращать код CKR_NEED_MORE_DATA, если установка соединения со стороны сервера не завершена, и требуются дополнительные данные от сервера.
	Параметры:
	out	context - контекст соедиения. После окончания работы с контекстом необходимо освободить его, вызвав функцию sslCloseConnection().
	in session - PKCS#11 сессия.
	in	certificate - сертификат.
	in	privateKey - закрытый ключ.
	out	data - данные для передачи на сервер. Буфер создается внутри функции. После окончания работы с ним необходимо освободить его, вызвав функцию freeBuffer().
	out	dataLength - длина данных для передачи на сервер.
	*/
	JCPKCS11_EXTENSIONS_EXPORT CK_RV sslEstablishConnectionBegin(
		CK_VOID_PTR_PTR context,
		CK_SESSION_HANDLE session,
		CK_OBJECT_HANDLE certificate,
		CK_OBJECT_HANDLE privateKey,
		CK_BYTE_PTR* data,
		CK_ULONG_PTR dataLength);

	/*
	Продолжить установку ssl соединения. Функция может возвращать код CKR_NEED_MORE_DATA, если установка соединения со стороны сервера не завершена, и требуются дополнительные данные от сервера.
	Параметры:
	in	context - контекст соедиения.
	in	dataIn - данные от сервера.
	in	dataInLength - длина данных от сервера.
	out	dataOut - данные для передачи на сервер. Буфер создается внутри функции. После окончания работы с ним необходимо освободить его, вызвав функцию freeBuffer().
	out	dataOutLength - длина данных для передачи на сервер.
	*/
	JCPKCS11_EXTENSIONS_EXPORT CK_RV sslEstablishConnectionContinue(
		CK_VOID_PTR context,
		CK_BYTE_PTR dataIn,
		CK_ULONG dataInLength,
		CK_BYTE_PTR* dataOut,
		CK_ULONG_PTR dataOutLength);

	/*
	Получить пертификат сервера. Можно вызывать только после успешного установления соединения.
	Параметры:
	in	context - контекст соедиения.
	out	certificate - сертификат сервера. Буфер создается внутри функции. После окончания работы с ним необходимо освободить его, вызвав функцию freeBuffer().
	out	certificateLength - длина сертификата сервера.
	*/
	JCPKCS11_EXTENSIONS_EXPORT CK_RV sslGetServerCertificate(
		CK_VOID_PTR context,
		CK_BYTE_PTR* certificate,
		CK_ULONG_PTR certificateLength);

	/*
	Закодировать данные для передачи на сервер.
	Параметры:
	in	context - контекст соедиения.
	in	dataIn - данные для передачи.
	in	dataInLength - длина данных для передачи.
	out	dataOut - закодированные данные для передачи на сервер. Буфер создается внутри функции. После окончания работы с ним необходимо освободить его, вызвав функцию freeBuffer().
	out	dataOutLength - длина закодированных данных для передачи на сервер.
	*/
	JCPKCS11_EXTENSIONS_EXPORT CK_RV sslEncodeData(
		CK_VOID_PTR context,
		CK_BYTE_PTR dataIn,
		CK_ULONG dataInLength,
		CK_BYTE_PTR* dataOut,
		CK_ULONG_PTR dataOutLength);

	/*
	Раскодировать данные, пришедшие от сервера.
	Параметры:
	in	context - контекст соедиения.
	in	dataIn - данные от сервера.
	in	dataInLength - длина данных от сервера.
	out	dataOut - раскодированные данные. Буфер создается внутри функции. После окончания работы с ним необходимо освободить его, вызвав функцию freeBuffer().
	out	dataOutLength - длина раскодированных данных.
	*/
	JCPKCS11_EXTENSIONS_EXPORT CK_RV sslDecodeData(
		CK_VOID_PTR context,
		CK_BYTE_PTR dataIn,
		CK_ULONG dataInLength,
		CK_BYTE_PTR* dataOut,
		CK_ULONG_PTR dataOutLength);

	/*
	Закрыть ssl соединение
	Параметры:
	in	context - контекст соедиения.
	*/
	JCPKCS11_EXTENSIONS_EXPORT CK_RV sslCloseConnection(
		CK_VOID_PTR_PTR context);


	typedef CK_RV (*PKCS7_SIGN)(
		CK_SESSION_HANDLE session,
		CK_BYTE_PTR data,
		CK_ULONG dataLength,
		CK_OBJECT_HANDLE signCertificate,
		CK_BYTE_PTR* envelope,
		CK_ULONG_PTR envelopeLength,
		CK_OBJECT_HANDLE privateKey,
		CK_OBJECT_HANDLE_PTR certificates,
		CK_ULONG certificatesLength,
		CK_ULONG flags);

	typedef CK_RV (*PKCS7_VERIFY)(
		CK_BYTE_PTR envelope,
		CK_ULONG envelopeLength,
		CK_BYTE_PTR data,
		CK_ULONG dataLength);

	typedef CK_RV (*CERT_VERIFY)(
		CK_SESSION_HANDLE session,
		CK_OBJECT_HANDLE certificateToVerify,
		CK_OBJECT_HANDLE_PTR trustedCertificates,
		CK_ULONG trustedCertificatesLength,
		CK_OBJECT_HANDLE_PTR certificateChain,
		CK_ULONG certificateChainLength,
		CK_BYTE_PTR* crls,
		CK_ULONG_PTR crlsLengths, 
		CK_ULONG crlsLength);

	typedef CK_RV (*CREATE_CSR)(
		CK_SESSION_HANDLE session,
		CK_OBJECT_HANDLE publicKey,
		CK_CHAR_PTR* dn,
		CK_ULONG dnLength,
		CK_BYTE_PTR* csr,
		CK_ULONG_PTR csrLength,
		CK_OBJECT_HANDLE privateKey,
		CK_CHAR_PTR* attributes,
		CK_ULONG attributesLength,
		CK_CHAR_PTR* extensions,
		CK_ULONG extensionsLength);

	typedef CK_RV (*VERIFY_REQ)(
		CK_BYTE_PTR csr,
		CK_ULONG csrLength);

	typedef CK_RV (*GEN_CERT)(
		CK_SESSION_HANDLE session,
		CK_BYTE_PTR csr,
		CK_ULONG csrLength,
		CK_OBJECT_HANDLE privateKey,
		CK_CHAR_PTR serial,
		CK_CHAR_PTR* issuerDN,
		CK_ULONG issuerDNLength,
		CK_ULONG days,
		CK_BYTE_PTR* certificate,
		CK_ULONG_PTR certificateLength);

	typedef CK_RV (*GET_CERTIFICATE_INFO)(
		CK_SESSION_HANDLE session,
		CK_OBJECT_HANDLE certificate,
		CK_CHAR_PTR* certificateInfo,
		CK_ULONG* certificateInfoLength);

	typedef CK_RV (*FREE_BUFFER)(CK_BYTE_PTR buffer);

	typedef CK_RV (*USE_HARDWARE_HASH)(CK_BBOOL hardware);

	typedef	CK_RV (*SSL_ESTABLISH_CONNECTION_BEGIN)(
		CK_VOID_PTR_PTR context,
		CK_SESSION_HANDLE session,
		CK_OBJECT_HANDLE certificate,
		CK_OBJECT_HANDLE privateKey,
		CK_BYTE_PTR* data,
		CK_ULONG_PTR dataLength);

	typedef CK_RV (*SSL_ESTABLISH_CONNECTION_CONTINUE)(
		CK_VOID_PTR context,
		CK_BYTE_PTR dataIn,
		CK_ULONG dataInLength,
		CK_BYTE_PTR* dataOut,
		CK_ULONG_PTR dataOutLength);

	typedef CK_RV (*SSL_GET_SERVER_CERTIFICATE)(
		CK_VOID_PTR context,
		CK_BYTE_PTR* certificate,
		CK_ULONG_PTR certificateLength);

	typedef CK_RV (*SSL_ENCODE_DATA)(
		CK_VOID_PTR context,
		CK_BYTE_PTR dataIn,
		CK_ULONG dataInLength,
		CK_BYTE_PTR* dataOut,
		CK_ULONG_PTR dataOutLength);

	typedef CK_RV (*SSL_DECODE_DATA)(
		CK_VOID_PTR context,
		CK_BYTE_PTR dataIn,
		CK_ULONG dataInLength,
		CK_BYTE_PTR* dataOut,
		CK_ULONG_PTR dataOutLength);

	typedef CK_RV (*SSL_CLOSE_CONNECTION)(
		CK_VOID_PTR_PTR context);

	typedef CK_RV (*PKSC7_TRUSTED_VERIFY_HW)
		(
		CK_SESSION_HANDLE session,
		CK_BYTE_PTR envelope,
		CK_ULONG envelopeLength,
		CK_BYTE_PTR data,
		CK_ULONG dataLength,
		CK_BYTE_PTR trustedSigner,
		CK_ULONG trustedSignerLen,
		CK_ULONG flags
		);


	typedef CK_RV (*CHECK_CERT_SIGNATURE)
		(
		CK_SESSION_HANDLE session,
		CK_BYTE_PTR certToCheck,
		CK_ULONG certToCheckLength,
		CK_BYTE_PTR trustedSignerCert,
		CK_ULONG trustedSignerCertLength
		);

	typedef CK_RV (*PKCS7_PARSE)
		(
		CK_BYTE_PTR envelope,
		CK_ULONG envelopeLength,
		CK_BYTE_PTR* signerCert,
		CK_ULONG_PTR signerCertLen,
		CK_BYTE_PTR* attachedData, 
		CK_ULONG_PTR dataLength 
		);


#ifdef __cplusplus
}
#endif

#endif

