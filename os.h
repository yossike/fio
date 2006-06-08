#ifndef FIO_OS_H
#define FIO_OS_H

#if defined(__linux__)
#include "os-linux.h"
#elif defined(__FreeBSD__)
#include "os-freebsd.h"
#elif defined(__sun__)
#include "os-solaris.h"
#else
#error "unsupported os"
#endif

#ifdef FIO_HAVE_LIBAIO
#include <libaio.h>
#endif

#ifdef FIO_HAVE_POSIXAIO
#include <aio.h>
#endif

#ifdef FIO_HAVE_SGIO
#include <linux/fs.h>
#include <scsi/sg.h>
#endif

#ifndef FIO_HAVE_FADVISE
#define fadvise(fd, off, len, advice)	(0)

#define POSIX_FADV_DONTNEED	(0)
#define POSIX_FADV_SEQUENTIAL	(0)
#define POSIX_FADV_RANDOM	(0)
#endif /* FIO_HAVE_FADVISE */

#ifndef FIO_HAVE_CPU_AFFINITY
#define fio_setaffinity(td)		(0)
#define fio_getaffinity(pid, mask)	(0)
#endif

#ifndef FIO_HAVE_IOPRIO
#define ioprio_set(which, who, prio)	(0)
#endif

#ifndef FIO_HAVE_ODIRECT
#define OS_O_DIRECT			0
#else
#define OS_O_DIRECT			O_DIRECT
#endif

struct thread_data;
extern int fio_libaio_init(struct thread_data *);
extern int fio_posixaio_init(struct thread_data *);
extern int fio_syncio_init(struct thread_data *);
extern int fio_mmapio_init(struct thread_data *);
extern int fio_sgio_init(struct thread_data *);
extern int fio_spliceio_init(struct thread_data *);

#endif
