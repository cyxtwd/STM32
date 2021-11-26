#ifndef key__

#define key__

#include "Include.h"

#define N_key 0 
#define S_key 1
#define D_key 2
#define L_key 3

#define key_state_0 0
#define key_state_1 1
#define key_state_2 2
#define key_state_3 3

u8 key_driver(void);
u8 key_read(void);

#endif

