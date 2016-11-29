#define __LIBRARY__
#include <unistd.h>
#include <errno.h>
#include <asm/segment.h>

char tmp[32] = {0};

int sys_iam(const char* name) {
	int i = 0;
	while (get_fs_byte(name+i) != 0) {
		++i;
	}
	if (i > 23) {
		return -EINVAL;
		// in _syscall, errno = -__res, so return -EINVAL
	}
	i = 0;
	while ((tmp[i] = get_fs_byte(name+i)) != 0) {
		++i;
	}
	return i;
}

int sys_whoami(char* name, unsigned int size) {
	int i = 0;
	while (tmp[i] != 0) {
		++i;
	}
	if (size < i) {
		return -EINVAL;
	}
	i = 0;
	while (tmp[i] != 0) {
		put_fs_byte(tmp[i], (name+i));
		// put_fs_byte(src, dst)
		++i;
	}
	return i;
}