/*
	���� 3�� 
*/

#include <stdio.h>
#include <stdlib.h>
#define LENGTH 20

void printList(int list[]) {
	int i;
	
	for(i = 0; i < LENGTH; i++)
		printf("%d ", list[i]);
	printf("\n");
}

void twoWayMerge(int list[], int left, int mid, int right) {
	int i = left;
	int j = mid + 1;
	int k = left;
	int *mList = (int*)malloc(sizeof(int) * (right + 1));
	
	while(i <= mid && j <= right) {
		if(list[i] < list[j])
			mList[k++] = list[i++];
		else
			mList[k++] = list[j++];
	}
	
	for(; i <= mid; i++)
		mList[k++] = list[i];
	for(; j <= right; j++)
		mList[k++] = list[j];
		
	for(i = left; i <= right; i++)
		list[i] = mList[i];
		
	free(mList);
}

void twoWayMergeSort(int list[], int left, int right) {
	int mid;
	
	if(left < right) {
		mid = (left + right) / 2;
		twoWayMergeSort(list, left, mid);
		twoWayMergeSort(list, mid + 1, right);
		twoWayMerge(list, left, mid, right); 
	}
}

void kWayMerge(int list[], int left, int right, int k) {
	int i;
	int j;
	int l;
	int p;
	int minPos;
	int min; 
	int n = (right - left + 1);
    int interval = n / k;
    int limitLast = n - interval * (k - 1);
    int mid = left + n / k - 1;
    int *curPos = (int*)malloc(sizeof(int) * k);
    int *mList = (int*)malloc(sizeof(int) * n);

    for (i = 0; i < k; i++)
        curPos[i] = 0;

	if(k == 2)
		twoWayMerge(list, left, mid, right);
	else {
		p = 0;
		
	    while (p < n) {
	    	// k����� �迭��� �� ���� ���� �� ���� 
	    	minPos = -1;
	    	min = 2147483647;
	
			for (i = 0; i < k - 1; i++) {
	            if (curPos[i] < interval) {
	                if(list[left + interval * i + curPos[i]] < min) {
	                    min = list[left + interval * i + curPos[i]];
	                    minPos = i;
	                }
	            }
	        }
            if (curPos[i] < limitLast) {
                if(list[left + interval * i + curPos[i]] < min) {
                    min = list[left + interval * i + curPos[i]];
                    minPos = i;
                }
            }
            // ���� ���� �������� �迭�� �ְ� k��� �迭�� �ε��� �Ѱ谪 ���� 
	        mList[p++] = min;
	        curPos[minPos]++;
	    }
	    // ���ĵ� �迭�� ���� �迭�� �ʱ�ȭ 
		for (i = 0; i < n; i++)
		    list[left + i] = mList[i];
	}
	
	free(curPos);
	free(mList);
}

void kWayMergeSort(int list[], int left, int right, int k) {
	int i;
	int interval;
	
	if(k < 2) {
		printf("�պ������� �Ұ����� k���� �Է��߽��ϴ�\n");
		return;
	}
	
	// ��е� �迭�� ���̰� k���� ������ 2-Way mergeSort ��� 
	if((right - left + 1) < k)
		twoWayMergeSort(list, left, right);
	else {
		interval = (right - left + 1) / k;
		
		for(i = 0; i < k - 1; i++)
			kWayMergeSort(list, left + i * interval, left + (i + 1) * interval - 1, k);
		
		kWayMergeSort(list, left + i * interval, right, k);
		kWayMerge(list, left, right, k);
	}
}

int main(void) {
	int list[LENGTH] = { 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	int k;
	
	printf("k�Է�: ");
	scanf("%d", &k);
	
	printf("���� ��: ");
	printList(list);
	kWayMergeSort(list, 0, LENGTH - 1, k);
	
	printf("���� ��: ");
	printList(list);
}
