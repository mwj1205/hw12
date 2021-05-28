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

/* �ʿ信 ���� �Լ� �߰� ���� */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function���� ���� */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a���� �� hash table�� �����. */
int hashing(int *a, int **ht);

/* hash table���� key�� ã�� hash table�� index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;
	
	srand(time(NULL));
	
	printf("[----- [�ѹο�] [2018038047] -----]\n");

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
			printArray(array); // ���ĵǱ� �� �迭 ���
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array); // ���� �� ���� �迭 ���

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

	/* array�� NULL�� ��� �޸� �Ҵ� */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else
		temp = *a;

	/* �������� �迭�� ������ ���� */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{ /* ���� �Ҵ�� �޸� ���� */
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a) // �迭 ���
{
	if (a == NULL) { 
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) // array number ���
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) // �迭�� ����ִ� ������ ���
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a) // ���� ����. ����Ʈ�� ���� ���� ���� �� �տ� �����س�����.
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // ���ĵǱ� �� �迭 ���

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i; // ���ĵ��� ���� �κ��� ���� ��
		min = a[i]; // ���ĵ��� ���� �κ��� ���� �տ� ����ִ� ������
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j]) // ����Ʈ���� �� ���� �� ã����
			{
				min = a[j]; // ���� ���� ��
				minindex = j; // ���� ���� ���� ����ִ� array number ����
			}
		}
		/* ���� ���� ���� �� ���� �� swap */
		a[minindex] = a[i];
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // ���� �� ���� �迭 ���
	return 0;
}

int insertionSort(int *a) // ���� ����. ���� ���� ������ �Űܳ�����
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // ���ĵǱ� �� �迭 ���

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i]; // ������ �Ǵ� �����͸� �����Ѵ�
		j = i; // �˻��� ������ array number
		while (a[j-1] > t && j > 0) // ���� �����ͺ��� ���ʿ� �ִ� �������� ũ�Ⱑ Ŭ����
		{
			a[j] = a[j-1]; // ū �����͸� �� ĭ �ڷ� �ű��.
			j--; // array ������ ��ĭ �̵�
		}
		a[j] = t; // ������ �Ǿ��� �����͸� ��ġ�� �����Ѵ�
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // ���� �� ���� �迭 ���

	return 0;
}

int bubbleSort(int *a) // ��������. �� ū ���� �ڷ� �ű�� ���ư���.
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // ���ĵǱ� �� �迭 ���

	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j]) // �տ� �ִ� �����Ͱ� �ٷ� �ڿ� �ִ� �����ͺ��� ũ�ٸ� swap
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // ���� �� ���� �迭 ���

	return 0;
}

int shellSort(int *a) // �� ����. ���� ���ݸ�ŭ ������ array�� ���� ��������
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // ���ĵǱ� �� �迭 ���

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) // �ʱ� ������ ũ��/2, /2�� �ٿ�����
	{
		for (i = 0; i < h; i++) // h��ŭ ������ array���� �迭
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h) // �տ� �ִ� data�� �� ũ�ٸ� �ڸ� �ٲ�
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
	printArray(a); // ���� �� ���� �迭 ���

	return 0;
}

int quickSort(int *a, int n) // �� ����. pivot�� �������� ���� ���������� ������ ����
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1]; // pivot ���� (�� �ڿ� �ִ� data)
		i = -1;
		j = n - 1;

		while(1)
		{
			while(a[++i] < v); // pivot���� ū ������ Ž��
			while(a[--j] > v); // pivot���� ���� ������ Ž��

			if (i >= j) break; // i�� j���� ũ�ų� ������ Ż��
			/* �ƴ϶�� a[i]�� a[j] �ڸ� swap */
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		/* a[i]�� pivot �ڸ� swap ���⼭ ������ pivot�� ���� pivot�� �ڸ��� */
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;
		/* pivot ���� ���� �����ʿ� ���� �ݺ� */
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

	/* hash table�� NULL�� ��� �޸� �Ҵ� */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else {
		hashtable = *ht;	/* hash table�� NULL�� �ƴѰ��, table ��Ȱ��, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++) // hash table -1�� �ʱ�ȭ
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
		hashcode = hashCode(key); // �ؽ� �Լ����� key�� �´� ��ġ �޾ƿ�
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1) // key�� �ְ��� �ϴ� ��ġ�� ���������
		{
			hashtable[hashcode] = key; // ��ġ�� ����
		} else 	{ // �ְ��� �ϴ� ��ġ�� ������� �ʾƼ� �����÷ο찡 �Ͼ�ٸ�

			index = hashcode;

			while(hashtable[index] != -1) // ���� �ε����� �Ѿ�� �� �� �˻�
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key; // �� ���� Ű ����
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key); // �ؽ� �Լ��� ��ġ �޾ƿ�

	if(ht[index] == key) // �޾ƿ� ��ġ�� ���ϴ� Ű�� �ִٸ� ����
		return index;

	while(ht[++index] != key) // ���ٸ� �ε��� ������Ű�� Ž��
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}



