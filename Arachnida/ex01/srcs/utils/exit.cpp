#include "../../inc/spider.h"

int exit_failure(t_data *data) {
    delete data;
    return 1;
}

int exit_success(t_data *data) {
    delete data;
    return 0;
}