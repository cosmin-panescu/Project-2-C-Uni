#include <stdio.h>
#include <stdlib.h>

int val_min(int *vector, int n)
{
    if (n == 1)
        return vector[0];
    else
        return (vector[n - 1] < val_min(vector, n - 1) ? vector[n - 1] : val_min(vector, n - 1));
}

int val_max(int *vector, int n)
{
    if (n == 1)
        return vector[0];
    else
        return (vector[n - 1] > val_max(vector, n - 1) ? vector[n - 1] : val_max(vector, n - 1));
}

int main()
{
    int *vector, n;

    printf("\nIntroduceti numarul de elemente: ");
    scanf("%d", &n);

    vector = (int *)malloc(sizeof(int) * n);
    if (vector == NULL)
    {
        printf("Eroare la alocarea de memorie!");
        exit(1);
    }

    printf("\nIntroduceti valorile elementelor vectorului:\n");
    for (int i = 0; i < n; i++)
    {
        printf("-Valoarea %d a vectorului: ", i + 1);
        scanf("%d", &vector[i]);
    }

    printf("\nValoarea minima a elementelor vectorului este: %d\n", val_min(vector, n));
    printf("Valoarea maxima a elementelor vectorului este: %d", val_max(vector, n));

    free(vector);
    return 0;
}
