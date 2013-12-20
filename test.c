#include <stdio.h>
int main()
{
    int a = 0;
    //成功时 == 1成立 失败 == 0成立
    if (__sync_bool_compare_and_swap(&a, 1, 1) == 0) {
        printf("1");
    } 
    printf("%d\n", a);
    return 0;
}
