//
// Created by Alexey Rogatkin on 10.06.14.
//

#import "JaCarta.h"

@implementation JaCarta

+ (CK_RV)initializeLibrary
{
#if TARGET_IPHONE_SIMULATOR
    return CKR_OK;
#else
    return C_Initialize (NULL);
#endif
}

+ (CK_RV)finalizeLibrary
{
#if TARGET_IPHONE_SIMULATOR
    return CKR_OK;
#else
    return C_Finalize (NULL);
#endif
}

+ (CK_RV)generateRandomWithSession:(CK_SESSION_HANDLE)session
                              data:(CK_BYTE_PTR)data
                            length:(CK_ULONG)length
{
#if TARGET_IPHONE_SIMULATOR
    return CKR_OK;
#else
    return C_GenerateRandom (session, data, length);
#endif
}

@end