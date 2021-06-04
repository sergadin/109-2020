#include "db.h"

static void strip(std::string &s) {
    auto it = s.begin();
    while (it != s.end() && isspace(static_cast<unsigned>(*it))) {
        ++it;
    }
    if (it == s.end()) {
        s = "";
        return;
    }
    auto jt = s.end();
    --jt;
    while (isspace(static_cast<unsigned>(*jt))) {
        --jt;
    }
    ++jt;
    s = std::string(it, jt);
}

Workload::Workload(const std::string &s) {
    std::stringstream str;
    str << s;
    str >> name_;
    workload_ = str.str().substr(str.tellg());
    strip(workload_);
}

const std::string &Workload::getName() const {
    return name_;
}

const std::string &Workload::getProperty() const {
    return workload_;
}

void Workload::updateName(const std::string &s) {
    name_ = s;
}

///////////////////////////////////

int Workloads::addWorkload(const std::string &s) {
    workloads_.push_back(Workload(s));
    return workloads_.size() - 1;
}

bool Workloads::isAvailable(const int index) const {
    return 0 <= index && index < static_cast<int>(workloads_.size())
            && deleted_.find(index) == deleted_.end();
}

int Workloads::size() const {
    return workloads_.size();
}

void Workloads::deleteWorkload(const std::string &s) {
    auto name = s;
    strip(name);
    for (int i = 0; i < static_cast<int>(workloads_.size()); ++i) {
        if (workloads_[i].getName() == name) {
            deleted_.insert(i);
            return;
        }
    }
}

void Workloads::deleteWorkload(const int index) {
    BadIndexCheck(index);
    deleted_.insert(index);
}

void Workloads::updateWorkload(const std::string name, const std::string &s) {
    for (int i = 0; i < static_cast<int>(workloads_.size()); ++i) {
        if (workloads_[i].getName() == name) {
            workloads_[i] = Workload(name + " " + s);
            return;
        }
    }
}

void Workloads::updateWorkloadName(const int index, std::string s) {
    strip(s);
    BadIndexCheck(index);
    workloads_[index].updateName(s);
}

void Workloads::updateWorkload(const int index, const std::string &s) {
    BadIndexCheck(index);
    workloads_[index] = Workload(workloads_[index].getName() + " " + s);
}

const Workload &Workloads::operator [] (const int index) const {
    BadIndexCheck(index);
    return workloads_[index];
}

void Workloads::BadIndexCheck(const int index) const {
    if (!isAvailable(index)) {
        throw "Bad index\n";
    }
}

/////////////////////////////////////////////

TreeElement::TreeElement(const std::string &name, const bool last_tree_elem)
  : name_(name), last_tree_elem_(last_tree_elem) {}

void TreeElement::addNext(const std::string &name, const int index) {
    next_indices_[name] = index;
}

int TreeElement::find(const std::string &name) const {
    if (next_indices_.find(name) == next_indices_.end()) {
        return -1;
    }
    return next_indices_[name];
}

void TreeElement::deleteNext(const std::string &name) {
    if (next_indices_.find(name) != next_indices_.end()) {
        next_indices_.erase(name);
    }
}

void TreeElement::deleteAllNext() {
    next_indices_.clear();
}

const std::string &TreeElement::getName() const {
    return name_;
}

bool TreeElement::lastTreeElem() const {
    return last_tree_elem_;
}

const auto &TreeElement::getNextIndices() const {
    return next_indices_;
}

////////////////////////////////////

Worker::Worker(const std::string &name) : name_(name) {}

void Worker::addWorkload(const int index) {
    workloads_.push_back({index, ""});
}

const std::list<std::pair<int, std::string>> &Worker::getWorkloads() const {
    return workloads_;
}

void Worker::deleteWorkload(const int index) {  /// индекс из глобальной таблицы с задачами
    for (auto it = workloads_.begin(); it != workloads_.end(); ++it) {
        if (it->first == index) {
            workloads_.erase(it);
            break;
        }
    }
}

void Worker::updateWorkload(const int index, const std::string &s) {
    for (auto it = workloads_.begin(); it != workloads_.end(); ++it) {
        if (it->first == index) {
            it->second = s;
            break;
        }
    }
}

const std::string &Worker::getName() const {
    return name_;
}

/////////////////////////////////////

Hierarchy::Hierarchy() {
    properties_.push_back(TreeElement("", false));
}

void Hierarchy::addWorker(const std::string &s) {
    std::stringstream str;
    str << s;
    std::vector<std::string> hier_layers(3);
    std::string name;
    str >> hier_layers[0] >> hier_layers[1] >> hier_layers[2] >> name;
    int cur = 0, next;
    for (int i = 0; i < 3; ++i) {
        if ((next = properties_[cur].find(hier_layers[i])) != -1) {
            cur = next;
        } else {
            properties_.push_back(TreeElement(hier_layers[i], i == 2));
            properties_[cur].addNext(hier_layers[i], properties_.size() - 1);
            cur = properties_.size() - 1;
        }
    }
    workers_.push_back(Worker(name));
    properties_[cur].addNext(name, workers_.size() - 1);
}

void Hierarchy::deleteWorker(const std::string &s) {
    std::stringstream str;
    str << s;
    std::vector<std::string> names;
    std::string t;
    while (str >> t) {
        names.push_back(t);
    }
    if (names.size() != 4) {
        throw "Bad worker delete parameters\n";
    }
    deleteDfs(0, 0, names);
}

void Hierarchy::deleteWorkersCourse(const std::string &s) {
    std::stringstream str;
    str << s;
    std::vector<std::string> names;
    std::string t;
    int index;
    while (names.size() < 4 && str >> t) {
        names.push_back(t);
    }
    if (names.size() != 4) {
        throw "Bad worker's course delete parameters\n";
    }
    if (str >> index) {
        deleteCourseDfs(0, 0, names, index);
    } else {
        throw "Bad index\n";
    }
}

void Hierarchy::updateWorkersCourse(const std::string &s) {
    std::stringstream str;
    str << s;
    std::vector<std::string> names;
    std::string t;
    int index;
    while (names.size() < 4 && str >> t) {
        names.push_back(t);
    }
    if (names.size() != 4) {
        throw "Bad worker's course update parameters\n";
    }
    if (str >> index) {
        updateCourseDfs(0, 0, names, index, str.str().substr(str.tellg()));
    } else {
        throw "Bad index\n";
    }
}

void Hierarchy::addWorkersCourse(const std::string &s) {
    std::stringstream str;
    str << s;
    std::vector<std::string> names;
    std::string t;
    int index;
    while (names.size() < 4 && str >> t) {
        names.push_back(t);
    }
    if (names.size() != 4) {
        throw "Bad worker's course add parameters\n";
    }
    if (str >> index) {
        addCourseDfs(0, 0, names, index);
    } else {
        throw "Bad index\n";
    }
}

void Hierarchy::getWorkersCourse(const std::string &s) {
    std::stringstream str;
    str << s;
    std::vector<std::string> names;
    std::string t;
    while (str >> t) {
        names.push_back(t);
    }
    if (names.size() != 4) {
        throw "Bad worker delete parameters\n";
    }

    getWorkloadsDfs(0, 0, names);
}

void Hierarchy::makeRequests(std::vector<std::string> &req) {
    requestsDfs(0, req, "");
}

void Hierarchy::select(const std::vector<std::string> &col, const std::set<std::string> &hier,
        std::vector<std::string> &names, std::vector<std::vector<int>> &table,
        std::vector<std::vector<std::string>> &workers_hier, const Workloads &wlds) {
    std::vector<std::string> cur_hierarchy;
    selectDfs(0, col, hier, names, table, workers_hier, cur_hierarchy, wlds);
}

std::vector<int> Hierarchy::toTable(const std::vector<std::string> &col,
        const std::list<std::pair<int, std::string>> &wl,
        const Workloads &wlds) {
    std::vector<int> res(col.size());
    std::map<std::string, int> indices;
    for (int i = 0; i < static_cast<int>(col.size()); ++i) {
        indices[col[i]] = i;
    }
    for (const auto &p : wl) {
        if (!wlds.isAvailable(p.first)) {
            continue;
        }
        std::stringstream str;
        str << wlds[p.first].getProperty();
        std::string name;
        int value;
        while (str >> name >> value) {
            if (indices.find(name) != indices.end()) {
                res[indices[name]] += value;
            }
        }
    }
    return res;
}

void Hierarchy::selectDfs(int index, const std::vector<std::string> &col, const std::set<std::string> &hier,
        std::vector<std::string> &names, std::vector<std::vector<int>> &table,
        std::vector<std::vector<std::string>> &workers_hier, std::vector<std::string> &cur_hier,
        const Workloads &wlds) {
    if (properties_[index].lastTreeElem()) {
        if (hier.empty()) {
            for (const auto &i : properties_[index].getNextIndices()) {
                names.push_back(i.first);
                workers_hier.push_back(cur_hier);
                table.push_back(toTable(col, workers_[i.second].getWorkloads(), wlds));
            }
        } else {
            bool flag = false;
            for (const auto &i : cur_hier) {
                if (hier.find(i) != hier.end()) {
                    flag = true;
                    break;
                }
            }
            if (flag) {
                for (const auto &i : properties_[index].getNextIndices()) {
                    names.push_back(i.first);
                    workers_hier.push_back(cur_hier);

                    table.push_back(toTable(col, workers_[i.second].getWorkloads(), wlds));
                }
            }
        }
        return;
    }
    for (const auto &i : properties_[index].getNextIndices()) {
        cur_hier.push_back(i.first);
        selectDfs(i.second, col, hier, names, table, workers_hier, cur_hier, wlds);
        cur_hier.pop_back();
    }
}

void Hierarchy::getWorkloadsDfs(const int index, const int cur_layer, const std::vector<std::string> &names) {
    if (properties_[index].lastTreeElem()) {
        if (names[cur_layer] == "!") {
            for (const auto &i : properties_[index].getNextIndices()) {
                std::cout << i.first << ":" << std::endl;
                for (const auto &j : workers_[i.second].getWorkloads()) {
                    std::cout << "\t#" << j.first << " info: " << j.second << std::endl;
                }
            }
        } else {
            auto ind = properties_[index].find(names[cur_layer]);
            if (ind != -1) {
                std::cout << workers_[ind].getName() << ":" << std::endl;
                for (const auto &j : workers_[ind].getWorkloads()) {
                    std::cout << "\t#" << j.first << " info: " << j.second << std::endl;
                }
            }
        }
        return;
    }
    if (names[cur_layer] == "!") {
        for (const auto &i : properties_[index].getNextIndices()) {
            getWorkloadsDfs(i.second, cur_layer + 1, names);
        }
        return;
    }
    auto ind = properties_[index].find(names[cur_layer]);
    if (ind != -1) {
        getWorkloadsDfs(ind, cur_layer + 1, names);
    }
}

void Hierarchy::deleteDfs(const int index, const int cur_layer, const std::vector<std::string> &names) {
    if (properties_[index].lastTreeElem()) {
        if (names[cur_layer] == "!") {
            properties_[index].deleteAllNext();
        } else {
            properties_[index].deleteNext(names[cur_layer]);
        }
        return;
    }
    if (names[cur_layer] == "!") {
        for (const auto &i : properties_[index].getNextIndices()) {
            deleteDfs(i.second, cur_layer + 1, names);
        }
        return;
    }
    auto ind = properties_[index].find(names[cur_layer]);
    if (ind != -1) {
        deleteDfs(ind, cur_layer + 1, names);
    }
}

void Hierarchy::deleteCourseDfs(const int index, const int cur_layer,
        const std::vector<std::string> &names, const int course_index) {
    if (properties_[index].lastTreeElem()) {
        if (names[cur_layer] == "!") {
            auto indices = properties_[index].getNextIndices();
            for (const auto &i : indices) {
                workers_[i.second].deleteWorkload(course_index);
            }
        } else {
            auto ind = properties_[index].find(names[cur_layer]);
            if (ind != -1) {
                workers_[ind].deleteWorkload(course_index);
            }
        }
        return;
    }
    if (names[cur_layer] == "!") {
        for (const auto &i : properties_[index].getNextIndices()) {
            deleteCourseDfs(i.second, cur_layer + 1, names, course_index);
        }
        return;
    }
    auto ind = properties_[index].find(names[cur_layer]);
    if (ind != -1) {
        deleteCourseDfs(ind, cur_layer + 1, names, course_index);
    }
}

void Hierarchy::updateCourseDfs(const int index, const int cur_layer,
        const std::vector<std::string> &names, const int course_index, const std::string &s) {
    if (properties_[index].lastTreeElem()) {
        if (names[cur_layer] == "!") {
            for (const auto &i : properties_[index].getNextIndices()) {
                workers_[i.second].updateWorkload(course_index, s);
            }
        } else {
            auto ind = properties_[index].find(names[cur_layer]);
            if (ind != -1) {
                workers_[ind].updateWorkload(course_index, s);
            }
        }
        return;
    }
    if (names[cur_layer] == "!") {
        for (const auto &i : properties_[index].getNextIndices()) {
            updateCourseDfs(i.second, cur_layer + 1, names, course_index, s);
        }
        return;
    }
    auto ind = properties_[index].find(names[cur_layer]);
    if (ind != -1) {
        updateCourseDfs(ind, cur_layer + 1, names, course_index, s);
    }
}

void Hierarchy::addCourseDfs(const int index, const int cur_layer,
        const std::vector<std::string> &names, const int course_index) {
    if (properties_[index].lastTreeElem()) {
        if (names[cur_layer] == "!") {
            for (const auto &i : properties_[index].getNextIndices()) {
                workers_[i.second].addWorkload(course_index);
            }
        } else {
            auto ind = properties_[index].find(names[cur_layer]);
            if (ind != -1) {
                workers_[ind].addWorkload(course_index);
            }
        }
        return;
    }
    if (names[cur_layer] == "!") {
        for (const auto &i : properties_[index].getNextIndices()) {
            addCourseDfs(i.second, cur_layer + 1, names, course_index);
        }
        return;
    }
    auto ind = properties_[index].find(names[cur_layer]);
    if (ind != -1) {
        addCourseDfs(ind, cur_layer + 1, names, course_index);
    }
}

void Hierarchy::requestsDfs(const int index, std::vector<std::string> &req, const std::string &cur_str) {
    if (properties_[index].lastTreeElem()) {
        for (const auto &i : properties_[index].getNextIndices()) {
            req.push_back("addWorker " + cur_str + " " + i.first);
            for (const auto &j : workers_[i.second].getWorkloads()) {
                std::stringstream str;
                str << "addWorkersCourse " << cur_str << " " << i.first << " " << j.first;
                req.push_back(str.str());
                if (j.second.size() > 0) {
                    std::stringstream str1;
                    str1 << "updateWorkersCourse " << cur_str << " "
                            << i.first << " " << j.first << " " << j.second;
                    req.push_back(str1.str());
                }
            }
        }
        return;
    }
    for (const auto &i : properties_[index].getNextIndices()) {
        requestsDfs(i.second, req, cur_str + " " + i.first);
    }
}

DataBase::DataBase() {
    functions_ = std::map<std::string, std::function<void(Hierarchy &, Workloads &, const std::string &)>> {
        {"addCourse", [](auto &tree, auto &tasks, const std::string &s) {
            std::cout << "Added new course: # " << tasks.addWorkload(s) << std::endl;
        }},
        {"addWorker", [](auto &tree, auto &tasks, const std::string &s) {
            tree.addWorker(s);
            std::cout << "Added new worker " << s << std::endl;
        }},
        {"deleteCourse", [](auto &tree, auto &tasks, const std::string &s) {
            std::stringstream str;
            str << s;
            std::string type;
            str >> type;
            if (type == "index") {
                int index;
                str >> index;
                tasks.deleteWorkload(index);
            } else if (type == "name") {
                std::string name;
                str >> name;
                tasks.deleteWorkload(name);
            }
            std::cout << "Course deleted" << std::endl;
        }},
        {"deleteWorker", [](auto &tree, auto &tasks, const std::string &s) {
            tree.deleteWorker(s);
            std::cout << "Worker deleted" << std::endl;
        }},
        {"updateWorkersCourse", [](auto &tree, auto &tasks, const std::string &s) {
            tree.updateWorkersCourse(s);
            std::cout << "Worker's course updated" << std::endl;
        }},
        {"deleteWorkersCourse", [](auto &tree, auto &tasks, const std::string &s) {
            tree.deleteWorkersCourse(s);
            std::cout << "Worker's course deleted" << std::endl;
        }},
        {"addWorkersCourse", [](auto &tree, auto &tasks, const std::string &s) {
            tree.addWorkersCourse(s);
            std::cout << "Worker's course added" << std::endl;
        }},
        {"getWorkersCourse", [](auto &tree, auto &tasks, const std::string &s) {
            tree.getWorkersCourse(s);
        }},
        {"updateCourse", [](auto &tree, auto &tasks, const std::string &s) {
            std::stringstream str;
            str << s;
            std::string type;  /// ключевое слово index или name
            str >> type;
            if (type == "index") {
                int index;
                str >> index;
                tasks.updateWorkload(index, str.str().substr(str.tellg()));
            } else if (type == "name") {
                std::string name;
                str >> name;
                tasks.updateWorkload(name, str.str().substr(str.tellg()));
            } else {
                throw "Bad updateCourse request\n";
            }
            std::cout << "Course updated" << std::endl;
        }},
        {"updateCourseName", [](auto &tree, auto &tasks, const std::string &s) {
            std::stringstream str;
            str << s;
            int index;
            str >> index;
            tasks.updateWorkloadName(index, str.str().substr(str.tellg()));
            std::cout << "Course name updated" << std::endl;
        }},
        {"select", [](auto &tree, auto &tasks, const std::string &s) {
            std::stringstream str;
            str << s;
            std::string t;
            str >> t;
            if (t != "columns") {
                throw "Bad select 1\n";
            }
            std::vector<std::string> columns;
            while (t != "end_columns") {
                if (!(str >> t)) {
                    throw "Bad select 2\n";
                }
                if (t == "end_columns") {
                    break;
                }
                columns.push_back(t);
            }
            if (!(str >> t) || t != "rows_for_all") {
                throw "Bad select 3\n";
            }
            std::set<std::string> hierarchy_names;
            while (true) {
                if (!(str >> t)) {
                    throw "Bad select 4\n";
                }
                if (t == "sum_row" || t == "end_row") {
                    break;
                }
                hierarchy_names.insert(t);
            }
            std::vector<std::string> names;
            std::vector<std::vector<int>> table;
            std::vector<std::vector<std::string>> workers_hier;
            tree.select(columns, hierarchy_names, names, table, workers_hier, tasks);

            std::cout << "name\t";
            for (const auto &i : columns) {
                std::cout << i << "\t";
            }
            std::cout << "\n";
            for (int j = 0; j < static_cast<int>(table.size()); ++j) {
                std::cout << names[j] << "\t";
                for (int i = 0; i < static_cast<int>(columns.size()); ++i) {
                    if (columns[i] == "faculty") {
                        std::cout << workers_hier[j][0] << "\t";
                    } else if (columns[i] == "department") {
                        std::cout << workers_hier[j][1] << "\t";
                    } else if (columns[i] == "post") {
                        std::cout << workers_hier[j][2] << "\t";
                    } else {
                        std::cout << table[j][i] << "\t";
                    }
                }
                std::cout << std::endl;
            }
            if (t == "sum_row") {
                std::cout << "total:\n";
                std::cout << "name\t";
                std::vector<int> res(columns.size());
                for (const auto &a : table) {
                    for (int i = 0; i < static_cast<int>(res.size()); ++i) {
                        res[i] += a[i];
                    }
                }
                for (int i = 0; i < static_cast<int>(res.size()); ++i) {
                    if (columns[i] == "faculty" || columns[i] == "department" || columns[i] == "post") {
                        std::cout << columns[i] << "\t";
                    } else {
                        std::cout << res[i] << "\t";
                    }
                }
                std::cout << std::endl;
            }
        }}
    };
    std::cout << "DB start\n" << std::endl;
}

void DataBase::uploadFromTxtFile(std::string filename) {
    hierarchy_ = Hierarchy();
    workloads_ = Workloads();
    strip(filename);
    std::ifstream fin(filename);
    process(fin);
    std::cout << std::endl;
    fin.close();
}

void DataBase::saveAsTxtFile(std::string filename) {
    strip(filename);
    std::cerr << filename << std::endl;
    std::ofstream fout(filename);

    if (!fout) {
        throw "Bad output file\n";
    }
    for (int i = 0; i < workloads_.size(); ++i) {
        if (workloads_.isAvailable(i)) {
            fout << "addCourse " << workloads_[i].getName() << " "<< workloads_[i].getProperty() << "\n";
        }
    }
    std::vector<std::string> hierarchy_requests;
    hierarchy_.makeRequests(hierarchy_requests);
    for (const auto &i : hierarchy_requests) {
        fout << i << "\n";
    }
    fout.close();
    std::cout << "Saved" << std::endl;
}

void DataBase::process(std::istream &fin) {
    std::string cmd;
    while (std::getline(fin, cmd)) {
        strip(cmd);
        if (cmd.empty()) {
            std::cout << std::endl;
            continue;
        }
        if (cmd == "exit") {
            std::cout << "DB finished\n\n";
            return;
        }
        try {
            request_processing(cmd);
        } catch (const char *s) {
            std::cout << s << std::endl;
        }
        std::cout.flush();
    }
}

void DataBase::request_processing(std::string s) {
    strip(s);
    if (s.size() == 0) {
        return;
    }
    std::stringstream str;
    str << s;
    std::string func_name;
    str >> func_name;

    if (func_name != "uploadFromTxtFile" && func_name != "saveAsTxtFile") {
        if (functions_.find(func_name) == functions_.end()) {
            throw "Bad command\n";
        }
        functions_[func_name](hierarchy_, workloads_, str.str().substr(str.tellg()));
        std::cout << std::endl;
    }
    if (func_name == "uploadFromTxtFile") {
        try {
          uploadFromTxtFile(str.str().substr(str.tellg()));
        } catch (...) {
            throw "Bad filename\n";
        }
    }
    if (func_name == "saveAsTxtFile") {
        try {
            saveAsTxtFile(str.str().substr(str.tellg()));
        } catch (...) {
            throw "Bad filename\n";
        }
    }
}
