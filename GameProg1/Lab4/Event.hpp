#ifndef HPP_EVENT
#define HPP_EVENT

#include <string>
#include "Subject.hpp"

class Subject;

struct Event 
{
    Event(Subject&, std::string const& type);

    Subject& source;
    std::string type;
};

#endif HPP_EVENT