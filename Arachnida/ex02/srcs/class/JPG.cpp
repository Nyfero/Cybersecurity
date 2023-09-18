
    char c = 0;
    while(file.read(buf, 2)) {
        std::cout << "buf: " << std::hex << (int)buf[0] << std::endl;
        std::cout << "buf: " << std::hex << (int)buf[1] << std::endl;

        if (buf[0] == '\xFF' && buf[1] == '\xE1') {
            std::cout << "perfect match" << std::endl;
            return 0;
        }
        else if (c == '\xFF' && buf[0] == '\xE1') {
            std::cout << "match" << std::endl;
            return 0;
        }
        else {
            std::cout << "no match" << std::endl;
            c = buf[1];
        }

    }