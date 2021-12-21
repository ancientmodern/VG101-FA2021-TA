#include <stdio.h>
#include <string.h>

int main()
{
    int n;
    char command[4];
    while (1)
    {
        printf("mathsh $ ");
        scanf("%s", command);
        if (!strcmp(command, "exit"))
        {
            printf("Exit the program!\n");
            return 0;
        }
        else if (!strcmp(command, "max"))
        {
            scanf("%d", &n);
            int max = -999999, num;
            for (int i = 0; i < n; ++i)
            {
                scanf("%d", &num);
                max = (max < num) ? num : max;
            }
            printf("max: %d\n", max);
        }
        else if (!strcmp(command, "min"))
        {
            scanf("%d", &n);
            int min = 999999, num;
            for (int i = 0; i < n; ++i)
            {
                scanf("%d", &num);
                min = (min > num) ? num : min;
            }
            printf("min: %d\n", min);
        }
        else if (!strcmp(command, "avg"))
        {
            scanf("%d", &n);
            float num;
            double avg = 0;
            for (int i = 0; i < n; ++i)
            {
                scanf("%f", &num);
                avg += num / (double)n;
            }
            printf("avg: %f\n", avg);
        }
        else if (!strcmp(command, "fib"))
        {
            scanf("%d", &n);
            if (n == 0 || n == 1)
            {
                printf("fib: %d\n", n);
                continue;
            }
            int first = 0, second = 1, curr = 0;
            for (int i = 2; i <= n; ++i)
            {
                curr = first + second;
                first = second;
                second = curr;
            }
            printf("fib: %d\n", curr);
        }
    }
}