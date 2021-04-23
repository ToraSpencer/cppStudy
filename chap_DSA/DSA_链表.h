#pragma once

#include "basicTools/basicTools.h"
#pragma comment(lib, "./Release/basicTools.lib")
using std::cout;
using std::cin;
using std::endl;


//********************************前置声明




//********************************类声明

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


// 链表节点类
template <typename ElemType>
struct LinkedListNode
{
public:
	ElemType data;
	LinkedListNode<ElemType>* next;

	//构造、析构函数
	LinkedListNode();								// 构造一个数据域、指针域都为空的节点。
	LinkedListNode(ElemType, LinkedListNode<ElemType>*);			//指定数据和指针的节点。
	LinkedListNode(const LinkedListNode<ElemType>&);
	~LinkedListNode();
};


// 单链表类
template <class ElemType>
class LinkedList
{
protected:
	LinkedListNode<ElemType> *head;				// 头结点指针
	int length;							// 单链表长度

public:
	LinkedList();							 
	LinkedList(ElemType v[], int n);		 
	LinkedList(const LinkedList<ElemType> &la);            
	virtual ~LinkedList();				 
	int GetLength() const;				// 求单链表长度
	bool IsEmpty() const;	 			// 判断单链表是否为空
	void Clear();						// 将单链表清空
	void Traverse(void(*Visit)(const ElemType &)) const;// 遍历单链表
	int LocateElem(const ElemType &e) const;	         // 元素定位
	Status GetElem(int position, ElemType &e) const;	 // 求指定位置的元素
	Status SetElem(int position, const ElemType &e);	 // 设置指定位置的元素值
	Status DeleteElem(int position, ElemType &e);		 // 删除元素
	Status InsertElem(int position, const ElemType &e);	 // 在指定位置插入元素
	Status InsertElem(const ElemType &e);	             // 在表尾插入元素

	LinkedList<ElemType> &operator =(const LinkedList<ElemType> &la); // 重载赋值运算
	void Display();
};


// 链式栈类
template<class ElemType>
class LinkStack
{
protected:
	LinkedListNode<ElemType> *top;							// 栈顶指针

public:
	LinkStack();									// 无参数的构造函数
	LinkStack(const LinkStack<ElemType> &s);
	virtual ~LinkStack();							// 析构函数
	int GetLength() const;							// 求栈长度			 
	bool IsEmpty() const;							// 判断栈是否为空
	void Clear();									// 将栈清空
	void Traverse(void(*Visit)(const ElemType &)) const;	// 遍历栈
	Status Push(const ElemType e);					// 入栈
	Status Top(ElemType &e) const;					// 返回栈顶元素
	Status Pop(ElemType &e);						// 出栈
			 
	LinkStack<ElemType> &operator =(const LinkStack<ElemType> &s); // 赋值语句重载
};


// 链队队列类
template<class ElemType>
class LinkQueue
{
protected:
	//  链队列实现的数据成员:
	LinkedListNode<ElemType> *front, *rear;					// 队头队尾指指

public:
	LinkQueue();									// 无参数的构造函数
	virtual ~LinkQueue();							// 析构函数
	int GetLength() const;								// 求队列长度			 
	bool IsEmpty() const;								// 判断队列是否为空
	void Clear();									// 将队列清空
	void Traverse(void(*Visit)(const ElemType &)) const;	// 遍历队列
	Status DelQueue(ElemType &e);				     // 出队操作
	Status GetHead(ElemType &e) const;			     // 取队头操作
	Status EnQueue(const ElemType e);			     // 入队操作
	LinkQueue(const LinkQueue<ElemType> &q);		// 复制构造函数
	LinkQueue<ElemType> &operator =(const LinkQueue<ElemType> &q);// 赋值语句重载
};


//********************************实现部分

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
	this->length = 0;						// 初始化单链表长度为0
}


// 使用数组v构造单链表
template <class ElemType>
LinkedList<ElemType>::LinkedList(ElemType v[], int n)
{
	LinkedListNode<ElemType> *p;
	p = head = new LinkedListNode<ElemType>(v[0], nullptr);	// 构造头结点
	assert(head != nullptr);               
	for (int i = 0; i < n-1; i++) 
	{
		p->next = new LinkedListNode<ElemType>(v[i+1], nullptr);
		assert(p->next);            // 构造元素结点失败，终止程序运行
		p = p->next;
	}
	length = n;						// 初始化单链表长度为n
}

template <class ElemType>
LinkedList<ElemType>::~LinkedList()
// 操作结果：销毁单链表
{
	Clear();			// 清空单链表
	delete head;		// 释放头结点所指空间
}

template <class ElemType>
int LinkedList<ElemType>::GetLength() const
// 操作结果：返回单链表的长度
{
	return length;
}

template <class ElemType>
bool LinkedList<ElemType>::IsEmpty() const
// 操作结果：如单链表为空，则返回true，否则返回false
{
	return head->next == NULL;
}

template <class ElemType>
void LinkedList<ElemType>::Clear()
// 操作结果：清空单链表,删除单链表中所有元素结点
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
// 操作结果：依次对单链表的每个元素调用函数(*visit)访问
{
	LinkedListNode<ElemType> *p = head->next;
	while (p != NULL) {
		(*Visit)(p->data);	// 对单链表中每个元素调用函数(*visit)访问
		p = p->next;
	}
}

template <class ElemType>
int LinkedList<ElemType>::LocateElem(const ElemType &e) const
// 元素定位
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
// 操作结果：当单链表存在第i个元素时，用e返回其值，函数返回ENTRY_FOUND,
//	否则函数返回NOT_PRESENT
{
	if (i < 1 || i > length)
		return RANGE_ERROR;
	else {
		LinkedListNode<ElemType> *p = head->next;
		int count;
		for (count = 1; count < i; count++)
			p = p->next;	            // p指向第i个结点
		e = p->data;				// 用e返回第i个元素的值
		return ENTRY_FOUND;
	}
}

template <class ElemType>
Status LinkedList<ElemType>::SetElem(int i, const ElemType &e)
// 操作结果：将单链表的第i个位置的元素赋值为e,
//	i的取值范围为1≤i≤length,
//	i合法时函数返回SUCCESS,否则函数返回RANGE_ERROR
{
	if (i < 1 || i > length)
		return RANGE_ERROR;
	else {
		LinkedListNode<ElemType> *p = head->next;
		int count;
		for (count = 1; count < i; count++)
			p = p->next;	           // 取出指向第i个结点的指针
		p->data = e;			   // 修改第i个元素的值为e
		return SUCCESS;
	}
}

template <class ElemType>
Status LinkedList<ElemType>::DeleteElem(int i, ElemType &e)
// 操作结果：删除单链表的第i个位置的元素, 并用e返回其值,
//	i的取值范围为1≤i≤length,
//	i合法时函数返回SUCCESS,否则函数返回RANGE_ERROR
{
	if (i < 1 || i > length)
		return RANGE_ERROR;   // i范围错
	else {
		LinkedListNode<ElemType> *p = head, *q;
		int count;
		for (count = 1; count < i; count++)
			p = p->next;	      // p指向第i-1个结点
		q = p->next;	      // q指向第i个结点
		p->next = q->next;	  // 删除结点
		e = q->data;		  // 用e返回被删结点元素值
		length--;			  // 删除成功后元素个数减1
		delete q;			  // 释放被删结点
		return SUCCESS;
	}
}

template <class ElemType>
Status LinkedList<ElemType>::InsertElem(int i, const ElemType &e)
// 操作结果：在单链表的第i个位置前插入元素e
//	i的取值范围为1≤i≤length+1
//	i合法时返回SUCCESS, 否则函数返回RANGE_ERROR
{
	if (i < 1 || i > length + 1)
		return RANGE_ERROR;
	else {
		LinkedListNode<ElemType> *p = head, *q;
		int count;
		for (count = 1; count < i; count++)
			p = p->next;	                    // p指向第i-1个结点
		q = new LinkedListNode<ElemType>(e, p->next); // 生成新结点q
		assert(q);                          // 申请结点失败，终止程序运行
		p->next = q;				        // 将q插入到链表中
		length++;							// 插入成功后，单链表长度加1
		return SUCCESS;
	}
}

template <class ElemType>
Status LinkedList<ElemType>::InsertElem(const ElemType &e)
// 操作结果：在单链表的表尾位置插入元素e
{
	LinkedListNode<ElemType>* p = nullptr;
	LinkedListNode<ElemType>* q = nullptr;
	q = new LinkedListNode<ElemType>(e, nullptr);    // 生成新结点q
	assert(q);        
	if (this->head == nullptr)
	{
		this->head = q;
		length++;
		return SUCCESS;
	}

	p = this->head;
	while(p->next != nullptr)	// p指向表尾结点
	{
		p = p->next;
	}
	
	p->next = q;                        // 在单链表的表尾位置插入新结点
	length++;							// 插入成功后，单链表长度加1
	return SUCCESS;
}

template <class ElemType>
LinkedList<ElemType>::LinkedList(const LinkedList<ElemType> &la)
// 操作结果：复制构造函数，由单链表la构造新单链表
{
	int laLength = la.GetLength();	// 取被复制单链表的长度
	ElemType e;
	head = new LinkedListNode<ElemType>;		// 构造头指针
	assert(head);                   // 构造头指针失败，终止程序运行
	length = 0;						// 初始化元素个数

	for (int i = 1; i <= laLength; i++) {	// 复制数据元素
		la.GetElem(i, e);	       // 取出第i个元素的值放在e中
		InsertElem(e);		       // 将e插入到当前单链表的表尾
	}
}

template <class ElemType>
LinkedList<ElemType> &LinkedList<ElemType>::operator =(const LinkedList<ElemType> &la)
// 操作结果：重载赋值运算符，将单链表la赋值给当前单链表
{
	if (&la != this) {
		int laLength = la.GetLength();// 取被赋值单链表的长度
		ElemType e;
		Clear();							// 清空当前单链表
		for (int i = 1; i <= laLength; i++) {
			la.GetElem(i, e);		    // 取出第i个元素的值放在e中
			InsertElem(e);		            // 将e插入到当前单链表的表尾
		}
	}
	return *this;
}


// 打印单链表所有元素：
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
// 操作结果：构造一个空栈表
{
	top = NULL;
}

template<class ElemType>
LinkStack<ElemType>::~LinkStack()
// 操作结果：销毁栈
{
	Clear();
}

template <class ElemType>
int LinkStack<ElemType>::GetLength() const
// 操作结果：返回栈元素个数
{
	int count = 0;		// 计数器 
	LinkedListNode<ElemType> *p;
	for (p = top; p != NULL; p = p->next)		// 用p依次搜寻每个元素
		count++;		// 统计链栈中结点数
	return count;
}

template<class ElemType>
bool LinkStack<ElemType>::IsEmpty() const
// 操作结果：如栈为空，则返回true，否则返回false
{
	return top == NULL;
}

template<class ElemType>
void LinkStack<ElemType>::Clear()
// 操作结果：清空栈
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
// 操作结果：从栈顶到栈底依次对栈的每个元素调用函数(*visit)访问 
{
	LinkedListNode<ElemType> *p;
	for (p = top; p != NULL; p = p->next)	// 用p依次搜寻当前栈的每个元素
		(*Visit)(p->data);		// 对p所指向的元素调用函数(*visit)访问 
}

template<class ElemType>
Status LinkStack<ElemType>::Push(const ElemType e)
// 操作结果：将元素e追加到栈顶,如成功则返加SUCCESS,否则如动态内存已耗尽
//	将返回OVER_FLOW
{
	LinkedListNode<ElemType> *p = new LinkedListNode<ElemType>(e, top);
	if (p == NULL) 	// 系统内存耗尽
		return OVER_FLOW;
	else {	// 操作成功
		top = p;
		return SUCCESS;
	}
}

template<class ElemType>
Status LinkStack<ElemType>::Top(ElemType &e) const
// 操作结果：如栈非空,用e返回栈顶元素,函数返回SUCCESS,否则函数返回UNDER_FLOW
{
	if (IsEmpty())	// 栈空
		return UNDER_FLOW;
	else {	// 栈非空,操作成功
		e = top->data;				// 用e返回栈顶元素
		return SUCCESS;
	}
}

template<class ElemType>
Status LinkStack<ElemType>::Pop(ElemType &e)
// 操作结果：如栈非空,删除栈顶元素,并用e返回栈顶元素,函数返回SUCCESS,否则
//	函数返回UNDER_FLOW
{
	if (IsEmpty())	// 栈空
		return UNDER_FLOW;
	else {	// 操作成功
		LinkedListNode<ElemType> *p = top;	// 保留原栈顶
		e = top->data;				// 用e返回栈顶元素
		top = top->next;			// 修改栈顶
		delete p;					// 删除原栈顶结点 
		return SUCCESS;
	}
}

template<class ElemType>
LinkStack<ElemType>::LinkStack(const LinkStack<ElemType> &s)
// 操作结果：由栈s构造新栈--复制构造函数
{
	if (s.IsEmpty())	// s为空
		top = NULL;									// 构造一空栈
	else {	                                    // s非空,复制栈
		top = new LinkedListNode<ElemType>(s.top->data);	// 生成当前栈项
		LinkedListNode<ElemType> *q = top;			        // 设置当前栈底指针
		for (LinkedListNode<ElemType> *p = s.top->next; p != NULL; p = p->next) {
			q->next = new LinkedListNode<ElemType>(p->data); // 向栈底追加元素	
			q = q->next;					       // 修改栈底指针 
		}
	}
}


template<class ElemType>
LinkStack<ElemType> &LinkStack<ElemType>::operator = (const LinkStack<ElemType> &s)
// 操作结果：将栈s赋值给当前栈--赋值语句重载
{
	if (&s != this) {
		Clear();			// 清空当前栈
		if (!s.IsEmpty()) {	                            // s非空,复制栈
			top = new LinkedListNode<ElemType>(s.top->data);       // 生成当前栈项
			LinkedListNode<ElemType> *q = top;			            // 设置当前栈底指针
			for (LinkedListNode<ElemType> *p = s.top->next; p != NULL; p = p->next) {
				q->next = new LinkedListNode<ElemType>(p->data);      // 向栈底追加元素	
				q = q->next;			                    // 修改栈底指针
			}
		}
	}
	return *this;
}


template<class ElemType>
LinkQueue<ElemType>::LinkQueue()
// 操作结果：构造一个空队列
{
	rear = front = new LinkedListNode<ElemType>;	// 生成链队列头结点
}

template<class ElemType>
LinkQueue<ElemType>::~LinkQueue()
// 操作结果：销毁队列
{
	Clear();
	delete front;
}

template<class ElemType>
int LinkQueue<ElemType>::GetLength() const
// 操作结果：返回队列长度			 
{
	int count = 0;		// 初始化计数器 
	for (LinkedListNode<ElemType> *p = front->next; p != NULL; p = p->next)
		count++;		// 统计链队列中的结点数 
	return count;
}

template<class ElemType>
bool LinkQueue<ElemType>::IsEmpty() const
// 操作结果：如队列为空，则返回true，否则返回false
{
	return rear == front;
}

template<class ElemType>
void LinkQueue<ElemType>::Clear()
// 操作结果：清空队列
{
	LinkedListNode<ElemType> *p = front->next;
	while (p != NULL) {	// 依次删除队列中的元素结点
		front->next = p->next;
		delete p;
		p = front->next;
	}
	rear = front;
}

template <class ElemType>
void LinkQueue<ElemType>::Traverse(void(*Visit)(const ElemType &)) const
// 操作结果：依次对队列的每个元素调用函数(*visit)
{
	for (LinkedListNode<ElemType> *p = front->next; p != NULL; p = p->next)
		// 对队列每个元素调用函数(*visit)访问 
		(*Visit)(p->data);
}


template<class ElemType>
Status LinkQueue<ElemType>::DelQueue(ElemType &e)
// 操作结果：如果队列非空，那么删除队头元素，并用e返回其值，函数返回SUCCESS,
//	否则函数返回UNDER_FLOW，
{
	if (!IsEmpty()) {	// 队列非空
		LinkedListNode<ElemType> *p = front->next;	// 指向队列头素
		e = p->data;						// 用e返回队头元素
		front->next = p->next;				// front指向下一元素
		if (rear == p)	// 出队前队列中只有一个元素，出队后为空队列
			rear = front;
		delete p;							// 释放出队的元素结点
		return SUCCESS;
	}
	else
		return UNDER_FLOW;
}

template<class ElemType>
Status LinkQueue<ElemType>::GetHead(ElemType &e) const
// 操作结果：如果队列非空，那么用e返回队头元素，函数返回SUCCESS,
//	否则函数返回UNDER_FLOW，
{
	if (!IsEmpty()) {	            // 队列非空
		e = front->next->data;		// 用e返回队头元素
		return SUCCESS;
	}
	else
		return UNDER_FLOW;
}

template<class ElemType>
Status LinkQueue<ElemType>::EnQueue(const ElemType e)
// 操作结果：如果系统空间不够，返回OVER_FLOW,
//	否则插入元素e为新的队尾，返回SUCCESS
{
	LinkedListNode<ElemType> *p;
	p = new LinkedListNode<ElemType>(e);	        // 生成一个新结点
	if (p) {
		rear->next = p;	                // 将新结点加在队尾
		rear = rear->next;				// rear指向新队尾
		return SUCCESS;
	}
	else                               //系统空间不够，返回OVER_FLOW 
		return OVER_FLOW;
}

template<class ElemType>
LinkQueue<ElemType>::LinkQueue(const LinkQueue<ElemType> &q)
// 操作结果：由队列q构造新队列--复制构造函数
{
	rear = front = new LinkedListNode<ElemType>;	// 生成队列头结点
	for (LinkedListNode<ElemType> *p = q.front->next; p != NULL; p = p->next)
		// 取q队列每个元素的值,将其在当前队列中作入队列操作
		EnQueue(p->data);
}

template<class ElemType>
LinkQueue<ElemType> &LinkQueue<ElemType>::operator =(const LinkQueue<ElemType> &q)
// 操作结果：将队列q赋值给当前队列--赋值语句重载
{
	if (&q != this) {
		Clear();       //清除原有队列 
		for (LinkedListNode<ElemType> *p = q.front->next; p != NULL; p = p->next)
			// 取q队列每个元素的值,将其在当前队列中作入队列操作
			EnQueue(p->data);
	}
	return *this;
}

