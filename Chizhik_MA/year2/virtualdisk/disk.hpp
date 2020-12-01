#pragma once
#include <iostream>
#include <cstdlib>
#include <cstring>

#define DEBUG

#define LAST_CLUSTER -1
#define FREE_CLUSTER -2
#define BAD_CLUSTER -9

// Файловый контейнер, реализованный по аналогии с файловой системой FAT
class VirtualDisk {
	public:
		class File {
			private:
				// Индекс первого кластера файла
				int start_;
		
				// Количество байт в файле
				unsigned int len_;

				// Тип файла (еще не используется)
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
		int* FAT_;

		// Размер таблицы FAT
		unsigned int FAT_SIZE_;
	
		// Массив описаний файлов (корневая директория)
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
		// Конструктор
		// Параметры по умолчанию: размер диска - 50 МБ, размер кластера - 4 КБ
		// Размеру кластера разрешается не делить размер диска; в таких случаях появляется память, которая не может быть использована для хранения информации
		// Минимальный размер диска - 64 байта, кластера - 4 байта
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
		// Если другой файл имеет имя new_name, то он будет утерян
		void mv(const std::string& old_name, const std::string& new_name);

		// Получение длины файла с именем name
		// Если такого файла нет, вызывается исключение
		int wc(const std::string& name) const;

		// Записать bytes_amount байт из to_write в файл с именем name, начиная с позиции start_position
		// Подразумевается, что память на все требуемые байты выделена
		// Запись по смещению, превосходящему длину файла, не считается исключительной ситуацией;
		// однако в этом случае не определено значение предшествующих байт в файле
		void write(const std::string& name, unsigned int start_position, unsigned int bytes_amount, unsigned char* to_write);

		// Прочтение bytes_amount байт из файла с именем name в dest, начиная с позиции start_position
		// Если последний байт, который нужно прочитать, выходит за границы файла, вызывается исключение
		void read(const std::string& name, unsigned int start_position, unsigned int bytes_amount, unsigned char* dest) const;

		// Удаление последних bytes_amount байтов
		// Если какие-то кластеры, принадлежащие файлу, полностью освобождаются от байтов, 
		// соответствующих файлу, они становятся доступными для выделения
		// Если длина файла меньше bytes_amount, она обнуляется
		void del(const std::string& name, unsigned int bytes_amount);

		// Вывод списка существующих на диске файлов в поток os (по умолчанию - std::cout)
		void ls(std::ostream& os = std::cout) const;

		#ifdef DEBUG
		// Отладочная печать таблицы FAT
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
