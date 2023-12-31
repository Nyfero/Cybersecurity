#ifndef EXTRACTOR_HPP_
#define EXTRACTOR_HPP_
# include "../inc/spider.h"

class Extractor {
    
    private:

        // the url to add to the links
        const std::string _first_url;

        // the url to extractor from
        std::string _url;

        // the depth of the search
        int _depth;

        // the path to store the data
        std::string _path;


    public:
        Extractor(t_data *data);
        Extractor(std::string first_url, std::string url, int depth, std::string path);
        ~Extractor();

        int extract();
        int extract_page();
        int extract_images();
        int extract_links();
        int download_images();
        int recursive_extract();
};

#endif /* !EXTRACTOR_HPP_ */