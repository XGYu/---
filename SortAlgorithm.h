#pragma once

#include <iostream>
#include <algorithm>
#include <ctime>
#include <string>
#include <cassert>
#include <chrono>
#include <ratio>

using namespace std;

long long int insertCampareTimes;
long long int insertMoveTimes;
long long int mergeCampareTimes;
long long int mergeMoveTimes;
long long int quickCampareTimes;
long long int quickMoveTimes;

namespace SortAlgorithm
{
	//���������㷨���Ӷ���O(n^2)��������ͬ����ģ�»��ѡ������Ч�ʸ�
	template<typename T>
	void insertionSort(T arr[], int n)
	{
		insertCampareTimes = 0;
		insertMoveTimes = 0;
		for (int i = 1; i < n; i++)   //�ӵڶ���Ԫ�����򼴿�
		{
			insertCampareTimes ++;
			T e = arr[i];
			int j = i;
			for (; j > 0 && arr[j - 1] > e; j--)
			{
				insertCampareTimes += 2;
				arr[j] = arr[j - 1];   //����һ������ǰ�ƵĹ���
				insertMoveTimes++;
			}
			arr[j] = e; //ʹ�����ַ�����Ч�ʻ��ֱ��ʹ��swap������
			insertMoveTimes++;
		}
	}

	//��arr[l ... r]���в�������
	template<typename T>
	void __insertionSortForMerge(T arr[], int l, int r)
	{
		for (int i = l + 1; i <= r; i++)
		{
			mergeCampareTimes ++;
			T e = arr[i];
			int j = i;
			for (; j > l&& arr[j - 1] > e; j--)
			{
				mergeCampareTimes += 2;		//�ȽϹ����������Ľ�
				arr[j] = arr[j - 1];
				mergeMoveTimes ++;
			}
			arr[j] = e;
			mergeMoveTimes ++;
		}
		return;
	}

	//��arr[l ... r]���в�������
	template<typename T>
	void __insertionSortForQuick(T arr[], int l, int r)
	{
		for (int i = l + 1; i <= r; i++)
		{
			quickCampareTimes ++;
			T e = arr[i];
			int j = i;
			for (; j > l && arr[j - 1] > e; j--)
			{
				quickCampareTimes += 2;
				arr[j] = arr[j - 1];
				quickMoveTimes ++;
			}
			arr[j] = e;
			quickMoveTimes ++;
		}
		return;
	}

	//��arr[l...mid]�Լ�arr[mid+1...r]���й鲢����
	template<typename T>
	void __merge(T arr[], int l, int mid, int r)
	{
		T* aux = new T[r - l + 1];
		for (int i = l; i <= r; i++)
			aux[i - l] = arr[i];

		int i = l, j = mid + 1;
		for (int k = l; k <= r; k++)
		{
			mergeCampareTimes ++;		//�Ƚϴ���+1
			if (i > mid)
			{
				mergeCampareTimes ++;	//��Ų����+1
				arr[k] = aux[j - l];
				mergeMoveTimes ++;		//��Ų����+1
				j++;
			}
			else if (j > r)
			{
				mergeCampareTimes += 2;	//�Ƚϴ���+2,��ΪifҲ�����˱Ƚ�,�������ŵ�������,����ͬ��
				arr[k] = aux[i - l];
				mergeMoveTimes ++;		//��Ų����+1
				i++;
			}
			else if (aux[i - l] <= aux[j - l]) //���������ƻ��㷨���ȶ���
			{
				mergeCampareTimes +=3;	//�Ƚϴ���+3
				arr[k] = aux[i - l];
				mergeMoveTimes ++;		//��Ų����+1
				i++;
			}
			else
			{
				mergeCampareTimes += 3;	//�Ƚϴ���+3
				arr[k] = aux[j - l];
				mergeMoveTimes ++;		//��Ų����+1
				j++;
			}
		}
		delete[] aux;
	}

	//�����漰���ݹ�����Լ�������ϣ���û�ֱ��ʹ�õĺ���������˫�»��߿�ͷ
	//��arr[l ... r]���кϲ�����
	template<typename T>
	void __mergeSort(T arr[], int l, int r)
	{
		//����ݹ鵽���˷Ѵ����Ķ�ջ�ռ��ʱ�䣬���Ե�ǰ���鳤��С��16ʱ��ֱ�ӽ����������
		if (r - l <= 15)
		{
			__insertionSortForMerge(arr, l, r);
			return;
		}

		int mid = l + (r - l) / 2;  //��ֹ���
		__mergeSort(arr, l, mid);
		__mergeSort(arr, mid + 1, r);

		//�����ߴ��ϲ���������Ҳ�ֵС���ұ���Сֵ������ֱ�Ӻϲ���һ�����飬���ý���merge����
		if (arr[mid] > arr[mid + 1])
		{
			mergeCampareTimes++;
			__merge(arr, l, mid, r);
		}
	}

	//�Զ����µĺϲ�����
	template<typename T>
	void mergeSort(T arr[], int n)
	{
		mergeCampareTimes = 0;
		mergeMoveTimes = 0;
		__mergeSort(arr, 0, n - 1);
	}

	//����p,ʹ��arr[l...p-1]<arr[p],arr[p+1...r]>arr[p]
	template<typename T>
	int __partition(T arr[], int l, int r)
	{
		swap(arr[l], arr[rand() % (r - l + 1) + l]); //���������Ϊ�ο�ֵ
		quickMoveTimes += 3;	//һ��swap���̶�Ӧ3����Ų����
		T e = arr[l];
		int j = l;
		for (int i = l + 1; i <= r; i++)
		{
			quickCampareTimes ++;
			if (arr[i] < e)
			{
				quickCampareTimes ++;
				j++;
				swap(arr[i], arr[j]);
				quickMoveTimes += 3;
			}
		}
		swap(arr[l], arr[j]);
		quickMoveTimes += 3;

		return j;
	}

	//��arr[l ... r]���п�������
	template<typename T>
	void __quickSort(T arr[], int l, int r)
	{
		if (r - l <= 15)
		{
			__insertionSortForQuick(arr, l, r);
			return;
		}

		int p = __partition(arr, l, r);

		__quickSort(arr, l, p - 1);
		__quickSort(arr, p + 1, r);
	}

	//��������
	template<typename T>
	void quickSort(T arr[], int n)
	{
		quickCampareTimes = 0;
		quickMoveTimes = 0;
		srand(time(NULL));
		__quickSort(arr, 0, n - 1);
	}
}
