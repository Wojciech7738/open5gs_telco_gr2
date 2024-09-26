#ifndef	_DedicatedNAS_Message_H_
#define	_DedicatedNAS_Message_H_

/* DedicatedNAS-Message */
typedef struct DedicatedNAS_Message {
	uint8_t *buf;	/* Buffer with consecutive OCTET_STRING bits */
	size_t size;	/* Size of the buffer */
} DedicatedNAS_Message_t;
     
#endif