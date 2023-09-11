#include "../../class/Extractor.hpp"

Extractor::Extractor(t_data *data) : _first_url(data->url), _url(data->url), _depth(data->depth), _path(data->path) {}

Extractor::Extractor(std::string first_url ,std::string url, int depth, std::string path) : _first_url(first_url), _url(url), _depth(depth), _path(path) {}

Extractor::~Extractor() {}

int Extractor::extract() {
    if (extract_page() || extract_images() || extract_links())
        return 1;
    std::string cmd = "rm -f " + _path + "/page" + std::to_string(_depth);
    system(cmd.c_str());
    if (this->_url.find_last_of('/') != this->_url.size() - 1)
        this->_url.erase(this->_url.find_last_of('/') + 1);
    if (download_images())
        return 1;
    if (_depth == 0) {
        cmd = "rm -f " + _path + "/links" + std::to_string(_depth);
        system(cmd.c_str());
        return 0;
    }
    if (recursive_extract())
        return 1;
    
    return 0;
}

int Extractor::extract_page() {
    std::string pagefile = _path + "/page" + std::to_string(_depth);
    std::string cmd = "curl -s -o \"" + pagefile + "\" \"" + _url + "\"";
    std::cout << "\e[93mDownloading images from: " << _url << "\e[39m" << std::endl;
    if (system(cmd.c_str()))
        return 1;
    return 0;
}

int Extractor::extract_images() {
    std::string pagefile = _path + "/page" + std::to_string(_depth);
    std::string imagesfile = _path + "/images" + std::to_string(_depth);
    std::string cmd = "grep -o '<img[^>]*>' " + pagefile + " | grep -o 'src=\"[^\"]*\\.\\(jpg\\|jpeg\\|png\\|gif\\|bmp\\)\"' | sort | uniq > " + imagesfile;
    if (system(cmd.c_str()))
        return 1;
    return 0;
}

int Extractor::extract_links() {
    std::string pagefile = _path + "/page" + std::to_string(_depth);
    std::string linksfile = _path + "/links" + std::to_string(_depth);
    std::string cmd = "grep -o '<a[^>]*>' " + pagefile + " | grep -o 'href=\"[^\"]*\"' | sort | uniq > " + linksfile;
    if (system(cmd.c_str()))
        return 1;
    return 0;
}

int Extractor::download_images() {
    std::ifstream file(_path + "/images" + std::to_string(_depth));
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
        img_name = _url + img_name;
        for (size_t i = 0; i < img_name.size(); i++)
            if (img_name[i] == '/')
                img_name.replace(i--, 1, "");


        cmd = "curl -s -o \"" + _path + "/" + img_name + "\" \"" + url + "\"";
        std::cout << cmd << std::endl;
        system(cmd.c_str());
    }
    cmd = "rm -f " + _path + "/images" + std::to_string(_depth);
    system(cmd.c_str());
    return 0;
}

// un truc du genre
int Extractor::recursive_extract() {
    std::ifstream file(_path + "/links" + std::to_string(_depth));
    std::string line;
    std::string url;

    if (!file.is_open())
        return 1;

    while (std::getline(file, line)) {
        if (line.find_first_of("#") == std::string::npos) {

            url = line.substr(6, line.size() - 7);

            for (size_t i = 0; i < url.size(); i++)
                if (url[i] == ' ')
                    url.replace(i, 1, "%20");
            if (url.find("http") == std::string::npos)
                url = _first_url + url;

            Extractor extractor = Extractor(this->_first_url, url, _depth - 1, _path);
            if (extractor.extract())
                return 1;
        }
    }
    std::string cmd = "rm -f " + _path + "/links" + std::to_string(_depth);
    system(cmd.c_str());
    return 0;
}