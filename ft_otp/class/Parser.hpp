#pragma once
#include "../inc/ft_otp.hpp"

class Parser {

    private:
        // Store argv without the program name
        std::vector<std::string>    _args;
        // Store argc - 1
        size_t                      _size;
        // Store all the flags that are useable
        std::vector<std::string>    _flags;

    public:
    // Constructors
        Parser(int ac, char **av);
        ~Parser();

    // Setters
        void                        Set_flags(std::vector<std::string> flag);

    // Getters
        size_t                      Get_size() const;
        std::vector<std::string>    Get_args() const;
        std::string                 Get_args_i(size_t i) const;
        std::vector<std::string>    Get_flags() const;
        std::string                 Get_flags_i(size_t i) const;

    // Checkers
        // Check the nb of param
        int                         Check_size_is(size_t i) const;
        int                         Check_size_less_than(size_t i) const;
        int                         Check_size_greater_than(size_t i) const;
        // Check if the args aren't numbers
        int                         Check_args_char() const;
        int                         Check_args_char_i(size_t i) const;
        // Check if the args are numbers
        int                         Check_args_nb() const;
        int                         Check_args_nb_i(size_t i) const;
        // Check if the args are a files
        int                         Check_args_file() const;
        int                         Check_args_file_i(size_t i) const;
        // Check if the args are a folders
        int                         Check_args_folder() const;
        int                         Check_args_folder_i(size_t i) const;
        // Check if they are the good flags
        // int                         Check_flag_is(std::vector<std::string> tab) const;
        // int                         Check_flag_is_i(std::vector<std::string> tab, size_t i) const;

    //Throw
		class ToMuchArgsE : public std::exception {
		
            public:
			    virtual const char* what() const throw();
		};

        class NotEnoughtArgsE : public std::exception {

            public:
                virtual const char* what() const throw();
        };

        class IsNotCharE : public std::exception {
            
            public:
			    virtual const char* what() const throw();
        };

        class IsNotNumberE : public std::exception {
            
            public:
			    virtual const char* what() const throw();
        };

        class IsNotFileE : public std::exception {
            
            public:
			    virtual const char* what() const throw();
        };

        class IsNotFolderE : public std::exception {
            
            public:
			    virtual const char* what() const throw();
        };

        class BadFlagE : public std::exception {
            
            public:
			    virtual const char* what() const throw();
        };
};
