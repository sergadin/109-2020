int Base::do_from(std::istream& in)
{
    char mes[1024];
    // ���� ��������� ������ ���������
    while (1)
    {
        // ������ ������ �������
        in >> mes;
        printf("  command = %s, size = %d\n", mes, strlen(mes));

        // ���������� �������
        if (strcmp(mes, "add_details") == 0)
            while (1)
            {
                // ������ �������� ������ / ��������� �� ��������� ����������
                in >> mes;

                if (strcmp(mes, "end") == 0)
                    break;
                else
                {
                    printf("    new detail = %s, ", mes);

                    // ������ ���������� �������
                    int det_quant;
                    in >> det_quant;
                    printf("quant = %d\n", det_quant);

                    // ��������� ������ � ����
                    std::string det_name(mes);
                    add_detail(det_name, det_quant);
                }
            }

        /*// ���������� �����
        if (strcmp(mes, "add_map") == 0)
        {
            std::vector <std::string> map;
            map.resize(1);

            // ������ �������� ������ ������
            if (scan_next(cur, mes) == -1) { close(as); return -1; }
            std::string det_name0(mes);
            map[0] = det_name0;

            while (1)
            {
                // ������ �������� ������ / ��������� �� ��������� ����������
                if (scan_next(cur, mes) == -1) { close(as); return -1; }
                if (strcmp(mes, "end") == 0)
                    break;
                else
                {
                    std::string det_name1(mes);
                    map.resize(map.size() + 2);
                    map[map.size() - 2] = det_name1;
                    printf("    detail = %s, ", mes);

                    // ������ ���������� �������
                    if (scan_next(cur, mes) == -1) { close(as); return -1; }
                    printf("quant = %s\n", mes);
                    std::string det_quant1(mes);
                    map[map.size() - 1] = det_quant1;
                }
            }

            // ��������� ����� � ����
            B.add_map(map);
        }

        // ����� �� ������� ������ �� ����� �...
        if (strcmp(mes, "can_build_map_#") == 0)
        {
            // ������ ����� ����� (������� � �������)
            int map_num;
            if (scan_next(cur, map_num) == -1) { close(as); return -1; }

            // ������� ������� ������� ����� �������
            int det_kol = B.can_build_map(map_num);
            if (det_kol < 0) { close(as); return -1; }
            std::cout << "    can build " << det_kol << " details '" << B.name[B.map[map_num - 1].res] << "'\n";
        }

        // ����� �� ������� ������ �� ����� ...
        if (strcmp(mes, "can_build_map") == 0)
        {
            std::vector <std::string> map;
            map.resize(1);

            // ������ �������� ������ ������
            if (scan_next(cur, mes) == -1) { close(as); return -1; }
            std::string det_name0(mes);
            map[0] = det_name0;

            while (1)
            {
                // ������ �������� ������ / ��������� �� ��������� ����������
                if (scan_next(cur, mes) == -1) { close(as); return -1; }
                if (strcmp(mes, "end") == 0)
                    break;
                else
                {
                    std::string det_name1(mes);
                    map.resize(map.size() + 2);
                    map[map.size() - 2] = det_name1;
                    printf("    detail = %s, ", mes);

                    // ������ ���������� �������
                    if (scan_next(cur, mes) == -1) { close(as); return -1; }
                    printf("quant = %s\n", mes);
                    std::string det_quant1(mes);
                    map[map.size() - 1] = det_quant1;
                }
            }

            // ������� ������� ������� ����� �������
            int det_kol = B.can_build_map(map);
            if (det_kol < 0) { close(as); return -1; }
            std::cout << "    can build " << det_kol << " details '" << map[0] << "'\n";
        }

        // ������� ������ �� �����
        if (strcmp(mes, "build_map_#") == 0)
        {
            // ������ ����� ����� (������� � �������)
            int map_num;
            if (scan_next(cur, map_num) == -1) { close(as); return -1; }

            // ������ ���������� ������� ������� ���� ������� 
            int map_kol;
            if (scan_next(cur, map_kol) == -1) { close(as); return -1; }

            // ������� ������� ������� ����� �������
            int det_kol = B.build_map(map_num, map_kol);
            if (det_kol < 0) { close(as); return -1; }
            std::cout << "    builded " << det_kol << " details '" << B.name[B.map[map_num - 1].res] << "'\n";
        }

        // �������� ���������� ����
        if (strcmp(mes, "show_details") == 0)
            B.show_details();
        if (strcmp(mes, "show_maps") == 0)
            B.show_maps();
        if (strcmp(mes, "show_base") == 0)
            B.show_base();*/

        if (cur[0] == 0) break;
    }

	return 0;
}
