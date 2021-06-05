#pragma once

#include <string>
#include <array>
#include <list>
#include <map>
#include <vector>
#include <unordered_map>
#include <set>
#include <sstream>
#include <algorithm>
#include <iostream>

std::list<std::string> split_to_list(const std::string input, char delim);
std::list<int> split_to_int_list(const std::string input, char delim);
void ltrim(std::string &s);
void rtrim(std::string &s);
void trim(std::string &s) ;
std::string split_and_remove(std::string &input, char delim);


#define N_OFF_CLASSES 6*8 // общее количестов пар 6 учебный дней по 8 пар в каждом
#define N_OF_ROOMS 1000 // общее количестов пар 6 учебный дней по 8 пар в каждом

#define time(day, class) (day + class) 
/*
class Database_R2
{
    private:

        matrix database;

    public:
        typedef enum {ADD, SELECT, DELETE, UPDATE, SORT, PRINT} Commandtype;
        typedef enum {GROUP, TEACHER, DAY, TIME, COURSE, ROOM} Field;
        typedef enum {EQUEAL, SPAN} Relation;
};
*/
class Cell
{
    private:
        std::string _teacher;
        std::string _course;
        int _group_number;
    public:
        Cell() = default;
        Cell(std::string teacher, std::string course, int group_number)
        {
            _teacher = teacher;
            _course = course;
            _group_number = group_number;
        }



        std::string & get_teacher()
        {return _teacher;}
        std::string & get_course()
        {return _course;}
        int& get_group()
        {return _group_number;}

        bool operator==(const Cell that);
        bool operator!=(const Cell that);

        friend class Database_R2;


};

class Database_R2
{
    private:

        std::array<std::array<Cell,N_OF_ROOMS>, N_OFF_CLASSES> _table; 

        std::unordered_map<std::string, std::list<std::array<int,2>>> _teachers;
        std::unordered_map<std::string, std::list<std::array<int,2>>> _courses;

    public:

        std::set<std::string> _fields_in_bd = {"teacher", "course", "time", "room", "group"};

        Database_R2() = default;
        Database_R2(Database_R2 & that)= default;
        ~Database_R2()= default;
        
        

        int read_file(std::string name = "R2_data.txt");
        int to_file(std::string name = "R2_data.txt");
        int parce(std::string request, std::list<std::pair<Cell*, std::array<int, 2>>> &result);

        int ADD(std::string teacher, std::string course = "", int time = -1,int room = -1, int group = -1);
        int DELETE(std::string teacher = "", std::string course = "", int time = -1,int room = -1, int group = -1);
        //int UPDATE(std::string teaher = "", std::string course = "", int time = -1,int room = -1, int group = -1);
        int SELECT(std::list<std::pair<Cell*, std::array<int, 2>>> & result, const std::list<std::string> &teachers,const std::list<std::string> &courses,const std::list<int> &times , const std::list<int> &rooms, const std::list<int> &groups, bool emplty = false );
        //std::list<Cell> RESELECT(std::string teaher = '', std::string course = '', int time = -1,int room = -1, int group = -1,)
};

