#pragma once
#include <iostream>
#include <climits>

class BitIntSet {
	public:
		// Итератор по расширяемому битовому множеству
		// Позволяет последовательно перебрать элементы множества в порядке возрастания или убывания
		// Можно начинать перебор не с первого элемента или выбирать элементы с определенной периодичностью
		// Итерируемое множество считается неизменным на протяжении работы итератора. Если множество было изменено, корректность работы итератора не гарантируется
		class Iterator {
			private:
				// Указатель на итерируемое множество
				const BitIntSet* parent_set_;

  		      		// Текущий элемент
	  		      	int curr_position_;
				// Индекс текущего элемента
				int curr_index_;

				// Шаг итератора
				int step_;
			public:
				// Объявление класса BitIntSet дружественным
				friend class BitIntSet;

				// Конструкторы
				// Получает на вход указатель на итерируемое множество, 
				// индекс, с которого нужно начинать обход (по умолчанию обход начинается 
				// с первого элемента множества) и шаг (по умолчанию равен 1)
				// Если шаг равен 0, или индекс начала обхода превосходит мощность множества, 
				// вызывается исключение
				Iterator(const BitIntSet* parent_set, int start_index = 0, int step = 1);
				// Конструктор копирования
				Iterator(const Iterator& iter);

				// Деструктор
				~Iterator();

  		      		// Получение предыдущего и следующего элементов
	  		      	int next();
  			      	int prev();

				// Выполнение шага итератора (abs(step_) раз вперед или назад 
				// в зависимости от знака step_)
				// Если совершено меньше, чем step_ шагов, но граница множества 
				// уже достигнута, выполнение останавливается и не вызывает исключение
				int next_step();
					
				// Получение текущего элемента
  			      	int curr() const { return curr_position_; }
				// Получение индекса текущего элемента
				int curr_index() const { return curr_index_; }
				// Получение значения шага итератора
				int step() const { return step_; }

				// Установка итератора в положение начала/конца соответственно
  		      		void begin();
	  		      	void end();

  			      	// Проверки итератора на регулярность (выход влево/вправо за границы множества)
  		      		bool at_begin() const { return curr_index_ < 0; }
  			      	bool at_end() const { return curr_index_ >= parent_set_->len_; }
		};
		typedef typename BitIntSet::Iterator iterator;
	private:
		// Число битов в целочисленной переменной
		const static int INT_CARDINALITY = (int)(CHAR_BIT * sizeof(int));

		// Границы множества
		int inf_;
		int sup_;

		// Целочисленный массив, используемый для хранения информации о том, 
		// какие элементы содержатся в множестве
		unsigned int* list_;

		// Длина массива list_
		int size_;

		// Число, соответствующее первому биту массива
		// (выделение памяти происходит с небольшим запасом в обе стороны, 
		// поэтому inf_ и list_start_ могут не совпадать)
		int list_start_;

		// Мощность множества
		int len_;

		// Запрет вызова конструктора без параметров
		BitIntSet();
	public:
		// Конструктор
		// На вход получает левую и правую границы диапазона значений
		BitIntSet(int left, int right);

		// Конструктор копирования
		// На вход получает константную ссылку на некоторый экземпляр класса 
		// и копирует его в новый объект
		BitIntSet(const BitIntSet& set);

		// Деструктор
		~BitIntSet();

		// Очистка множества
		// Превращает множество в пустое с таким же заданным диапазоном 
		void clear();

		// Проверка пустоты множества
		// Если множество пусто, возвращает true, иначе - false
		bool empty() const { return len_ == 0; }

		// Получение длины множества
		// Возвращает мощность множества
		int len() const { return len_; }

		// Добавление в множество элемента со значением a
		// В случае, если элемента со значением a нет в множестве, добавляет его туда,
		// иначе никаких действий не производится
		void add(int a);

		// Удаление из множества элемента со значением a
		// При попытке удалить из множества элемент, не содержащийся в нем,
		// метод не производит никаких действий и
		// возвращает -1; в случае успешного удаления элемента возвращает 0 
		int remove(int a);

		// Проверка на то, является ли целое число a элементом множества
		bool belongs(int a) const;

		// Нахождение минимума и максимума 
		int min() const;
		int max() const;

		// Получение границ диапазона множества
		int left() const { return inf_; }
		int right() const { return sup_; }

		iterator start(int start_index = 0, int step = 1) const;

		// Получение элемента с порядковым номером index, если упорядочить множество по возрастанию
		// Перегруженный оператор взятия индекса является псевдонимом метода get
		int get(int index) const;
		int operator[](int index) const;

		// Операторы пересечения, объединения, разности и симметрической разности множеств
		// соответственно
		friend BitIntSet operator*(const BitIntSet& A, const BitIntSet& B);
		friend BitIntSet operator+(const BitIntSet& A, const BitIntSet& B);
		friend BitIntSet operator-(const BitIntSet& A, const BitIntSet& B);
		friend BitIntSet operator^(const BitIntSet& A, const BitIntSet& B);

		// Перегруженный оператор присваивания
		BitIntSet& operator=(const BitIntSet& B);

		// Операторы присваивания
		BitIntSet& operator*=(const BitIntSet& B);
		BitIntSet& operator+=(const BitIntSet& B);
		BitIntSet& operator-=(const BitIntSet& B);
		BitIntSet& operator^=(const BitIntSet& B);

		// Оператор подмножества
		// Если A - подмножество B, возвращает true, иначе - false
		friend bool operator<=(const BitIntSet& A, const BitIntSet& B);

		// Операторы равенства
		// Если все элементы совпадают, возвращают true, иначе - false
		friend bool operator==(const BitIntSet& A, const BitIntSet& B);

		// Оператор вывода множества
		// Печатает упорядоченные в порядке возрастания элементы множества
		friend std::ostream& operator<<(std::ostream& os, const BitIntSet& set);
};

class BitIntSetException {
	private:
		// Код ошибки
		const int error_code_;
		// Сообщение для пользователя
		const std::string reason_;
	public:
		// Конструктор исключения
		BitIntSetException(int code, const std::string& message): error_code_(code), reason_(message) {}
		// Получение кода ошибки
		int code() const { return error_code_; }
		// Получение сообщения
		const std::string& message() const { return reason_; }

		// Оператор форматированного вывода ошибки
		friend std::ostream& operator<<(std::ostream& os, const BitIntSetException& e);
};
