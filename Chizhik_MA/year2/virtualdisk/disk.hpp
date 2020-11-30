#pragma once
#include <iostream>
#include <cstdlib>
#include <cstring>

#define DEBUG

#define FREE_CLUSTER -1
#define LAST_CLUSTER -2
#define BAD_CLUSTER -3

// Файловый контейнер, реализованный по аналогии с файловой системой FAT
class VirtualDisk {
	public:
		class File {
			private:
				// Индекс первого кластера файла
				int start_;
		
				// Количество байт в файле
				unsigned int len_;

				// Тип файла
				// 0 - обычный файл, 1 - директория
				// unsigned int type_;

				// Расположение файла (иерархическая система еще не реализована)
				// -1 - корневая директория, неотрицательное значение - индекс директории в FAT
				// int parent_;
		
				// Имя файла
				std::string name_;
		
				// Время создания
				// const unsigned int creation_time_;
				// Время последнего изменения
				// unsigned int mod_time_;
			public:	
				// Конструктор
				File();

				// Объявление класса VirtualDisk дружественным
				friend class VirtualDisk;
		};
		typedef typename VirtualDisk::File FileObject;
	private:
		// Указатель на выделенную память (виртуальный диск)
		unsigned char* disk_;

		// Объем диска (в байтах)
		const unsigned int DISK_SIZE_;

		// Размер кластера (в байтах)
		const unsigned int CLUSTER_SIZE_;

		// Таблица ссылок между блоками (FAT)
		int* table_;

		// Размер таблицы FAT
		unsigned int FAT_SIZE_;
	
		// Массив описаний файлов
		FileObject* dir_;

		// Текущее количество файлов в системе
		int files_amount_;

		// Найти запись о файле в корневой директории по его имени
		// Если параметр required равен true и файла с таким именем не находится, вызывается исключение
		FileObject* find(const std::string& name, bool required = true) const;

		// Выделить новый кластер под файл
		// Если last_cluster_index равен FREE_CLUSTER, подразумевается, что кластер выделяется для нового файла, и привязки к уже существующей цепочке не происходит
		int bind_next_cluster(int last_cluster_index);
	public:
		// Конструтор
		// Параметры по умолчанию: размер диска - 50 МБ, размер кластера - 4 КБ
		VirtualDisk(unsigned int size = (50 << 20), unsigned int cluster_size = 4096);

		// Деструктор
		~VirtualDisk();

		// Создание файла
		// Если файл с таким именем уже есть, будет вызвано исключение
		FileObject* create(const std::string& name);

		// Удаление файла с именем name
		// Если файла с таким именем нет, будет вызвано исключение
		void rm(const std::string& name);

		// Копирование файла
		// Если другой файл носит имя, которым предполагается назвать копию, то он будет перезаписан
		void cp(const std::string& name, const std::string& copy_name);

		// Переименование файла с именем old_name 
		// Если другой файл имеет имя, на которое меняется имя файла с текущим именем old_name, то он будет утерян
		void mv(const std::string& old_name, const std::string& new_name);

		// Получение длины файла
		int wc(const std::string& name) const;

		// Записать заданное количество байт
		void write(const std::string& name, unsigned int start_position, unsigned int bytes_amount, unsigned char* to_write);

		// Прочтение заданного количества байт
		void read(const std::string& name, unsigned int start_position, unsigned int bytes_amount, unsigned char* dest) const;

		// Получение списка существующих файлов
		void ls(std::ostream& os = std::cout) const;

		#ifdef DEBUG
		void printFAT() const;
		#endif
};

class VirtualDiskException {
	private:
		// Код ошибки
		const int code_;

		// Сообщение для пользователя
		const std::string reason_;
	public:
		// Конструктор исключения
		VirtualDiskException(int code, const std::string& error_msg): code_(code), reason_(error_msg) {}
		// Получение кода ошибки
		int code() const { return code_; }
		// Получение сообщения об ошибке
		const std::string& message() const { return reason_; }

		// Оператор форматированного вывода ошибки
		friend std::ostream& operator<<(std::ostream& os, const VirtualDiskException& e);
};
