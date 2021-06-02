int Base::do_from(std::istream& in)
{
    char mes[1024];
    // цикл обработки одного сообщения
    for (int o = 1; o == 1; o++)
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

    }

	return 0;
}
