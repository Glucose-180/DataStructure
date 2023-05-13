#ifndef __BUDDYSYSTEM_H__
#define __BUDDYSYSTEM_H__

#include <stdio.h>
#include <stdint.h>

#ifndef EM
	#define EM 9U
#endif

enum Tag_t { FREE, OCCUPIED };

typedef struct header {
	uint32_t log2size;	/* log_2 (size) */
	int tag;
	struct header* next;
} header;

int8_t allocbuf[1U << EM];

void bs_init(void);
void* bs_malloc(const uint32_t Size);
int bs_free(void* const P);
void print_freelist(void);

#endif