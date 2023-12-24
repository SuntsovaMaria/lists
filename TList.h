#pragma once
#include<iostream>
#include<vector>

using namespace std;

template<typename T> class TList {
	struct TNode {
		T val;
		TNode* Next;
	};
	TNode* First;
	size_t sz;
public:
	TList() : First(nullptr), sz(0) { }
	TList(const vector<T>& v) {
		for (size_t i = v.size(); i > 0; i--)
			PushFront(v[i - 1]);
	}
	TList(const TList& list) :
		First(nullptr), sz(list.sz) {
		if (list.pFirst == nullptr)
			return;
		TNode* New = First = new TNode{ *list.pFirst };
		for (; New->Next != nullptr; New = New->Next)
			New->Next = new TNode{ *New->Next };
	}
	TList(TList&& list) noexcept {
		First = nullptr;
		swap(*this, list);
	}
	TList& operator=(const TList& list) {
		if (this != &list) {
			TList tmp(list);
			swap(*this, tmp);
		}
		return *this;
	}
	TList& operator=(TList&& list) noexcept {
		swap(*this, list);
		return *this;
	}
	~TList() {
		while (First != nullptr){
	TNode * Next = First->Next;
	delete First;
	First = Next;
			}

	}
	size_t size() const noexcept {
		return sz;
	}
	bool IsEmpty() const noexcept {
		return sz == 0;
	}
	T& Front() noexcept {
		return First->value;
	}
	void PushFront(const T& val) {
		TNode* node = new TNode{ val, First };
		First = node;
		sz++;
	}
	void PopFront() noexcept {
		TNode* p = First;
		First = First->Next;
		delete p;
		sz--;
	}
	T& operator[](size_t pos) {
		TNode* p = ToPos(pos);
		return p->value;
	}
	void EraseAfter(size_t pos) {
		TNode* p = ToPos(pos);
		TNode* Del = p->Next;
		p->Next = Del->Next;
		delete Del;
		sz--;
	}
	

	TNode* ToPos(size_t pos) {
		if (pos > sz) throw invalid_argument("pos is not correct");
		TNode* current = First;
		for (size_t i = 0; i < pos && current; i++) {
			current = current->Next;
		}
		return current;
		
	}
	void PushMidle(const T& val) {
		TNode* p = ToPos(sz/2);
		TNode* New = new TNode{ val, p->Next };
		p->Next = New;
		sz++;
		}
	void PopMiddle() {
		TNode* Del = ToPos(sz/2);
		TNode* prevNode = ToPos(sz/2 - 1); 
			prevNode->Next = Del->Next; 
			delete Del;  
			sz--;
	}
	void PushBack(const T& val) {
		if (First == nullptr) {
			PushFront(val); 
		}
		else {
			TNode* temp = First;
			while (temp->Next != nullptr) {
				temp = temp->Next;
			}
			TNode* New = new TNode{ val, nullptr };
			temp->Next = New;
			sz++;
		}
	}
	void PopBack() {
		if (First != nullptr) {
			if (First->Next == nullptr) {
				delete First;
				First = nullptr;
				sz = 0;
			}
			else {
				TNode* temp = First;
				while (temp->Next->Next != nullptr) {
					temp = temp->Next;
				}
				delete temp->Next;
				temp->Next = nullptr;
				sz--;
			}
		}
	}
friend	ostream& operator<<(ostream& os, const TList<T>& list) {
		TNode* current = list.First;
		while (current != nullptr) {
			os << current->val << " ";
			current = current->Next; 
		}
		return os;
	}
};
