/*
	문제 1-2번 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 100

typedef int element;

typedef struct _Element {
	int id;
	char name[NAME_SIZE];
} Element;

typedef struct _SortType {
	char menu;
	int sort;
	int length;
	Element *list;
} SortType; 

void init(SortType *s, int *menu) {
	int data, i;
	
	if(*menu == 1) {
		FILE *fp = fopen("1-2.txt", "r");
		
		if(fp == NULL) {
			printf("data.txt 파일이 존재하지 않습니다\n");
			exit(0);
		}
		
		fscanf(fp, "%d", &(s->length));
		
		s->list = (Element*)malloc(sizeof(Element) * s->length);
		
		for(i = 0; i < s->length; i++)
			fscanf(fp, "%d %s", &(s->list[i].id), s->list[i].name);
			
	} else if(*menu == 2) {
		printf("데이터 개수 입력: ");
		scanf("%d", &(s->length));
		
		s->list = (Element*)malloc(sizeof(Element) * s->length);
		
		for(i = 0; i < s->length; i++)
			scanf("id, 이름 입력: %d %s", &(s->list[i].id), s->list[i].name);
	}	
}

void swap(Element *a, Element *b) {
	Element temp = *a;
	*a = *b;
	*b = temp;
}

void printList(SortType *s) {
	int i;
	
	printf("***** 결과 *****\n");
	
	for(i = 0; i < s->length; i++)
		printf("%d. %s\n", s->list[i].id, s->list[i].name);
		
	printf("\n");
}

void selectInput(int *menu) {
	printf("****데이터 입력방법 선택****\n");
	printf("1. 파일로 입력\n");
	printf("2. 키보드로 입력\n");
	printf("메뉴 입력: ");
	scanf("%d", menu);
} 

void selectSortInput(SortType *s) {
	fflush(stdin);
	
	printf("*************\n");
	printf("s: 선택정렬\n");
	printf("i: 삽입정렬\n");
	printf("b: 버블정렬\n");
	printf("h: 쉘 정렬\n");
	printf("m: 합병정렬\n");
	printf("q: 퀵정렬\n");
	printf("*************\n");
	
	printf("메뉴 입력: ");
	scanf("%c", &(s->menu));
	
	printf("1. 오름차순\n");
	printf("2. 내림차순\n");
	printf("메뉴 입력: ");
	scanf("%d", &(s->sort));
}

// 선택정렬 
void selectSort(SortType *s) {
	int i, j;
	int sort = s->sort;
	int mIndex;
	
	for(i = 0; i < s->length; i++) {
		mIndex = i;
		
		for(j = i + 1; j < s->length; j++) {
			if(sort == 1)  {
				if(s->list[mIndex].id > s->list[j].id)
					mIndex = j;
			}
			else if(sort == 2) {
				if(s->list[mIndex].id < s->list[j].id)
					mIndex = j;
			}
		}
				
		if(mIndex != i)
			swap(&(s->list[i]), &(s->list[mIndex]));
	} 
}

// 삽입정렬
void insertSort(SortType *s) {
	int i, j;
	int sort = s->sort; 
	Element key;
	
	for(i = 1; i < s->length; i++) {
		key = s->list[i];
		
		if(sort == 1) {
			for(j = i - 1; j >= 0 && s->list[j].id > key.id; j--)
				s->list[j + 1] = s->list[j];
		}
		else if(sort == 2) {
			for(j = i - 1; j >= 0 && s->list[j].id < key.id; j--)
				s->list[j + 1] = s->list[j];
		}
		s->list[j + 1] = key;
	}
}

// 버블정렬
void bubbleSort(SortType *s) {
	int i, j;
	int sort = s->sort;
	
	for(i = 0; i < s->length - 1; i++) {
		for(j = i + 1; j < s->length; j++) {
			if(sort == 1) {
				if(s->list[i].id > s->list[j].id)
					swap(&(s->list[i]), &(s->list[j]));
			}
			else if(sort == 2) {
				if(s->list[i].id < s->list[j].id)
					swap(&(s->list[i]), &(s->list[j]));
			}
		}
	} 
}

// 쉘정렬
void shellSort(SortType *s) {
	int i, j, k; 
	int sort = s->sort;
	int interval;
	Element key;
		
	for(interval = s->length / 2; interval > 0; interval /= 2) {
		for(i = 0; i < interval; i++) {
			for(j = i + interval; j < s->length; j += interval) {
				key = s->list[j];
				
				if(sort == 1) {
					for(k = j - interval; k >= 0 && s->list[k].id > key.id; k -= interval)
						s->list[k + interval] = s->list[k];
				}
				else if(sort == 2) {
					for(k = j - interval; k >= 0 && s->list[k].id < key.id; k -= interval)
						s->list[k + interval] = s->list[k];
				}
				
				s->list[k + interval] = key;
			}
		}
	}
}

// 합병정렬
void merge(SortType *s, int left, int mid, int right) {  
	int sort = s->sort;
	int i = left;
	int j = mid + 1;
	int k = left;
	int l;
	
	Element *sorted = (Element*)malloc(sizeof(Element) * (right + 1));
	
	while(i <= mid && j <= right){
		if(sort == 1) {
			if(s->list[i].id <= s->list[j].id)
				sorted[k++] = s->list[i++];
			else
				sorted[k++] = s->list[j++];
		}
		else if(sort == 2) {
			if(s->list[i].id >= s->list[j].id)
				sorted[k++] = s->list[i++];
			else
				sorted[k++] = s->list[j++];
		}
	}
	
	while(i <= mid)
		sorted[k++] = s->list[i++];
		
	while(j <= right)
		sorted[k++] = s->list[j++];
	
	for(l = left; l <= right; l++)
		s->list[l] = sorted[l];
	
	free(sorted);
}

void mergeSort(SortType *s, int left, int right) {
	int mid;
	
	if(left < right){
		mid = (left + right) / 2;
		mergeSort(s, left, mid);
		mergeSort(s, mid + 1, right);
		merge(s, left, mid, right);
	}
} 

// 퀵정렬
int partition(SortType *s, int left, int right) {
	
	if(right <= left)
		return left;
	
	int low = left;
	int high = right + 1;
	int sort = s->sort;
	Element pivot = s->list[left];
    
    while(low < high) {
		if(sort == 1) {
			do
	    		low++;
	    	while(low <= right && pivot.id > s->list[low].id);
	    	
	    	do
	    		high--;
	    	while(high > left && pivot.id <= s->list[high].id);
    	}
    	
    	if(sort == 2) {
    		do {
	    		low++;
	    	} while(low <= right && pivot.id < s->list[low].id);
	    	
	    	do {
	    		high--;
	    	} while(high > left && pivot.id >= s->list[high].id);
		}
    	if(low < high)
    		swap(&(s->list[low]), &(s->list[high]));
	}
	
	s->list[left] = s->list[high];
	s->list[high] = pivot;
	
	return high;
}

void quickSort(SortType *s, int left, int right) {  
	int q;
    
	if(left < right) {
		q = partition(s, left, right);
		quickSort(s, left, q - 1);
		quickSort(s, q + 1, right);
	}
}

void sortList(SortType *s) {
	switch(s->menu) {
		case 's':
			selectSort(s);
			break;
		case 'i':
			insertSort(s);
			break;
		case 'b':
			bubbleSort(s);
			break;
		case 'h':
			shellSort(s);
			break;
		case 'm':
			mergeSort(s, 0, s->length - 1);
			break;
		case 'q':
			quickSort(s, 0, s->length - 1);
			break;
	} 
}

int main() {
	int inputMenu;
	SortType s;
	
	selectInput(&inputMenu);
	init(&s, &inputMenu);
	selectSortInput(&s);
	sortList(&s);
	printList(&s);
	
	free(s.list);
}
