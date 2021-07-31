#include "R2.hpp"
#include <algorithm>
#include <iostream>
using namespace std;

//splits string ignores repeated delim chars
std::list<std::string> split_to_list(const std::string input, char delim)
{
    std::stringstream ss(input);
    std::list<std::string> split;
    while( ss.good() )
    {
        string substr;
        getline( ss, substr, delim );
        if(substr != "")
            split.push_back( substr );
    }
    return split;
}

//splits string ignores repeated delim chars
std::list<int> split_to_int_list(const std::string input, char delim)
{
    std::stringstream ss(input);
    std::list<int> split;
    while( ss.good() )
    {
        string substr;
        getline( ss, substr, delim );
        if(substr != "")
            split.push_back( stoi(substr) );
    }
    return split;
}

// trim from start 
void ltrim(std::string &s) 
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end 
void rtrim(std::string &s) 
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) 
    {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends 
void trim(std::string &s) 
{
    ltrim(s);
    rtrim(s);
}


std::string split_and_remove(std::string &input, char delim)
{
    size_t pos = input.find(delim);
    string result(input, 0, pos);
    input.erase(0,pos + 1);
    //ltrim(input);
    return result;
}

int Database_R2::parcing(std::string request, std::list<std::pair<Cell*, std::array<int, 2>>> &result)
{

    list<string> split_request = split_to_list(request, ' ');


    string command = split_request.front();
    split_request.pop_front();

    if(command == "SELECT")
    {
        std::list<std::string> teachers, courses;
        std::list<int> times ,rooms, groups;
        for(string field_and_data : split_request)
        {
            string field = split_and_remove(field_and_data, '=');
            string data = field_and_data;
            
            if (_fields_in_bd.find(field) == _fields_in_bd.end())
            {
                continue;
                // throw exeption  
            }
            if(field == "teacher")
            {
                teachers.merge(split_to_list(data, ','));
            }
            
            if(field == "course")
            {
                courses.merge(split_to_list(data, ','));
            }

            if(field == "room")
            {
                rooms.merge((split_to_int_list(data, ',')));
            }

            if(field == "time")
            {
                times.merge((split_to_int_list(data, ',')));
            }
            
            if(field == "group")
            {
                groups.merge((split_to_int_list(data, ',')));
            }
            
        }
        _database.SELECT(result, teachers, courses, times, rooms, groups );
        return 0;
    }
    if(command == "ADD")
    {
        string teacher, course;
        int time, room, group;
        for(string field_and_data : split_request)
        {
            string field = split_and_remove(field_and_data, '=');
            string data = field_and_data;

            if (_fields_in_bd.find(field) == _fields_in_bd.end())
            {
                continue;
                // throw exeption  
            }
            if(field == "teacher")
            {
                teacher = data;
            }
            
            if(field == "course")
            {
                course =data;
            }

            if(field == "room")
            {
                room = stoi(data);
            }

            if(field == "time")
            {
                try
                {
                    time  = stoi(data);
                }
                catch(std::invalid_argument)
                {

                }
            }
            
            if(field == "group")
            {
                group = stoi(data);
            }

        }
        _database.ADD(teacher, course, time, room, group);
        return 0;
    }
    if(command == "DELETE")
    {
        string teacher, course;
        int time, room, group;
        for(string field_and_data : split_request)
        {
            string field = split_and_remove(field_and_data, '=');
            string data = field_and_data;

            if (_fields_in_bd.find(field) == _fields_in_bd.end())
            {
                continue;
                // throw exeption  
            }
            if(field == "teacher")
            {
                teacher = data;
            }
            
            if(field == "course")
            {
                course =data;
            }

            if(field == "room")
            {
                room = stoi(data);
            }

            if(field == "time")
            {
                try
                {
                    time  = stoi(data);
                }
                catch(std::invalid_argument)
                {
                    
                }
            }
            
            if(field == "group")
            {
                group = stoi(data);
            }

        }
        _database.DELETE(teacher, course, time, room, group);
        return 0;
    }
}