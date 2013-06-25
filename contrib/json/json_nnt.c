
#include "config.h"
#include "json.h"
#include "json_object_private.h"

#include <stdlib.h>
#include <string.h>

size_t json_object_get_string_len(json_object* jso)
{
    if(!jso) return NULL;
    switch(jso->o_type) {
        case json_type_string:
            return strlen((char const*)jso->o.c_string);
        default: {
            char const* obj = json_object_to_json_string(jso);
            size_t ret = (size_t)strlen(obj);
            free((void*)obj);
            return ret;
        } break;
    }
    return 0;
}