int Base::do_from(std::istream& in)
{
    char mes[1024];
    // ���� ��������� ������ ���������
    for (int o = 1; o == 1; o++)
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

    }

	return 0;
}
