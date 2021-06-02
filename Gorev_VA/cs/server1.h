int Base::read_from(std::istream& in)
{
	int i = 1;
	std::string str;
	while (in >> str)
	{
		std::cout << i << ") " << str << "\n";
		i++;
	}
	std::cout << "It's done\n";
	return 0;
}
