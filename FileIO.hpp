//
//  FileIO.hpp
//  OpenGL
//
//  Created by Andrew Diggs on 8/21/22.
//

#ifndef FileIO_hpp
#define FileIO_hpp

#include <stdio.h>
#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <sstream>


class Valid{
private:
    std::string m_dig = "[[:digit:]]+";
    std::string m_float = "[[:digit:]]+\\.[[:digit:]]+";
    std::string m_space = "[[:blank:]]";
    std::string m_exp_float = "[[:digit:]]+\\.[[:digit:]]+e\\+[[:digit:]]+";
    std::string m_comment = "#.*";
    
    bool match(std::string input, std::string m_type);
    
public:
    Valid();
    ~Valid();
    bool match_int(std::string input);
    bool match_float(std::string input);
    bool match_space(std::string input);
    bool match_comment(std::string input);
    
    
    int get_int(std::string int_str);
    float get_float(std::string fl_str);
    
};

bool ITEM(std::string str, std::string reg_ex);










#endif /* FileIO_hpp */
