#ifndef __IClient_Ia_HPP__
#define __IClient_Ia_HPP__
#include "ICommand.hpp"
#include "IPrioritie.hpp"
#include <map>
#include <vector>
#include <tuple>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <algorithm>

    class IClient_Ia
    {
        private :
        std::map<std::string, std::unique_ptr<ICommand>> Allcommand;
        std::map<std::string, std::unique_ptr<IPrioritie>> AllPriority;
        std::pair< std::map<std::string, std::unique_ptr<ICommand>>, std::map<std::string, std::unique_ptr<ICommand>> > IA;
        public :
};

#endif