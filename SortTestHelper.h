#pragma once

#include "SortAlgorithm.h"


namespace SortTestHelper
{
	//�������һ��[rangeL,rangeR],��ģΪn������
	int* generateRandomArray(int n, int rangeL, int rangeR)
	{
		srand(time(NULL));
		int* arr = new int[n];
		for (int i = 0; i < n; i++)
			arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
		return arr;
	}

	//����һ�������������鲢�������swaptimes��
	int* generateNearlyOrderedArray(int n, int swaptimes)
	{
		int* arr = new int[n];
		for (int i = 0; i < n; i++)
		{
			arr[i] = i;
		}
		srand(time(NULL));
		for (int i = 0; i < swaptimes;i++)
		{
			int x = rand() % n;
			int y = rand() % n;
			swap(arr[x], arr[y]);
		}
		return arr;
	}

	//����һ�������������鲢�漴����swaptimes��
	int* generateNearlyReverseArray(int n, int swaptimes)
	{
		int* arr = new int[n];
		for (int i = 0; i < n; i++)
			arr[i] = n - i - 1;
		srand(time(NULL));
		for (int i = 0; i < swaptimes; i++)
		{
			int x = rand() % n;
			int y = rand() % n;
			swap(arr[x], arr[y]);
		}
		return arr;
	}

	//�ж�һ�������Ƿ����ź����
	template<typename T>
	bool isSorted(T arr[], int n)
	{
		for (int i = 0; i < n - 1; i++)
			if (arr[i] > arr[i + 1])
				return false;
		return true;
	}

	//����һ����������
	int* copyArray(int arr[], int n)
	{
		int* arrNew = new int[n];
		copy(arr, arr + n, arrNew);
		return arrNew;
	}

	//���������㷨��ִ��ʱ��
	template<typename T>
	void testSort(string sortName, void (*sort)(T[], int), T arr[], int n)
	{
		//�ȼ������������̽��ж���ʱ��
		chrono::high_resolution_clock::time_point startTime = chrono::high_resolution_clock::now();
		sort(arr, n);
		chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();

		chrono::duration<double, std::milli> timeSpend = endTime - startTime;
		//Ȼ��ȷ����������������ȷ��
		assert(isSorted(arr, n));
		cout << sortName << ":" << endl  << "Running time: "<< timeSpend.count() << "ms.  ";
		if (sortName == "InsertionSort")
		{
			cout << "Moving times: " << insertMoveTimes << ".  " << "Camparing times: " << insertCampareTimes << ".  " << endl;
		}
		else if (sortName == "MergeSort")
		{
			cout << "Moving times: " << mergeMoveTimes << ".  " << "Camparing times: " << mergeCampareTimes << ".  " << endl;
		}
		else if (sortName == "QuickSort")
		{
			cout << "Moving times: " << quickMoveTimes << ".  " << "Camparing times: " << quickCampareTimes << ".  " << endl;
		}

		return;
	}
}
