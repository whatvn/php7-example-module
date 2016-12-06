/**
 *
 * @author hungnv
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "php_globals.h"
#include "ext/standard/info.h"
#include "ext/standard/basic_functions.h"
#include "example.h"
#include "zend_exceptions.h"
#include "zend_interfaces.h"

static zend_object_handlers example_obj_handlers;
static zend_class_entry *example_ce;

static inline example_t* example_obj_fetch(zend_object* obj) {
    return (example_t*) ((char*) (obj) - XtOffsetOf(example_t, std));
}
#define Z_EXAMLE_P(zv) example_obj_fetch(Z_OBJ_P((zv)))


static inline zend_object* example_obj_new(zend_class_entry *ce) {
    example_t* example;
    example = ecalloc(1, sizeof (example_t) + zend_object_properties_size(ce));
    zend_object_std_init(&example->std, ce);
    object_properties_init(&example->std, ce);
    example->std.handlers = &example_obj_handlers;
    return &example->std;
}

static void example_obj_free(zend_object *object) {
    example_t* example;
    example = example_obj_fetch(object);
    if (!example) {
        return;
    }
    zend_object_std_dtor(&example->std TSRMLS_CC);
    efree(example);
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_example_none, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_example_one, 0, 0, 1)
ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()


typedef size_t strlen_t;

PHP_MINFO_FUNCTION(example) {
    php_info_print_table_start();
    php_info_print_table_header(2, "example support", "enabled");
    php_info_print_table_row(2, "example module version", EXAMPLE_VERSION);
    php_info_print_table_row(2, "author", "hungnv");
    php_info_print_table_end();
    DISPLAY_INI_ENTRIES();
}

PHP_METHOD(example, __construct) {

    char* value;
    strlen_t len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &value, &len) == FAILURE) {
        RETURN_FALSE;
    }
    return_value = getThis();
    example_t* example;
    example = Z_EXAMLE_P(return_value);
    example->a_value = value;
}

PHP_METHOD(example, get) {
    example_t* example;
    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_FALSE;
    }
    example = Z_EXAMLE_P(getThis());
    ZVAL_STRING(return_value, (char*) example->a_value);
}

zend_function_entry example_methods[] = {
    PHP_ME(example, __construct, arginfo_example_one, ZEND_ACC_CTOR | ZEND_ACC_PUBLIC)
    PHP_ME(example, get, arginfo_example_none, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

PHP_MINIT_FUNCTION(example) {

    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "example", example_methods);
    example_ce = zend_register_internal_class(&ce TSRMLS_CC);
    example_ce->create_object = example_obj_new;
    memcpy(&example_obj_handlers, zend_get_std_object_handlers(), sizeof (example_obj_handlers));
    example_obj_handlers.offset = XtOffsetOf(example_t, std);
    example_obj_handlers.free_obj = example_obj_free;

    return SUCCESS;

}

PHP_RINIT_FUNCTION(example) {
#if defined(COMPILE_DL_EXAMPLE) && defined(ZTS)
    ZEND_TSRMLS_CACHE_UPDATE();
#endif
    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(example) {
    return SUCCESS;
}

zend_module_entry example_module_entry = {
    STANDARD_MODULE_HEADER,
    "example",
    NULL,
    PHP_MINIT(example),
    PHP_MSHUTDOWN(example),
    PHP_RINIT(example),
    NULL,
    PHP_MINFO(example),
    EXAMPLE_VERSION,
    STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(example)