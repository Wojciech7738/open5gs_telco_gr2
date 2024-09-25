#ifndef TYPE_DEF
#define TYPE_DEF

#include "stdint.h"


#define	A_SEQUENCE_OF(type)	A_SET_OF(type)

#define	A_SET_OF(type)					\
	struct {					\
		type **array;				\
		int count;	/* Meaningful size */	\
		int size;	/* Allocated size */	\
		void (*free)(type *);			\
	}

typedef struct BIT_STRING_s {
	uint8_t *buf;	/* BIT STRING body */
	int size;	/* Size of the above buffer */

	int bits_unused;/* Unused trailing bits in the last octet (0..7) */

} BIT_STRING_t;


typedef struct OCTET_STRING_s {
	uint8_t *buf;	/* Buffer with consecutive OCTET_STRING bits */
	int size;	/* Size of the buffer */

} OCTET_STRING_t;


#endif

