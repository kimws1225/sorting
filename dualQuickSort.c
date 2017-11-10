

#include <stdio.h>
#define LENGTH 10

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printList(int list[]) {
	int i;
	
	for(i = 0; i < LENGTH; i++)
		printf("%d ", list[i]);
	printf("\n");
}

int partition(int* list, int left, int right, int* lp) {
    if (list[left] > list[right])
        swap(&list[left], &list[right]);

    int j = left + 1;
    int g = right - 1, k = left + 1, p = list[left], q = list[right];
    while (k <= g) {
 
        if (list[k] < p) {
            swap(&list[k], &list[j]);
            j++;
        }
 
        else if (list[k] >= q) {
            while (list[g] > q && k < g)
                g--;
            swap(&list[k], &list[g]);
            g--;
            if (list[k] < p) {
                swap(&list[k], &list[j]);
                j++;
            }
        }
        k++;
    }
    j--;
    g++;
 
    swap(&list[left], &list[j]);
    swap(&list[right], &list[g]);
 
    *lp = j;
    return g;
}
 
void quickSort(int list[], int left, int right) {
	int lp;
	int rp;
	
    if (left < right) {
        rp = partition(list, left, right, &lp);
        quickSort(list, left, lp - 1);
        quickSort(list, lp + 1, rp - 1);
        quickSort(list, rp + 1, right);
    }
}
 
int main()
{
    int list[LENGTH] = { 6, 2, 4, 10, 9, 7, 8, 1, 3, 5 };
    
    printf("정렬 전: ");
    printList(list);
    quickSort(list, 0, LENGTH - 1);
    
    printf("정렬 후: "); 
    printList(list);
}
