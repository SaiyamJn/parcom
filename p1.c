#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void merge(int a[], int l, int m, int r) {
    int i = l, j = m + 1, k = 0;
    int *t = malloc((r - l + 1) * sizeof(int));

    if (t == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    while (i <= m && j <= r)
        t[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];

    while (i <= m)
        t[k++] = a[i++];

    while (j <= r)
        t[k++] = a[j++];

    for (i = l, k = 0; i <= r; i++, k++)
        a[i] = t[k];

    free(t);
}

// Sequential Merge Sort
void sort(int a[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        sort(a, l, m);
        sort(a, m + 1, r);

        merge(a, l, m, r);
    }
}

// Parallel Merge Sort
void psort(int a[], int l, int r, int d) {
    if (l >= r)
        return;

    int m = l + (r - l) / 2;

    if (d <= 0) {
        sort(a, l, m);
        sort(a, m + 1, r);
    } else {
        #pragma omp task shared(a) firstprivate(l, m, d)
        psort(a, l, m, d - 1);

        #pragma omp task shared(a) firstprivate(m, r, d)
        psort(a, m + 1, r, d - 1);

        #pragma omp taskwait
    }

    merge(a, l, m, r);
}

int main(void) {
    int n = 100000;

    int *a = malloc(n * sizeof(int));
    int *b = malloc(n * sizeof(int));
    int *c = malloc(n * sizeof(int));

    if (a == NULL || b == NULL || c == NULL) {
        printf("Memory allocation failed!\n");
        free(a);
        free(b);
        free(c);
        return 1;
    }

    srand((unsigned int)time(NULL));

    for (int i = 0; i < n; i++)
        a[i] = rand() % 100000;

    for (int i = 0; i < n; i++)
        b[i] = c[i] = a[i];

    // Sequential Merge Sort
    double start = omp_get_wtime();

    sort(b, 0, n - 1);

    double end = omp_get_wtime();

    printf("Sequential Merge Sort Time: %f seconds\n",
           end - start);

    // Parallel Merge Sort
    start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        psort(c, 0, n - 1, 4);
    }

    end = omp_get_wtime();

    printf("Parallel Merge Sort Time: %f seconds\n",
           end - start);

    free(a);
    free(b);
    free(c);

    return 0;
}


// gcc mergesort_omp.c -fopenmp -o mergesort
// ./mergesort
// Sample output
// Sequential Merge Sort Time: (varies) seconds
// Parallel Merge Sort Time: (varies) seconds