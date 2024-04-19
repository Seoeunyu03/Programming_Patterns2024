#pragma once

template <typename T>
struct Node {
    T data;  // 노드가 보관할 데이터
    Node* next;  // 다음 노드를 가리키는 포인터
    Node(T val) : data(val), next(nullptr) {}  // 생성자
};

template <typename T>
class MSList {
private:
    Node<T>* head;  // 리스트의 첫 번째 노드
    Node<T>* tail;  // 리스트의 마지막 노드
    int size;  // 리스트의 크기

public:
    MSList();  // 생성자
    ~MSList();  // 소멸자
    void push_back(const T& value);  // 리스트의 끝에 요소 추가
    Node<T>* begin();  // 리스트의 시작을 가리키는 포인터 반환
    Node<T>* end();  // 리스트의 끝을 가리키는 포인터 반환(사실상 nullptr)
    int getSize() const;  // 리스트의 크기 반환
};