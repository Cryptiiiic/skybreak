//
//  common.h
//  skybreak
//
//  Created by Cryptic on 2/16/19.
//  Copyright © 2019 Cryptic. All rights reserved.
//

#ifndef common_h
#define common_h

#define KERN_LOG(success_msg, error_msg, port, return) \
    if(return == KERN_SUCCESS) \
        printf(""success_msg": port: 0x%X\n", port); \
    else \
    { \
        printf("Error: "error_msg": return: %d\n", return); \
        return -1; \
    }

#endif /* common_h */
