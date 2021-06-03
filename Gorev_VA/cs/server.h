int Base::do_from(std::istream& in)
{
    char mes[1024];
    // цикл обработки одного сообщения
    while(1)
    {
        // читаем первую команду
        if (!(in >> mes)) return 0;
        printf("  command = %s, size = %d\n", mes, strlen(mes));

        // добавление деталей
        if (strcmp(mes, "add_details") == 0)
            while (1)
            {
                // читаем название детали / сообщение об окончинии добавления
                if (!(in >> mes)) return -1;

                if (strcmp(mes, "end") == 0)
                    break;
                else
                {
                    printf("    new detail = %s, ", mes);

                    // читаем количество деталей
                    int det_quant;
                    if (!(in >> det_quant)) return -2;
                    printf("quant = %d\n", det_quant);

                    // добавляем детали в базу
                    std::string det_name(mes);
                    add_detail(det_name, det_quant);
                }
            }

        // добавление карты
        if (strcmp(mes, "add_map") == 0)
        {
            std::vector <std::string> map;
            map.resize(1);

            // читаем название первой детали
            if (!(in >> mes)) return -3;
            std::string det_name0(mes);
            map[0] = det_name0;

            while (1)
            {
                // читаем название детали / сообщение об окончинии добавления
                if (!(in >> mes)) return -4;
                if (strcmp(mes, "end") == 0)
                    break;
                else
                {
                    std::string det_name1(mes);
                    map.resize(map.size() + 2);
                    map[map.size() - 2] = det_name1;
                    printf("    detail = %s, ", mes);

                    // читаем количество деталей
                    if (!(in >> mes)) return -5;
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
            if (!(in >> map_num)) return -6;

            // считаем сколько деталей можно создать
            int det_kol = can_build_map(map_num);
            if (det_kol < 0) { return -6; }
            std::cout << "    can build " << det_kol << " details '" << name.map[map_num - 1].res] << "'\n";
        }

        // можно ли создать деталь по карте ...
        if (strcmp(mes, "can_build_map") == 0)
        {
            std::vector <std::string> map;
            map.resize(1);

            // читаем название первой детали
            if (!(in >> mes)) return -7;
            std::string det_name0(mes);
            map[0] = det_name0;

            while (1)
            {
                // читаем название детали / сообщение об окончинии добавления
                if (!(in >> mes)) return -8;
                if (strcmp(mes, "end") == 0)
                    break;
                else
                {
                    std::string det_name1(mes);
                    map.resize(map.size() + 2);
                    map[map.size() - 2] = det_name1;
                    printf("    detail = %s, ", mes);

                    // читаем количество деталей
                    if (!(in >> mes)) return -9;
                    printf("quant = %s\n", mes);
                    std::string det_quant1(mes);
                    map[map.size() - 1] = det_quant1;
                }
            }

            // считаем сколько деталей можно создать
            int det_kol = B.can_build_map(map);
            if (det_kol < 0) { return -10; }
            std::cout << "    can build " << det_kol << " details '" << map[0] << "'\n";
        }

        // создать деталь по карте
        if (strcmp(mes, "build_map_#") == 0)
        {
            // читаем номер карты (порядок с единицы)
            int map_num;
            if (!(in >> map_num)) return -11;

            // читаем количество деталей которые надо создать 
            int map_kol;
            if (!(in >> map_kol)) return -12;

            // считаем сколько деталей можно создать
            int det_kol = build_map(map_num, map_kol);
            if (det_kol < 0) { return -13; }
            std::cout << "    builded " << det_kol << " details '" << name[map[map_num - 1].res] << "'\n";
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
