//
// Created by Alexey Rogatkin on 10.06.14.
//

#import "JaCarta.h"

@implementation JaCarta

+ (CK_RV)initializeLibrary:(CK_VOID_PTR)args
{
#if TARGET_IPHONE_SIMULATOR
    return CKR_OK;
#else
    return C_Initialize (args);
#endif
}

+ (CK_RV)finalizeLibrary:(CK_VOID_PTR)reserved
{
#if TARGET_IPHONE_SIMULATOR
    return CKR_OK;
#else
    return C_Finalize (reserved);
#endif
}

+ (CK_RV)generateRandomInSession:(CK_SESSION_HANDLE)session
                            data:(CK_BYTE_PTR)data
                          length:(CK_ULONG)length
{
#if TARGET_IPHONE_SIMULATOR
    return CKR_OK;
#else
    return C_GenerateRandom (session, data, length);
#endif
}

+ (CK_RV)getSlotInfoForSlotId:(CK_SLOT_ID)slotID
                  infoPointer:(CK_SLOT_INFO_PTR)infoPointer
{
#if TARGET_IPHONE_SIMULATOR
    return CKR_OK;
#else
    return C_GetSlotInfo (slotID, infoPointer);
#endif
}

+ (CK_RV)getTokenInfoForSlotId:(CK_SLOT_ID)slotId
                   infoPointer:(CK_TOKEN_INFO_PTR)infoPointer
{
#if TARGET_IPHONE_SIMULATOR
    return CKR_OK;
#else
    return C_GetTokenInfo (slotId, infoPointer);
#endif
}

+ (CK_RV)initPINInSession:(CK_SESSION_HANDLE)session
                      pin:(CK_UTF8CHAR_PTR)pin
                pinLength:(CK_ULONG)pinLength
{
#if TARGET_IPHONE_SIMULATOR
    return CKR_OK;
#else
    return C_InitPIN (session, pin, pinLength);
#endif
}

+ (CK_RV)initTokenForSlotId:(CK_SLOT_ID)slotId
                        pin:(CK_UTF8CHAR_PTR)pin
                  pinLength:(CK_ULONG)pinLength
                      label:(CK_UTF8CHAR_PTR)label
{
#if TARGET_IPHONE_SIMULATOR
    return CKR_OK;
#else
    return C_InitToken (slotId, pin, pinLength, label);
#endif
}

+ (CK_RV)createObjectInSession:(CK_SESSION_HANDLE)session
               templatePointer:(CK_ATTRIBUTE_PTR)templatePointer
                         count:(CK_ULONG)count
                        object:(CK_OBJECT_HANDLE_PTR)objectPointer
{
#if TARGET_IPHONE_SIMULATOR
    return CKR_OK;
#else
    return C_CreateObject (session, templatePointer, count, objectPointer);
#endif
}

+ (CK_RV)destroyObjectInSession:(CK_SESSION_HANDLE)session
                         object:(CK_OBJECT_HANDLE)object
{
#if TARGET_IPHONE_SIMULATOR
    return CKR_OK;
#else
    return C_DestroyObject (session, object);
#endif
}

+ (CK_RV)findObjectsInitInSession:(CK_SESSION_HANDLE)session
                  templatePointer:(CK_ATTRIBUTE_PTR)templatePointer
                            count:(CK_ULONG)count
{
#if TARGET_IPHONE_SIMULATOR
    return CKR_OK;
#else
    return C_FindObjectsInit (session, templatePointer, count);
#endif
}

+ (CK_RV)findObjectsInSession:(CK_SESSION_HANDLE)session
                objectPointer:(CK_OBJECT_HANDLE_PTR)objectsPointer
              maxObjectsCount:(CK_ULONG)maxObjectsCount
           pulledObjectsCount:(CK_ULONG_PTR)pulledObjectsCount
{
#if TARGET_IPHONE_SIMULATOR
    return CKR_OK;
#else
    return C_FindObjects (session, objectsPointer, maxObjectsCount, pulledObjectsCount);
#endif
}

+ (CK_RV)findObjectsFinalInSession:(CK_SESSION_HANDLE)session
{
#if TARGET_IPHONE_SIMULATOR
    return CKR_OK;
#else
    return C_FindObjectsFinal (session);
#endif
}

+ (CK_RV)getAttributeValueInSession:(CK_SESSION_HANDLE)session
                             object:(CK_OBJECT_HANDLE)object
                    templatePointer:(CK_ATTRIBUTE_PTR)templatePointer
                              count:(CK_ULONG)count
{
#if TARGET_IPHONE_SIMULATOR
    return CKR_OK;
#else
    return C_GetAttributeValue (session, object, templatePointer, count);
#endif
}

+ (CK_RV)setAttributeValueInSession:(CK_SESSION_HANDLE)session
                             object:(CK_OBJECT_HANDLE)object
                    templatePointer:(CK_ATTRIBUTE_PTR)templatePointer
                              count:(CK_ULONG)count
{
#if TARGET_IPHONE_SIMULATOR
    return CKR_OK;
#else
    return C_SetAttributeValue (session, object, templatePointer, count);
#endif
}

+ (CK_RV)loginInSession:(CK_SESSION_HANDLE)session
               userType:(CK_USER_TYPE)userType
                    pin:(CK_UTF8CHAR_PTR)pin
              pinLength:(CK_ULONG)pinLength
{
#if TARGET_IPHONE_SIMULATOR
    return CKR_OK;
#else
    return C_Login (session, userType, pin, pinLength);
#endif
}

+ (CK_RV)logoutFromSession:(CK_SESSION_HANDLE)session
{
#if TARGET_IPHONE_SIMULATOR
    return CKR_OK;
#else
    return C_Logout (session);
#endif
}

+ (CK_RV)closeSession:(CK_SESSION_HANDLE)session
{
#if TARGET_IPHONE_SIMULATOR
    return CKR_OK;
#else
    return C_CloseSession (session);
#endif
}

+ (CK_RV)openSessionForSlotId:(CK_SLOT_ID)slotId
                        flags:(CK_FLAGS)flags
                  application:(CK_VOID_PTR)application
                       notify:(CK_NOTIFY)notify
                      session:(CK_SESSION_HANDLE_PTR)session
{
#if TARGET_IPHONE_SIMULATOR
    return CKR_OK;
#else
    return C_OpenSession (slotId, flags, application, notify, session);
#endif
}

+ (CK_RV)waitForSlotEventWithFlags:(CK_FLAGS)flags
                     slotIdPointer:(CK_SLOT_ID_PTR)slotIdPointer
                           rserved:(CK_VOID_PTR)reserved
{
#if TARGET_IPHONE_SIMULATOR
    return CKR_OK;
#else
    return C_WaitForSlotEvent (flags, slotIdPointer, reserved);
#endif
}

@end