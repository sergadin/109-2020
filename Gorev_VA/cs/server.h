int Base::do_from(std::istream& in)
{
    char mes[1024];
    // цикл обработки одного сообщения
    while (1)
    {
        // читаем первую команду
        in >> mes;
        printf("  command = %s, size = %d\n", mes, strlen(mes));

        // добавление деталей
        if (strcmp(mes, "add_details") == 0)
            while (1)
            {
                // читаем название детали / сообщение об окончинии добавления
                in >> mes;

                if (strcmp(mes, "end") == 0)
                    break;
                else
                {
                    printf("    new detail = %s, ", mes);

                    // читаем количество деталей
                    int det_quant;
                    in >> det_quant;
                    printf("quant = %d\n", det_quant);

                    // добавляем детали в базу
                    std::string det_name(mes);
                    add_detail(det_name, det_quant);
                }
            }

        /*// добавление карты
        if (strcmp(mes, "add_map") == 0)
        {
            std::vector <std::string> map;
            map.resize(1);

            // читаем название первой детали
            if (scan_next(cur, mes) == -1) { close(as); return -1; }
            std::string det_name0(mes);
            map[0] = det_name0;

            while (1)
            {
                // читаем название детали / сообщение об окончинии добавления
                if (scan_next(cur, mes) == -1) { close(as); return -1; }
                if (strcmp(mes, "end") == 0)
                    break;
                else
                {
                    std::string det_name1(mes);
                    map.resize(map.size() + 2);
                    map[map.size() - 2] = det_name1;
                    printf("    detail = %s, ", mes);

                    // читаем количество деталей
                    if (scan_next(cur, mes) == -1) { close(as); return -1; }
                    printf("quant = %s\n", mes);
                    std::string det_quant1(mes);
                    map[map.size() - 1] = det_quant1;
                }
            }

            // добавляем карту в базу
            B.add_map(map);
        }

        // можно ли создать деталь по карте №...
        if (strcmp(mes, "can_build_map_#") == 0)
        {
            // читаем номер карты (порядок с единицы)
            int map_num;
            if (scan_next(cur, map_num) == -1) { close(as); return -1; }

            // считаем сколько деталей можно создать
            int det_kol = B.can_build_map(map_num);
            if (det_kol < 0) { close(as); return -1; }
            std::cout << "    can build " << det_kol << " details '" << B.name[B.map[map_num - 1].res] << "'\n";
        }

        // можно ли создать деталь по карте ...
        if (strcmp(mes, "can_build_map") == 0)
        {
            std::vector <std::string> map;
            map.resize(1);

            // читаем название первой детали
            if (scan_next(cur, mes) == -1) { close(as); return -1; }
            std::string det_name0(mes);
            map[0] = det_name0;

            while (1)
            {
                // читаем название детали / сообщение об окончинии добавления
                if (scan_next(cur, mes) == -1) { close(as); return -1; }
                if (strcmp(mes, "end") == 0)
                    break;
                else
                {
                    std::string det_name1(mes);
                    map.resize(map.size() + 2);
                    map[map.size() - 2] = det_name1;
                    printf("    detail = %s, ", mes);

                    // читаем количество деталей
                    if (scan_next(cur, mes) == -1) { close(as); return -1; }
                    printf("quant = %s\n", mes);
                    std::string det_quant1(mes);
                    map[map.size() - 1] = det_quant1;
                }
            }

            // считаем сколько деталей можно создать
            int det_kol = B.can_build_map(map);
            if (det_kol < 0) { close(as); return -1; }
            std::cout << "    can build " << det_kol << " details '" << map[0] << "'\n";
        }

        // создать деталь по карте
        if (strcmp(mes, "build_map_#") == 0)
        {
            // читаем номер карты (порядок с единицы)
            int map_num;
            if (scan_next(cur, map_num) == -1) { close(as); return -1; }

            // читаем количество деталей которые надо создать 
            int map_kol;
            if (scan_next(cur, map_kol) == -1) { close(as); return -1; }

            // считаем сколько деталей можно создать
            int det_kol = B.build_map(map_num, map_kol);
            if (det_kol < 0) { close(as); return -1; }
            std::cout << "    builded " << det_kol << " details '" << B.name[B.map[map_num - 1].res] << "'\n";
        }

        // показать компоненты базы
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
