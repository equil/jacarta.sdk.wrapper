//
// Created by Alexey Rogatkin on 10.06.14.
//

#import "JaCarta.h"

void iR301SetTimeout() {

}

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

@end