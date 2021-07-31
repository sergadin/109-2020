#pragma once
#include "matrix.hpp"
#include <sstream>
#include <set>

std::list<std::string> split_to_list(const std::string input, char delim);
std::list<int> split_to_int_list(const std::string input, char delim);
void ltrim(std::string &s);
void rtrim(std::string &s);
void trim(std::string &s) ;
std::string split_and_remove(std::string &input, char delim);

class Database_R2
{
    private:

        matrix _database;
        std::set<std::string> _fields_in_bd = {"teacher", "course", "time", "room", "group"};
    public:
    /*
    typedef enum {ADD, SELECT, DELETE, UPDATE, SORT, PRINT} Commandtype;
    typedef enum {GROUP, TEACHER, DAY, TIME, COURSE, ROOM} Field;
    typedef enum {EQUEAL, SPAN} Relation;
    */
    int parce(std::string request, std::list<std::pair<Cell*, std::array<int, 2>>> &result);


};