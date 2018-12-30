#pragma once
#include <iostream>
#include <vector>
#include <functional>
using namespace std;
/*
* 이 우선순위 큐는 배열을 활용하여 구현하였습니다.
* 왼쪽 자식의 인덱스 = (부모의 인덱스) * 2
* 오른쪽 자식의 인덱스 = (부모의 인덱스) * 2 + 1
* 부모의 인덱스 = (자식의 인덱스) / 2 입니다.
* 생성 시 우선순위 비교함수를 등록하면
* 우선순위는 등록한 함수의 로직에 따라 판단합니다.
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
		{//부모가 더 크면 swap한다.
			swap(container[parentIdx], container[currectIdx]);
			currectIdx = parentIdx;
			parentIdx = currectIdx >> 1;
		}
		else
		{//아니라면 정렬을 마친다.
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
	container[ROOT] = container[lastIdx];//루트의 값을 맨 뒤의 값으로 바꾼뒤
	container.pop_back();//맨 뒤의 값을 삭제한다.
	lastIdx--;

	int curIdx = ROOT;	
	int nextIdx = curIdx * 2;
	//루트부터 재 정렬 시작
	while (nextIdx <= lastIdx) 
	{
		if (nextIdx < lastIdx)
		{//다음 자식을 선택하고
			nextIdx = (container[nextIdx] < container[nextIdx + 1]) ? nextIdx : nextIdx + 1;
		}
		if (container[curIdx] > container[nextIdx]) 
		{//선택한 자식이 부모보다 크다면 스왑한뒤 정보를 업데이트 하고 정렬을 이어간다.
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