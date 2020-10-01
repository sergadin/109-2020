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
		intset(const intset& IS);
		bool find_item(int item) const; // найти элемент в множестве
		void put(int item); // добавить item в конец множества
		void del(int item); // удалить элементы со значением item из множества
		bool is_empty() const // проверка пустоты множества
		{
			return size_ == 0;
		}
		bool size() const // вычисление количества элементов множества
		{
			return size_;
		}
		int find_max() const; // максимальный элемент в множестве
		int find_min() const; // минимальный элемент в множестве
		int left_bord() const // левая граница множества
		{
			return minval_;
		}
		int right_bord() const // правая граница множества
		{
			return maxval_;
		}

		friend intset& operator* (const intset &left, const intset &right); // пересечение двух множеств
		friend intset& operator*= (intset &left, const intset &right); // пересечение множества с другим множеством

};
