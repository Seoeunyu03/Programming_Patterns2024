#pragma once

template <typename T>
struct Node {
    T data;  // ��尡 ������ ������
    Node* next;  // ���� ��带 ����Ű�� ������
    Node(T val) : data(val), next(nullptr) {}  // ������
};

template <typename T>
class MSList {
private:
    Node<T>* head;  // ����Ʈ�� ù ��° ���
    Node<T>* tail;  // ����Ʈ�� ������ ���
    int size;  // ����Ʈ�� ũ��

public:
    MSList();  // ������
    ~MSList();  // �Ҹ���
    void push_back(const T& value);  // ����Ʈ�� ���� ��� �߰�
    Node<T>* begin();  // ����Ʈ�� ������ ����Ű�� ������ ��ȯ
    Node<T>* end();  // ����Ʈ�� ���� ����Ű�� ������ ��ȯ(��ǻ� nullptr)
    int getSize() const;  // ����Ʈ�� ũ�� ��ȯ
};