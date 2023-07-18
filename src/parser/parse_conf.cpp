#include "../config.hpp"
#include "parser.hpp"
#include <stack>
using namespace greensql;

struct Location
{
    const char *code;
    std::string path;
    std::string file;
    unsigned line;
    Location(const char * c, const char *p, const char *f, unsigned u)
    {code = c; path = p; file = p; line = u}

};
static std::stack<Location> files;
void get_parse_location(const char *&file, unsigned line)
{
    if(files.empty())
    {
        file = nullptr;
        line = 0;
        return;
    }
    Location& loc = files.top();
    file = loc.file.c_str();
    line = loc.line;
}