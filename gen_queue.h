/* Type agnostic FIFO queue.
 * The filename stands or general_queue or generate_queue or generic_queue :P
 *
 * Defines a new type, GQNAME_q, and corresponding functions which are named
 * like GQNAME_q_push() GQNAME_q_pop() etc.
 *
 * # Usage: 
 *
 * 1. In a header file, define GQTYPE and GQNAME and include this file.
 *    Optionally enable additional features by defining GQFEAT_*, where
 *    GQ_FEAT* is one of:
 *
 *    GQ_FEAT_MAX   <max>
 *    GQ_FEAT_COUNT
 *    GQ_FEAT_MUTEX
 *    GQ_FEAT_FD
 *
 *    For example:
 *
 *    #define GQTYPE struct mytype*
 *    #define GQNAME mytype
 *		#define GQFEAT_MAX 42
 *    #include "gen_queue.h"
 *
 * 2. In a source file, define the same GQTYPE and GQNAME and also GQIMPLEMENT.
 *    GQFEAT_*s defined in the header have to be defined here too.
 *
 *    For example:
 *
 *    #define GQTYPE struct mytype*
 *    #define GQNAME mytype
 *    #define GQIMPLEMENT
 *    #define GQFEAT_MAX 42
 *    #include "gen_queue.h"
 *
 * 3. Include the header you included this file in any file you need access to
 *    the GQNAME_q type and related functions.
 *
 * 4. Use GQNAME_q* ptr = GQNAME_q_init() to make a new queue.
 *
 * 5. Use GQNAME_q_free(GQNAME_q* ptr) to free the queue (does not free any
 *    data still stored in the queue).
 *
 */

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#define CONCAT(a, b) CONCAT_(a, b)
#define CONCAT_(a, b) a ## b

#ifndef GQTYPE
#error "No GQTYPE specified for this specialization of gen_queue"
#endif
#ifndef GQNAME
#error "No GQNAME specified for this specialization of gen_queue"
#endif

#define GQ       CONCAT(GQNAME,_q)
#define GQNODE   CONCAT(GQNAME,_qn)

#define _GQINIT  CONCAT(GQ,_init)
#define _GQPUSH  CONCAT(GQ,_push)
#define _GQPEEK  CONCAT(GQ,_peek)
#define _GQPOP   CONCAT(GQ,_pop)
#define _GQEMPTY CONCAT(GQ,_empty)
#define _GQFREE  CONCAT(GQ,_free)


#ifdef GQFEAT_MAX
#define GQFEAT_COUNT
#endif //GQFEAT_MAX

#ifdef GQFEAT_MUTEX
#include <pthread.h>
#endif //GQFEAT_MUTEX

#ifdef GQFEAT_FD
#include <inttypes.h>
#include <unistd.h>
#include <sys/eventfd.h>
#endif //GQFEAT_FD


#ifndef GQIMPLEMENT

typedef struct GQNODE {
	GQTYPE data;
	struct GQNODE* next;
} GQNODE;

typedef struct GQ {
	// int max;
	GQNODE* head;
	GQNODE* tail; // one before last

#ifdef GQFEAT_MUTEX
	pthread_mutex_t lock;
#endif //GQFEAT_MUTEX

#ifdef GQFEAT_MAX
	int max;
#endif //GQFEAT_MAX

#ifdef GQFEAT_COUNT
	int count;
#endif //GQFEAT_COUNT

#ifdef GQFEAT_FD
	int fd;
#endif //GQFEAT_FD

} GQ;


/* gqname_q_init()
 * Allocate and initialize memory for a new GQNAME_q and return a pointer to
 * it.
 */
GQ* _GQINIT();

/* gqname_q_push()
 * Push data into last position in the queue. If GQFEAT_MAX is set, will
 * silently do nothing if count+1 == max. (FIXME, maybe this can be handled better)
 */
void _GQPUSH(GQ*, GQTYPE data);

/* gqname_q_peek()
 * Get data from first position in the queue, returning it without removing it
 * from the queue.  Behavior when called on an empty queue is undefined.
 */
GQTYPE _GQPEEK(const GQ*);

/* gqname_q_pop()
 * Pop data from first position in the queue, returning and removing it.
 * Behavior when popping from an empty queue is undefined.
 */
GQTYPE _GQPOP(GQ*);

/* gqname_q_empty()
 * Return true if queue is empty, false otherwise.
 */
bool _GQEMPTY(const GQ*);

/* gqname_q_free()
 * Free memory related to queue data structure; if you have stored pointers to
 * dynamically allocated memory in here they will not be free'd by this
 * function.
 */
void _GQFREE(GQ*);

#else //GQIMPLEMENT

/* ~ Implementation ~ */

#ifdef GQFEAT_MUTEX

// locking and unlocking our mutex doesn't *really* need to count as modifying
// our object, does it?
#define _GQMUTEX_LOCK() \
do { \
_Pragma("GCC diagnostic push") \
_Pragma("GCC diagnostic ignored \"-Wdiscarded-qualifiers\"") \
pthread_mutex_lock(&Q->lock); \
_Pragma("GCC diagnostic pop") \
} while(0)

#define _GQMUTEX_UNLOCK() \
do { \
_Pragma("GCC diagnostic push") \
_Pragma("GCC diagnostic ignored \"-Wdiscarded-qualifiers\"") \
pthread_mutex_unlock(&Q->lock); \
_Pragma("GCC diagnostic pop") \
} while(0)

#else //GQFEAT_MUTEX
#define _GQMUTEX_LOCK()
#define _GQMUTEX_UNLOCK()
#endif //GQFEAT_MUTEX

// init()
GQ* _GQINIT() {
	GQ* Q = malloc(sizeof(GQ));
	Q->head = NULL;
	Q->tail = NULL;

#ifdef GQFEAT_MUTEX
	pthread_mutex_init(&Q->lock, NULL);
#endif //GQFEAT_MUTEX

#ifdef GQFEAT_MAX
	Q->max = GQFEAT_MAX;
#endif //GQFEAT_MAX

#ifdef GQFEAT_COUNT
	Q->count = 0;
#endif //GQFEAT_COUNT

#ifdef GQFEAT_FD
	Q->fd = eventfd(0, EFD_SEMAPHORE);
#endif //GQFEAT_FD

	return Q;
}

// push()
void _GQPUSH(GQ* Q, GQTYPE data) {
	_GQMUTEX_LOCK();

#ifdef GQFEAT_MAX
	if(Q->count+1 >= Q->max)
		return;
#endif //GQFEAT_MAX

	GQNODE* node = malloc(sizeof(GQNODE));
	node->next = NULL;
	node->data = data;

	if (!Q->head) {
		Q->head = node;
		Q->tail = node;
	}
	else {
		Q->tail->next = node;
		Q->tail = node;
	}

#ifdef GQFEAT_COUNT
	Q->count++;
#endif //GQFEAT_COUNT

#ifdef GQFEAT_FD
	int64_t fdbuf = 1;
	write(Q->fd, &fdbuf, sizeof fdbuf);
#endif //GQFEAT_FD

	_GQMUTEX_UNLOCK();
}

// peek()
GQTYPE _GQPEEK(const GQ* Q) {
#ifdef GQFEAT_MUTEX
	_GQMUTEX_LOCK();
	GQTYPE d = Q->head->data;
	_GQMUTEX_UNLOCK();
	return d;
#else
	return Q->head->data;
#endif //GQFEAT_MUTEX
}

// pop()
GQTYPE _GQPOP(GQ* Q) {
	_GQMUTEX_LOCK();

	GQTYPE d = Q->head->data;
	GQNODE* tmp;
	tmp = Q->head;
	Q->head = Q->head->next;
	free(tmp);

#ifdef GQFEAT_COUNT
	Q->count--;
#endif //GQFEAT_COUNT

#ifdef GQFEAT_FD
	int64_t fdbuf;
	read(Q->fd, &fdbuf, sizeof fdbuf);
#endif //GQFEAT_FD

	_GQMUTEX_UNLOCK();
	return d;
}

// empty()
bool _GQEMPTY(const GQ* Q) {
	_GQMUTEX_LOCK();

	bool ret;
	if (Q->head)
		ret = false;
	else
		ret = true;

	_GQMUTEX_UNLOCK();
	return ret;
}

// free()
// Don't think there is any good reason to call this while another thread could
// be using it, so no point in locking the mutex
void _GQFREE(GQ* Q) {
	GQNODE* here = Q->head;

	while (here) {
		GQNODE* tmp = here->next;
		free(here);
		here = tmp;
	}

#ifdef GQFEAT_MUTEX
	pthread_mutex_destroy(&Q->lock);
#endif

#ifdef GQFEAT_FD
	close(Q->fd);
#endif

	free(Q);
}

#undef GQIMPLEMENT
#endif //GQIMPLEMENT

#undef _GQINIT
#undef _GQPUSH
#undef _GQPEEK
#undef _GQPOP
#undef _GQEMPTY
#undef _GQFREE

#undef GQNODE
#undef GQ

#undef GQFEAT_MAX
#undef GQFEAT_COUNT
#undef GQFEAT_MUTEX
#undef GQFEAT_FD

#undef GQTYPE
#undef GQNAME

#undef CONCAT
#undef CONCAT_

