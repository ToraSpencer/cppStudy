#pragma once

#include "basicTools/basicTools.h"

using std::cout;
using std::cin;
using std::endl;


//********************************ǰ������




//********************************������

struct DSA_linked_list_module : public virtualModule
{
protected:
	DSA_linked_list_module() = default;

public:
	static virtualModule* getInstance();
	virtual void test0();
	virtual void test1();
	virtual void test2();
	virtual void test3();
	virtual void test4();
	virtual void test5();
	virtual void test6();
};


// ����ڵ���
template <typename ElemType>
struct LinkedListNode
{
public:
	ElemType data;
	LinkedListNode<ElemType>* next;

	//���졢��������
	LinkedListNode();								// ����һ��������ָ����Ϊ�յĽڵ㡣
	LinkedListNode(ElemType, LinkedListNode<ElemType>*);			//ָ�����ݺ�ָ��Ľڵ㡣
	LinkedListNode(const LinkedListNode<ElemType>&);
	~LinkedListNode();
};


// ��������
template <class ElemType>
class LinkedList
{
protected:
	LinkedListNode<ElemType> *head;				// ͷ���ָ��
	int length;							// ��������

public:
	LinkedList();							 
	LinkedList(ElemType v[], int n);		 
	LinkedList(const LinkedList<ElemType> &la);            
	virtual ~LinkedList();				 
	int GetLength() const;				// ��������
	bool IsEmpty() const;	 			// �жϵ������Ƿ�Ϊ��
	void Clear();						// �����������
	void Traverse(void(*Visit)(const ElemType &)) const;// ����������
	int LocateElem(const ElemType &e) const;	         // Ԫ�ض�λ
	Status GetElem(int position, ElemType &e) const;	 // ��ָ��λ�õ�Ԫ��
	Status SetElem(int position, const ElemType &e);	 // ����ָ��λ�õ�Ԫ��ֵ
	Status DeleteElem(int position, ElemType &e);		 // ɾ��Ԫ��
	Status InsertElem(int position, const ElemType &e);	 // ��ָ��λ�ò���Ԫ��
	Status InsertElem(const ElemType &e);	             // �ڱ�β����Ԫ��

	LinkedList<ElemType> &operator =(const LinkedList<ElemType> &la); // ���ظ�ֵ����
	void Display();
};


// ��ʽջ��
template<class ElemType>
class LinkStack
{
protected:
	LinkedListNode<ElemType> *top;							// ջ��ָ��

public:
	LinkStack();									// �޲����Ĺ��캯��
	LinkStack(const LinkStack<ElemType> &s);
	virtual ~LinkStack();							// ��������
	int GetLength() const;							// ��ջ����			 
	bool IsEmpty() const;							// �ж�ջ�Ƿ�Ϊ��
	void Clear();									// ��ջ���
	void Traverse(void(*Visit)(const ElemType &)) const;	// ����ջ
	Status Push(const ElemType e);					// ��ջ
	Status Top(ElemType &e) const;					// ����ջ��Ԫ��
	Status Pop(ElemType &e);						// ��ջ
			 
	LinkStack<ElemType> &operator =(const LinkStack<ElemType> &s); // ��ֵ�������
};


// ���Ӷ�����
template<class ElemType>
class LinkQueue
{
protected: 
	LinkedListNode<ElemType> *front, *rear;					// ��ͷ��βָָ

public:
	LinkQueue();										// �޲����Ĺ��캯��
	virtual ~LinkQueue();							// ��������
	int GetLength() const;								// ����г���			 
	bool IsEmpty() const;								// �ж϶����Ƿ�Ϊ��
	void Clear();									// ���������
	void Traverse(void(*Visit)(const ElemType &)) const;	// ��������
	Status DelQueue(ElemType &e);				     // ���Ӳ���
	Status GetHead(ElemType &e) const;			     // ȡ��ͷ����
	Status EnQueue(const ElemType e);						// ��Ӳ���
	LinkQueue(const LinkQueue<ElemType> &q);		// ���ƹ��캯��
	LinkQueue<ElemType> &operator =(const LinkQueue<ElemType> &q);// ��ֵ�������
};


//********************************ʵ�ֲ���

template <typename ElemType>
LinkedListNode<ElemType>::LinkedListNode() :data(0), next(NULL) {}

template <typename ElemType>
LinkedListNode<ElemType>::LinkedListNode(ElemType da, LinkedListNode<ElemType>* ne) : data(da), next(ne) {}

template <typename ElemType>
LinkedListNode<ElemType>::LinkedListNode(const LinkedListNode& n)
{
	this->data = n.data;
	this->next = n.next;
}

template <typename ElemType>
LinkedListNode<ElemType>::~LinkedListNode() {}


template <class ElemType>
LinkedList<ElemType>::LinkedList()
{
	this->head = nullptr;
	this->length = 0;						// ��ʼ����������Ϊ0
}


// ʹ������v���쵥����
template <class ElemType>
LinkedList<ElemType>::LinkedList(ElemType v[], int n)
{
	LinkedListNode<ElemType> *p;
	p = head = new LinkedListNode<ElemType>(v[0], nullptr);	// ����ͷ���
	assert(head != nullptr);               
	for (int i = 0; i < n-1; i++) 
	{
		p->next = new LinkedListNode<ElemType>(v[i+1], nullptr);
		assert(p->next);            // ����Ԫ�ؽ��ʧ�ܣ���ֹ��������
		p = p->next;
	}
	length = n;						// ��ʼ����������Ϊn
}

template <class ElemType>
LinkedList<ElemType>::~LinkedList()
// ������������ٵ�����
{
	Clear();			// ��յ�����
	delete head;		// �ͷ�ͷ�����ָ�ռ�
}

template <class ElemType>
int LinkedList<ElemType>::GetLength() const
// ������������ص�����ĳ���
{
	return length;
}

template <class ElemType>
bool LinkedList<ElemType>::IsEmpty() const
// ����������絥����Ϊ�գ��򷵻�true�����򷵻�false
{
	return head->next == NULL;
}

template <class ElemType>
void LinkedList<ElemType>::Clear()
// �����������յ�����,ɾ��������������Ԫ�ؽ��
{
	LinkedListNode<ElemType> *p = head->next;
	while (p != NULL) {
		head->next = p->next;
		delete p;
		p = head->next;
	}
	length = 0;
}

template <class ElemType>
void LinkedList<ElemType>::Traverse(void(*Visit)(const ElemType &)) const
// ������������ζԵ������ÿ��Ԫ�ص��ú���(*visit)����
{
	LinkedListNode<ElemType> *p = head->next;
	while (p != NULL) {
		(*Visit)(p->data);	// �Ե�������ÿ��Ԫ�ص��ú���(*visit)����
		p = p->next;
	}
}

template <class ElemType>
int LinkedList<ElemType>::LocateElem(const ElemType &e) const
// Ԫ�ض�λ
{
	LinkedListNode<ElemType> *p = head->next;
	int count = 1;
	while (p != NULL && p->data != e) {
		count++;
		p = p->next;
	}
	return  (p != NULL) ? count : 0;
}

template <class ElemType>
Status LinkedList<ElemType>::GetElem(int i, ElemType &e) const
// �������������������ڵ�i��Ԫ��ʱ����e������ֵ����������ENTRY_FOUND,
//	����������NOT_PRESENT
{
	if (i < 1 || i > length)
		return RANGE_ERROR;
	else {
		LinkedListNode<ElemType> *p = head->next;
		int count;
		for (count = 1; count < i; count++)
			p = p->next;	            // pָ���i�����
		e = p->data;				// ��e���ص�i��Ԫ�ص�ֵ
		return ENTRY_FOUND;
	}
}

template <class ElemType>
Status LinkedList<ElemType>::SetElem(int i, const ElemType &e)
// �����������������ĵ�i��λ�õ�Ԫ�ظ�ֵΪe,
//	i��ȡֵ��ΧΪ1��i��length,
//	i�Ϸ�ʱ��������SUCCESS,����������RANGE_ERROR
{
	if (i < 1 || i > length)
		return RANGE_ERROR;
	else {
		LinkedListNode<ElemType> *p = head->next;
		int count;
		for (count = 1; count < i; count++)
			p = p->next;	           // ȡ��ָ���i������ָ��
		p->data = e;			   // �޸ĵ�i��Ԫ�ص�ֵΪe
		return SUCCESS;
	}
}

template <class ElemType>
Status LinkedList<ElemType>::DeleteElem(int i, ElemType &e)
// ���������ɾ��������ĵ�i��λ�õ�Ԫ��, ����e������ֵ,
//	i��ȡֵ��ΧΪ1��i��length,
//	i�Ϸ�ʱ��������SUCCESS,����������RANGE_ERROR
{
	if (i < 1 || i > length)
		return RANGE_ERROR;   // i��Χ��
	else {
		LinkedListNode<ElemType> *p = head, *q;
		int count;
		for (count = 1; count < i; count++)
			p = p->next;	      // pָ���i-1�����
		q = p->next;	      // qָ���i�����
		p->next = q->next;	  // ɾ�����
		e = q->data;		  // ��e���ر�ɾ���Ԫ��ֵ
		length--;			  // ɾ���ɹ���Ԫ�ظ�����1
		delete q;			  // �ͷű�ɾ���
		return SUCCESS;
	}
}

template <class ElemType>
Status LinkedList<ElemType>::InsertElem(int i, const ElemType &e)
// ����������ڵ�����ĵ�i��λ��ǰ����Ԫ��e
//	i��ȡֵ��ΧΪ1��i��length+1
//	i�Ϸ�ʱ����SUCCESS, ����������RANGE_ERROR
{
	if (i < 1 || i > length + 1)
		return RANGE_ERROR;
	else {
		LinkedListNode<ElemType> *p = head, *q;
		int count;
		for (count = 1; count < i; count++)
			p = p->next;	                    // pָ���i-1�����
		q = new LinkedListNode<ElemType>(e, p->next); // �����½��q
		assert(q);                          // ������ʧ�ܣ���ֹ��������
		p->next = q;				        // ��q���뵽������
		length++;							// ����ɹ��󣬵������ȼ�1
		return SUCCESS;
	}
}

template <class ElemType>
Status LinkedList<ElemType>::InsertElem(const ElemType &e)
// ����������ڵ�����ı�βλ�ò���Ԫ��e
{
	LinkedListNode<ElemType>* p = nullptr;
	LinkedListNode<ElemType>* q = nullptr;
	q = new LinkedListNode<ElemType>(e, nullptr);    // �����½��q
	assert(q);        
	if (this->head == nullptr)
	{
		this->head = q;
		length++;
		return SUCCESS;
	}

	p = this->head;
	while(p->next != nullptr)	// pָ���β���
	{
		p = p->next;
	}
	
	p->next = q;                        // �ڵ�����ı�βλ�ò����½��
	length++;							// ����ɹ��󣬵������ȼ�1
	return SUCCESS;
}

template <class ElemType>
LinkedList<ElemType>::LinkedList(const LinkedList<ElemType> &la)
// ������������ƹ��캯�����ɵ�����la�����µ�����
{
	int laLength = la.GetLength();	// ȡ�����Ƶ�����ĳ���
	ElemType e;
	head = new LinkedListNode<ElemType>;		// ����ͷָ��
	assert(head);                   // ����ͷָ��ʧ�ܣ���ֹ��������
	length = 0;						// ��ʼ��Ԫ�ظ���

	for (int i = 1; i <= laLength; i++) {	// ��������Ԫ��
		la.GetElem(i, e);	       // ȡ����i��Ԫ�ص�ֵ����e��
		InsertElem(e);		       // ��e���뵽��ǰ������ı�β
	}
}

template <class ElemType>
LinkedList<ElemType> &LinkedList<ElemType>::operator =(const LinkedList<ElemType> &la)
// ������������ظ�ֵ���������������la��ֵ����ǰ������
{
	if (&la != this) {
		int laLength = la.GetLength();// ȡ����ֵ������ĳ���
		ElemType e;
		Clear();							// ��յ�ǰ������
		for (int i = 1; i <= laLength; i++) {
			la.GetElem(i, e);		    // ȡ����i��Ԫ�ص�ֵ����e��
			InsertElem(e);		            // ��e���뵽��ǰ������ı�β
		}
	}
	return *this;
}


// ��ӡ����������Ԫ�أ�
template <class ElemType>
void LinkedList<ElemType>::Display()
{
	LinkedListNode<ElemType>* ptr = nullptr;
	ptr = this->head;
	while (ptr != nullptr) 
	{
		if (ptr->next != nullptr) 
		{
			std::cout << ptr->data << ", ";
		}
		else
		{
			std::cout << ptr->data << std::endl;
		}
		ptr = ptr->next;
	}
}


template<class ElemType>
LinkStack<ElemType>::LinkStack()
// �������������һ����ջ��
{
	top = NULL;
}

template<class ElemType>
LinkStack<ElemType>::~LinkStack()
// �������������ջ
{
	Clear();
}

template <class ElemType>
int LinkStack<ElemType>::GetLength() const
// �������������ջԪ�ظ���
{
	int count = 0;		// ������ 
	LinkedListNode<ElemType> *p;
	for (p = top; p != NULL; p = p->next)		// ��p������Ѱÿ��Ԫ��
		count++;		// ͳ����ջ�н����
	return count;
}

template<class ElemType>
bool LinkStack<ElemType>::IsEmpty() const
// �����������ջΪ�գ��򷵻�true�����򷵻�false
{
	return top == NULL;
}

template<class ElemType>
void LinkStack<ElemType>::Clear()
// ������������ջ
{
	LinkedListNode<ElemType> *p;
	while (top != NULL) {
		p = top;
		top = top->next;
		delete p;
	}
}

template <class ElemType>
void LinkStack<ElemType>::Traverse(void(*Visit)(const ElemType &)) const
// �����������ջ����ջ�����ζ�ջ��ÿ��Ԫ�ص��ú���(*visit)���� 
{
	LinkedListNode<ElemType> *p;
	for (p = top; p != NULL; p = p->next)	// ��p������Ѱ��ǰջ��ÿ��Ԫ��
		(*Visit)(p->data);		// ��p��ָ���Ԫ�ص��ú���(*visit)���� 
}

template<class ElemType>
Status LinkStack<ElemType>::Push(const ElemType e)
// �����������Ԫ��e׷�ӵ�ջ��,��ɹ��򷵼�SUCCESS,�����綯̬�ڴ��Ѻľ�
//	������OVER_FLOW
{
	LinkedListNode<ElemType> *p = new LinkedListNode<ElemType>(e, top);
	if (p == NULL) 	// ϵͳ�ڴ�ľ�
		return OVER_FLOW;
	else {	// �����ɹ�
		top = p;
		return SUCCESS;
	}
}

template<class ElemType>
Status LinkStack<ElemType>::Top(ElemType &e) const
// �����������ջ�ǿ�,��e����ջ��Ԫ��,��������SUCCESS,����������UNDER_FLOW
{
	if (IsEmpty())	// ջ��
		return UNDER_FLOW;
	else {	// ջ�ǿ�,�����ɹ�
		e = top->data;				// ��e����ջ��Ԫ��
		return SUCCESS;
	}
}

template<class ElemType>
Status LinkStack<ElemType>::Pop(ElemType &e)
// �����������ջ�ǿ�,ɾ��ջ��Ԫ��,����e����ջ��Ԫ��,��������SUCCESS,����
//	��������UNDER_FLOW
{
	if (IsEmpty())	// ջ��
		return UNDER_FLOW;
	else {	// �����ɹ�
		LinkedListNode<ElemType> *p = top;	// ����ԭջ��
		e = top->data;				// ��e����ջ��Ԫ��
		top = top->next;			// �޸�ջ��
		delete p;					// ɾ��ԭջ����� 
		return SUCCESS;
	}
}

template<class ElemType>
LinkStack<ElemType>::LinkStack(const LinkStack<ElemType> &s)
// �����������ջs������ջ--���ƹ��캯��
{
	if (s.IsEmpty())	// sΪ��
		top = NULL;									// ����һ��ջ
	else {	                                    // s�ǿ�,����ջ
		top = new LinkedListNode<ElemType>(s.top->data);	// ���ɵ�ǰջ��
		LinkedListNode<ElemType> *q = top;			        // ���õ�ǰջ��ָ��
		for (LinkedListNode<ElemType> *p = s.top->next; p != NULL; p = p->next) {
			q->next = new LinkedListNode<ElemType>(p->data); // ��ջ��׷��Ԫ��	
			q = q->next;					       // �޸�ջ��ָ�� 
		}
	}
}


template<class ElemType>
LinkStack<ElemType> &LinkStack<ElemType>::operator = (const LinkStack<ElemType> &s)
// �����������ջs��ֵ����ǰջ--��ֵ�������
{
	if (&s != this) {
		Clear();			// ��յ�ǰջ
		if (!s.IsEmpty()) {	                            // s�ǿ�,����ջ
			top = new LinkedListNode<ElemType>(s.top->data);       // ���ɵ�ǰջ��
			LinkedListNode<ElemType> *q = top;			            // ���õ�ǰջ��ָ��
			for (LinkedListNode<ElemType> *p = s.top->next; p != NULL; p = p->next) {
				q->next = new LinkedListNode<ElemType>(p->data);      // ��ջ��׷��Ԫ��	
				q = q->next;			                    // �޸�ջ��ָ��
			}
		}
	}
	return *this;
}


template<class ElemType>
LinkQueue<ElemType>::LinkQueue()					// ����һ���ն���
{
	front = new LinkedListNode<ElemType>;		// ����������ͷ���
	rear = front;
}

template<class ElemType>
LinkQueue<ElemType>::~LinkQueue()
// ������������ٶ���
{
	Clear();
	delete front;
}

template<class ElemType>
int LinkQueue<ElemType>::GetLength() const
// ������������ض��г���			 
{
	int count = 0;		// ��ʼ�������� 
	for (LinkedListNode<ElemType> *p = front->next; p != NULL; p = p->next)
		count++;		// ͳ���������еĽ���� 
	return count;
}

template<class ElemType>
bool LinkQueue<ElemType>::IsEmpty() const
// ��������������Ϊ�գ��򷵻�true�����򷵻�false
{
	return rear == front;
}

template<class ElemType>
void LinkQueue<ElemType>::Clear()
// �����������ն���
{
	LinkedListNode<ElemType> *p = front->next;
	while (p != NULL) {	// ����ɾ�������е�Ԫ�ؽ��
		front->next = p->next;
		delete p;
		p = front->next;
	}
	rear = front;
}

template <class ElemType>
void LinkQueue<ElemType>::Traverse(void(*Visit)(const ElemType &)) const
// ������������ζԶ��е�ÿ��Ԫ�ص��ú���(*visit)
{
	for (LinkedListNode<ElemType> *p = front->next; p != NULL; p = p->next)
		// �Զ���ÿ��Ԫ�ص��ú���(*visit)���� 
		(*Visit)(p->data);
}


template<class ElemType>
Status LinkQueue<ElemType>::DelQueue(ElemType &e)
// ���������������зǿգ���ôɾ����ͷԪ�أ�����e������ֵ����������SUCCESS,
//	����������UNDER_FLOW��
{
	if (!IsEmpty()) {	// ���зǿ�
		LinkedListNode<ElemType> *p = front->next;	// ָ�����ͷ��
		e = p->data;						// ��e���ض�ͷԪ��
		front->next = p->next;				// frontָ����һԪ��
		if (rear == p)	// ����ǰ������ֻ��һ��Ԫ�أ����Ӻ�Ϊ�ն���
			rear = front;
		delete p;							// �ͷų��ӵ�Ԫ�ؽ��
		return SUCCESS;
	}
	else
		return UNDER_FLOW;
}

template<class ElemType>
Status LinkQueue<ElemType>::GetHead(ElemType &e) const
// ���������������зǿգ���ô��e���ض�ͷԪ�أ���������SUCCESS,
//	����������UNDER_FLOW��
{
	if (!IsEmpty()) {	            // ���зǿ�
		e = front->next->data;		// ��e���ض�ͷԪ��
		return SUCCESS;
	}
	else
		return UNDER_FLOW;
}

template<class ElemType>
Status LinkQueue<ElemType>::EnQueue(const ElemType e)
// ������������ϵͳ�ռ䲻��������OVER_FLOW,
//	�������Ԫ��eΪ�µĶ�β������SUCCESS
{
	LinkedListNode<ElemType> *p;
	p = new LinkedListNode<ElemType>(e);	        // ����һ���½��
	if (p) {
		rear->next = p;	                // ���½����ڶ�β
		rear = rear->next;				// rearָ���¶�β
		return SUCCESS;
	}
	else                               //ϵͳ�ռ䲻��������OVER_FLOW 
		return OVER_FLOW;
}

template<class ElemType>
LinkQueue<ElemType>::LinkQueue(const LinkQueue<ElemType> &q)
// ����������ɶ���q�����¶���--���ƹ��캯��
{
	rear = front = new LinkedListNode<ElemType>;	// ���ɶ���ͷ���
	for (LinkedListNode<ElemType> *p = q.front->next; p != NULL; p = p->next)
		// ȡq����ÿ��Ԫ�ص�ֵ,�����ڵ�ǰ������������в���
		EnQueue(p->data);
}

template<class ElemType>
LinkQueue<ElemType> &LinkQueue<ElemType>::operator =(const LinkQueue<ElemType> &q)
// ���������������q��ֵ����ǰ����--��ֵ�������
{
	if (&q != this) {
		Clear();       //���ԭ�ж��� 
		for (LinkedListNode<ElemType> *p = q.front->next; p != NULL; p = p->next)
			// ȡq����ÿ��Ԫ�ص�ֵ,�����ڵ�ǰ������������в���
			EnQueue(p->data);
	}
	return *this;
}

