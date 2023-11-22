
/*
插入排序算法的原理如下：
	1.从第一个元素开始，该元素可以认为已经被排序
	2.取下一个元素tem，从已排序的元素序列从后往前扫描
	3.如果该元素大于tem，则将该元素移到下一位
	4.重复步骤3，直到找到已排序元素中小于等于tem的元素
	5.tem插入到该元素的后面，如果已排序所有元素都大于tem，则将tem插入到下标为0的位置
	6.重复步骤2~5
*/
void InsertSort(int* arr, int n)
{
	for (int i = 0; i < n - 1; ++i)
	{
		//记录有序序列最后一个元素的下标
		int end = i;
		//待插入的元素
		int tem = arr[end + 1];
		//单趟排
		while (end >= 0)
		{
			//比插入的数大就向后移
			if (tem < arr[end])
			{
				arr[end + 1] = arr[end];
				end--;
			}
			//比插入的数小，跳出循环
			else
			{
				break;
			}
		}
		//tem放到比插入的数小的数的后面
		arr[end + 1] = tem;
		//代码执行到此位置有两种情况:
		//1.待插入元素找到应插入位置（break跳出循环到此）
		//2.待插入元素比当前有序序列中的所有元素都小（while循环结束后到此）
	}
}


/*冒泡排序：
    1、从列表的第一个元素开始，依次比较相邻的两个元素。
	2、如果第一个元素比第二个元素大，则交换它们的位置。
	3、继续比较下一对相邻元素，重复上述步骤，直到列表末尾。
	4、重复上述步骤，直到没有发生交换的元素对，即列表已经排序完成。
*/
void BubbleSort(int arr[], int length)
{
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int temp;
				temp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

/**
快速排序算法的原理如下：
​	1.从数列中挑出一个元素，称为 “基准”（pivot）;
​	2.重新排序数列，所有元素比基准值小的摆放在基准前面，所有元素比基准值大的摆在基准的后面（相同的数可以到任一边）。
	  在这个分区退出之后，该基准就处于数列的中间位置。这个称为分区（partition）操作；
​	3.递归地（recursive）把小于基准值元素的子数列和大于基准值元素的子数列排序。
*/

// 快速排序
void QuickSort(int arr[], int start, int end)
{
	if (start >= end)
		return;
	int i = start;
	int j = end;
	// 基准数
	int baseval = arr[start];
	while (i < j)
	{
		// 从右向左找比基准数小的数
		while (i < j && arr[j] >= baseval)
		{
			j--;
		}
		if (i < j)
		{
			arr[i] = arr[j];
			i++;
		}
		// 从左向右找比基准数大的数
		while (i < j && arr[i] < baseval)
		{
			i++;
		}
		if (i < j)
		{
			arr[j] = arr[i];
			j--;
		}
	}
	// 把基准数放到i的位置
	arr[i] = baseval;
	// 递归
	QuickSort(arr, start, i - 1);
	QuickSort(arr, i + 1, end);
}


/*
	选择排序算法是通过遍历数组，选择出数组的最小或最大值，与指定位置交换数据，遍历完整个数组的所有位置就完成排序
	1、遍历第一趟数组，找出数组的最小值，与第一个数据交换
	2、遍历第二趟数组，继续找出最小值，与第二个数据交换
	3、重复上述动作，遍历完数组就得到一个有序数组
*/
//交换两个数据
void Swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

//选择排序
void SelectSort(int* arr, int size)
{
	int i = 0;
	for (i = 0; i < size - 1; i++)
	{
		int min = i;
		int j = 0;
		for (j = i + 1; j < size; j++)
		{
			if (arr[j] < arr[min])
			{
				min = j;
			}
		}
		Swap(&arr[i], &arr[min]);
	}
}