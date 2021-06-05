#include <iostream>
#include <fstream>
#include <sstream>

int Base::do_from(std::istream& in, int ms)
{
    char mes[1024];
    char key[1024];
    bzero(mes, sizeof(mes));
    bzero(key, sizeof(key));
    int count = 0;
    // цикл обработки одного сообщения
    while(1)
    {
        // читаем первую команду
        if (!(in >> mes))
        {
            bzero(key, sizeof(key));
            strcpy(key, "END");
            write(ms, key, sizeof(key));
            return 0;
        }
        write(ms, mes, sizeof(mes));
        printf("  command = %s, size = %d\n", mes, strlen(mes));

        // добавление деталей
        if (strcmp(mes, "add_details") == 0)
        {
            count = 0;
            while (1)
            {
                // читаем название детали / сообщение об окончинии добавления
                if (!(in >> mes))
                {
                    bzero(key, sizeof(key));
                    strcpy(key, "error");
                    write(ms, key, sizeof(key));
                    return -1;
                }

                if (strcmp(mes, "end") == 0)
                    break;
                else
                {
                    count++;
                    std::string det_name(mes);
                    bzero(key, sizeof(key));
                    strcpy(key, "add_details_name");
                    write(ms, key, sizeof(key));
                    sprintf(key, "%d", count);
                    write(ms, key, sizeof(key));
                    write(ms, mes, sizeof(mes));
                    printf("    new detail = %s\n", mes);

                    // читаем количество деталей
                    int det_quant;
                    if (!(in >> det_quant))
                    {
                        strcpy(mes, "error");
                        write(ms, mes, sizeof(mes));
                        return -2;
                    }
                    bzero(key, sizeof(key));
                    strcpy(key, "add_details_quant");
                    write(ms, key, sizeof(key));
                    sprintf(key, "%d", count);
                    write(ms, key, sizeof(key));
                    bzero(mes, sizeof(mes));
                    sprintf(mes, "%d", det_quant);
                    write(ms, mes, sizeof(mes));
                    printf("quant = %d\n", det_quant);

                    // добавляем детали в базу
                    add_detail(det_name, det_quant);
                }
            }
            continue;
        }
            

        // добавление карты
        if (strcmp(mes, "add_map") == 0)
        {
            count = 0;
            std::vector <std::string> map;
            map.resize(1);

            // читаем название первой детали
            if (!(in >> mes))
            {
                bzero(key, sizeof(key));
                strcpy(key, "error");
                write(ms, key, sizeof(key));
                return -3;
            }
            std::string det_name0(mes);
            map[0] = det_name0;
            bzero(key, sizeof(key));
            strcpy(key, "add_map_res");
            write(ms, key, sizeof(key));
            write(ms, mes, sizeof(mes));

            while (1)
            {
                // читаем название детали / сообщение об окончинии добавления
                if (!(in >> mes))
                {
                    bzero(key, sizeof(key));
                    strcpy(key, "error");
                    write(ms, key, sizeof(key));
                    return -4;
                }
                if (strcmp(mes, "end") == 0)
                    break;
                else
                {
                    count++;
                    std::string det_name1(mes);
                    map.resize(map.size() + 2);
                    map[map.size() - 2] = det_name1;
                    printf("    detail = %s, ", mes);
                    bzero(key, sizeof(key));
                    strcpy(key, "add_map_comp_name");
                    write(ms, key, sizeof(key));
                    sprintf(key, "%d", count);
                    write(ms, key, sizeof(key));
                    write(ms, mes, sizeof(mes));

                    // читаем количество деталей
                    if (!(in >> mes))
                    {
                        bzero(key, sizeof(key));
                        strcpy(key, "error");
                        write(ms, key, sizeof(key));
                        return -5;
                    }
                    printf("quant = %s\n", mes);
                    bzero(key, sizeof(key));
                    strcpy(key, "add_map_comp_quant");
                    write(ms, key, sizeof(key));
                    sprintf(key, "%d", count);
                    write(ms, key, sizeof(key));
                    write(ms, mes, sizeof(mes));
                    std::string det_quant1(mes);
                    map[map.size() - 1] = det_quant1;
                }
            }

            // добавляем карту в базу
            add_map(map);
            continue;
        }

        // можно ли создать деталь по карте №...
        if (strcmp(mes, "can_build_map_#") == 0)
        {
            // читаем номер карты (порядок с единицы)
            int map_num;
            if (!(in >> map_num))
            {
                bzero(key, sizeof(key));
                strcpy(key, "error");
                write(ms, key, sizeof(key));
                return -6;
            }

            bzero(key, sizeof(key));
            strcpy(key, "can_build_map_#_num");
            write(ms, key, sizeof(key));
            bzero(mes, sizeof(mes));
            sprintf(mes, "%d", map_num);
            write(ms, mes, sizeof(mes));

            // считаем сколько деталей можно создать
            int det_kol = can_build_map(map_num);
            if (det_kol < 0)
            {
                bzero(key, sizeof(key));
                strcpy(key, "error");
                write(ms, key, sizeof(key));
                return -7;
            }
            bzero(key, sizeof(key));
            strcpy(key, "can_build_map_#_quant");
            write(ms, key, sizeof(key));
            bzero(mes, sizeof(mes));
            sprintf(mes, "%d", det_kol);
            write(ms, mes, sizeof(mes));
            bzero(mes, sizeof(mes));
            std::istringstream sin(name[map[map_num - 1].res]);
            sin >> mes;
            write(ms, mes, sizeof(mes));
            std::cout << "    can build " << det_kol << " details '" << name[map[map_num - 1].res] << "'\n";
            continue;
        }

        // можно ли создать деталь по карте ...
        if (strcmp(mes, "can_build_map") == 0)
        {
            count = 0;
            std::vector <std::string> map;
            map.resize(1);

            // читаем название первой детали
            if (!(in >> mes))
            {
                bzero(key, sizeof(key));
                strcpy(key, "error");
                write(ms, key, sizeof(key));
                return -8;
            }
            std::string det_name0(mes);
            map[0] = det_name0;
            bzero(key, sizeof(key));
            strcpy(key, "can_build_map_res");
            write(ms, key, sizeof(key));
            write(ms, mes, sizeof(mes));

            while (1)
            {
                // читаем название детали / сообщение об окончинии добавления
                if (!(in >> mes))
                {
                    bzero(key, sizeof(key));
                    strcpy(key, "error");
                    write(ms, key, sizeof(key));
                    return -9;
                }
                if (strcmp(mes, "end") == 0)
                    break;
                else
                {
                    count++;
                    std::string det_name1(mes);
                    map.resize(map.size() + 2);
                    map[map.size() - 2] = det_name1;
                    printf("    detail = %s, ", mes);
                    bzero(key, sizeof(key));
                    strcpy(key, "can_build_map_comp_name");
                    write(ms, key, sizeof(key));
                    sprintf(key, "%d", count);
                    write(ms, key, sizeof(key));
                    write(ms, mes, sizeof(mes));

                    // читаем количество деталей
                    if (!(in >> mes))
                    {
                        bzero(key, sizeof(key));
                        strcpy(key, "error");
                        write(ms, key, sizeof(key));
                        return -10;
                    }
                    printf("quant = %s\n", mes);
                    std::string det_quant1(mes);
                    map[map.size() - 1] = det_quant1;
                    bzero(key, sizeof(key));
                    strcpy(key, "can_build_map_comp_quant");
                    write(ms, key, sizeof(key));
                    sprintf(key, "%d", count);
                    write(ms, key, sizeof(key));
                    write(ms, mes, sizeof(mes));
                }
            }

            // считаем сколько деталей можно создать
            int det_kol = can_build_map(map);
            if (det_kol < 0)
            {
                bzero(key, sizeof(key));
                strcpy(key, "error");
                write(ms, key, sizeof(key));
                return -11;
            }
            std::cout << "    can build " << det_kol << " details '" << map[0] << "'\n";
            bzero(key, sizeof(key));
            strcpy(key, "can_build_map_quant");
            write(ms, key, sizeof(key));
            bzero(mes, sizeof(mes));
            sprintf(mes, "%d", det_kol);
            write(ms, mes, sizeof(mes));
            std::istringstream sin1(map[0]);
            sin1 >> mes;
            write(ms, mes, sizeof(mes));
            continue;
        }

        // создать деталь по карте
        if (strcmp(mes, "build_map_#") == 0)
        {
            // читаем номер карты (порядок с единицы)
            int map_num;
            if (!(in >> map_num))
            {
                bzero(key, sizeof(key));
                strcpy(key, "error");
                write(ms, key, sizeof(key));
                return -12;
            }
            bzero(key, sizeof(key));
            strcpy(key, "build_map_#_num");
            write(ms, key, sizeof(key));
            bzero(mes, sizeof(mes));
            sprintf(mes, "%d", map_num);
            write(ms, mes, sizeof(mes));

            // читаем количество деталей которые надо создать 
            int map_kol;
            if (!(in >> map_kol))
            {
                bzero(key, sizeof(key));
                strcpy(key, "error");
                write(ms, key, sizeof(key));
                return -13;
            }
            bzero(key, sizeof(key));
            strcpy(key, "build_map_#_quant");
            write(ms, key, sizeof(key));
            bzero(mes, sizeof(mes));
            sprintf(mes, "%d", map_kol);
            write(ms, mes, sizeof(mes));
            bzero(mes, sizeof(mes));
            std::istringstream sin2(name[map[map_num - 1].res]);
            sin2 >> mes;
            write(ms, mes, sizeof(mes));

            // считаем сколько деталей можно создать
            int det_kol = build_map(map_num, map_kol);
            if (det_kol < 0)
            {
                bzero(key, sizeof(key));
                strcpy(key, "error");
                write(ms, key, sizeof(key));
                return -14;
            }
            std::cout << "    builded " << det_kol << " details '" << name[map[map_num - 1].res] << "'\n";
            bzero(key, sizeof(key));
            strcpy(key, "build_map_#_builded");
            write(ms, key, sizeof(key));
            bzero(mes, sizeof(mes));
            sprintf(mes, "%d", map_kol);
            write(ms, mes, sizeof(mes));
            bzero(mes, sizeof(mes));
            std::istringstream sin3(name[map[map_num - 1].res]);
            sin3 >> mes;
            write(ms, mes, sizeof(mes));
            continue;
        }

        // прочитать команды из файла
        if (strcmp(mes, "read_from_file") == 0)
        {
            // читаем название файла
            if (!(in >> mes))
            {
                bzero(key, sizeof(key));
                strcpy(key, "error");
                write(ms, key, sizeof(key));
                return -15;
            }
            std::cout << "    start reading from file '" << mes << "'\n";
            std::ifstream fin(mes);
            if (!fin.is_open())
            {
                bzero(key, sizeof(key));
                strcpy(key, "error");
                write(ms, key, sizeof(key));
                return -16;
            }
            bzero(key, sizeof(key));
            strcpy(key, "read_from_file_open");
            write(ms, key, sizeof(key));
            write(ms, mes, sizeof(mes));

            int er_code = do_from(fin, ms);
            if (er_code < 0) { fin.close(); return er_code; }
            fin.close();
            std::cout << "    file '" << mes << "' closed\n";
            bzero(key, sizeof(key));
            strcpy(key, "read_from_file_close");
            write(ms, key, sizeof(key));
            write(ms, mes, sizeof(mes));
            continue;
        }

        // показать компоненты базы
        if (strcmp(mes, "show_details") == 0)
        {
            show_details(ms);
            continue;
        }
            
        if (strcmp(mes, "show_maps") == 0)
        {
            show_maps(ms);
            continue;
        }
            
        if (strcmp(mes, "show_base") == 0)
        {
            show_base(ms);
            continue;
        }

        // удалить детали
        if (strcmp(mes, "del_details") == 0)
        {
            count = 0;
            while (1)
            {
                // читаем название детали / сообщение об окончинии удаления
                if (!(in >> mes))
                {
                    bzero(key, sizeof(key));
                    strcpy(key, "error");
                    write(ms, key, sizeof(key));
                    return -17;
                }

                if (strcmp(mes, "end") == 0)
                    break;
                else
                {
                    count++;
                    std::string det_name(mes);
                    bzero(key, sizeof(key));
                    strcpy(key, "del_details_name");
                    write(ms, key, sizeof(key));
                    sprintf(key, "%d", count);
                    write(ms, key, sizeof(key));
                    write(ms, mes, sizeof(mes));
                    printf("    deleted detail = %s\n", mes);

                    // читаем количество деталей
                    int det_quant;
                    if (!(in >> det_quant))
                    {
                        strcpy(mes, "error");
                        write(ms, mes, sizeof(mes));
                        return -18;
                    }
                    bzero(key, sizeof(key));
                    strcpy(key, "del_details_quant");
                    write(ms, key, sizeof(key));
                    sprintf(key, "%d", count);
                    write(ms, key, sizeof(key));
                    bzero(mes, sizeof(mes));
                    sprintf(mes, "%d", det_quant);
                    write(ms, mes, sizeof(mes));
                    printf("quant = %d\n", det_quant);

                    // удяляем детали из базы
                    if (del_detail(det_name, det_quant) < 0)
                    {
                        strcpy(mes, "error");
                        write(ms, mes, sizeof(mes));
                        return -19;
                    }
                }
            }
            continue;
        }

        // записать базу в файл
        if (strcmp(mes, "write_in_file") == 0)
        {
            // читаем название файла
            if (!(in >> mes))
            {
                bzero(key, sizeof(key));
                strcpy(key, "error");
                write(ms, key, sizeof(key));
                return -20;
            }
            std::cout << "    start reading from file '" << mes << "'\n";
            std::ofstream fout(mes);
            if (!fout.is_open())
            {
                bzero(key, sizeof(key));
                strcpy(key, "error");
                write(ms, key, sizeof(key));
                return -21;
            }
            bzero(key, sizeof(key));
            strcpy(key, "write_in_file_open");
            write(ms, key, sizeof(key));
            write(ms, mes, sizeof(mes));

            write_in_file(fout);
            fout.close();
            std::cout << "    file '" << mes << "' closed\n";
            bzero(key, sizeof(key));
            strcpy(key, "write_in_file_close");
            write(ms, key, sizeof(key));
            write(ms, mes, sizeof(mes));
            continue;
        }
    }

	return 0;
}
