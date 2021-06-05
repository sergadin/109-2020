
#include <iostream>
#include <utility>
#include <fstream>
#include "R2.hpp"
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


bool Cell::operator==(const Cell that)
{
    if((that._course == this->_course) && (that._group_number == this->_group_number) && (that._teacher == this->_teacher))
    {
        return true;
    }
    return false;
}

bool Cell::operator!=(const Cell that)
{
    if((that._course != this->_course) && (that._group_number != this->_group_number) && (that._teacher != this->_teacher))
    {
        return true;
    }
    return false;
}
int Database_R2::ADD(std::string teacher, std::string course, int time, int room, int group)
{
    if((room > N_OF_ROOMS - 1) || (time >N_OFF_CLASSES - 1))
        return -1;

    if(_table[time][room] == Cell())
    {
        
        _table[time][room] = Cell(teacher, course, group);
    }
    else
    {
        return -2;
    }
    array<int,2> coordinates = {time, room};
    _teachers[teacher].push_back(coordinates);
    _courses[course].push_back(coordinates);
    
    return 0;
}

int Database_R2::DELETE(std::string teacher, std::string course, int time,int room, int group )
{
    if((room > N_OF_ROOMS - 1) || (time >N_OFF_CLASSES - 1))
        return -1;

    //Cell *d_cell;
    if(_table[time][room] != Cell())
    {
        //d_cell = &_table[time][room];
        _table[time][room] = Cell();
    }
    else
    {
        return -2;
    }

    bool teacher_deleted = false; //flag to show that teacher was compleatly deleted from _teachers
    if( _teachers[teacher].size() ==1)
    {
        teacher_deleted = true;
        _teachers.erase(teacher);
    }

    bool course_deleted = false;
    if( _courses[course].size() ==1)
    {
        course_deleted = true;
        _courses.erase(course);
    }

    if(!teacher_deleted)
    array<int,2> coordinates = {time, room};
        array<int,2> coordinates = {time, room};
        _teachers[teacher].remove(coordinates);
    
    if(!course_deleted)
        array<int,2> coordinates = {time, room};
        _courses[course].remove(coordinates);

    return 0;
}


int comp(const std::array<int, 2> &a, const std::array<int, 2> &b )
{
    return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
}


int Database_R2::SELECT(std::list<std::pair<Cell*, std::array<int, 2>>> & result, const std::list<std::string> &teachers,const std::list<std::string> &courses,const std::list<int> &times , const std::list<int> &rooms, const std::list<int> &groups )
{
    if((!teachers.empty()) || (!courses.empty()) || (!times.empty()) || (!rooms.empty()))
    {
        if((teachers.size() == 0) && (courses.size() == 0) )
        {
            if((!times.empty())&&(!rooms.empty()))
            {
                for(const int room :rooms)
                {
                    for(const int  time : times)
                    {
                        bool ok_group = true;
                        if(!groups.empty())
                        {
                            for(int group :groups)
                            {
                                if(_table[time][room]._group_number == group )
                                    ok_group = true;
                            }
                        }
                        else
                            ok_group = true;

                        //adding to result if fields match
                        if(ok_group)
                        {
                            array<int,2> coordinates = {time, room};
                            result.push_back(make_pair(&_table[time][room],coordinates));
                        }

                    }
                }
                return 0;
            }
            if(!times.empty())
            {
                for(const int time : times)
                {
                    int room = 0;
                    for( Cell &cell : _table[time])
                    {

                        bool ok_group = true;
                        if(!groups.empty())
                        {
                            for(int group :groups)
                            {
                                if(cell._group_number == group )
                                    ok_group = true;
                            }
                        }
                        else
                            ok_group = true;

                        if(ok_group)
                        {
                            array<int,2> coordinates = {time, room};
                            result.push_back(make_pair(&cell,coordinates));
                        }
                        room++;
                    }
                }
                return 0;
            }

            if(!rooms.empty())
            {
                for(const int room : rooms)
                {
                    int time = 0;
                    while(time < N_OFF_CLASSES)
                    {
                        bool ok_group = true;
                        if(!groups.empty())
                        {
                            for(int group :groups)
                            {
                                if(_table[time][room]._group_number == group )
                                    ok_group = true;
                            }
                        }
                        else
                            ok_group = true;

                        if(ok_group)
                        {
                            array<int,2> coordinates = {time, room};
                            result.push_back(make_pair(&_table[time][room],coordinates));
                        }
                        time++;
                    }
                }
                return 0;
            }
        }
        list<std::array<int, 2>> res_coordinates;
        list<std::array<int, 2>> teacher_coordinates;
        list<std::array<int, 2>> course_coordinates;
        list<std::array<int, 2>> room_time;

        if(teachers.size() > 0)
        {
            for(string teacher : teachers)
            {
                try
                {
                    for(array<int, 2> coord : _teachers.at(teacher) )
                    {
                        teacher_coordinates.push_back(coord);
                    }
                }
                catch(std::out_of_range)
                {
                    return -1;
                }
            }
        }

        if(courses.size() > 0)
        {
            for(string course : courses)
            {
                try
                {
                    for(array<int, 2> coord : _courses.at(course) )
                    {
                        course_coordinates.push_back(coord);
                    }
                }
                catch(std::out_of_range)
                {
                    return -1;
                }
            }
        }


        for(const int time : times)
        {
            if(time > N_OFF_CLASSES)
            {
                return -1;
            }
            for(const array<int, 2> coord : teacher_coordinates)
            {
                if(find(times.begin(), times.end(), time) == times.end())
                {
                    teacher_coordinates.remove(coord);
                }
            }
        }

        for(const int room : rooms)
        {
            if(room > N_OF_ROOMS)
            {
                return -1;
            }
            for(const array<int, 2> coord : teacher_coordinates)
            {
                if(find(times.begin(), times.end(), room) == times.end())
                {
                    teacher_coordinates.remove(coord);
                }
            }
        }


        if(teacher_coordinates.empty())
        {
            for(array<int, 2> coord : course_coordinates)
            {
                result.push_back(make_pair(&_table[coord[0]][coord[1]],coord));
            }
        }

        if(course_coordinates.empty())
        {
            for(array<int, 2> coord : teacher_coordinates)
            {
                result.push_back(make_pair(&_table[coord[0]][coord[1]],coord));
            }
        }
        teacher_coordinates.sort(&comp);
        course_coordinates.sort(&comp);

        std::set_intersection(teacher_coordinates.begin(), teacher_coordinates.end(), course_coordinates.begin(), course_coordinates.end(), std::back_inserter(res_coordinates) );


        for(array<int, 2> coord : res_coordinates)
        {
            bool ok_group = true;
            if(!groups.empty())
            {
                for(int group :groups)
                {
                    if(_table[coord[0]][coord[1]]._group_number == group )
                        ok_group = true;
                }
            }
            else
                ok_group = true;

            //adding to result if fields match
            if(ok_group)
            {
                result.push_back(make_pair(&_table[coord[0]][coord[1]],coord));
                return 0;
            }
        }
    }
    else
    {
        for(int time = 0; time < N_OFF_CLASSES; time++)
        {
            for(int room = 0; room < N_OF_ROOMS; room++ )
            {
                bool ok_group = true;
                if(!groups.empty())
                {
                    for(int group :groups)
                    {
                        if(_table[time][room]._group_number == group )
                            ok_group = true;
                    }
                }
                else
                    ok_group = true;

                //adding to result if fields match
                if(ok_group)
                {
                    array<int,2> coordinates = {time, room};
                    result.push_back(make_pair(&_table[time][room],coordinates));
                }
            }
        }
        return 0;
    }


    return 0;
    /*
    if((!times.empty())&&(!rooms.empty()))
    {
        for(const int room :rooms)
        {
            for(const int  time : times)
            {
                //cheaking if fileds match reaquevested
                bool ok_teacher = false;
                if(!teachers.empty())
                {
                    for(string teacher :teachers)
                    {
                        if(_table[time][room]._teacher == teacher )
                            ok_teacher = true;
                    }
                }
                else
                    ok_teacher = true;
                
                bool ok_course = false;
                if(!courses.empty())
                {
                    for(string course :courses)
                    {
                        if(_table[time][room]._course == course )
                            ok_course = true;
                    }
                }
                else
                    ok_course = true;
                
                bool ok_group = false;
                if(!groups.empty())
                {
                    for(int group :groups)
                    {
                        if(_table[time][room]._group_number == group )
                            ok_group = true;
                    }
                }
                else
                    ok_group = true;

                //adding to result if fields match
                if((ok_course)&&(ok_teacher)&&(ok_group))
                {
                    array<int,2> coordinates = {time, room};
                    result.push_back(make_pair(&_table[time][room],coordinates));
                }

            }
        }
    }
    */
}

// returns 0 if sucsesfull, -1 if file is not open -2 if wrong format
int Database_R2::read_file(string name)
{
    fstream file;
    file.open(name, fstream::in);
    std::list<std::pair<Cell*, std::array<int, 2>>> result;
    if(!file.is_open())
    {
        return -1;
    }

    for( std::string line; getline( file, line ); )
    {
        if (parce("ADD " +line, result) != 0)
        {
            return -2;
        }
    }
    return 0;
}
/*
int Database_R2::to_file(string name)
{
    fstream file;
    file.open(name, fstream::out);
    std::list<std::pair<Cell*, std::array<int, 2>>> result;
    if(!file.is_open())
    {
        return -1;
    }

    for(const auto &teacher : _teachers)
    {
        for(Cell* Cell : teacher.second)
        {
        file <<"time: "<< data.second[0] <<" room: " <<data.second[1] << " teacher: " << data.first->get_teacher() << " course: " << data.first->get_course() << << endl;
        }
    }

}*/




int Database_R2::parce(std::string request, std::list<std::pair<Cell*, std::array<int, 2>>> &result)
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
        SELECT(result, teachers, courses, times, rooms, groups );
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
        ADD(teacher, course, time, room, group);
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
        DELETE(teacher, course, time, room, group);
        return 0;
    }
}