// Author: strawberryhacker

#include "utilities.h"

//--------------------------------------------------------------------------------------------------

extern u32 linker_relocate_start;
extern u32 linker_stack_end;
extern u32 linker_vector_start;
extern u32 linker_data_start;
extern u32 linker_data_end;
extern u32 linker_zero_start;
extern u32 linker_zero_end;

extern void main();

//--------------------------------------------------------------------------------------------------

void reset_handler() {
    u32* source = &linker_relocate_start;
    u32* destination = &linker_data_start;

    while (destination != &linker_data_end) {
        *destination++ = *source++;
    }

    source = &linker_zero_start;

    while (source != &linker_zero_end) {
        *source++ = 0;
    }

    main();
    while (1);
}

//--------------------------------------------------------------------------------------------------

__attribute__ ((section(".vector_table"))) volatile const void* vectors[] = {
    &linker_stack_end,
    reset_handler,
};