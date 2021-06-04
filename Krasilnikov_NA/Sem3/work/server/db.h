#ifndef DB_H
#define DB_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <map>
#include <sstream>
#include <utility>
#include <cctype>
#include <set>
#include <fstream>
#include <functional>
#include <list>

class Workload {
public:
    Workload(const std::string &s);
    const std::string &getName() const;
    const std::string &getProperty() const;
    void updateName(const std::string &s);

private:
    std::string name_;
    std::string workload_;
};

class Workloads {
public:
    int addWorkload(const std::string &s);
    bool isAvailable(const int index) const;
    int size() const;
    void deleteWorkload(const std::string &s);
    void deleteWorkload(const int index);
    void updateWorkload(const std::string name, const std::string &s);
    void updateWorkloadName(const int index, std::string s);
    void updateWorkload(const int index, const std::string &s);
    const Workload &operator [] (const int index) const;

private:
    std::vector<Workload> workloads_;
    std::set<int> deleted_;
    void BadIndexCheck(const int index) const;
};

class TreeElement {
public:
    TreeElement(const std::string &name, const bool last_tree_elem);
    void addNext(const std::string &name, const int index);
    int find(const std::string &name) const;
    void deleteNext(const std::string &name);
    void deleteAllNext();
    const std::string &getName() const;
    bool lastTreeElem() const;
    const auto &getNextIndices() const;

private:
    std::string name_;
    bool last_tree_elem_;
    mutable std::map<std::string, int> next_indices_;
};

class Worker {
public:
    Worker(const std::string &name);
    void addWorkload(const int index);
    const std::list<std::pair<int, std::string>> &getWorkloads() const;
    void deleteWorkload(const int index); /// индекс из глобальной таблицы с задачами
    void updateWorkload(const int index, const std::string &s);
    const std::string &getName() const;

private:
    std::string name_;
    std::list<std::pair<int, std::string>> workloads_;
};

class Hierarchy {
public:
    Hierarchy();
    void addWorker(const std::string &s);
    void deleteWorker(const std::string &s);
    void deleteWorkersCourse(const std::string &s);
    void updateWorkersCourse(const std::string &s);
    void addWorkersCourse(const std::string &s);
    void getWorkersCourse(const std::string &s);
    void makeRequests(std::vector<std::string> &req);
    void select(const std::vector<std::string> &col, const std::set<std::string> &hier,
            std::vector<std::string> &names, std::vector<std::vector<int>> &table,
            std::vector<std::vector<std::string>> &workers_hier, const Workloads &wlds);

private:
    std::vector<TreeElement> properties_;
    std::vector<Worker> workers_;
    std::vector<int> toTable(const std::vector<std::string> &col,
            const std::list<std::pair<int, std::string>> &wl,
            const Workloads &wlds);
    void selectDfs(int index, const std::vector<std::string> &col, const std::set<std::string> &hier,
            std::vector<std::string> &names, std::vector<std::vector<int>> &table,
            std::vector<std::vector<std::string>> &workers_hier, std::vector<std::string> &cur_hier,
            const Workloads &wlds);
    void getWorkloadsDfs(const int index, const int cur_layer, const std::vector<std::string> &names);
    void deleteDfs(const int index, const int cur_layer, const std::vector<std::string> &names);
    void deleteCourseDfs(const int index, const int cur_layer,
            const std::vector<std::string> &names, const int course_index);
    void updateCourseDfs(const int index, const int cur_layer,
            const std::vector<std::string> &names, const int course_index, const std::string &s);
    void addCourseDfs(const int index, const int cur_layer,
            const std::vector<std::string> &names, const int course_index);
    void requestsDfs(const int index, std::vector<std::string> &req, const std::string &cur_str);
};

class DataBase {
public:
    DataBase();
    void uploadFromTxtFile(std::string filename);
    void saveAsTxtFile(std::string filename);
    void process(std::istream &fin);

private:
    Hierarchy hierarchy_;
    Workloads workloads_;
    std::map<std::string, std::function<void(Hierarchy &, Workloads &, const std::string &)>> functions_;
    void request_processing(std::string s);
};

#endif
