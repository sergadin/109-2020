#include "disk.hpp"

VirtualDisk::File::File() {
	start_ = -1;
	len_ = 0;
	name_ = "";
	//type_ = 0;
	//parent_ = -1;
}

#ifdef DEBUG
void VirtualDisk::printFAT() const {
	for (int i = 0; i < FAT_SIZE_; i++) {
		std::cout << i << ": " << table_[i] << "; " << std::endl;
	}
}
#endif

VirtualDisk::VirtualDisk(unsigned int size, unsigned int cluster_size) : 
			DISK_SIZE_(size), CLUSTER_SIZE_(cluster_size) {
	if ((size % cluster_size != 0) || cluster_size < 2 || size < 32) {
		throw VirtualDiskException(1, "Incorrect disk parameters");
	}
	FAT_SIZE_ = DISK_SIZE_ / CLUSTER_SIZE_;

	try {
		disk_ = new unsigned char[size];
	} catch (const std::bad_alloc& e) {
		throw VirtualDiskException(2, "Can't allocate memory");
	}

	try {
		table_ = new int[FAT_SIZE_];
		for (int i = 0; i < FAT_SIZE_; i++) {
			table_[i] = FREE_CLUSTER;
		}
	} catch (const std::bad_alloc& e) {
		throw VirtualDiskException(3, "Can't create FAT");
	}

	try {
		dir_ = new File[FAT_SIZE_];
	} catch (const std::bad_alloc& e) {
		throw VirtualDiskException(4, "Can't create root directory");
	}

	files_amount_ = 0;
}

VirtualDisk::~VirtualDisk() {
	delete[] disk_;
	delete[] table_;
	delete[] dir_;
}

VirtualDisk::File* VirtualDisk::find(const std::string& name, bool required) const {
	FileObject *file = NULL;
	if (name == "") {
		throw VirtualDiskException(5, "Impossible filename");
	}

	for (int i = 0; i < files_amount_; i++) {
		if (dir_[i].name_ == name) {
			file = dir_ + i;
			break;
		}
	}

	if ((file == NULL) && required) {
		throw VirtualDiskException(6, "File doesn't exist");
	}
	return file;
}

int VirtualDisk::bind_next_cluster(int last_cluster_index) {
	if (last_cluster_index < 0 && last_cluster_index != FREE_CLUSTER) {
		return BAD_CLUSTER;
	} 

	if (last_cluster_index >= 0 && table_[last_cluster_index] != LAST_CLUSTER) {
		return BAD_CLUSTER;
	}

	for (int i = 0; i < FAT_SIZE_; i++) {
		if (table_[i] == FREE_CLUSTER) {
			if (last_cluster_index != FREE_CLUSTER) {
				table_[last_cluster_index] = i;
			}

			table_[i] = LAST_CLUSTER;
			return i;
		}
	}
	throw VirtualDiskException(7, "Not enough memory");
}

VirtualDisk::File* VirtualDisk::create(const std::string& name) {
	FileObject *file = find(name, false);
	if (name == "") {
		throw VirtualDiskException(5, "Impossible filename");
	}
	if (file != NULL) {
		throw VirtualDiskException(8, "File already exists");
	}

	dir_[files_amount_].start_ = bind_next_cluster(FREE_CLUSTER);
	dir_[files_amount_].name_ = name;
	files_amount_++;

	return dir_ + (files_amount_ - 1);
}

void VirtualDisk::rm(const std::string& name) {
	FileObject *file = find(name);
	int *current_cluster = table_ + file->start_;
	int *next_cluster;

	while (*current_cluster >= 0) {
		next_cluster = table_ + *current_cluster;
		*current_cluster = FREE_CLUSTER;
		current_cluster = next_cluster;
	}

	if (*current_cluster == LAST_CLUSTER) {
		*current_cluster = FREE_CLUSTER;
	}

	int deleted_file_index = file - dir_;
	files_amount_--;
	for (int i = deleted_file_index; i < files_amount_; i++) {
		dir_[i] = dir_[i + 1];
	}
}

void VirtualDisk::cp(const std::string& name, const std::string& copy_name) {
	if (copy_name == name) {
		throw VirtualDiskException(8, "File already exists");
	}

	FileObject *file = find(name);
	FileObject *copy_address = find(copy_name, false);

	if (copy_address != NULL) {
		rm(copy_name);
	}

	copy_address = create(copy_name);

	
	int current_src_cluster = table_[file->start_];
	int current_dest_cluster = table_[copy_address->start_];

	int k = 0;
	while (current_src_cluster >= 0) {
		if (k > 0) {
			if ((current_dest_cluster = bind_next_cluster(current_dest_cluster)) == BAD_CLUSTER) {
				throw VirtualDiskException(9, "Unknown memory error");
			}
		}

		for (int i = 0; i < CLUSTER_SIZE_; i++, k++) {
			if (k >= file->len_) {
				break;
			}
			disk_[CLUSTER_SIZE_ * table_[current_dest_cluster] + i] = disk_[CLUSTER_SIZE_ * table_[current_src_cluster] + i];
		}
		current_src_cluster = table_[current_src_cluster];		
	}

	files_amount_++;
	if (k < file->len_ || current_src_cluster != LAST_CLUSTER) {
		throw VirtualDiskException(10, "Reading the file has led to an error");
	}
}

void VirtualDisk::mv(const std::string& name, const std::string& new_name) {
	if (new_name == name) {
		throw VirtualDiskException(8, "File already exists");
	}

	FileObject *file = find(name);
	FileObject *new_address = find(new_name, false);
	if (new_address != NULL) {
		rm(new_name);
	}

	file->name_ = new_name;
}

int VirtualDisk::wc(const std::string& name) const {
	FileObject *file = find(name);
	return file->len_;
}

void VirtualDisk::write(const std::string& name, unsigned int start_position, unsigned int bytes_amount, unsigned char* to_write) {
	FileObject* file = find(name, false);
	if (file == NULL) {
		file = create(name);
	}

	int start_cluster_index = start_position / CLUSTER_SIZE_;
	int current_cluster = file->start_;
	for (int k = 0; k < start_cluster_index; k++) {
		switch(table_[current_cluster]) {
			case LAST_CLUSTER:
				current_cluster = bind_next_cluster(current_cluster);
				break;
			case BAD_CLUSTER:
			case FREE_CLUSTER:
				throw VirtualDiskException(11, "Unknown memory allocation error");
			default:
				current_cluster = table_[current_cluster];
		}
	}

	int curr_shift_inside_cluster = start_position % CLUSTER_SIZE_;

	for (int i = 0; i < bytes_amount; i++) {
		disk_[CLUSTER_SIZE_ * current_cluster + curr_shift_inside_cluster] = to_write[i];
		curr_shift_inside_cluster++;
		if (curr_shift_inside_cluster == CLUSTER_SIZE_) {
			curr_shift_inside_cluster = 0;
			current_cluster = bind_next_cluster(current_cluster);
		}
	}

	int a = file->len_;
	int b = start_position + bytes_amount;
	file->len_ = (a >= b) ? a : b;
}

void VirtualDisk::read(const std::string& name, unsigned int start_position, unsigned int bytes_amount, unsigned char* dest) const {
	FileObject* file = find(name);
	if (start_position + bytes_amount > file->len_) {
		throw VirtualDiskException(12, "File has been read till its end, required information doesn't exist");
	}

	int start_cluster_index = start_position / CLUSTER_SIZE_;
	int current_cluster = file->start_;
	for (int k = 0; k < start_cluster_index; k++) {
		current_cluster = table_[current_cluster];
	}

	int curr_shift_inside_cluster = start_position % CLUSTER_SIZE_;

	for (int i = 0; i < bytes_amount; i++) {
		dest[i] = disk_[CLUSTER_SIZE_ * current_cluster + curr_shift_inside_cluster];
		curr_shift_inside_cluster++;
		if (curr_shift_inside_cluster == CLUSTER_SIZE_) {
			curr_shift_inside_cluster = 0;
			current_cluster = table_[current_cluster];
		}
	}
}

void VirtualDisk::ls(std::ostream& os) const {
	for (int i = 0; i < files_amount_; i++) {
		os << dir_[i].name_ << std::endl;
	}
}

std::ostream& operator<<(std::ostream& os, const VirtualDiskException& e) {
	os << "Error " << e.code() << ": " << e.message();
	return os;
}
