#include "05.h"

void
inner4(vec_ptr u, vec_ptr v, data_t* dest)
{
    size_t i;
    size_t length = vec_length(u);
    data_t* udata = get_vec_start(v);
    data_t* vdata = get_vec_start(v);
    data_t sum = (data_t)0;

    for (i = 0; i < length; i++) {
        sum = sum + udata[i] * vdata[i];
    }

    *dest = sum;
}

int
main()
{
    srand(0x12345678);

    printf("ok\n");
    return 0;
}
