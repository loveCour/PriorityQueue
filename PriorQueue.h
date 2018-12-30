#pragma once
#include <iostream>
#include <vector>
#include <functional>
using namespace std;
/*
* �� �켱���� ť�� �迭�� Ȱ���Ͽ� �����Ͽ����ϴ�.
* ���� �ڽ��� �ε��� = (�θ��� �ε���) * 2
* ������ �ڽ��� �ε��� = (�θ��� �ε���) * 2 + 1
* �θ��� �ε��� = (�ڽ��� �ε���) / 2 �Դϴ�.
* ���� �� �켱���� ���Լ��� ����ϸ�
* �켱������ ����� �Լ��� ������ ���� �Ǵ��մϴ�.
*/

template <typename T>
bool comp(const T a, const T b) {
	return a > b;
}

template <typename T>
class PriorQ {
private:
	static const int ROOT = 1;
	vector<T> container;
	int lastIdx;
public:
	PriorQ();
	PriorQ(PriorQ& pq);
	void Push(T src);
	bool Pop();
	T Top();
	void Print(int depth, int curidx);
};

template <typename T>
PriorQ<T>::PriorQ(): container(vector<T>(1)), lastIdx(0)
{
}

template <typename T>
PriorQ<T>::PriorQ(PriorQ& pq)
{
	container = pq.container;
	lastIdx = pq.lastIdx;
}

template <typename T>
T PriorQ<T>::Top() {
	if (lastIdx > 0) {
		return container[ROOT];
	}
	return container[0];
}

template <typename T>
void PriorQ<T>::Push(T src) {
	container.push_back(src);
	lastIdx++;
	int currectIdx = lastIdx;
	int parentIdx = currectIdx >> 1;
	while (parentIdx > 0) 
	{
		if ( container[parentIdx] > container[currectIdx] )
		{//�θ� �� ũ�� swap�Ѵ�.
			swap(container[parentIdx], container[currectIdx]);
			currectIdx = parentIdx;
			parentIdx = currectIdx >> 1;
		}
		else
		{//�ƴ϶�� ������ ��ģ��.
			break;
		}
	}	
}

template <typename T>
bool PriorQ<T>::Pop() {
	if (lastIdx < ROOT) 
	{
		return false;
	}
	container[ROOT] = container[lastIdx];//��Ʈ�� ���� �� ���� ������ �ٲ۵�
	container.pop_back();//�� ���� ���� �����Ѵ�.
	lastIdx--;

	int curIdx = ROOT;	
	int nextIdx = curIdx * 2;
	//��Ʈ���� �� ���� ����
	while (nextIdx <= lastIdx) 
	{
		if (nextIdx < lastIdx)
		{//���� �ڽ��� �����ϰ�
			nextIdx = (container[nextIdx] < container[nextIdx + 1]) ? nextIdx : nextIdx + 1;
		}
		if (container[curIdx] > container[nextIdx]) 
		{//������ �ڽ��� �θ𺸴� ũ�ٸ� �����ѵ� ������ ������Ʈ �ϰ� ������ �̾��.
			swap(container[curIdx], container[nextIdx]);
			curIdx = nextIdx;
			nextIdx = curIdx * 2;
		}
		else {
			break;
		}
	}
	return true;
}

template <typename T>
void PriorQ<T>::Print(int depth, int curidx) {	
	cout << depth << ":";
	if (curidx <= lastIdx)
	{		
		cout << container[curidx] << "  ";
		int leftChildIdx = curidx * 2;
		int rightChildIdx = curidx * 2 + 1;
		if (leftChildIdx <= lastIdx)
		{
			Print(depth + 1, leftChildIdx);			
		}
		if (rightChildIdx <= lastIdx)
		{
			Print(depth + 1, rightChildIdx);
		}
		cout << " " << endl;
	}
}