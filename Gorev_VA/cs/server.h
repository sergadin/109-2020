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

    }

	return 0;
}
