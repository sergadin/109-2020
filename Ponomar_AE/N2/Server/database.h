#ifndef DATABASE
#define DATABASE

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

#define WORKLOAD_TYPES 4
#define HIERARCHY_CLASSES 6

// Пусть есть 4 вида нагрузки по предмету: лекции, семинары, коллоквиумы, экзамены.
class course
{
public:
	std::string course_name;
	std::vector<int> course_hours; // { Лекции, Семинары, Коллоквиумы, Экзамены }
	course(std::string course_name, std::vector<int> course_hours)
	{
		this->course_name = course_name;
		this->course_hours = course_hours;
	}
};

class staff
{
public:
	staff() {}
	std::string name;
	std::vector<int> course_indexes;                                   // Пусть есть 6 классов иерархии:
	std::vector<int> hierarchy_code; // { Факультет (№ ), Кафедра (№ ), Заведующий?(0/1), Профессор? (0/1), Доцент?(0/1), Преподаватель? (0/1) }
	bool compare_hierarchy(std::vector<int> hc);
	// Service functions to check hierarchy_code
	bool only_faculty(std::vector<int> hc);
	bool faculty_dept(std::vector<int> hc);
};



class database
{
private:
	std::vector<std::string> work_loads = { "Лекции", "Семинары", "Коллоквиумы", "Экзамены" }; // Виды часов нагрузки: фиксированный "массив"
	std::vector<course> courses; // "Массив" учебных курсов, на который будут ссылаться индексы у преподавателя в графе course_indexes
	std::vector<staff> v_staff; // Сотрудники структуры
	// Service functions
	std::vector<std::string> split_by_space(std::string s);
	std::string get_info_row(staff s);
	// Service map
	std::map<std::string, std::vector<std::string>> prev_request; // For subcols
public:
	database() {}
	void add_course(course c);
	course get_course(int index);

	void set_courses(std::vector<course> vc);
	std::vector<course> get_courses();

	void add_staff(staff s);
	staff get_staff(int index);

	std::string handle_request(std::string request);
};



class database_error : public std::exception
{
private:
	std::string error_msg;
public:
	database_error(std::string error_msg) { this->error_msg = error_msg; }
	const char* what() const noexcept override { return error_msg.c_str(); }
};

#endif//DATABASE
