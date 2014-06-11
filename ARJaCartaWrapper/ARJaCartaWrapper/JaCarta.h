//
// Created by Alexey Rogatkin on 10.06.14.
//

#import <Foundation/Foundation.h>
#import "Extensions.h"

@interface JaCarta : NSObject

+ (CK_RV) initializeLibrary;

+ (CK_RV) finalizeLibrary;

+ (CK_RV) generateRandomWithSession: (CK_SESSION_HANDLE) session
                               data: (CK_BYTE_PTR) data
                             length: (CK_ULONG) length;
@end