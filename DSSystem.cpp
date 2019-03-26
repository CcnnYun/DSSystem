#include <stdio.h>
#include <iostream>
using namespace std;

// OOP实现一个循环队列结构
class CCircleQueue
{
public:
	CCircleQueue(int size = 10) // 构造函数
	{
		msize = size;
		mpQue = new int[msize];
		mfront = 0;
		mrear = 0;
	}
	~CCircleQueue() // 析构函数
	{
		delete[] mpQue;
		mpQue = nullptr;
	}
	CCircleQueue(const CCircleQueue &src) // 拷贝构造函数
	{
		mpQue = new int[src.msize];
		for (int i = mfront; i != src.mrear; i = (i + 1) % src.msize)
		{
			mpQue[i] = src.mpQue[i];
		}
		mfront = src.mfront;
		mrear = src.mrear;
		msize = src.msize;
	}
	void operator=(const CCircleQueue &src)// 赋值重载函数
	{
		if (this == &src)
		{
			return;
		}
		delete[]mpQue;
		mpQue = new int[src.msize];
		for (int i = mfront; i != src.mrear; i = (i + 1) % src.msize)
		{
			mpQue[i] = src.mpQue[i];
		}
		mfront = src.mfront;
		mrear = src.mrear;
		msize = src.msize;
	}

	void addQue(int val) // 入队
	{
		if (full())
		{
			resize();
		}
		mpQue[mrear] = val;
		mrear = (mrear + 1) % msize;//（0，msize - 1）
	}
	void delQue()// 出队
	{
		if (empty())
		{
			return;
		}
		mfront = (mfront + 1) % msize;
	}
	int front()// 返回队头元素
	{
		return mpQue[mfront];
	}
	int back()// 返回队尾元素
	{
		return mpQue[(mrear - 1 + msize) % msize];
	}

	bool full() // 判满
	{
		if (((mrear + 1) % msize) == mfront)
		{
			return true;
		}
		return false;
	}
	bool empty() // 判空
	{
		if (mfront == mrear)
		{
			return true;
		}
		return false;
	}
	void show()
	{
		for (int i = mfront; i != mrear; i = (i + 1) % msize)
		{
			cout << mpQue[i] << " ";
		}
		cout << endl;
	}
	void research(int val)
	{
		for (int i = mfront; i != mrear; i = (i + 1) % msize)
		{
			if (mpQue[i] == val)
			{
				cout << val << "存在于队列" << endl;
				return;
			}
		}
		cout << val << "不存在于队列" << endl;
	}
private:
	int *mpQue; //保存队列元素的数据结构
	int mfront; //队头下标
	int mrear; //队尾下标
	int msize; //扩容的总长度

	void resize() // 2倍扩容循环队列
	{
		int *newQue = new int[msize * 2];
		int count = 0;
		for (int i = mfront; i != mrear; i = (i + 1) % msize)
		{
			newQue[count++] = mpQue[i];
		}
		delete[] mpQue;
		msize = msize * 2;
		mfront = 0;
		mrear = count;
		mpQue = newQue;
	}
};

// OOP实现一个链表结构
class Link
{
public:
	Link() // 构造函数
	{
		mphead = new Node();
	}
	~Link() // 析构函数
	{
		Node *tmp = mphead;
		while (tmp->mpnext != nullptr)
		{
			mphead = mphead->mpnext;
			delete tmp;
			tmp = mphead;
		}
	}
	void insertHead(int val)
	{
		Node *tem = new Node(val);
		tem->mpnext = mphead->mpnext;
		mphead->mpnext = tem;
	}
	void insertTail(int val)
	{
		Node *p = mphead->mpnext;
		while (p->mpnext != nullptr)
		{
			p = p->mpnext;
		}
		p->mpnext = new Node(val);
	}
	void remove(int val) // 删除所有值为val的节点
	{
		Node *p = mphead->mpnext;
		Node *tem = mphead;
		while (p != nullptr)
		{
			if (p->mdata == val)
			{
				tem->mpnext = p->mpnext;
				delete p;
				p = tem->mpnext;
			}
			tem = p;
			p = p->mpnext;
		}
	}
	bool empty()
	{
		return mphead->mpnext;
	}
	int firstItem()
	{
		if (empty())
			throw "链表出错";
		return mphead->mpnext->mdata;
	}
	void outItem()
	{
		if (empty())
		{
			return;
		}
		Node *p = mphead->mpnext;
		if (p != nullptr)
		{
			mphead->mpnext = p->mpnext;
			delete p;
		}
	}
	void show()
	{
		Node *p = mphead->mpnext;
		while (p != nullptr)
		{
			cout << p->mdata << " ";
			p = p->mpnext;
		}
		cout << endl;
	}
	void research(int val)
	{
		Node *p = mphead->mpnext;
		while (p != nullptr)
		{
			if (p->mdata == val)
			{
				cout << val << "存在于链表中" << endl;
				break;
			}
		}
		cout << val << "不存在于链表中" << endl;
	}
	
private:
	// 节点类型
	struct Node
	{
		Node(int data = 0)
		{
			mdata = data;
			mpnext = nullptr;
		}
		int mdata;
		Node *mpnext;
	};

	// private化拷贝构造和赋值重载函数
	Link(const Link&);
	void operator=(const Link&);

	Node *mphead;
};

//栈
class CStack
{
public:
	// CStack() CStack(int)
	CStack(int size = 3) // 构造函数，给对象成员变量进行初始化
	{
		//cout << this << " CStack(int)" << endl;
		mtop = 0;
		msize = size;
		mpstack = new int[msize];
	}
	// 拷贝构造对象 默认做的是浅拷贝
	CStack(const CStack &src)
	{
		//cout << this << "CStack(const CStack&)" << endl;
		mpstack = new int[src.msize];
		for (int i = 0; i < src.msize; ++i)
		{
			mpstack[i] = src.mpstack[i];
		}
		mtop = src.mtop;
		msize = src.msize;
	}
	// 赋值重载函数  stack1 = stack1
	void operator=(const CStack &src)
	{
		//cout << "operator=" << endl;

		// 防止自赋值
		if (this == &src)
			return;

		// 先释放this指向对象现有的外部资源
		delete[]mpstack;

		// 根据src引用的对象资源尺寸，重新开辟空间，拷贝数据
		mpstack = new int[src.msize];
		for (int i = 0; i < src.msize; ++i)
		{
			mpstack[i] = src.mpstack[i];
		}
		mtop = src.mtop;
		msize = src.msize;
	}
	~CStack() // 析构函数，释放对象
	{
		cout << this << " ~CStack()" << endl;
		delete[]mpstack;
		mpstack = nullptr;
	}
	void push(int val) // 入栈
	{
		if (full())
			resize();
		mpstack[mtop++] = val;
	}
	void pop() // 出栈
	{
		if (empty())
			return;
		--mtop;
	}
	int top()
	{
		if (empty())
			throw "stack is empty!";
		return mpstack[mtop - 1];
	}
	bool full() { return mtop == msize; }
	bool empty() { return mtop == 0; }
	void show()
	{
		for (int i = 0; i < mtop; i++)
		{
			cout << mpstack[i] << " ";
		}
		cout << endl;
	}
	void research(int val)
	{
		for (int i = 0; i < mtop; i++)
		{
			if (mpstack[i] == val)
			{
				cout << val << "存在于栈中" << endl;
				break;
			}
		}
		cout << val << "不存在于栈中" << endl;
	}
private:
	int *mpstack; // 存储栈的数据
	int mtop; // 表示栈顶下标
	int msize; // 表示栈的总长度

	void resize()
	{
		int *ptmp = new int[msize * 2];
		//memcpy(ptmp, mpstack, sizeof(int)*msize);
		//realloc  对象扩容禁止使用realloc/memcpy这些函数!!!
		for (int i = 0; i < msize; ++i)
		{
			ptmp[i] = mpstack[i];
		}
		delete[]mpstack;
		mpstack = ptmp;
		msize *= 2;
	}
};

/*
软件运行如下：
加载数据当中...加载完成！
-------------
1.单链表
2.栈
3.队列
4.退出系统 => 保存内存数据
-------------
请选择：1

-------------
当前数据结构是：xxx
1.查看
2.增加
3.删除
4.查询
5.返回上一级菜单
-------------
请选择：
*/

// 数据结构系统类
class DSSystem
{
public:
	void run() // 系统的启动函数
	{
		// 1.加载文件中的数据
		loadData();
		// 2.显示主菜单
		cout << "-------------" << endl;
		cout << "1.单链表" << endl;
		cout << "2.栈" << endl;
		cout << "3.队列" << endl;
		cout << "4.退出系统" << endl;
		cout << "-------------" << endl;
		cout << "请选择:";
		cin >> mDsChoice;
		switch (mDsChoice)
		{
		case 1:
		case 2:
		case 3:
			runChild();
			break;
		case 4:
			cout << "保存数据中...";
			// 保存数据，写入文件
			savedata();
			cout << "保存成功！欢迎下次使用！" << endl;
			return;
		}
	}
	void runChild() // 系统二级菜单的启动函数
	{
		int choice = 0;

		cout << "-------------" << endl;
		cout << "当前选择的数据结构是:" << "xxx" << endl;
		cout << "1.查看" << endl;
		cout << "2.增加" << endl;
		cout << "3.删除" << endl;
		cout << "4.查询" << endl;
		cout << "5.返回" << endl;
		cout << "-------------" << endl;
		cout << "请选择:";
		cin >> choice;
		switch (choice)
		{
		case 1:
			show();
			break;
		case 2:
			insterItem();
			break;
		case 3:
			removeItem();
			break;
		case 4:
			searchItem();
			break;
		case 5:
			run();
			break;
		}
	}
private:
	CStack mstack;
	CCircleQueue mqueue;
	Link mlink;
	FILE *mflie;
	int mDsChoice; // 表示主菜单选择的数据结构
	void loadData()
	{
		cout << "数据加载中... ..." << endl;
		mflie = fopen("CSeqStack.txt", "r");
		if (mflie == nullptr)
		{
			cout << "加载失败1!" << endl;
		}
		int num = 0;
		while (!feof(mflie))
		{
			int a=fgetc(mflie);
			if (a != ' ')
			{
				num *= 10;
				num += (a - 48);
			}
			else
			{
				mstack.push(num);
				num = 0;
			}
		}
		//mstack.push(num);
		cout << "CStack加载完成... ..." << endl;
		fclose(mflie);
		mflie = nullptr;
		mstack.show();
		num = 0;
		mflie = fopen("CCircleQueue.txt", "r");
		while (!feof(mflie))
		{
			int a = fgetc(mflie);
			if (a != ' ')
			{
				num *= 10;
				num += (a - 48);
			}
			else
			{
				mqueue.addQue(num);
				num = 0;
			}
		}
		// mqueue.addQue(num);
		cout << "CCircleQueue加载完成... ..." << endl;
		fclose(mflie);
		mflie = nullptr;
		mqueue.show();
		num = 0;
		mflie = fopen("Link.txt", "r");
		while (!feof(mflie))
		{
			int a = fgetc(mflie);
			if (a != ' ')
			{
				num *= 10;
				num += (a - 48);
			}
			else
			{
				mlink.insertHead(num);
				num = 0;
			}
		}
		//mlink.insertHead(num);
		cout << "Link加载完成... ..." << endl;
		fclose(mflie);
		mflie = nullptr;
		mlink.show();
		cout << "数据加载成功... ..." << endl;
	}
	void show()
	{
		if (mDsChoice == 1)
		{
			mlink.show();
		}
		if (mDsChoice == 2)
		{
			mstack.show();
		}
		else
		{
			mqueue.show();
		}
		runChild();
	}
	void insterItem()
	{
		int val;
		cout << "+++++++++" << endl;
		cout << "请输入增加的内容 ：";
		cin >> val;
		if (mDsChoice == 1)
		{
			mlink.insertHead(val);
		}
		if (mDsChoice == 2)
		{
			mstack.push(val);
		}
		if (mDsChoice == 3)
		{
			mqueue.addQue(val);
		}
		runChild();
	}
	void removeItem()
	{
		int val;
		cout << "+++++++++" << endl;
		if (mDsChoice == 2)
		{
			cout << "删除栈顶元素：" << mstack.top() << endl;
			mstack.pop();
		}
		cout << "请输入删除的内容 ：";
		cin >> val;
		if (mDsChoice == 1)
		{
			mlink.remove(val);
		}
		if (mDsChoice == 3)
		{
			mqueue.addQue(val);
		}
		cout << "删除成功";
		runChild();
	}
	void searchItem()
	{
		int val;
		cout << "+++++++++" << endl;
		cout << "请输入查询的内容 ：";
		cin >> val;
		if (mDsChoice == 1)
		{
			mlink.research(val);
		}
		if (mDsChoice == 2)
		{
			mstack.research(val);
		}
		if (mDsChoice == 3)
		{
			mqueue.research(val);
		}
		runChild();
	}
	void savedata()
	{
		mflie=fopen("CSeqStack.txt", "w");
		while (!mstack.empty())
		{
			char ch[20];
			itoa(mstack.top(), ch, 10);
			fputs(ch, mflie);
			fputc(' ', mflie);
			mstack.pop();
		}
		fclose(mflie);
		mflie = nullptr;

		mflie=fopen("CCircleQueue.txt", "w");
		while (!mqueue.empty())
		{
			char ch[20];
			itoa(mqueue.back(), ch, 10);
			fputs(ch, mflie);
			fputc(' ', mflie);
			mqueue.delQue();
		}
		fclose(mflie);
		mflie = nullptr;
		/*mflie=fopen("Link.txt", "w");
		
		while (mlink.empty())
		{
			fputc(mlink.firstItem(), mflie);
			mlink.outItem();
		}
		fclose(mflie);
		mflie = nullptr;*/
		cout << "数据保存成功... ..." << endl;
	}
};

int main0()
{
	DSSystem dss;
	dss.run();
	return 0;
}