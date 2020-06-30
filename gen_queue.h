/* Type agnostic FIFO queue.
 * The filename stands or general_queue or generate_queue or generic_queue :P
 *
 * Defines a new type, GQNAME_q, and corresponding functions which are named
 * like GQNAME_q_push() GQNAME_q_pop() etc.
 *
 * # Usage: 
 *
 * 1. In a header file, define GQTYPE and GQNAME and include this file.
 *    For example:
 *
 *    #define GQTYPE struct mytype*
 *    #define GQNAME mytype
 *    #include "gen_queue.h"
 *
 * 2. In a source file, define the same GQTYPE and GQNAME and also GQIMPLEMENT.
 *    Optionally enable additional features by defining GQFEAT_*, where GQ_FEAT*
 *    is one of:
 *
 *    GQ_FEAT_MAX   <max>  (not yet implemented)
 *    GQ_FEAT_MUTEX        (not yet implemented)
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

#ifndef GQIMPLEMENT

typedef struct GQNODE GQNODE;
typedef struct GQ GQ;

/* gqname_q_init()
 * Allocate and initialize memory for a new GQNAME_q and return a pointer to
 * it.
 */
GQ* _GQINIT();

/* gqname_q_push()
 * Push data into last position in the queue.
 */
void _GQPUSH(GQ*, GQTYPE data);

/* gqname_q_peek()
 * Pop data from first position in the queue, returning and removing it.
 */
GQTYPE _GQPEEK(const GQ*);

/* gqname_q_pop()
 * Pop data from first position in the queue, returning and removing it.
 */
GQTYPE _GQPOP(GQ*);

/* gqname_q_empty()
 * Return 1 if queue is empty, 0 otherwise.
 */
int _GQEMPTY(const GQ*);

/* gqname_q_free()
 * Free memory related to queue data structure; if you have stored pointers to
 * dynamically allocated memory in here they will not be free'd by this
 * function.
 */
void _GQFREE(GQ*);

#else //GQIMPLEMENT

/* ~ Implementation ~ */

typedef struct GQNODE {
	GQTYPE data;
	struct GQNODE* next;
} GQNODE;

typedef struct GQ {
	// int max;
	GQNODE* head;
	GQNODE* tail; // one before last
} GQ;

// init()
GQ* _GQINIT() {
	GQ* Q = malloc(sizeof(GQ));
	Q->head = NULL;
	Q->tail = NULL;
	return Q;
}

// push()
void _GQPUSH(GQ* Q, GQTYPE data) {
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

	// Q->count++;
}

// peek()
GQTYPE _GQPEEK(const GQ* Q) {
	return Q->head->data;
}

// pop()
GQTYPE _GQPOP(GQ* Q) {
	//Returning NULL generates warnings when GQTYPE is not a pointer type; maybe
	//we just leave the behavior of pop() in the empty case undefined and
	//require the caller to check empty() first?
// #pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Wint-conversion"
	// if (!Q->head)
	// 	return NULL; 
// #pragma GCC diagnostic pop

	GQTYPE d = Q->head->data;
	GQNODE* tmp;
	tmp = Q->head;
	Q->head = Q->head->next;
	free(tmp);
	return d;
}

// empty()
int _GQEMPTY(const GQ* Q) {
	if (Q->head)
		return 0;
	else
		return 1;
}

// free()
void _GQFREE(GQ* Q) {
	GQNODE* here = Q->head;

	while (here) {
		GQNODE* tmp = here->next;
		free(here);
		here = tmp;
	}

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

#undef GQTYPE
#undef GQNAME

#undef CONCAT
#undef CONCAT_

