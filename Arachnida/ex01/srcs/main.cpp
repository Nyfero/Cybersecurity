#include "../class/Extractor.hpp"

int main(int ac, char **av) {
    t_data *data = NULL;

    if (parsing(ac, av))
        return 1;
    data = init_data(ac, av);
    if (data == NULL)
        return 1;
    if (create_path_folder(data->path)) {
        delete data;
        return 1;
    }

    Extractor extractor = Extractor(data->url, data->depth, data->path);
    if (extractor->extract()) {
        delete data;
        return 1;    
    }

    delete data;
    return 0;
}