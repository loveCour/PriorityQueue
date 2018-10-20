#pragma once
using namespace std;

template <typename T>
class PriorQ {
private:
	const int ROOT = 1;
	vector<T> tong;
	int lastIdx;
public:
	PriorQ():tong(vector<T>(1)), lastIdx(0) {}
	PriorQ(PriorQ& pq) {
		tong = pq.tong;
		lastIdx = pq.lastIdx;
	}
	void Push(T src);
	bool Pop();
	T Top() {
		if (lastIdx > 0) {
			return tong[ROOT];
		}
		return tong[0];
	}
	void print() {
		for (int i = 1; i < lastIdx +1 ; i++) {
			cout << tong[i] << " ";
		}
	}
};

template <typename T>
void PriorQ<T>::Push(T src) {
	tong.push_back(src);
	lastIdx++;
	int currectIdx = lastIdx;
	int parentIdx = currectIdx >> 1;
	
	while (parentIdx > 0) {
		if (tong[parentIdx] > tong[currectIdx]) {
			swap(tong[parentIdx], tong[currectIdx]);
			currectIdx = parentIdx;
			parentIdx = currectIdx >> 1;
		}
		else {
			break;
		}
	}	
}

template <typename T>
bool PriorQ<T>::Pop() {
	if (lastIdx < ROOT) {
		return false;
	}
	tong[ROOT] = tong[lastIdx];
	tong.pop_back();
	lastIdx--;

	int curIdx = ROOT;	
	int nextIdx = curIdx * 2;
	while (nextIdx <= lastIdx) {
		if (nextIdx < lastIdx) {
			nextIdx = (tong[nextIdx] < tong[nextIdx + 1]) ? nextIdx : nextIdx + 1;
		}
		if (tong[curIdx] > tong[nextIdx]) {
			swap(tong[curIdx], tong[nextIdx]);
			curIdx = nextIdx;
			nextIdx = curIdx * 2;
		}
		else {
			break;
		}
	}
	return true;
}