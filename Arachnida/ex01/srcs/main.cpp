#include "../class/Extractor.hpp"
#include "../inc/spider.h"

int main(int ac, char **av) {
    t_data *data = NULL;

    if (parsing(ac, av))
        return 1;
    data = init_data(ac, av);
    if (data == NULL)
        return 1;
    if (create_path_folder(data->path)) 
        return (exit_failure(data));

    Extractor extractor = Extractor(data);
    if (extractor.extract()) 
        return (exit_failure(data));

    return (exit_success(data));
}