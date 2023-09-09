#include "../../class/Extractor.hpp"

Extractor::Extractor(t_data *data) : _first_url(data->url), _url(data->url), _depth(data->depth), _path(data->path) {
    std::cout << "Extractor constructor called" << std::endl;
}

Extractor::Extractor(std::string first_url ,std::string url, int depth, std::string path) : _first_url(first_url), _url(url), _depth(depth), _path(path) {
        std::cout << "Extractor constructor called" << std::endl;
        std::cout << this->_url << std::endl;
}

Extractor::~Extractor() {
    std::cout << "Extractor destructor called" << std::endl;
}

int Extractor::extract() {
    std::cout << "Extractor extract called" << std::endl;
    if (extract_page() || extract_images() || extract_links())
        return 1;
    // if (download_images())
    //     return 1;
    if (_depth == 0)
        return 0;
    if (recursive_extract())
        return 1;
    
    return 0;
}

int Extractor::extract_page() {
    std::cout << "Extractor extract_page called" << std::endl;
    std::string cmd = "curl -o \"" + _path + "/page\" \"" + _url + "\"";
    if (system(cmd.c_str()))
        return 1;
    return 0;
}

int Extractor::extract_images() {
    std::cout << "Extractor extract_images called" << std::endl;
    std::string cmd = "grep -o '<img[^>]*>' " + _path + "/page | grep -o 'src=\"[^\"]*\\.\\(jpg\\|jpeg\\|png\\|gif\\|bmp\\)\"' | sort | uniq > " + _path + "/images";
    if (system(cmd.c_str()))
        return 1;
    return 0;
}

int Extractor::extract_links() {
    std::cout << "Extractor extract_links called" << std::endl;
    std::string cmd = "grep -o '<a[^>]*>' " + _path + "/page | grep -o 'href=\"[^\"]*\"' | sort | uniq > " + _path + "/links";
    if (system(cmd.c_str()))
        return 1;
    return 0;
}

int Extractor::download_images() {
    std::cout << "Extractor download_images called" << std::endl;
    std::ifstream file(_path + "/images");
    std::string line;
    std::string url;
    std::string img_name;
    std::string cmd;

    if (!file.is_open())
        return 1;

    while (std::getline(file, line)) {

        url = line.substr(5, line.size() - 6);
        for (size_t i = 0; i < url.size(); i++)
            if (url[i] == ' ')
                url.replace(i, 1, "%20");
        if (url.find("http") == std::string::npos)
            url = _url + url;
        
        img_name = line.substr(5, line.size() - 6);
        for (size_t i = 0; i < img_name.size(); i++)
            if (img_name[i] == '/' || img_name[i] == ' ')
                img_name.replace(i, 1, "_");

        cmd = "curl -s -o \"" + _path + "/" + img_name + "\" \"" + url + "\"";
        std::cout << cmd << std::endl;
        if (system(cmd.c_str()))
            return 1;
    }
    return 0;
}

// un truc du genre
int Extractor::recursive_extract() {
    std::cout << "Extractor recursive_extract called" << std::endl;
    std::ifstream file(_path + "/links");
    std::string line;
    std::string url;

    if (!file.is_open())
        return 1;

    while (std::getline(file, line)) {
        url = line.substr(6, line.size() - 7);
        std::cout << line << std::endl;

        for (size_t i = 0; i < url.size(); i++)
            if (url[i] == ' ')
                url.replace(i, 1, "%20");
        if (url.find("http") == std::string::npos)
            url = _first_url + url;

        Extractor extractor = Extractor(this->_first_url, url, _depth - 1, _path);
        if (extractor.extract())
            return 1;

    }
    return 0;
}