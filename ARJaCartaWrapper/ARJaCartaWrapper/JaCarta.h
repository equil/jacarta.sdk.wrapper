//
// Created by Alexey Rogatkin on 10.06.14.
//

#import <Foundation/Foundation.h>
#import "Extensions.h"

@interface JaCarta : NSObject

+ (CK_RV)initializeLibrary;

+ (CK_RV)finalizeLibrary;

+ (CK_RV)generateRandomInSession:(CK_SESSION_HANDLE)session
                            data:(CK_BYTE_PTR)data
                          length:(CK_ULONG)length;

+ (CK_RV)getSlotInfoForSlotId:(CK_SLOT_ID)slotID
                  infoPointer:(CK_SLOT_INFO_PTR)infoPointer;

+ (CK_RV)getTokenInfoForSlotId:(CK_SLOT_ID)slotId
                   infoPointer:(CK_TOKEN_INFO_PTR)infoPointer;

+ (CK_RV)initPINInSession:(CK_SESSION_HANDLE)session
                      pin:(CK_UTF8CHAR_PTR)pin
                pinLength:(CK_ULONG)pinLength;

+ (CK_RV)initTokenForSlotId:(CK_SLOT_ID)slotId
                        pin:(CK_UTF8CHAR_PTR)pin
                  pinLength:(CK_ULONG)pinLength
                      label:(CK_UTF8CHAR_PTR)label;

+ (CK_RV)createObjectInSession:(CK_SESSION_HANDLE)session
               templatePointer:(CK_ATTRIBUTE_PTR)templatePointer
                         count:(CK_ULONG)count
                        object:(CK_OBJECT_HANDLE_PTR)objectPointer;

+ (CK_RV)destroyObjectInSession:(CK_SESSION_HANDLE)session
                         object:(CK_OBJECT_HANDLE)object;

+ (CK_RV)findObjectsInitInSession:(CK_SESSION_HANDLE)session
                  templatePointer:(CK_ATTRIBUTE_PTR)templatePointer
                            count:(CK_ULONG)count;

+ (CK_RV)findObjectsInSession:(CK_SESSION_HANDLE)session
                objectPointer:(CK_OBJECT_HANDLE_PTR)objectsPointer
              maxObjectsCount:(CK_ULONG)maxObjectsCount
           pulledObjectsCount:(CK_ULONG_PTR)pulledObjectsCount;

+ (CK_RV)findObjectsFinalInSession:(CK_SESSION_HANDLE)session;

+ (CK_RV)getAttributeValueInSession:(CK_SESSION_HANDLE)session
                             object:(CK_OBJECT_HANDLE)object
                    templatePointer:(CK_ATTRIBUTE_PTR)templatePointer
                              count:(CK_ULONG)count;

+ (CK_RV)setAttributeValueInSession:(CK_SESSION_HANDLE)session
                             object:(CK_OBJECT_HANDLE)object
                    templatePointer:(CK_ATTRIBUTE_PTR)templatePointer
                              count:(CK_ULONG)count;

+ (CK_RV)loginInSession:(CK_SESSION_HANDLE)session
               userType:(CK_USER_TYPE)userType
                    pin:(CK_UTF8CHAR_PTR)pin
              pinLength:(CK_ULONG)pinLength;

+ (CK_RV)logoutFromSession:(CK_SESSION_HANDLE)session;

+ (CK_RV)closeSession:(CK_SESSION_HANDLE)session;

+ (CK_RV)openSessionForSlotId:(CK_SLOT_ID)slotId
                        flags:(CK_FLAGS)flags
               sessionPointer:(CK_SESSION_HANDLE_PTR)sessionPointer;

+ (CK_RV)waitForSlotEventWithFlags:(CK_FLAGS)flags
                     slotIdPointer:(CK_SLOT_ID_PTR)slotIdPointer;
@end