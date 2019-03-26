#include <stdio.h>
#include <iostream>
using namespace std;

// OOPʵ��һ��ѭ�����нṹ
class CCircleQueue
{
public:
	CCircleQueue(int size = 10) // ���캯��
	{
		msize = size;
		mpQue = new int[msize];
		mfront = 0;
		mrear = 0;
	}
	~CCircleQueue() // ��������
	{
		delete[] mpQue;
		mpQue = nullptr;
	}
	CCircleQueue(const CCircleQueue &src) // �������캯��
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
	void operator=(const CCircleQueue &src)// ��ֵ���غ���
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

	void addQue(int val) // ���
	{
		if (full())
		{
			resize();
		}
		mpQue[mrear] = val;
		mrear = (mrear + 1) % msize;//��0��msize - 1��
	}
	void delQue()// ����
	{
		if (empty())
		{
			return;
		}
		mfront = (mfront + 1) % msize;
	}
	int front()// ���ض�ͷԪ��
	{
		return mpQue[mfront];
	}
	int back()// ���ض�βԪ��
	{
		return mpQue[(mrear - 1 + msize) % msize];
	}

	bool full() // ����
	{
		if (((mrear + 1) % msize) == mfront)
		{
			return true;
		}
		return false;
	}
	bool empty() // �п�
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
				cout << val << "�����ڶ���" << endl;
				return;
			}
		}
		cout << val << "�������ڶ���" << endl;
	}
private:
	int *mpQue; //�������Ԫ�ص����ݽṹ
	int mfront; //��ͷ�±�
	int mrear; //��β�±�
	int msize; //���ݵ��ܳ���

	void resize() // 2������ѭ������
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

// OOPʵ��һ������ṹ
class Link
{
public:
	Link() // ���캯��
	{
		mphead = new Node();
	}
	~Link() // ��������
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
	void remove(int val) // ɾ������ֵΪval�Ľڵ�
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
			throw "�������";
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
				cout << val << "������������" << endl;
				break;
			}
		}
		cout << val << "��������������" << endl;
	}
	
private:
	// �ڵ�����
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

	// private����������͸�ֵ���غ���
	Link(const Link&);
	void operator=(const Link&);

	Node *mphead;
};

//ջ
class CStack
{
public:
	// CStack() CStack(int)
	CStack(int size = 3) // ���캯�����������Ա�������г�ʼ��
	{
		//cout << this << " CStack(int)" << endl;
		mtop = 0;
		msize = size;
		mpstack = new int[msize];
	}
	// ����������� Ĭ��������ǳ����
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
	// ��ֵ���غ���  stack1 = stack1
	void operator=(const CStack &src)
	{
		//cout << "operator=" << endl;

		// ��ֹ�Ը�ֵ
		if (this == &src)
			return;

		// ���ͷ�thisָ��������е��ⲿ��Դ
		delete[]mpstack;

		// ����src���õĶ�����Դ�ߴ磬���¿��ٿռ䣬��������
		mpstack = new int[src.msize];
		for (int i = 0; i < src.msize; ++i)
		{
			mpstack[i] = src.mpstack[i];
		}
		mtop = src.mtop;
		msize = src.msize;
	}
	~CStack() // �����������ͷŶ���
	{
		cout << this << " ~CStack()" << endl;
		delete[]mpstack;
		mpstack = nullptr;
	}
	void push(int val) // ��ջ
	{
		if (full())
			resize();
		mpstack[mtop++] = val;
	}
	void pop() // ��ջ
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
				cout << val << "������ջ��" << endl;
				break;
			}
		}
		cout << val << "��������ջ��" << endl;
	}
private:
	int *mpstack; // �洢ջ������
	int mtop; // ��ʾջ���±�
	int msize; // ��ʾջ���ܳ���

	void resize()
	{
		int *ptmp = new int[msize * 2];
		//memcpy(ptmp, mpstack, sizeof(int)*msize);
		//realloc  �������ݽ�ֹʹ��realloc/memcpy��Щ����!!!
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
����������£�
�������ݵ���...������ɣ�
-------------
1.������
2.ջ
3.����
4.�˳�ϵͳ => �����ڴ�����
-------------
��ѡ��1

-------------
��ǰ���ݽṹ�ǣ�xxx
1.�鿴
2.����
3.ɾ��
4.��ѯ
5.������һ���˵�
-------------
��ѡ��
*/

// ���ݽṹϵͳ��
class DSSystem
{
public:
	void run() // ϵͳ����������
	{
		// 1.�����ļ��е�����
		loadData();
		// 2.��ʾ���˵�
		cout << "-------------" << endl;
		cout << "1.������" << endl;
		cout << "2.ջ" << endl;
		cout << "3.����" << endl;
		cout << "4.�˳�ϵͳ" << endl;
		cout << "-------------" << endl;
		cout << "��ѡ��:";
		cin >> mDsChoice;
		switch (mDsChoice)
		{
		case 1:
		case 2:
		case 3:
			runChild();
			break;
		case 4:
			cout << "����������...";
			// �������ݣ�д���ļ�
			savedata();
			cout << "����ɹ�����ӭ�´�ʹ�ã�" << endl;
			return;
		}
	}
	void runChild() // ϵͳ�����˵�����������
	{
		int choice = 0;

		cout << "-------------" << endl;
		cout << "��ǰѡ������ݽṹ��:" << "xxx" << endl;
		cout << "1.�鿴" << endl;
		cout << "2.����" << endl;
		cout << "3.ɾ��" << endl;
		cout << "4.��ѯ" << endl;
		cout << "5.����" << endl;
		cout << "-------------" << endl;
		cout << "��ѡ��:";
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
	int mDsChoice; // ��ʾ���˵�ѡ������ݽṹ
	void loadData()
	{
		cout << "���ݼ�����... ..." << endl;
		mflie = fopen("CSeqStack.txt", "r");
		if (mflie == nullptr)
		{
			cout << "����ʧ��1!" << endl;
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
		cout << "CStack�������... ..." << endl;
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
		cout << "CCircleQueue�������... ..." << endl;
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
		cout << "Link�������... ..." << endl;
		fclose(mflie);
		mflie = nullptr;
		mlink.show();
		cout << "���ݼ��سɹ�... ..." << endl;
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
		cout << "���������ӵ����� ��";
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
			cout << "ɾ��ջ��Ԫ�أ�" << mstack.top() << endl;
			mstack.pop();
		}
		cout << "������ɾ�������� ��";
		cin >> val;
		if (mDsChoice == 1)
		{
			mlink.remove(val);
		}
		if (mDsChoice == 3)
		{
			mqueue.addQue(val);
		}
		cout << "ɾ���ɹ�";
		runChild();
	}
	void searchItem()
	{
		int val;
		cout << "+++++++++" << endl;
		cout << "�������ѯ������ ��";
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
		cout << "���ݱ���ɹ�... ..." << endl;
	}
};

int main0()
{
	DSSystem dss;
	dss.run();
	return 0;
}