#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <addrdb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

extern int yydebug;

int main(int argc, char **argv)
{
	unsigned char gwa[8];
	const char *fname;
	int i, fd;
	if (argc == 2)
		fname = argv[1];
	else
		fname = LEASE_FILE;

//	yydebug = 1;
	fd = open("/dev/urandom", O_RDONLY);
	if(fd < 0)
		goto method2;
	if(read(fd, gwa, 8) < 0)
		goto method2;
	close(fd);
	goto testing;
method2:
	memcpy(gwa, "whack000", 8);
testing:
	addrdb_init();
	addrdb_parse(fname);
	for (i = 0; i < 80; i++) {
		gwa[0] = i;
		printf("allocating %d\n", addrdb_alloc(gwa));
	}
	addrdb_dump_leases(fname);
	addrdb_parse(fname);
	return 0;
}

