#include "database.h"

void database::add_course(course c)
{
	courses.push_back(c);
}

course database::get_course(int index)
{
	if (index >= static_cast<int>(courses.size()))
	{
		throw database_error("Error: incorrect course index.");
	}
	return courses[index];
}

std::vector<course> database::get_courses()
{
	return courses;
}

void database::set_courses(std::vector<course> v_c)
{
	courses = v_c;
}

void database::add_staff(staff s)
{
	v_staff.push_back(s);
}

staff database::get_staff(int index)
{
	if (index >= static_cast<int>(v_staff.size()))
	{
		throw database_error("Error: incorrect staff index.");
	}
	return v_staff[index];
}

bool staff::only_faculty(std::vector<int> hc)
{
	if (hc[0] != 0)
	{
		for (int i = 1; i < static_cast<int>(HIERARCHY_CLASSES); ++i)
		{
			if (hc[i] != 0)
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

bool staff::faculty_dept(std::vector<int> hc)
{
	if (hc[0] != 0 && hc[1] != 0)
	{
		for (int i = 2; i < static_cast<int>(HIERARCHY_CLASSES); ++i)
		{
			return false;
		}
		return true;
	}
	return false;
}

bool staff::compare_hierarchy(std::vector<int> hc)
{
	if (only_faculty(hc) == true)
	{
		if (hc[0] == hierarchy_code[0])
		{
			return true;
		}
	}
	else if (faculty_dept(hc) == true)
	{
		if (hc[0] == hierarchy_code[0] && hc[1] == hierarchy_code[1])
		{
			return true;
		}
	}
	else
	{
		for (int i = 0; i < static_cast<int>(HIERARCHY_CLASSES); ++i)
		{
			if (hc[i] != hierarchy_code[i])
			{
				return false;
			}
		}
		return true;
	}
}

std::vector<std::string> database::split_by_space(std::string src)
{
	std::vector<std::string> res_v;
	std::string curr_piece = "";
	for (size_t i = 0; i < src.size(); ++i)
	{
		if (src[i] == ' ')
		{
			res_v.push_back(curr_piece);
			curr_piece = "";
		}
		else
		{
			curr_piece += src[i];
		}
	}
	res_v.push_back(curr_piece);
	return res_v;
}

std::string database::get_info_row(staff s)
{
	std::vector<int> workload = { 0,0,0,0 }; // Лекции Семинары Коллоквиумы Экзамены
	for (size_t i = 0; i < s.course_indexes.size(); ++i)
	{
		for (int j = 0; j < static_cast<int>(WORKLOAD_TYPES); ++j)
		{
			workload[j] += courses[s.course_indexes[i]].course_hours[j];
		}
	}
	int sum_hrs = 0; for (int i = 0; i < static_cast<int>(WORKLOAD_TYPES); ++i) sum_hrs += workload[i];
	workload.push_back(static_cast<int>(WORKLOAD_TYPES)); // Sum load hours
	std::stringstream info_ss;
	info_ss << s.name;
	for (int i = 0; i < static_cast<int>(WORKLOAD_TYPES) + 1; ++i) info_ss << " " << workload[i];
	for (int i = 0; i < static_cast<int>(HIERARCHY_CLASSES); ++i)
	{
		info_ss << " " << s.hierarchy_code[i];
	}
	return info_ss.str();
}

std::string database::handle_request(std::string request)
{
	if (request.find("add_course") != std::string::npos)
	{
		std::vector<std::string> request_vector = split_by_space(request);
		std::vector<int> course_hrs; for (int i = 0; i < static_cast<int>(WORKLOAD_TYPES); ++i) course_hrs.push_back(std::stoi(request_vector[2 + i]));
		courses.push_back(course(request_vector[1], course_hrs));
	}
	else if (request.find("add_staff") != std::string::npos)
	{
		// add_staff Name Ncourses H1 ... H6 C1 ... C6
		std::vector<std::string> request_vector = split_by_space(request);
		std::string name = request_vector[1];
		int course_number = std::stoi(request_vector[2]);
		std::vector<int> hierarchy_code;
		std::vector<int> courses;
		for (int i = 0; i < static_cast<int>(HIERARCHY_CLASSES); ++i)
		{
			hierarchy_code.push_back(std::stoi(request_vector[3 + i]));
		}
		for (int i = 0; i < course_number; ++i)
		{
			courses.push_back(std::stoi(request_vector[9 + i]));
		}
		staff s;
		s.name = name; s.course_indexes = courses; s.hierarchy_code = hierarchy_code;
		v_staff.push_back(s);
	}
	else if (request.find("delete_staff") != std::string::npos)
	{
		std::string delete_name = (split_by_space(request))[1];
		for (size_t i = 0; i < v_staff.size(); ++i)
		{
			if (v_staff[i].name == delete_name)
			{
				v_staff.erase(v_staff.begin() + i);
				return "Ok";
			}
		}
		return "Cannot delete: no such staff in database.";
	}
	else if (request.find("delete_course") != std::string::npos)
	{
		std::string delete_course = (split_by_space(request))[1];
		for (size_t i = 0; i < courses.size(); ++i)
		{
			if (courses[i].course_name == delete_course)
			{
				courses.erase(courses.begin() + i);
				return "Ok";
			}
		}
		return "Cannot delete: no such course in database.";
	}
	else if (request.find("get_full_database") != std::string::npos)
	{
		std::stringstream database_ss;
		database_ss << courses.size() << "\n";
		for (size_t i = 0; i < courses.size(); ++i)
		{
			database_ss << courses[i].course_name << " " << courses[i].course_hours[0] << " " << courses[i].course_hours[1] << " ";
			database_ss << courses[i].course_hours[2] << " " << courses[i].course_hours[3] << "\n";
		}
		database_ss << v_staff.size() << "\n";
		for (size_t i = 0; i < v_staff.size(); ++i)
		{
			database_ss << v_staff[i].name;
			database_ss << " " << v_staff[i].course_indexes.size();
			for (int j = 0; j < static_cast<int>(HIERARCHY_CLASSES); ++j) database_ss << " " << v_staff[i].hierarchy_code[j];
			for (size_t j = 0; j < v_staff[i].course_indexes.size(); ++j)
			{
				database_ss << " " << v_staff[i].course_indexes[j];
			}
			database_ss << "\n";
		}
		return database_ss.str();
	}
	else if (request.find("save") != std::string::npos)
	{
		std::string filename = (split_by_space(request))[1];
		std::ofstream output_file;
		output_file.open(filename);
		if (!output_file.is_open())
		{
			throw database_error("Failed to save database: cannot open file.");
		}
		output_file << handle_request("get_full_database");
		output_file.close();
	}
	else if (request.find("get_course") != std::string::npos)
	{
		std::string crs_name = (split_by_space(request))[1];
		std::stringstream course_ss;
		bool found_flag = false;
		for (size_t i = 0; i < courses.size(); ++i)
		{
			if (courses[i].course_name == crs_name)
			{
				found_flag = true;
				course_ss << crs_name;
				for (int j = 0; j < static_cast<int>(WORKLOAD_TYPES); ++j)
				{
					course_ss << "       " << courses[i].course_hours[j];
				}
			}
		}
		if (found_flag == true)
		{
			std::stringstream res_s; res_s << "Course Name   Lectures   Seminars   Colloqiums   Exams" << std::endl;
			res_s << course_ss.str();
			return res_s.str();
		}
		return "Sorry: No such course in database :(";
	}
	else if (request.find("get_staff") != std::string::npos)
	{
		std::string staff_name = (split_by_space(request))[1];
		std::stringstream staff_ss;
		bool found_flag = false;
		for (size_t i = 0; i < v_staff.size(); ++i)
		{
			if (v_staff[i].name == staff_name)
			{
				found_flag = true;
				staff_ss << staff_name;
				staff_ss << v_staff[i].course_indexes.size();
				for (int j = 0; j < static_cast<int>(HIERARCHY_CLASSES); ++j)
				{
					staff_ss << "    " << v_staff[i].hierarchy_code[j];
				}
				for (int j = 0; j < static_cast<int>(v_staff[i].course_indexes.size()); ++j)
				{
					staff_ss << "    " << v_staff[i].course_indexes[j];
				}
			}
		}
		if (found_flag == true)
		{
			std::stringstream res_s; res_s << "Name  Courses Number  Faculty  Dept  Director?  Proffessor?  Docent?  Tutor?  >> Courses" << std::endl;
			res_s << staff_ss.str();
			return res_s.str();
		}
		return "Sorry: No such staff in database :(";
	}
	else if (request.find("print") != std::string::npos)
	{
		std::stringstream db_ss;
		db_ss << "Course Name   Lectures    Seminars    Colloqiums    Exams" << std::endl;
		for (size_t i = 0; i < courses.size(); ++i)
		{
			db_ss << courses[i].course_name;
			for (int j = 0; j < static_cast<int>(WORKLOAD_TYPES); ++j)
			{
				db_ss << " " << courses[i].course_hours[j];
			}
			db_ss << std::endl;
		}
		db_ss << std::endl;
		db_ss << "Name  Courses  Faculty  Dept  Director?  Proffessor?  Docent?  Tutor?  >>Courses" << std::endl;
		for (size_t i = 0; i < v_staff.size(); ++i)
		{
			db_ss << v_staff[i].name;
			db_ss << " " << v_staff[i].course_indexes.size();
			for (int j = 0; j < static_cast<int>(HIERARCHY_CLASSES); ++j)
			{
				db_ss << " " << v_staff[i].hierarchy_code[j];
			}
			for (size_t j = 0; j < v_staff[i].course_indexes.size(); ++j)
			{
				db_ss << " " << v_staff[i].course_indexes[j];
			}
			db_ss << std::endl;
		}
		return db_ss.str();
	}
	else if (request.find("update_course") != std::string::npos)
	{
		std::vector<std::string> request_vector = split_by_space(request);
		std::string name = request_vector[1];
		std::stringstream req, req_; req << "delete_course " << name;
		handle_request(req.str());
		req_ << "add_course " << name;
		for (int i = 0; i < static_cast<int>(WORKLOAD_TYPES); ++i) req_ << " " << request_vector[2 + i];
		handle_request(req_.str());
	}
	else if (request.find("update_staff") != std::string::npos)
	{
		std::vector<std::string> request_vector = split_by_space(request);
		std::string name = request_vector[1];
		std::stringstream req, req_; req << "delete_staff " << name;
		handle_request(req.str());
		req_ << "add_staff " << name << " " << request_vector[2];
		for (int i = 0; i < static_cast<int>(HIERARCHY_CLASSES); ++i)
		{
			req_ << " " << request_vector[3 + i];
		}
		for (int i = 0; i < std::stoi(request_vector[2]); ++i)
		{
			req_ << " " << request_vector[9 + i];
		}
		handle_request(req_.str());
	}
	else if (request.find("columns") != std::string::npos)
	{
		std::vector<std::string> request_vector = split_by_space(request);
		std::vector<std::string> requested_cols;
		size_t i = 1;
		// Getting requested columns
		while (request_vector[i] != "for_all")
		{
			requested_cols.push_back(request_vector[i]);
			i++;
		}
		i++;
		std::vector<int> hierarchy_code;
		for (int j = 0; j < static_cast<int>(HIERARCHY_CLASSES); ++j)
		{
			hierarchy_code.push_back(std::stoi(request_vector[i + j]));
		}
		std::vector<std::string> staff_info;
		for (size_t j = 0; j < v_staff.size(); ++j)
		{
			if (v_staff[j].compare_hierarchy(hierarchy_code) == true)
			{
				staff_info.push_back(get_info_row(v_staff[j]));
			}
		}
		std::vector<std::string> names, lects, sems, colloqs, exams, totals, hc_s;
		for (size_t i = 0; i < staff_info.size(); ++i)
		{
			std::vector<std::string> splitted_info = split_by_space(staff_info[i]);
			names.push_back(splitted_info[0]); lects.push_back(splitted_info[1]);
			sems.push_back(splitted_info[2]); colloqs.push_back(splitted_info[3]);
			exams.push_back(splitted_info[4]); totals.push_back(splitted_info[5]);
			std::stringstream h_ss; h_ss << splitted_info[static_cast<int>(HIERARCHY_CLASSES)];
			for (int j = 7; j < 12; ++j) h_ss << " " << splitted_info[j];
			hc_s.push_back(h_ss.str());
		}
		std::map<std::string, std::vector<std::string>> info;
		std::map<std::string, std::vector<std::string>> subcol_dump;
		info["Name"] = names; info["Lectures"] = lects; info["Seminars"] = sems;
		info["Colloqiums"] = colloqs; info["Exams"] = exams; info["row_sum"] = totals;
		std::stringstream response_ss;
		for (size_t i = 0; i < requested_cols.size(); ++i)
		{
			response_ss << requested_cols[i] << " ";
			subcol_dump[requested_cols[i]] = info[requested_cols[i]];
		}
		subcol_dump["hierarchy_codes"] = hc_s;
		response_ss << std::endl;
		for (size_t k = 0; k < names.size(); ++k)
		{
			for (size_t j = 0; j < requested_cols.size(); ++j)
			{
				response_ss << info[requested_cols[j]][k] << " ";
			}
			response_ss << std::endl;
		}
		prev_request = subcol_dump;
		return response_ss.str();
	}
	else if (request.find("subcols") != std::string::npos)
	{
		std::vector<std::string> request_vector = split_by_space(request);
		std::vector<std::string> requested_cols;
		int i = 1;
		while (request_vector[i] != "for_all")
		{
			requested_cols.push_back(request_vector[i]);
			i++;
		}
		i++;
		std::vector<int> hierarchy_code;
		for (int j = 0; j < static_cast<int>(HIERARCHY_CLASSES); ++j)
		{
			hierarchy_code.push_back(std::stoi(request_vector[i + j]));
		}
		std::stringstream response_ss;
		std::map<std::string, std::vector<std::string>> subcol_dump;
		for (size_t j = 0; j < requested_cols.size(); ++j)
		{
			response_ss << requested_cols[j] << " ";
		}
		response_ss << std::endl;

		for (size_t j = 0; j < prev_request["hierarchy_codes"].size(); ++j)
		{
			std::vector<int> curr_hierarchy;
			std::vector<std::string> tmp = split_by_space(prev_request["hierarchy_codes"][j]);
			for (int k = 0; k < static_cast<int>(HIERARCHY_CLASSES); ++k)
			{
				curr_hierarchy.push_back(std::stoi(tmp[k]));
			}
			staff tmp_staff; tmp_staff.hierarchy_code = curr_hierarchy;
			if (tmp_staff.compare_hierarchy(hierarchy_code) == true)
			{
				std::stringstream h_ss; h_ss << curr_hierarchy[0];
				for (int p = 1; p < static_cast<int>(HIERARCHY_CLASSES); ++p) h_ss << " " << curr_hierarchy[p];
				subcol_dump["hierarchy_codes"].push_back(h_ss.str());
				for (size_t q = 0; q < requested_cols.size(); ++q)
				{
					response_ss << prev_request[requested_cols[q]][j] << " ";
					subcol_dump[requested_cols[q]].push_back(prev_request[requested_cols[q]][j]);
				}
				response_ss << std::endl;
			}
		}
		prev_request = subcol_dump;
		return response_ss.str();
	}
	else if (request.find("html_col") != std::string::npos)
	{
		std::vector<std::string> request_vector = split_by_space(request);
		std::vector<std::string> requested_cols;
		size_t i = 1;
		// Getting requested columns
		while (request_vector[i] != "for_all")
		{
			requested_cols.push_back(request_vector[i]);
			i++;
		}
		i++;
		std::vector<int> hierarchy_code;
		for (int j = 0; j < static_cast<int>(HIERARCHY_CLASSES); ++j)
		{
			hierarchy_code.push_back(std::stoi(request_vector[i + j]));
		}
		std::vector<std::string> staff_info;
		for (size_t j = 0; j < v_staff.size(); ++j)
		{
			if (v_staff[j].compare_hierarchy(hierarchy_code) == true)
			{
				staff_info.push_back(get_info_row(v_staff[j]));
			}
		}
		std::vector<std::string> names, lects, sems, colloqs, exams, totals, hc_s;
		for (size_t i = 0; i < staff_info.size(); ++i)
		{
			std::vector<std::string> splitted_info = split_by_space(staff_info[i]);
			names.push_back(splitted_info[0]); lects.push_back(splitted_info[1]);
			sems.push_back(splitted_info[2]); colloqs.push_back(splitted_info[3]);
			exams.push_back(splitted_info[4]); totals.push_back(splitted_info[5]);
			std::stringstream h_ss; h_ss << splitted_info[static_cast<int>(HIERARCHY_CLASSES)];
			for (int j = 7; j < 12; ++j) h_ss << " " << splitted_info[j];
			hc_s.push_back(h_ss.str());
		}
		std::map<std::string, std::vector<std::string>> info;
		std::map<std::string, std::vector<std::string>> subcol_dump;
		info["Name"] = names; info["Lectures"] = lects; info["Seminars"] = sems;
		info["Colloqiums"] = colloqs; info["Exams"] = exams; info["row_sum"] = totals;
		std::stringstream response_ss; response_ss << "<table border = '1'>";
		response_ss << "<tr>";
		for (size_t i = 0; i < requested_cols.size(); ++i)
		{
			response_ss << "<th>";
			response_ss << requested_cols[i] << " ";
			response_ss << "</th>";
			subcol_dump[requested_cols[i]] = info[requested_cols[i]];
		}
		response_ss << "</tr>";
		subcol_dump["hierarchy_codes"] = hc_s;
		response_ss << std::endl;
		for (size_t k = 0; k < names.size(); ++k)
		{
			response_ss << "<tr>";
			for (size_t j = 0; j < requested_cols.size(); ++j)
			{
				response_ss << "<td>";
				response_ss << info[requested_cols[j]][k];
				response_ss << "</td>";
			}
			response_ss << "</tr>";
		}
		response_ss << "</table>";
		prev_request = subcol_dump;
		return response_ss.str();
	}
	else if (request.find("clear") != std::string::npos)
	{
		courses.clear();
		v_staff.clear();
		prev_request.clear();
	}
	else
	{
		throw database_error("Error: Unknown Request appeared");
	}
	return "Ok";
}