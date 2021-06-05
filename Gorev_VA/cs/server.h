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
    // ���� ��������� ������ ���������
    while(1)
    {
        // ������ ������ �������
        if (!(in >> mes))
        {
            bzero(key, sizeof(key));
            strcpy(key, "END");
            write_mes(ms, key);
            return 0;
        }
        write_mes(ms, mes);
        printf("  command = %s, size = %d\n", mes, strlen(mes));

        // ���������� �������
        if (strcmp(mes, "add_details") == 0)
        {
            count = 0;
            while (1)
            {
                // ������ �������� ������ / ��������� �� ��������� ����������
                if (!(in >> mes))
                {
                    bzero(key, sizeof(key));
                    strcpy(key, "error");
                    write_mes(ms, key);
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
                    write_mes(ms, key);
                    sprintf(key, "%d", count);
                    write_mes(ms, key);
                    write_mes(ms, mes);
                    printf("    new detail = %s\n", mes);

                    // ������ ���������� �������
                    int det_quant;
                    if (!(in >> det_quant))
                    {
                        strcpy(mes, "error");
                        write_mes(ms, mes);
                        return -2;
                    }
                    bzero(key, sizeof(key));
                    strcpy(key, "add_details_quant");
                    write_mes(ms, key);
                    sprintf(key, "%d", count);
                    write_mes(ms, key);
                    bzero(mes, sizeof(mes));
                    sprintf(mes, "%d", det_quant);
                    write_mes(ms, mes);
                    printf("quant = %d\n", det_quant);

                    // ��������� ������ � ����
                    add_detail(det_name, det_quant);
                }
            }
            continue;
        }
            

        // ���������� �����
        if (strcmp(mes, "add_map") == 0)
        {
            count = 0;
            std::vector <std::string> map;
            map.resize(1);

            // ������ �������� ������ ������
            if (!(in >> mes))
            {
                bzero(key, sizeof(key));
                strcpy(key, "error");
                write_mes(ms, key);
                return -3;
            }
            std::string det_name0(mes);
            map[0] = det_name0;
            bzero(key, sizeof(key));
            strcpy(key, "add_map_res");
            write_mes(ms, key);
            write_mes(ms, mes);

            while (1)
            {
                // ������ �������� ������ / ��������� �� ��������� ����������
                if (!(in >> mes))
                {
                    bzero(key, sizeof(key));
                    strcpy(key, "error");
                    write_mes(ms, key);
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
                    write_mes(ms, key);
                    sprintf(key, "%d", count);
                    write_mes(ms, key);
                    write_mes(ms, mes);

                    // ������ ���������� �������
                    if (!(in >> mes))
                    {
                        bzero(key, sizeof(key));
                        strcpy(key, "error");
                        write_mes(ms, key);
                        return -5;
                    }
                    printf("quant = %s\n", mes);
                    bzero(key, sizeof(key));
                    strcpy(key, "add_map_comp_quant");
                    write_mes(ms, key);
                    sprintf(key, "%d", count);
                    write_mes(ms, key);
                    write_mes(ms, mes);
                    std::string det_quant1(mes);
                    map[map.size() - 1] = det_quant1;
                }
            }

            // ��������� ����� � ����
            add_map(map);
            continue;
        }

        // ����� �� ������� ������ �� ����� �...
        if (strcmp(mes, "can_build_map_#") == 0)
        {
            // ������ ����� ����� (������� � �������)
            int map_num;
            if (!(in >> map_num))
            {
                bzero(key, sizeof(key));
                strcpy(key, "error");
                write_mes(ms, key);
                return -6;
            }

            bzero(key, sizeof(key));
            strcpy(key, "can_build_map_#_num");
            write_mes(ms, key);
            bzero(mes, sizeof(mes));
            sprintf(mes, "%d", map_num);
            write_mes(ms, mes);

            // ������� ������� ������� ����� �������
            int det_kol = can_build_map(map_num);
            if (det_kol < 0)
            {
                bzero(key, sizeof(key));
                strcpy(key, "error");
                write_mes(ms, key);
                return -7;
            }
            bzero(key, sizeof(key));
            strcpy(key, "can_build_map_#_quant");
            write_mes(ms, key);
            bzero(mes, sizeof(mes));
            sprintf(mes, "%d", det_kol);
            write_mes(ms, mes);
            bzero(mes, sizeof(mes));
            std::istringstream sin(name[map[map_num - 1].res]);
            sin >> mes;
            write_mes(ms, mes);
            std::cout << "    can build " << det_kol << " details '" << name[map[map_num - 1].res] << "'\n";
            continue;
        }

        // ����� �� ������� ������ �� ����� ...
        if (strcmp(mes, "can_build_map") == 0)
        {
            count = 0;
            std::vector <std::string> map;
            map.resize(1);

            // ������ �������� ������ ������
            if (!(in >> mes))
            {
                bzero(key, sizeof(key));
                strcpy(key, "error");
                write_mes(ms, key);
                return -8;
            }
            std::string det_name0(mes);
            map[0] = det_name0;
            bzero(key, sizeof(key));
            strcpy(key, "can_build_map_res");
            write_mes(ms, key);
            write_mes(ms, mes);

            while (1)
            {
                // ������ �������� ������ / ��������� �� ��������� ����������
                if (!(in >> mes))
                {
                    bzero(key, sizeof(key));
                    strcpy(key, "error");
                    write_mes(ms, key);
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
                    write_mes(ms, key);
                    sprintf(key, "%d", count);
                    write_mes(ms, key);
                    write_mes(ms, mes);

                    // ������ ���������� �������
                    if (!(in >> mes))
                    {
                        bzero(key, sizeof(key));
                        strcpy(key, "error");
                        write_mes(ms, key);
                        return -10;
                    }
                    printf("quant = %s\n", mes);
                    std::string det_quant1(mes);
                    map[map.size() - 1] = det_quant1;
                    bzero(key, sizeof(key));
                    strcpy(key, "can_build_map_comp_quant");
                    write_mes(ms, key);
                    sprintf(key, "%d", count);
                    write_mes(ms, key);
                    write_mes(ms, mes);
                }
            }

            // ������� ������� ������� ����� �������
            int det_kol = can_build_map(map);
            if (det_kol < 0)
            {
                bzero(key, sizeof(key));
                strcpy(key, "error");
                write_mes(ms, key);
                return -11;
            }
            std::cout << "    can build " << det_kol << " details '" << map[0] << "'\n";
            bzero(key, sizeof(key));
            strcpy(key, "can_build_map_quant");
            write_mes(ms, key);
            bzero(mes, sizeof(mes));
            sprintf(mes, "%d", det_kol);
            write_mes(ms, mes);
            std::istringstream sin1(map[0]);
            sin1 >> mes;
            write_mes(ms, mes);
            continue;
        }

        // ������� ������ �� �����
        if (strcmp(mes, "build_map_#") == 0)
        {
            // ������ ����� ����� (������� � �������)
            int map_num;
            if (!(in >> map_num))
            {
                bzero(key, sizeof(key));
                strcpy(key, "error");
                write_mes(ms, key);
                return -12;
            }
            bzero(key, sizeof(key));
            strcpy(key, "build_map_#_num");
            write_mes(ms, key);
            bzero(mes, sizeof(mes));
            sprintf(mes, "%d", map_num);
            write_mes(ms, mes);

            // ������ ���������� ������� ������� ���� ������� 
            int map_kol;
            if (!(in >> map_kol))
            {
                bzero(key, sizeof(key));
                strcpy(key, "error");
                write_mes(ms, key);
                return -13;
            }
            bzero(key, sizeof(key));
            strcpy(key, "build_map_#_quant");
            write_mes(ms, key);
            bzero(mes, sizeof(mes));
            sprintf(mes, "%d", map_kol);
            write_mes(ms, mes);
            bzero(mes, sizeof(mes));
            std::istringstream sin2(name[map[map_num - 1].res]);
            sin2 >> mes;
            write_mes(ms, mes);

            // ������� ������� ������� ����� �������
            int det_kol = build_map(map_num, map_kol);
            if (det_kol < 0)
            {
                bzero(key, sizeof(key));
                strcpy(key, "error");
                write_mes(ms, key);
                return -14;
            }
            std::cout << "    builded " << det_kol << " details '" << name[map[map_num - 1].res] << "'\n";
            bzero(key, sizeof(key));
            strcpy(key, "build_map_#_builded");
            write_mes(ms, key);
            bzero(mes, sizeof(mes));
            sprintf(mes, "%d", map_kol);
            write_mes(ms, mes);
            bzero(mes, sizeof(mes));
            std::istringstream sin3(name[map[map_num - 1].res]);
            sin3 >> mes;
            write_mes(ms, mes);
            continue;
        }

        // ��������� ������� �� �����
        if (strcmp(mes, "read_from_file") == 0)
        {
            // ������ �������� �����
            if (!(in >> mes))
            {
                bzero(key, sizeof(key));
                strcpy(key, "error");
                write_mes(ms, key);
                return -15;
            }
            std::cout << "    start reading from file '" << mes << "'\n";
            std::ifstream fin(mes);
            if (!fin.is_open())
            {
                bzero(key, sizeof(key));
                strcpy(key, "error");
                write_mes(ms, key);
                return -16;
            }
            bzero(key, sizeof(key));
            strcpy(key, "read_from_file_open");
            write_mes(ms, key);
            write_mes(ms, mes);

            int er_code = do_from(fin, ms);
            if (er_code < 0) { fin.close(); return er_code; }
            fin.close();
            std::cout << "    file '" << mes << "' closed\n";
            bzero(key, sizeof(key));
            strcpy(key, "read_from_file_close");
            write_mes(ms, key);
            write_mes(ms, mes);
            continue;
        }

        // �������� ���������� ����
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

        // ������� ������
        if (strcmp(mes, "del_details") == 0)
        {
            count = 0;
            while (1)
            {
                // ������ �������� ������ / ��������� �� ��������� ��������
                if (!(in >> mes))
                {
                    bzero(key, sizeof(key));
                    strcpy(key, "error");
                    write_mes(ms, key);
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
                    write_mes(ms, key);
                    sprintf(key, "%d", count);
                    write_mes(ms, key);
                    write_mes(ms, mes);
                    printf("    deleted detail = %s\n", mes);

                    // ������ ���������� �������
                    int det_quant;
                    if (!(in >> det_quant))
                    {
                        strcpy(mes, "error");
                        write_mes(ms, mes);
                        return -18;
                    }
                    bzero(key, sizeof(key));
                    strcpy(key, "del_details_quant");
                    write_mes(ms, key);
                    sprintf(key, "%d", count);
                    write_mes(ms, key);
                    bzero(mes, sizeof(mes));
                    sprintf(mes, "%d", det_quant);
                    write_mes(ms, mes);
                    printf("quant = %d\n", det_quant);

                    // ������� ������ �� ����
                    if (del_detail(det_name, det_quant) < 0)
                    {
                        strcpy(mes, "error");
                        write_mes(ms, mes);
                        return -19;
                    }
                }
            }
            continue;
        }

        // �������� ���� � ����
        if (strcmp(mes, "write_in_file") == 0)
        {
            // ������ �������� �����
            if (!(in >> mes))
            {
                bzero(key, sizeof(key));
                strcpy(key, "error");
                write_mes(ms, key);
                return -20;
            }
            std::cout << "    start reading from file '" << mes << "'\n";
            std::ofstream fout(mes);
            if (!fout.is_open())
            {
                bzero(key, sizeof(key));
                strcpy(key, "error");
                write_mes(ms, key);
                return -21;
            }
            bzero(key, sizeof(key));
            strcpy(key, "write_in_file_open");
            write_mes(ms, key);
            write_mes(ms, mes);

            write_in_file(fout);
            fout.close();
            std::cout << "    file '" << mes << "' closed\n";
            bzero(key, sizeof(key));
            strcpy(key, "write_in_file_close");
            write_mes(ms, key);
            write_mes(ms, mes);
            continue;
        }
    }

	return 0;
}
