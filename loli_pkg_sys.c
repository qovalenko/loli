
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "loli.h"
#include "loli_vm.h"

const char *loli_sys_info_table[] = {
    "\0\0"
    ,"F\0getenv\0(String): Option[String]"
    ,"F\0recursion_limit\0: Integer"
    ,"F\0set_recursion_limit\0(Integer)"
    ,"R\0argv\0List[String]"
    ,"Z"
};
void loli_sys__getenv(loli_state *);
void loli_sys__recursion_limit(loli_state *);
void loli_sys__set_recursion_limit(loli_state *);
void loli_sys_var_argv(loli_state *);
loli_call_entry_func loli_sys_call_table[] = {
    NULL,
    loli_sys__getenv,
    loli_sys__recursion_limit,
    loli_sys__set_recursion_limit,
    loli_sys_var_argv,
};

void loli_sys_var_argv(loli_state *s)
{
    loli_config *config = loli_config_get(s);
    int opt_argc = config->argc;
    char **opt_argv = config->argv;
    loli_container_val *lv = loli_push_list(s, opt_argc);

    int i;
    for (i = 0;i < opt_argc;i++) {
        loli_push_string(s, opt_argv[i]);
        loli_con_set_from_stack(s, lv, i);
    }
}

void loli_sys__getenv(loli_state *s)
{
    char *env = getenv(loli_arg_string_raw(s, 0));

    if (env) {
        loli_container_val *variant = loli_push_some(s);
        loli_push_string(s, env);
        loli_con_set_from_stack(s, variant, 0);
        loli_return_top(s);
    }
    else
        loli_return_none(s);
}

void loli_sys__recursion_limit(loli_state *s)
{
    loli_return_integer(s, s->depth_max);
}

void loli_sys__set_recursion_limit(loli_state *s)
{
    int64_t limit = loli_arg_integer(s, 0);

    if (limit < 1 || limit > INT32_MAX)
        loli_ValueError(s, "Limit value (%ld) is not reasonable.", limit);

    if (limit < s->call_depth)
        loli_ValueError(s,
            "Limit value (%ld) is lower than the current recursion depth.",
            limit);

    s->depth_max = (int32_t)limit;
    loli_return_unit(s);
}
