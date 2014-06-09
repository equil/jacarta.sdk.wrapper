//
// Created by Alexey Rogatkin on 10.06.14.
//

#import <Foundation/Foundation.h>
#import "Extensions.h"

@interface JaCarta : NSObject

+ (CK_RV) initializeLibrary;

+ (CK_RV) finalizeLibrary;

@end