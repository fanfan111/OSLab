#define _LIBRARY_
#include <unistd.h>
#include <errno.h>
#include <asm/segment.h>

char store[64]={0}; //to store parameter name

int sys_iam(const char* name) {
	int i = 0;
	//judge if the length of name is out of 23
	//if it's the case, return -1 and set errno = -EINVAL
	while (get_fs_byte(name+i) != 0) {
		i++;	
	}

	if (i > 23) {
		return -EINVAL;
	}

	printk("iam1: %d\n", i);

	i = 0;
	
	//clean the cache
	for (i = 0; i < 64; i++) {
		store[i] = 0;
	}

	i = 0;

	//then copy name's content into store
	//to assume that we write in name's content to kernel
	while (get_fs_byte(name+i) != 0) {
		store[i] = get_fs_byte(name+i);
		i++;
	}

	printk("iam2: %s\n", store);
	printk("iam2: %d\n", i);

	return i;
}

int sys_whoami(char* name, unsigned int size) {
	int i = 0;
	
	//judge if store's length is out of size
	//if it's the case, return -1 and set errno = -EINVAL
	while (store[i] != 0) {
		i++;
	}
	if (i > size) {
		return -EINVAL;
	}	

	printk("whoami1: %d\n", i);

	i = 0;

	//then copy store's content into name

	while (store[i] != 0) {
		put_fs_byte(store[i], name+i);
		i++;
	}
	
	printk("whoami2: %d\n", i);

	return i;
}
