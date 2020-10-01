class intset
{
	private:
		int *ar_;
		int size_;
		int maxval_;
		int minval_;
	public:
		intset(int maxval, int minval);
		~intset();
		intset(intset& IS);
		void put(int item); // добавить item в конец множества
		void del(int item); // удалить элементы со значением item из множества
		bool is_empty() // проверка пустоты множества
		{
			return size_ == 0;
		}
		bool size() // вычисление количества элементов множества
		{
			return size_;
		}
		int find_max(); // максимальный элемент в множестве
		int find_min(); // минимальный элемент в множестве
		int left_bord() // левая граница множества
		{
			return minval_;
		}
		int right_bord() // правая граница множества
		{
			return maxval_;
		}

};
