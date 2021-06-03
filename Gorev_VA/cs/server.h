#include <iostream>
#include <fstream>
#include <sstream>

int Base::do_from(std::istream& in, int ms)
{
    char mes[1024];
    // ���� ��������� ������ ���������
    while(1)
    {
        // ������ ������ �������
        if (in >> mes)
            write(ms, mes, sizeof(mes));
        else
        {
            write(ms, "END", sizeof("END"));
            return 0;
        }

        // ���������� �������
        if (strcmp(mes, "add_details") == 0)
            while (1)
            {
                // ������ �������� ������ / ��������� �� ��������� ����������
                if (!(in >> mes)) { write(ms, "error", sizeof("error"));  return -1; }

                if (strcmp(mes, "end") == 0)
                    break;
                else
                {
                    std::string det_name(mes);
                    write(ms, "add_details_name", sizeof("add_details_name"));
                    write(ms, mes, sizeof(mes));

                    // ������ ���������� �������
                    int det_quant;
                    if (!(in >> det_quant)) { write(ms, "error", sizeof("error"));  return -2; }
                    write(ms, "add_details_quant", sizeof("add_details_quant"));
                    bzero(mes, sizeof(mes));
                    sprintf(mes, "%d", det_quant);
                    write(ms, mes, sizeof(mes));

                    // ��������� ������ � ����
                    add_detail(det_name, det_quant);
                }
            }

        // ���������� �����
        if (strcmp(mes, "add_map") == 0)
        {
            std::vector <std::string> map;
            map.resize(1);

            // ������ �������� ������ ������
            if (!(in >> mes)) { write(ms, "error", sizeof("error"));  return -3; }
            std::string det_name0(mes);
            map[0] = det_name0;

            while (1)
            {
                // ������ �������� ������ / ��������� �� ��������� ����������
                if (!(in >> mes)) { write(ms, "error", sizeof("error"));  return -4; }
                if (strcmp(mes, "end") == 0)
                    break;
                else
                {
                    std::string det_name1(mes);
                    map.resize(map.size() + 2);
                    map[map.size() - 2] = det_name1;
                    printf("    detail = %s, ", mes);

                    // ������ ���������� �������
                    if (!(in >> mes)) { write(ms, "error", sizeof("error"));  return -5; }
                    printf("quant = %s\n", mes);
                    std::string det_quant1(mes);
                    map[map.size() - 1] = det_quant1;
                }
            }

            // ��������� ����� � ����
            add_map(map);
        }

        // ����� �� ������� ������ �� ����� �...
        if (strcmp(mes, "can_build_map_#") == 0)
        {
            // ������ ����� ����� (������� � �������)
            int map_num;
            if (!(in >> map_num)) { write(ms, "error", sizeof("error"));  return -6; }

            // ������� ������� ������� ����� �������
            int det_kol = can_build_map(map_num);
            if (det_kol < 0) { write(ms, "error", sizeof("error"));  return -7; }
            std::cout << "    can build " << det_kol << " details '" << name[map[map_num - 1].res] << "'\n";
        }

        // ����� �� ������� ������ �� ����� ...
        if (strcmp(mes, "can_build_map") == 0)
        {
            std::vector <std::string> map;
            map.resize(1);

            // ������ �������� ������ ������
            if (!(in >> mes)) { write(ms, "error", sizeof("error"));  return -8; }
            std::string det_name0(mes);
            map[0] = det_name0;

            while (1)
            {
                // ������ �������� ������ / ��������� �� ��������� ����������
                if (!(in >> mes)) { write(ms, "error", sizeof("error"));  return -9; }
                if (strcmp(mes, "end") == 0)
                    break;
                else
                {
                    std::string det_name1(mes);
                    map.resize(map.size() + 2);
                    map[map.size() - 2] = det_name1;
                    printf("    detail = %s, ", mes);

                    // ������ ���������� �������
                    if (!(in >> mes)) { write(ms, "error", sizeof("error"));  return -10; }
                    printf("quant = %s\n", mes);
                    std::string det_quant1(mes);
                    map[map.size() - 1] = det_quant1;
                }
            }

            // ������� ������� ������� ����� �������
            int det_kol = can_build_map(map);
            if (det_kol < 0) { write(ms, "error", sizeof("error"));  return -11; }
            std::cout << "    can build " << det_kol << " details '" << map[0] << "'\n";
        }

        // ������� ������ �� �����
        if (strcmp(mes, "build_map_#") == 0)
        {
            // ������ ����� ����� (������� � �������)
            int map_num;
            if (!(in >> map_num)) { write(ms, "error", sizeof("error"));  return -12; }

            // ������ ���������� ������� ������� ���� ������� 
            int map_kol;
            if (!(in >> map_kol)) { write(ms, "error", sizeof("error"));  return -13; }

            // ������� ������� ������� ����� �������
            int det_kol = build_map(map_num, map_kol);
            if (det_kol < 0) { write(ms, "error", sizeof("error"));  return -14; }
            std::cout << "    builded " << det_kol << " details '" << name[map[map_num - 1].res] << "'\n";
        }

        // ��������� ������� �� �����
        if (strcmp(mes, "read_from_file") == 0)
        {
            // ������ �������� �����
            if (!(in >> mes)) { write(ms, "error", sizeof("error"));  return -15; }
            std::cout << "    start reading from file '" << mes << "'\n";
            std::ifstream fin(mes);
            if (!fin.is_open()) { write(ms, "error", sizeof("error"));  return -16; }

            int er_code = do_from(fin, ms);
            if (er_code < 0) return er_code;
            fin.close();
            std::cout << "    file '" << mes << "' closed\n";
        }

        // �������� ���������� ����
        if (strcmp(mes, "show_details") == 0)
            show_details();
        if (strcmp(mes, "show_maps") == 0)
            show_maps();
        if (strcmp(mes, "show_base") == 0)
            show_base();

    }

	return 0;
}
