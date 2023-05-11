/* Memory allocation without Alignment and Compression */
#ifndef __MALLOC_G__
#define __MALLOC_G__

#include <stdio.h>
#include <stdint.h>

/* Total memory size: byte */
#ifndef SL
	#define SL 512U
#endif
/* Size less than EU will not be preserved */
#ifndef EU
	#define EU 64U
#endif

enum Tag_t { FREE,OCCUPIED };

typedef struct header {
	union {
		/* the last(left) node */
		struct header* last;
		/* the head of this node */
		struct header* head;
	};
	int32_t tag;
	uint32_t size;
	/* the next(right) node */
	struct header* next;
} header;

void malloc_init(void);
void* malloc_g(const uint32_t Size);
void free_g(void* const P);
void print_avail_table(void);

#endif
