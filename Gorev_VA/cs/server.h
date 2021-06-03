#include <iostream>
#include <fstream>
#include <sstream>

int Base::do_from(std::istream& in, int ms)
{
    char mes[1024];
    // цикл обработки одного сообщения
    while(1)
    {
        // читаем первую команду
        if (in >> mes)
            write(ms, mes, sizeof(mes));
        else
        {
            write(ms, "END", sizeof("END"));
            return 0;
        }

        // добавление деталей
        if (strcmp(mes, "add_details") == 0)
            while (1)
            {
                // читаем название детали / сообщение об окончинии добавления
                if (!(in >> mes)) { write(ms, "error", sizeof("error"));  return -1; }

                if (strcmp(mes, "end") == 0)
                    break;
                else
                {
                    std::string det_name(mes);
                    write(ms, "add_details_name", sizeof("add_details_name"));
                    write(ms, mes, sizeof(mes));

                    // читаем количество деталей
                    int det_quant;
                    if (!(in >> det_quant)) { write(ms, "error", sizeof("error"));  return -2; }
                    write(ms, "add_details_quant", sizeof("add_details_quant"));
                    bzero(mes, sizeof(mes));
                    sprintf(mes, "%d", det_quant);
                    write(ms, mes, sizeof(mes));

                    // добавляем детали в базу
                    add_detail(det_name, det_quant);
                }
            }

        // добавление карты
        if (strcmp(mes, "add_map") == 0)
        {
            std::vector <std::string> map;
            map.resize(1);

            // читаем название первой детали
            if (!(in >> mes)) { write(ms, "error", sizeof("error"));  return -3; }
            std::string det_name0(mes);
            map[0] = det_name0;

            while (1)
            {
                // читаем название детали / сообщение об окончинии добавления
                if (!(in >> mes)) { write(ms, "error", sizeof("error"));  return -4; }
                if (strcmp(mes, "end") == 0)
                    break;
                else
                {
                    std::string det_name1(mes);
                    map.resize(map.size() + 2);
                    map[map.size() - 2] = det_name1;
                    printf("    detail = %s, ", mes);

                    // читаем количество деталей
                    if (!(in >> mes)) { write(ms, "error", sizeof("error"));  return -5; }
                    printf("quant = %s\n", mes);
                    std::string det_quant1(mes);
                    map[map.size() - 1] = det_quant1;
                }
            }

            // добавляем карту в базу
            add_map(map);
        }

        // можно ли создать деталь по карте №...
        if (strcmp(mes, "can_build_map_#") == 0)
        {
            // читаем номер карты (порядок с единицы)
            int map_num;
            if (!(in >> map_num)) { write(ms, "error", sizeof("error"));  return -6; }

            // считаем сколько деталей можно создать
            int det_kol = can_build_map(map_num);
            if (det_kol < 0) { write(ms, "error", sizeof("error"));  return -7; }
            std::cout << "    can build " << det_kol << " details '" << name[map[map_num - 1].res] << "'\n";
        }

        // можно ли создать деталь по карте ...
        if (strcmp(mes, "can_build_map") == 0)
        {
            std::vector <std::string> map;
            map.resize(1);

            // читаем название первой детали
            if (!(in >> mes)) { write(ms, "error", sizeof("error"));  return -8; }
            std::string det_name0(mes);
            map[0] = det_name0;

            while (1)
            {
                // читаем название детали / сообщение об окончинии добавления
                if (!(in >> mes)) { write(ms, "error", sizeof("error"));  return -9; }
                if (strcmp(mes, "end") == 0)
                    break;
                else
                {
                    std::string det_name1(mes);
                    map.resize(map.size() + 2);
                    map[map.size() - 2] = det_name1;
                    printf("    detail = %s, ", mes);

                    // читаем количество деталей
                    if (!(in >> mes)) { write(ms, "error", sizeof("error"));  return -10; }
                    printf("quant = %s\n", mes);
                    std::string det_quant1(mes);
                    map[map.size() - 1] = det_quant1;
                }
            }

            // считаем сколько деталей можно создать
            int det_kol = can_build_map(map);
            if (det_kol < 0) { write(ms, "error", sizeof("error"));  return -11; }
            std::cout << "    can build " << det_kol << " details '" << map[0] << "'\n";
        }

        // создать деталь по карте
        if (strcmp(mes, "build_map_#") == 0)
        {
            // читаем номер карты (порядок с единицы)
            int map_num;
            if (!(in >> map_num)) { write(ms, "error", sizeof("error"));  return -12; }

            // читаем количество деталей которые надо создать 
            int map_kol;
            if (!(in >> map_kol)) { write(ms, "error", sizeof("error"));  return -13; }

            // считаем сколько деталей можно создать
            int det_kol = build_map(map_num, map_kol);
            if (det_kol < 0) { write(ms, "error", sizeof("error"));  return -14; }
            std::cout << "    builded " << det_kol << " details '" << name[map[map_num - 1].res] << "'\n";
        }

        // прочитать команды из файла
        if (strcmp(mes, "read_from_file") == 0)
        {
            // читаем название файла
            if (!(in >> mes)) { write(ms, "error", sizeof("error"));  return -15; }
            std::cout << "    start reading from file '" << mes << "'\n";
            std::ifstream fin(mes);
            if (!fin.is_open()) { write(ms, "error", sizeof("error"));  return -16; }

            int er_code = do_from(fin, ms);
            if (er_code < 0) return er_code;
            fin.close();
            std::cout << "    file '" << mes << "' closed\n";
        }

        // показать компоненты базы
        if (strcmp(mes, "show_details") == 0)
            show_details();
        if (strcmp(mes, "show_maps") == 0)
            show_maps();
        if (strcmp(mes, "show_base") == 0)
            show_base();

    }

	return 0;
}
