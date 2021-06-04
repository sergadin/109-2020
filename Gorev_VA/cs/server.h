#include <iostream>
#include <fstream>
#include <sstream>

int Base::do_from(std::istream& in, int ms)
{
    char mes[1024];
    char key[1024];
    // ���� ��������� ������ ���������
    while(1)
    {
        // ������ ������ �������
        if (!(in >> mes))
        {
            bzero(key, sizeof(key));
            strcpy(key, "END");
            std::cout << "~" << key << ", " << write(ms, key, sizeof(key)) << "\n";
            return 0;
        }
        std::cout << mes << ", " << write(ms, mes, sizeof(mes)) << "\n";
        printf("  command = %s, size = %d\n", mes, strlen(mes));

        // ���������� �������
        if (strcmp(mes, "add_details") == 0)
            while (1)
            {
                // ������ �������� ������ / ��������� �� ��������� ����������
                if (!(in >> mes))
                {
                    bzero(key, sizeof(key));
                    strcpy(key, "error");
                    std::cout << "~~" << key << ", " << write(ms, key, sizeof(key)) << "\n";
                    return -1;
                }

                if (strcmp(mes, "end") == 0)
                    break;
                else
                {
                    std::string det_name(mes);
                    bzero(key, sizeof(key));
                    strcpy(key, "add_details_name");
                    std::cout << "~~~" << key << ", " << write(ms, key, sizeof(key)) << "\n";
                    std::cout << "~~~" << mes << ", " << write(ms, mes, sizeof(mes)) << "\n";
                    printf("    new detail = %s, ", mes);

                    // ������ ���������� �������
                    int det_quant;
                    if (!(in >> det_quant))
                    {
                        strcpy(mes, "error");
                        std::cout << "~~~~" << mes << ", " << write(ms, mes, sizeof(mes)) << "\n";
                        return -2;
                    }
                    bzero(key, sizeof(key));
                    strcpy(key, "add_details_quant");
                    std::cout << "~~~" << key << ", " << write(ms, key, sizeof(key)) << "\n";
                    bzero(mes, sizeof(mes));
                    sprintf(key, "%d", det_quant);
                    strcpy(mes, key);
                    std::cout << "~~~~" << mes << ", " << write(ms, mes, sizeof(mes)) << "\n";
                    printf("quant = %d\n", det_quant);

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
            if (!(in >> mes)) return -3;
            std::string det_name0(mes);
            map[0] = det_name0;

            while (1)
            {
                // ������ �������� ������ / ��������� �� ��������� ����������
                if (!(in >> mes)) return -4;
                if (strcmp(mes, "end") == 0)
                    break;
                else
                {
                    std::string det_name1(mes);
                    map.resize(map.size() + 2);
                    map[map.size() - 2] = det_name1;
                    printf("    detail = %s, ", mes);

                    // ������ ���������� �������
                    if (!(in >> mes)) return -5;
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
            if (!(in >> map_num)) return -6;

            // ������� ������� ������� ����� �������
            int det_kol = can_build_map(map_num);
            if (det_kol < 0) { return -6; }
            std::cout << "    can build " << det_kol << " details '" << name[map[map_num - 1].res] << "'\n";
        }

        // ����� �� ������� ������ �� ����� ...
        if (strcmp(mes, "can_build_map") == 0)
        {
            std::vector <std::string> map;
            map.resize(1);

            // ������ �������� ������ ������
            if (!(in >> mes)) return -7;
            std::string det_name0(mes);
            map[0] = det_name0;

            while (1)
            {
                // ������ �������� ������ / ��������� �� ��������� ����������
                if (!(in >> mes)) return -8;
                if (strcmp(mes, "end") == 0)
                    break;
                else
                {
                    std::string det_name1(mes);
                    map.resize(map.size() + 2);
                    map[map.size() - 2] = det_name1;
                    printf("    detail = %s, ", mes);

                    // ������ ���������� �������
                    if (!(in >> mes)) return -9;
                    printf("quant = %s\n", mes);
                    std::string det_quant1(mes);
                    map[map.size() - 1] = det_quant1;
                }
            }

            // ������� ������� ������� ����� �������
            int det_kol = can_build_map(map);
            if (det_kol < 0) { return -10; }
            std::cout << "    can build " << det_kol << " details '" << map[0] << "'\n";
        }

        // ������� ������ �� �����
        if (strcmp(mes, "build_map_#") == 0)
        {
            // ������ ����� ����� (������� � �������)
            int map_num;
            if (!(in >> map_num)) return -11;

            // ������ ���������� ������� ������� ���� ������� 
            int map_kol;
            if (!(in >> map_kol)) return -12;

            // ������� ������� ������� ����� �������
            int det_kol = build_map(map_num, map_kol);
            if (det_kol < 0) { return -13; }
            std::cout << "    builded " << det_kol << " details '" << name[map[map_num - 1].res] << "'\n";
        }

        // ��������� ������� �� �����
        if (strcmp(mes, "read_from_file") == 0)
        {
            // ������ �������� �����
            if (!(in >> mes)) return -13;
            std::cout << "    start reading from file '" << mes << "'\n";
            std::ifstream fin(mes);
            if (!fin.is_open()) return -14;

            int er_code = do_from(fin, ms);
            if (er_code < 0) return er_code;
            fin.close();
            std::cout << "    file '" << mes << "' closed\n";

            // ������� ������� ������� ����� �������
            //int det_kol = can_build_map(map_num);
            //if (det_kol < 0) { return -6; }
            //std::cout << "    can build " << det_kol << " details '" << name[map[map_num - 1].res] << "'\n";
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
