/*
 * hw12-sorting-hashing.c
 *
 *  Created on: May 22, 2021
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;
	
	srand(time(NULL));
	
	printf("[----- [한민우] [2018038047] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); // 정렬되기 전 배열 출력
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array); // 정렬 된 후의 배열 출력

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{ /* 동적 할당된 메모리 해제 */
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a) // 배열 출력
{
	if (a == NULL) { 
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) // array number 출력
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) // 배열에 들어있는 데이터 출력
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a) // 선택 정렬. 리스트중 가장 작은 값을 맨 앞에 삽입해나간다.
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 정렬되기 전 배열 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i; // 정렬되지 않은 부분의 가장 앞
		min = a[i]; // 정렬되지 않은 부분의 가장 앞에 들어있는 데이터
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j]) // 리스트에서 더 작은 값 찾으면
			{
				min = a[j]; // 가장 작은 값
				minindex = j; // 가장 작은 값이 들어있는 array number 변경
			}
		}
		/* 가장 작은 값과 맨 앞의 값 swap */
		a[minindex] = a[i];
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬 된 후의 배열 출력
	return 0;
}

int insertionSort(int *a) // 삽입 정렬. 작은 값을 앞으로 옮겨나간다
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 정렬되기 전 배열 출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i]; // 기준이 되는 데이터를 저장한다
		j = i; // 검색을 시작할 array number
		while (a[j-1] > t && j > 0) // 기준 데이터보다 앞쪽에 있는 데이터의 크기가 클동안
		{
			a[j] = a[j-1]; // 큰 데이터를 한 칸 뒤로 옮긴다.
			j--; // array 앞으로 한칸 이동
		}
		a[j] = t; // 기준이 되었던 데이터를 위치에 삽입한다
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬 된 후의 배열 출력

	return 0;
}

int bubbleSort(int *a) // 버블정렬. 더 큰 값을 뒤로 옮기며 나아간다.
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 정렬되기 전 배열 출력

	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j]) // 앞에 있는 데이터가 바로 뒤에 있는 데이터보다 크다면 swap
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬 된 후의 배열 출력

	return 0;
}

int shellSort(int *a) // 셸 정렬. 일정 간격만큼 떨어진 array와 비교해 삽입정렬
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 정렬되기 전 배열 출력

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) // 초기 간격은 크기/2, /2씩 줄여나감
	{
		for (i = 0; i < h; i++) // h만큼 떨어진 array끼리 배열
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h) // 앞에 있는 data가 더 크다면 자리 바꿈
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v) 
				{
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬 된 후의 배열 출력

	return 0;
}

int quickSort(int *a, int n) // 퀵 정렬. pivot을 기준으로 왼쪽 오른쪽으로 나누어 정렬
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1]; // pivot 설정 (맨 뒤에 있는 data)
		i = -1;
		j = n - 1;

		while(1)
		{
			while(a[++i] < v); // pivot보다 큰 데이터 탐색
			while(a[--j] > v); // pivot보다 작은 데이터 탐색

			if (i >= j) break; // i가 j보다 크거나 같으면 탈출
			/* 아니라면 a[i]와 a[j] 자리 swap */
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		/* a[i]와 pivot 자리 swap 여기서 고정된 pivot은 최종 pivot의 자리임 */
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;
		/* pivot 기준 왼쪽 오른쪽에 대해 반복 */
		quickSort(a, i);
		quickSort(a+i+1, n-i-1);
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++) // hash table -1로 초기화
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key); // 해시 함수에서 key에 맞는 위치 받아옴
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1) // key를 넣고자 하는 위치가 비어있으면
		{
			hashtable[hashcode] = key; // 위치에 삽입
		} else 	{ // 넣고자 하는 위치가 비어있지 않아서 오버플로우가 일어났다면

			index = hashcode;

			while(hashtable[index] != -1) // 다음 인덱스로 넘어가며 빈 곳 검색
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key; // 빈 곳에 키 삽입
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key); // 해시 함수로 위치 받아옴

	if(ht[index] == key) // 받아온 위치에 원하는 키가 있다면 리턴
		return index;

	while(ht[++index] != key) // 없다면 인덱스 증가시키며 탐색
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}



