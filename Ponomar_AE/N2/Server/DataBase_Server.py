#!usr/bin python
import socket, select

HIERARCHY_CLASSES = 6
WORKLOADS = 4

class course:
    # Course Line: Name Lectures Sems Colloqs Exams 
    def __init__(self, course_name : str, course_hours : list):
        self.course_name = course_name
        self.course_hours = course_hours

class staff:
    # Staff line: Name N C1 C2 ... CN H1 ... H6 
    def __init__(self, name : str, course_indexes : list, hierarchy_code : list):
        self.name = name
        self.course_indexes = course_indexes
        self.hierarchy_code = hierarchy_code
    
    def only_faculty(self, hierarchy : list):
        if (hierarchy[0] != 0):
            for i in range(1, HIERARCHY_CLASSES):
                if (hierarchy[i] != 0):
                    return False
            return True
        return False
    
    def faculty_dept(self, hierarchy : list):
        if (hierarchy[0] != 0 and hierarchy[1] != 0):
            for i in range(2, HIERARCHY_CLASSES):
                if (hierarchy[i] != 0):
                    return False
            return True
        return False
    
    def compare_hierarchy(self, hierarchy : list):
        if (self.only_faculty(hierarchy) == True):
            if (hierarchy[0] == self.hierarchy_code[0]):
                return True
        elif (self.faculty_dept(hierarchy) == True):
            if (hierarchy[0] == self.hierarchy_code[0] and hierarchy[1] == self.hierarchy[1]):
                return True
        else:
            for i in range(HIERARCHY_CLASSES):
                if (hierarchy[i] != self.hierarchy_code[i]):
                    return False
            return True

class database:
    def __init__(self):
        self.workloads = ["Лекции", "Семинары", "Коллоквиумы", "Экзамены"]
        self.courses = []
        self.staff = []
        self.cols_dump = []
        
    def add_course(self, c : course):       
        self.courses.append(c)
    
    def add_staff(self, s : staff):       
        self.staff.append(s)

    def delete_course(self, Course_name : str):
        for i in range(len(self.courses)):
            curr_name = (self.courses)[i].course_name
            if (curr_name == Course_name):
                self.courses.pop(i)
                break
                
    def delete_staff(self, staff_name : str):
        for i in range(len(self.staff)):
            if (self.staff[i].name == staff_name):
                self.staff.pop(i)
                break
                
    def course_info(self, course_name : str):
        for course in self.courses:
            if (course.course_name == course_name):
                return (course_name + " " + " ".join( list(map(lambda x: str(x), course.course_hours)) ))
            
    def staff_info(self, staff_name : str):
        for staff in self.staff:
            if (staff.name == staff_name):
                S = staff_name + " " + str(len(staff.course_indexes)) + " " + " ".join(list(map(lambda x: str(x), staff.hierarchy_code)))
                S += " " + " ".join(list(map(lambda x: str(x), staff.course_indexes)))
                return S
            
    def staff_hours(self, staff_name):
        hours_dict = {"Lectures" : 0, "Seminars" : 0, "Colloqiums" : 0, "Exams" : 0, "row_sum" : 0}
        for staff in self.staff:
            if (staff.name == staff_name):
                hours_dict["Name"] = staff.name
                for course_id in staff.course_indexes:
                    hours_dict["Lectures"] += self.courses[course_id].course_hours[0]
                    hours_dict["Seminars"] += self.courses[course_id].course_hours[1]
                    hours_dict["Colloqiums"] += self.courses[course_id].course_hours[2]
                    hours_dict["Exams"] += self.courses[course_id].course_hours[3]
                    hours_dict["row_sum"] += hours_dict["Lectures"] + hours_dict["Seminars"] + hours_dict["Colloqiums"] + hours_dict["Exams"]
        return hours_dict
    
    def handle_request(self, request):     
        request_tokens = request.split(' ')
        command = request_tokens[0]
        
        if (command == "add_course"):
            course_hours = list(map(lambda x: int(x), request_tokens[2:]))
            C = course(request_tokens[1], course_hours)
            self.add_course(C)
        
        elif (command == "delete_course"):
            course_name = request_tokens[1]
            self.delete_course(course_name)
        
        elif (command == "add_staff"):
            staff_name = request_tokens[1]
            course_number = int(request_tokens[2])
            hierarchy_code = [int(request_tokens[i]) for i in range(3, 3+HIERARCHY_CLASSES)]
            course_indexes = [int(request_tokens[i]) for i in range(3+HIERARCHY_CLASSES, 3+course_number+HIERARCHY_CLASSES)]
            S = staff(staff_name, course_indexes, hierarchy_code)
            self.add_staff(S)
        
        elif (command == "delete_staff"):
            self.delete_staff(request_tokens[1])
          
        elif (command == "get_course"):
            course_name = request_tokens[1]
            return self.course_info(course_name)
        
        elif (command == "get_staff"):
            staff_name = request_tokens[1]
            return self.staff_info(staff_name)
        
        elif (command == "update_course"):
            C = course(request_tokens[1], list(map(lambda x: int(x), request_tokens[2:])))
            self.delete_course(C.course_name)
            self.add_course(C)
        
        elif (command == "update_staff"):
            staff_name = request_tokens[1]
            course_number = int(request_tokens[2])
            course_indexes = [int(request_tokens[i]) for i in range(3, 3+course_number)]
            hierarchy_code = [int(request_tokens[i]) for i in range(3+course_number, 3+course_number+HIERARCHY_CLASSES)]
            S = staff(staff_name, course_indexes, hierarchy_code)
            self.delete_staff(S.name)
            self.add_staff(S)
          
        elif (command == "clear"):
            self.courses = []
            self.staff = []
        
        elif (command == "save"):
            filename = request_tokens[1]
            outfile = open(filename, 'w')
            outfile.write(self.handle_request("get_full_database"))
            outfile.close()
            
        elif (command == "columns"):
            requested_cols, hierarchy_code, satisfying_staff = [], [], []
            i = 1
            while (request_tokens[i] != 'for_all'):
                requested_cols.append(request_tokens[i])
                i += 1
            i += 1 # Standing on first hierarchy marker
            for j in range(i, len(request_tokens)):
                hierarchy_code.append(int(request_tokens[j]))
            for s in self.staff:
                if (s.compare_hierarchy(hierarchy_code) == True):
                    satisfying_staff.append(s)
            response = " ".join(requested_cols) + '\n'
            for s in satisfying_staff:
                staff_hrs = self.staff_hours(s.name)
                response += " ".join( list(map(lambda x: str(x), [staff_hrs[col] for col in requested_cols])) ) + '\n'
            self.cols_dump = satisfying_staff
            return response[:-1]
        
        elif (command == "get_full_database"): 
            full_db = str(len(self.courses)) + '\n'
            for c in self.courses:
                full_db += self.course_info(c.course_name) + '\n'
            full_db += str(len(self.staff)) + '\n'
            for s in self.staff:
                full_db += self.staff_info(s.name) + '\n'
            return full_db[:-1]       
        
        elif (command == "print"): 
            echo = 'Course Name   Lectures    Seminars    Colloqiums    Exams\n'
            for c in self.courses:
                echo += self.course_info(c.course_name) + '\n'
            echo += 'Name  Courses  Faculty  Dept  Director?  Proffessor?  Docent?  Tutor?  >>Courses\n'
            for s in self.staff:
                echo += self.staff_info(s.name) + '\n'
            return echo   
        
        elif (command == "subcols"):
            requested_cols, hierarchy_code, satisfying_staff = [], [], []
            i = 1
            while (request_tokens[i] != 'for_all'):
                requested_cols.append(request_tokens[i])
                i += 1
            i += 1 # Standing on first hierarchy marker
            for j in range(i, len(request_tokens)):
                hierarchy_code.append(int(request_tokens[j]))
            for s in self.cols_dump:
                if (s.compare_hierarchy(hierarchy_code) == True):
                    satisfying_staff.append(s)
            response = " ".join(requested_cols) + '\n'
            for s in satisfying_staff:
                staff_hrs = self.staff_hours(s.name)
                response += " ".join( list(map(lambda x: str(x), [staff_hrs[col] for col in requested_cols])) ) + '\n'
            self.cols_dump = satisfying_staff
            return response[:-1]   
        
        elif (command == "html_col"):
            requested_cols, hierarchy_code, satisfying_staff = [], [], []
            i = 1
            while (request_tokens[i] != 'for_all'):
                requested_cols.append(request_tokens[i])
                i += 1
            i += 1 # Standing on first hierarchy marker
            for j in range(i, len(request_tokens)):
                hierarchy_code.append(int(request_tokens[j]))
            for s in self.staff:
                if (s.compare_hierarchy(hierarchy_code) == True):
                    satisfying_staff.append(s)
            response = '<table border = 1> <tr>'
            for rc in requested_cols:
                response += '<th>' + rc + '</th>'
            response += '</tr>'
            for s in satisfying_staff:
                response += '<tr>'
                staff_hrs = self.staff_hours(s.name)
                for rc in requested_cols:
                    response += '<td>' + str(staff_hrs[rc]) + '</td>'
                response += '</tr>'
            response += '</table>'
            self.cols_dump = satisfying_staff
            return response
        
        else:
            return "Error: unknown request occured." 
        return 'Ok'
                
def server(no_connections_timeout, max_buffer_size):
    DB = database()
    
    host = socket.gethostname()
    host_addr = '127.0.0.1'
    
    port = 8000
    
    server_socket = socket.socket()
    server_socket.settimeout(no_connections_timeout)
    server_socket.bind((host_addr, port))
    
    print('Seeking for incoming connections...')
    server_socket.listen()
    
    ready_to_connect = True
    
    try:
        while True:
            if (ready_to_connect == True):
                connection, address = server_socket.accept()
                ready_to_connect = False
            print('Connection accepted.')
            while True:
                request = connection.recv(max_buffer_size).decode()
                #print('Got request: {}'.format(request))
                if (not request):
                    break               
                database_response = DB.handle_request(request)
                if (database_response != 'Ok'):
                    connection.send(database_response.encode())
            connection.close()
            ready_to_connect = True
                
    except socket.timeout:
        print('Connection timeout: no more connections occured for {} seconds.'.format(no_connections_timeout))
    
    server_socket.close()
        
server(20, 4096)
