#include "MSList.h"
#include "Star.hpp" 

template <typename T>
MSList<T>::MSList() : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
MSList<T>::~MSList() {
    Node<T>* current = head;
    while (current != nullptr) {
        Node<T>* next = current->next;
        delete current;  // �޸� ����
        current = next;
    }
}

template <typename T>
void MSList<T>::push_back(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (tail == nullptr) {  // ����Ʈ�� ������� ���
        head = tail = newNode;
    }
    else {  // ����Ʈ�� ������� ���� ���
        tail->next = newNode;
        tail = newNode;
    }
    size++;  // ����Ʈ ũ�� ����
}

template <typename T>
Node<T>* MSList<T>::begin() {
    return head;  // ����Ʈ�� ���� ��� ��ȯ
}

template <typename T>
Node<T>* MSList<T>::end() {
    return nullptr;  // ����Ʈ�� ���� ��Ÿ���� nullptr ��ȯ
}

template <typename T>
int MSList<T>::getSize() const {
    return size;  // ����Ʈ�� ũ�� ��ȯ
}

// ����� ���ø� �ν��Ͻ�ȭ
template class MSList<Star>;