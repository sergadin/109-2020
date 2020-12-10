#pragma once
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <climits>

#define DEBUG

#define LAST_CLUSTER -1
#define BAD_CLUSTER -9

// Файловый контейнер, реализованный по аналогии с файловой системой FAT
class VirtualDisk {
	public:
		const static unsigned int RECORD_SIZE = 64;
		class FileObj {
			private:
				// Ссылка на диск 
				VirtualDisk *parent_disk_;

				// Индекс первого кластера файла
				int *start_;
			
				// Количество байт в файле
				unsigned int *len_;

				// Тип файла
				// 0 - обычный файл, 1 - директория
				unsigned char *type_;
			
				// Имя файла
				char *name_;
			
				// Время создания
				time_t *creation_time_;
				// Время последнего изменения
				time_t *mod_time_;

				// Создание объекта для работы с существующим файлом по его файловой записи
				// При вызове конструктора корректность указателя подразумевается
				FileObj(VirtualDisk* disk, void* file_record);
			public:
				// Деструктор
				~FileObj() {}

				// Получение строки с именем файла
				// На возвращаемую строку динамически выделяется память, необходим вызов free() по окончании использования строки
				char* name() const;

				// Удаление файла
				void rm();

				// Получение длины файла
				unsigned int wc() const;

				// Записать bytes_amount байт из to_write, начиная с позиции start_position
				// Подразумевается, что память на все требуемые байты выделена
				// Запись по смещению, превосходящему длину файла, не считается исключительной ситуацией;
				// однако в этом случае не определено значение предшествующих байт в файле
				void write(unsigned int start_position, unsigned int bytes_amount, unsigned char* to_write);

				// Прочтение bytes_amount байт в dest, начиная с позиции start_position в файле
				// Если последний байт, который нужно прочитать, выходит за границы файла, вызывается исключение
				void read(unsigned int start_position, unsigned int bytes_amount, unsigned char* dest) const;

				// Удаление последних bytes_amount байтов
				// Если какие-то кластеры, принадлежащие файлу, полностью освобождаются от байтов, 
				// соответствующих файлу, они становятся доступными для выделения
				// Если длина файла меньше bytes_amount, она обнуляется
				void del(unsigned int bytes_amount);

				// Переименование файла
				// Если другой файл располагается по адресу new_path, то он будет утерян
				void mv(const char *new_path);

				// Вывод списка файлов директории в поток os (по умолчанию в std::cout)
				void ls(std::ostream& os = std::cout);

				// Объявление класса VirtualDisk дружественным
				friend class VirtualDisk;
		};
		typedef typename VirtualDisk::FileObj File;
	private:
		// Указатель на выделенную память (виртуальный диск)
		unsigned char *disk_;

		// Объем диска (в байтах)
		const unsigned int DISK_SIZE_;

		// Размер кластера (в байтах)
		const unsigned int CLUSTER_SIZE_;

		// Таблица ссылок между блоками (FAT)
		int *FAT_;

		// Размер таблицы FAT
		unsigned int FAT_SIZE_;

		// Найти файл по его пути
		// Если параметр required равен true и файла с таким именем не находится, вызывается исключение
		// Параметр prohibited_parent_fcluster содержит номер первого кластера директории, которая не должна содержать данного файла.
		// Если она будет содержаться в пути к файлу, будет вызвано исключение
		File* find(const char *path, bool required = true, int prohibited_parent_fcluster = -1);

		// Выделить новый кластер под файл с последним кластером, имеющим индекс last_cluster_index
		// Если last_cluster_index равен LAST_CLUSTER, подразумевается, что кластер выделяется для нового файла, и привязки к уже существующей цепочке не происходит
		int bind_next_cluster(int last_cluster_index);

		// Вспомогательная функция для копирования файлов
		// В функцию подаются указатели на файловые записи копируемого файла и свободной файловой записи, а также (при рекурсивном копировании) запись родителя создаваемой копии и глубина рекурсии
		void copy_file(void *file, void *copy_path, void *parent_r = NULL, unsigned int depth = 1);

		// Функция добавления стандартных файловых записей папки
		// На вход подаются номера первых кластеров папки и ее родителя
		void add_default_dir_records(int start, int parent_start);
	public:
		// Конструктор
		// Параметры по умолчанию: размер диска - 50 МБ, размер кластера - 4 КБ
		// Размеру кластера разрешается не делить размер диска; в таких случаях появляется память, которая не может быть использована для хранения информации
		// Минимальный размер диска - 64 байта, кластера - 4 байта
		VirtualDisk(unsigned int size = (50 << 20), unsigned int cluster_size = 4096);

		// Деструктор
		~VirtualDisk();

		// Открытие файла (получение указателя на объект для работы с файлом)
		File* open(const char *path);

		// Создание файла по адресу path
		// Если файл с таким путем уже есть, будет вызвано исключение
		// Если type = 1, создается директория, в которой первые две записи 
		// занимаются файлами . и .. (нулевой длины)
		// Возвращает указатель на объект для работы с файлом
		File* create(const char *path, unsigned char type = 0);

		// Копирование файла file
		// Если другой файл носит имя, которым предполагается назвать копию, то он будет перезаписан
		File* cp(File* file, const char *copy_path);

		#ifdef DEBUG
		// Отладочная печать таблицы FAT
		void printFAT(int amount) const;
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
