#include "disk.hpp"

VirtualDisk::File* VirtualDisk::open(const char *path) {
	return find(path);
}

VirtualDisk::FileObj::FileObj(VirtualDisk *disk, void *file_record) {
	void *u_pointer = file_record;
	parent_disk_ = disk;
	
	name_ = (char *)u_pointer;

	u_pointer = name_ + 12;
	len_ = (unsigned int *)u_pointer;

	u_pointer = len_ + 1;
	start_ = (int *)u_pointer;

	u_pointer = start_ + 1;
	type_ = (unsigned char *)u_pointer;

	u_pointer = type_ + 1;
	creation_time_ = (time_t *)u_pointer;

	u_pointer = creation_time_ + 1;
	mod_time_ = (time_t *)u_pointer;
}

#ifdef DEBUG
void VirtualDisk::printFAT(int amount) const {
	for (int i = 0; i < FAT_SIZE_ && i < amount; i++) {
		std::cout << i << ": " << FAT_[i] << "; " << std::endl;
	}
}
#endif

VirtualDisk::VirtualDisk(unsigned int size, unsigned int cluster_size) : 
			DISK_SIZE_(size), CLUSTER_SIZE_(cluster_size) {
	if (cluster_size % 512 != 0 || size < 2048) {
		throw VirtualDiskException(1, "Incorrect disk parameters");
	}
	FAT_SIZE_ = DISK_SIZE_ / CLUSTER_SIZE_;

	if (FAT_SIZE_ < 16) {
		throw VirtualDiskException(1, "Incorrect disk parameters");
	}

	try {
		disk_ = new unsigned char[size];
		for (unsigned int i = 0; i < size; i++) {
			disk_[i] = 0;
		}
	} catch (const std::bad_alloc& e) {
		throw VirtualDiskException(2, "Can't allocate memory");
	}

	try {
		FAT_ = new int[FAT_SIZE_];

		FAT_[0] = -1;
		for (int i = 1; i < FAT_SIZE_; i++) {
			FAT_[i] = 0;
		}
		
		File one_dot = FileObj(this, disk_);
		File two_dots = FileObj(this, disk_ + RECORD_SIZE);

		one_dot.name_[0] = two_dots.name_[0] = two_dots.name_[1] = '.';

		*one_dot.len_ = *two_dots.len_ = 0;
		*one_dot.start_ = *two_dots.start_ = 0;
		*one_dot.type_ = *two_dots.type_ = 1;
		*one_dot.creation_time_ = *one_dot.mod_time_ = time(NULL);
		*two_dots.creation_time_ = *two_dots.mod_time_ = time(NULL);
	} catch (const std::bad_alloc& e) {
		throw VirtualDiskException(3, "Can't create FAT");
	}
}

VirtualDisk::~VirtualDisk() {
	delete[] disk_;
	delete[] FAT_;
}

VirtualDisk::File* VirtualDisk::find(const char *path, bool required, int prohibited_parent_fcluster) {
	File *file = NULL;
	bool eos = false; // End of search
	
	int plen = strlen(path);

	if (prohibited_parent_fcluster == 0) {
		throw VirtualDiskException(23, "Can't copy root foolder");
	} 

	if ((plen == 1 && (path[0] == '/' || path[0] == '.')) || strcmp(path, "..") == 0) {
		return new FileObj(this, disk_);
	}

	if (plen == 0 || path[0] == 5) {
		throw VirtualDiskException(4, "Incorrect path");
	}

	unsigned char type = (path[plen - 1] == '/') ? 1 : 0;
	int parent_cluster = 0, curr_dir_start = 0;
	int name_len = 0, i = 0;

	if (type == 1) {
		plen--;
	}

	if (plen > 0 && path[plen - 1] == '/') {
		throw VirtualDiskException(4, "Incorrect path");
	}

	if (path[0] == '/') {
		i++;
	}

	for (; i < plen; i++, name_len++) {
		if (path[i] != '/' && i < plen - 1) {
			continue;
		}
		
		if (i == plen - 1) {
			name_len++;
		}

		if (name_len == 0 || name_len > 12 || path[i] == 5) {
			delete file;
			throw VirtualDiskException(5, "There's incorrect filename in the path");
		}

		const char *curr_name = path + curr_dir_start;
		int dir_shift = 0;

		void *tmp_p = disk_ + parent_cluster * CLUSTER_SIZE_;
		char *filename = (char *)tmp_p;

		while (strncmp(curr_name, filename, name_len) != 0) {
			if (*filename == 0) {
				eos = true;
				break;
			}

			filename += RECORD_SIZE;
			dir_shift += RECORD_SIZE;

			if (dir_shift == CLUSTER_SIZE_) {
				dir_shift = 0;
				if (FAT_[parent_cluster] > 0) {
					parent_cluster = FAT_[parent_cluster];
					tmp_p = disk_ + parent_cluster * CLUSTER_SIZE_;
					filename = (char *)tmp_p; 
				} else {
					eos = true;
					break;
				}
			}
		}

		if (eos) {
			break;
		} else {
			File curr_file = FileObj(this, filename);
			if (*curr_file.start_ == prohibited_parent_fcluster) {
				throw VirtualDiskException(24, "Can't copy folder to itself");
			}

			if (i == plen - 1) {
				if (type == 1 && *(curr_file.type_) == 0) {
					throw VirtualDiskException(6, "File you're searching is not directory");
				}
				file = new FileObj(this, filename);
				break;
			} else if (*(curr_file.type_) == 0) {
				throw VirtualDiskException(4, "Incorrect path");
			}

			parent_cluster = *(curr_file.start_);
			dir_shift = 0;
		}

		curr_dir_start += name_len + 1;
		name_len = -1;
	}

	if ((file == NULL) && required) {
		throw VirtualDiskException(6, "File doesn't exist");
	}

	return file;
}

int VirtualDisk::bind_next_cluster(int last_cluster_index) {
	if (last_cluster_index < 0 && last_cluster_index != LAST_CLUSTER) {	
		return BAD_CLUSTER;
	} 

	if (last_cluster_index >= 0 && FAT_[last_cluster_index] != LAST_CLUSTER) {
		return BAD_CLUSTER;
	}

	for (int i = 0; i < FAT_SIZE_; i++) {
		if (FAT_[i] == 0) {
			if (last_cluster_index != LAST_CLUSTER) {
				FAT_[last_cluster_index] = i;
			}

			FAT_[i] = LAST_CLUSTER;
			#ifdef DEBUG_EXTENDED
			std::cout << "Success: cluster " << i << " was added to clusterchain after " << last_cluster_index << std::endl;
			#endif
			return i;
		}
	}
	throw VirtualDiskException(7, "Not enough memory");
}

VirtualDisk::File* VirtualDisk::create(const char *path, unsigned char type) {
	if (strlen(path) == 0 || path[0] == 5) {
		throw VirtualDiskException(8, "Impossible filename");
	}

	File *file = find(path, false);
	if (file != NULL) {
		delete file;
		throw VirtualDiskException(9, "File already exists");
	}

	char *dir_path;
	int filename_len = 0, plen = strlen(path);

	if (path[plen - 1] == '/') {
		plen--;
		type = 1;
	}

	while(filename_len < plen && path[plen - filename_len - 1] != '/') {
		filename_len++;
	}

	if (filename_len < 3) {
		const char *filename = path + plen - filename_len;
		bool is_impossible = strcmp(filename, ".") == 0 || strcmp(filename, "..") == 0 || filename_len == 0;
		if (is_impossible) {
			throw VirtualDiskException(8, "Impossible filename");
		}
	}

	File *parent_dir;
	if (filename_len == plen) {
		parent_dir = find("/");
	} else {
		dir_path = (char *)malloc(plen - filename_len + 1);
		strncpy(dir_path, path, plen - filename_len);
		dir_path[plen - filename_len] = 0;
		parent_dir = find(dir_path, false);

		free(dir_path);
		if (parent_dir == NULL) {
			throw VirtualDiskException(10, "Parent directory for file doesn't exist");
		}
	}

	int dir_shift = 0, parent_cluster = *(parent_dir->start_);
	void* buffer_p = disk_ + parent_cluster * CLUSTER_SIZE_;
	char* curr_file_r = (char *)buffer_p;
	bool eos = false; // End of search
	while (true) {		
		if (curr_file_r[0] == 0 || curr_file_r[0] == 5) {
			break;
		}

		curr_file_r += RECORD_SIZE;
		dir_shift += RECORD_SIZE;

		if (dir_shift == CLUSTER_SIZE_) {
			dir_shift = 0;
			if (FAT_[parent_cluster] > 0) {
				parent_cluster = FAT_[parent_cluster];
			} else {
				parent_cluster = bind_next_cluster(parent_cluster);
				eos = true;
			}

			buffer_p = disk_ + parent_cluster * CLUSTER_SIZE_;
			curr_file_r = (char *)buffer_p;
			if (eos) {
				break;
			}
		}
	}
 
	file = new FileObj(this, curr_file_r);
	for (int i = 0; i < 12; i++) {
		if (i < filename_len) {
			file->name_[i] = path[plen - filename_len + i];
		} else {
			file->name_[i] = 0;
		}
	}

	*(file->len_) = 0;
	*(file->start_) = bind_next_cluster(LAST_CLUSTER);
	*(file->type_) = type;

	*(file->creation_time_) = time(NULL);
	*(file->mod_time_) = time(NULL);

	if (type == 1) {
		add_default_dir_records(*file->start_, *parent_dir->start_);
	}

	delete parent_dir;
	return file;
}

void VirtualDisk::add_default_dir_records(int start, int parent_start) {
	unsigned char* file_start = disk_ + start * CLUSTER_SIZE_;
	File one_dot = FileObj(this, file_start);
	File two_dots = FileObj(this, file_start + RECORD_SIZE);

	one_dot.name_[0] = two_dots.name_[0] = two_dots.name_[1] = '.';

	*one_dot.len_ = *two_dots.len_ = 0;

	*one_dot.start_ = start;
	*two_dots.start_ = parent_start;

	*one_dot.type_ = *two_dots.type_ = 1;

	*one_dot.creation_time_ = *one_dot.mod_time_ = time(NULL);
	*two_dots.creation_time_ = *two_dots.mod_time_ = time(NULL);
}

void VirtualDisk::FileObj::rm() {
	if (name_[0] == 5 || name_[0] == 0) {
		throw VirtualDiskException(11, "File has been deleted");
	}

	if (*type_ == 1) {
		if (strcmp(name_, ".") == 0 || strcmp(name_, "..") == 0) {
			throw VirtualDiskException(12, "Can't delete directory which is . or ..");
		}

		int dir_shift = 0, current_cluster = *start_;
		unsigned char *curr_file_r = (parent_disk_->disk_) + current_cluster * parent_disk_->CLUSTER_SIZE_;
		File *curr_file = NULL;
		while (true) {
			if (curr_file_r[0] == 0) {
				break;
			} else if (curr_file_r[0] != 5) {
				delete curr_file; 
				curr_file = new FileObj(parent_disk_, curr_file_r);
				curr_file->rm();
			}

			dir_shift += VirtualDisk::RECORD_SIZE;
			curr_file_r += VirtualDisk::RECORD_SIZE;
			

			if (dir_shift == parent_disk_->CLUSTER_SIZE_) {
				dir_shift = 0;
				if ((parent_disk_->FAT_)[current_cluster] > 0) {
					current_cluster = (parent_disk_->FAT_)[current_cluster];
					curr_file_r = (parent_disk_->disk_) + current_cluster * parent_disk_->CLUSTER_SIZE_;
				} else {
					break;
				}
			}
		}

		delete curr_file;
	}

	int curr_cluster = *start_, next_cluster;
	if (curr_cluster == 0) {
		curr_cluster = (parent_disk_->FAT_)[curr_cluster];
	}

	while ((parent_disk_->FAT_)[curr_cluster] >= 0) {
		next_cluster = (parent_disk_->FAT_)[curr_cluster];
		(parent_disk_->FAT_)[curr_cluster] = 0;
		curr_cluster = next_cluster;
	}

	if ((parent_disk_->FAT_)[curr_cluster] == LAST_CLUSTER && curr_cluster != 0) {
		(parent_disk_->FAT_)[curr_cluster] = 0;
	}

	name_[0] = 5;
	
}

void VirtualDisk::copy_file(void *to_copy, void *to_fill, void *parent_r, unsigned int depth) {
	File src = FileObj(this, to_copy), dest = FileObj(this, to_fill), parent = FileObj(this, parent_r);

	if (depth > 1) {
		for (int i = 0; i < 12; i++) {
			dest.name_[i] = src.name_[i];
		}

		*dest.len_ = 0;
		*dest.start_ = bind_next_cluster(LAST_CLUSTER);
		*dest.type_ = *src.type_;

		*dest.creation_time_ = time(NULL);
		*dest.mod_time_ = time(NULL);

		if (*src.type_ == 1) {
			add_default_dir_records(*dest.start_, *parent.start_);
		}
	}

	int current_src_cluster = *(src.start_);
	int current_dest_cluster = *(dest.start_);

	if (*src.type_ == 0) {
		int k = 0;
		while (current_src_cluster > 0) {
			if (k > 0) {
				if ((current_dest_cluster = bind_next_cluster(current_dest_cluster)) == BAD_CLUSTER) {
					throw VirtualDiskException(16, "Memory allocation error");
				}
			}
	
			for (int i = 0; i < CLUSTER_SIZE_; i++, k++) {
				if (k >= *src.len_) {
					break;
				}
				disk_[CLUSTER_SIZE_ * current_dest_cluster + i] = disk_[CLUSTER_SIZE_ * current_src_cluster + i];
			}
			current_src_cluster = FAT_[current_src_cluster];
		}
	
		if (k < *src.len_ || current_src_cluster != LAST_CLUSTER) {
			throw VirtualDiskException(17, "File was damaged");
		}
	
		*dest.len_ = *src.len_;	
	} else {
		int src_shift = 2 * RECORD_SIZE;
		int dest_shift = 2 * RECORD_SIZE;
		unsigned char *curr_src_file_r = disk_ + current_src_cluster * CLUSTER_SIZE_ + 2 * RECORD_SIZE;
		unsigned char *curr_dest_file_r = disk_ + current_dest_cluster * CLUSTER_SIZE_ + 2 * RECORD_SIZE;
		while (true) {
			if (*curr_src_file_r == 0) {
				break;
			} else if (*curr_src_file_r != 5) {
				copy_file(curr_src_file_r, curr_dest_file_r, dest.name_, depth + 1);	

				dest_shift += RECORD_SIZE;
				curr_dest_file_r += RECORD_SIZE;
			}

			src_shift += RECORD_SIZE;
			curr_src_file_r += RECORD_SIZE;	

			if (src_shift == CLUSTER_SIZE_) {
				src_shift = 0;
				if (FAT_[current_src_cluster] > 0) {
					current_src_cluster = FAT_[current_src_cluster];
					curr_src_file_r = disk_ + current_src_cluster * CLUSTER_SIZE_;
				} else {
					break;
				}
			}

			if (dest_shift == CLUSTER_SIZE_) {
				dest_shift = 0;
				current_dest_cluster = bind_next_cluster(current_dest_cluster);
				curr_dest_file_r = disk_ + current_dest_cluster * CLUSTER_SIZE_;
			}
		}
	}
}

VirtualDisk::File* VirtualDisk::cp(File *file, const char *copy_path) {
	if (file == NULL) {
		throw VirtualDiskException(13, "Nothing to copy");
	}

	void *buffer_p = file->name_;
	unsigned char *name = (unsigned char *)buffer_p;
	if (name[0] == 5 || name[0] == 0) {
		throw VirtualDiskException(11, "File has been deleted");
	}

	File *copy_address = find(copy_path, false, *file->start_);

	if (copy_address != NULL && file->start_ == copy_address->start_) {
		delete copy_address;
		throw VirtualDiskException(14, "Can't copy file to itself");
	} else if (copy_address != NULL) {
		copy_address->rm();
		delete copy_address;
	}

	copy_address = create(copy_path, *(file->type_));

	try {
		copy_file(file->name_, copy_address->name_);	
	} catch (VirtualDiskException& e) {
		delete copy_address;
		throw e;
		return NULL;
	}
	
	return copy_address;
}

void VirtualDisk::FileObj::mv(const char *new_path) {
	if (name_[0] == 5 || name_[0] == 0) {
		throw VirtualDiskException(11, "File has been deleted");
	}

	File *new_address = parent_disk_->find(new_path, false);

	if (new_address != NULL && new_address->start_ == this->start_) {
		delete new_address;
		return;
	} else if (new_address != NULL) {
		new_address->rm();
		delete new_address;
	}

	new_address = parent_disk_->create(new_path);
	(this->name_)[0] = 5;

	*(new_address->len_) = *(this->len_);
	*(new_address->type_) = *(this->type_);
	*(new_address->start_) = *(this->start_);
	*(new_address->creation_time_) = *(this->creation_time_);
	*(new_address->mod_time_) = *(this->mod_time_);

	this->name_ = new_address->name_;
	this->len_ = new_address->len_;
	this->type_ = new_address->type_;
	this->start_ = new_address->start_;
	this->creation_time_ = new_address->creation_time_;
	this->mod_time_ = new_address->mod_time_;

	delete new_address;
}

unsigned int VirtualDisk::FileObj::wc() const {
	if (name_[0] == 5 || name_[0] == 0) {
		throw VirtualDiskException(11, "File has been deleted");
	}
	return *len_;
}

void VirtualDisk::FileObj::write(unsigned int start_position, unsigned int bytes_amount, unsigned char* to_write) {
	if (name_[0] == 5 || name_[0] == 0) {
		throw VirtualDiskException(11, "File has been deleted");
	}

	if (*type_ == 1) {
		throw VirtualDiskException(15, "Directories can't be edited using write() method");
	}

	unsigned int start_cluster_index = start_position / parent_disk_->CLUSTER_SIZE_;
	int current_cluster = *start_;
	for (unsigned int k = 0; k < start_cluster_index; k++) {
		if ((parent_disk_->FAT_)[current_cluster] >= 0) {
			current_cluster = (parent_disk_->FAT_)[current_cluster];
			continue;
		}
		switch((parent_disk_->FAT_)[current_cluster]) {
			case LAST_CLUSTER:
				current_cluster = parent_disk_->bind_next_cluster(current_cluster);
				break;
			default:
				throw VirtualDiskException(16, "Memory allocation error");	
		}
	}

	if (current_cluster <= 0) {
		throw VirtualDiskException(16, "Memory allocation error");
	}

	unsigned int curr_shift_inside_cluster = start_position % parent_disk_->CLUSTER_SIZE_;

	for (unsigned int i = 0; i < bytes_amount; i++, curr_shift_inside_cluster++) {
		if (curr_shift_inside_cluster == parent_disk_->CLUSTER_SIZE_) {
			curr_shift_inside_cluster = 0;
			if ((current_cluster = parent_disk_->bind_next_cluster(current_cluster)) == BAD_CLUSTER) {	
				throw VirtualDiskException(16, "Memory allocation error");
			}
		}

		(parent_disk_->disk_)[parent_disk_->CLUSTER_SIZE_ * current_cluster + curr_shift_inside_cluster] = to_write[i];
	}

	unsigned int a = *len_;
	unsigned int b = start_position + bytes_amount;
	*len_ = (a >= b) ? a : b;
	*mod_time_ = time(NULL);
}

void VirtualDisk::FileObj::read(unsigned int start_position, unsigned int bytes_amount, unsigned char* dest) const {
	if (name_[0] == 5 || name_[0] == 0) {
		throw VirtualDiskException(11, "File has been deleted");
	}

	if (*type_ == 1) {
		throw VirtualDiskException(18, "Directories can't be read using read() method");
	}

	if (start_position > UINT_MAX / 2 || bytes_amount > UINT_MAX / 2) {
		unsigned int max = (start_position >= bytes_amount) ? start_position : bytes_amount;
		unsigned int min = (max == start_position) ? bytes_amount : start_position;
		unsigned int halfed_index = min + ( (max - min) / 2 );
		if (halfed_index > UINT_MAX / 2) {
			throw VirtualDiskException(19, "Too big parameters");
		}
	}
	if (start_position + bytes_amount > *len_) {
		throw VirtualDiskException(20, "File has been read till its end, required information doesn't exist");
	}

	unsigned int start_cluster_index = start_position / parent_disk_->CLUSTER_SIZE_;
	int current_cluster = *start_;
	for (unsigned int k = 0; k < start_cluster_index; k++) {
		current_cluster = (parent_disk_->FAT_)[current_cluster];
	}

	unsigned int curr_shift_inside_cluster = start_position % parent_disk_->CLUSTER_SIZE_;

	for (unsigned int i = 0; i < bytes_amount; i++) {
		if (curr_shift_inside_cluster == parent_disk_->CLUSTER_SIZE_) {
			curr_shift_inside_cluster = 0;
			current_cluster = (parent_disk_->FAT_)[current_cluster];
		}

		dest[i] = (parent_disk_->disk_)[parent_disk_->CLUSTER_SIZE_ * current_cluster + curr_shift_inside_cluster];
		curr_shift_inside_cluster++;
	}
}

void VirtualDisk::FileObj::del(unsigned int bytes_amount) {
	if (name_[0] == 5 || name_[0] == 0) {
		throw VirtualDiskException(11, "File has been deleted");
	}

	if (*type_ == 1) {
		throw VirtualDiskException(21, "Directories can't be edited using del() method");
	}

	unsigned int new_len = (*len_ >= bytes_amount) ? (*len_ - bytes_amount) : 0;
	unsigned int curr_clusterchain_len = *len_ / parent_disk_->CLUSTER_SIZE_;
	unsigned int upd_clusterchain_len = new_len / parent_disk_->CLUSTER_SIZE_;

	if (curr_clusterchain_len - upd_clusterchain_len > 0) {
		unsigned int i = 0;
			
		int current_cluster = *start_;
		int next_cluster;
	
		while ((parent_disk_->FAT_)[current_cluster] >= 0) {
			next_cluster = (parent_disk_->FAT_)[current_cluster];
			if (i >= upd_clusterchain_len) {
				(parent_disk_->FAT_)[current_cluster] = (i == upd_clusterchain_len) ? LAST_CLUSTER : 0;
			}
			current_cluster = next_cluster;
			i++;
		}
	
		if ((parent_disk_->FAT_)[current_cluster] == LAST_CLUSTER) {
			(parent_disk_->FAT_)[current_cluster] = 0;
		}
	}

	*len_ = new_len;
	*mod_time_ = time(NULL);
}

char *VirtualDisk::FileObj::name() const {
	char *name = (char *)malloc(13);
	strncpy(name, name_, 12);
	name[12] = 0;
	return name;
}

void VirtualDisk::FileObj::ls(std::ostream& os) {
	if (name_[0] == 5 || name_[0] == 0) {
		throw VirtualDiskException(11, "File has been deleted");
	}

	if (*type_ == 0) {
		throw VirtualDiskException(22, "Directory was expected, ordinary file given");
	}

	int current_cluster = *start_;
	void *tmp_p = parent_disk_->disk_ + current_cluster * parent_disk_->CLUSTER_SIZE_;
	char *curr_file_r = (char *)tmp_p, *filename;
	int dir_shift = 0;
	int k = 0;
	while (true) {
		if (curr_file_r[0] == 0) {
			break;
		} else if (curr_file_r[0] != 5) {
			void *buffer_p = curr_file_r + 12 + 2 * sizeof(int);
			unsigned char *type = (unsigned char *)buffer_p;
			File current = FileObj(parent_disk_, curr_file_r);
			if (*current.type_ == 1 && k >= 2) {
				os << "/--------------------" << std::endl;
			}
			for (int i = 0; i < 12; i++) {
				if (!current.name_[i]) {
					break;
				}
				os << current.name_[i];
			}

			#ifdef DEBUG_EXTENDED
			os << " (first cluster = " << *current.start_ << ")";
			#endif

			if (*current.type_ == 1 && k >= 2) {
				os << ":" << std::endl;	
				current.ls(os);
				os << "--------------------/" << std::endl;
			}
			os << std::endl;
	}

		dir_shift += VirtualDisk::RECORD_SIZE;
		curr_file_r += VirtualDisk::RECORD_SIZE;
			
		if (dir_shift == parent_disk_->CLUSTER_SIZE_) {
			dir_shift = 0;
			if ((parent_disk_->FAT_)[current_cluster] > 0) {
				current_cluster = (parent_disk_->FAT_)[current_cluster];
				tmp_p = parent_disk_->disk_ + current_cluster * parent_disk_->CLUSTER_SIZE_;
				curr_file_r = (char *)tmp_p;
			} else {
				break;
			}
		}

		k++;
	}
}

std::ostream& operator<<(std::ostream& os, const VirtualDiskException& e) {
	os << "Error " << e.code() << ": " << e.message();
	return os;
}
