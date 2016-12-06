/**
 *
 * @author hungnv
 */
#ifndef EXAMPLE_H
#define EXAMPLE_H

#define EXAMPLE_VERSION "0.1"

#ifdef ZTS
#include "TSRM.h"
#endif
#pragma once 

typedef struct {
    char* a_value;
    zend_object std;
} example_t;


extern zend_module_entry example_module_entry;
#define phpext_fiftyonedegrees_ptr &example_module_entry;


#if defined(ZTS) && defined(COMPILE_DL_EXAMPLE)
ZEND_TSRMLS_CACHE_EXTERN();
#endif

#endif

