#include "MSList.h"
#include "Star.hpp" 

template <typename T>
MSList<T>::MSList() : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
MSList<T>::~MSList() {
    Node<T>* current = head;
    while (current != nullptr) {
        Node<T>* next = current->next;
        delete current;  // 메모리 해제
        current = next;
    }
}

template <typename T>
void MSList<T>::push_back(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (tail == nullptr) {  // 리스트가 비어있을 경우
        head = tail = newNode;
    }
    else {  // 리스트가 비어있지 않을 경우
        tail->next = newNode;
        tail = newNode;
    }
    size++;  // 리스트 크기 증가
}

template <typename T>
Node<T>* MSList<T>::begin() {
    return head;  // 리스트의 시작 노드 반환
}

template <typename T>
Node<T>* MSList<T>::end() {
    return nullptr;  // 리스트의 끝을 나타내는 nullptr 반환
}

template <typename T>
int MSList<T>::getSize() const {
    return size;  // 리스트의 크기 반환
}

// 명시적 템플릿 인스턴스화
template class MSList<Star>;