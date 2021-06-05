#include <iostream>
#include "R2.hpp"

using namespace std;

int main()
{
    Database_R2 A;
    std::list<std::pair<Cell*, std::array<int, 2>>> result;
    A.parce("ADD teacher=John course=matan time=0 room=0 group=101", result);
    A.parce("ADD teacher=John course=diffgem time=1 room=0 group=101", result);
    //A.parce("DELETE teacher=John course=diffgem time=1 room=0 group=101", result);
    A.parce("SELECT course=matan", result);

    stringstream ss;
    for(pair<Cell*, array<int,2 >> data : result)
    {
        cout <<"time: "<< data.second[0] <<" room: " <<data.second[1] << " teacher: " << data.first->get_teacher() << " course: " << data.first->get_course() 
        << " group:"<< data.first->get_group() << endl;
    }
    /*
    matrix B;
    cout <<B.ADD("John", "diffgem", 0, 100, 101) << endl;
    cout <<B.ADD("mal", "diffgem", 0, 101, 101) << endl;
    cout <<B.ADD("abd", "matan", 1, 100, 101) << endl;
    cout <<B.ADD("abd", "matan", 1, 101, 102) << endl;

    cout << B._teachers["John"].front()->get_teacher()<< endl;
    */
    /*
    string abd = "dawd wdadwa";
    cout << split_and_remove(abd, ' ') <<abd <<endl;*/
    return 0;

}