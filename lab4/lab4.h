/**************************************************/
/*                                                */
/*  Lab 4				                          */
/*                                                */
/*  Name:  Ashwin Anand                           */
/*  Student number:  152042206                    */
/*                                                */
/**************************************************/

#include <iostream>

template <typename T>
class DList{
	struct Node{
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data=T{},Node* next=nullptr, Node* prev=nullptr){
			data_=data;
			next_=next;
			prev_=prev;
		}
	};
	Node* front_;
	Node* back_;
public:
	DList(){
		front_=nullptr;
		back_=nullptr;
	}
	void push_front(const T& data);
	~DList();

	class const_iterator
	{
		friend class DList;
	protected:
		Node* curr_;
		const DList* dList_;
		const_iterator(Node* n, const DList* dList)
		{
			curr_ = n;
			dList_ = dList;
		}
	public:
		const_iterator()
		{
			curr_ = nullptr;
			dList_ = nullptr;
		}
		const_iterator& operator++()
		{
			if (curr_)
				curr_ = curr_->next_;
			return *this;
		}
		const_iterator operator++(int)
		{
			const_iterator oldIterator = *this;
			if (curr_)
				curr_ = curr_->next_;
			return oldIterator;
		}
		const_iterator& operator--()
		{
			if (curr_)
				curr_ = curr_->prev_;
			else
			{
				if (dList_)
				{
					curr_ = dList_->back_;
				}
			}
			return *this;
		}
		const_iterator operator--(int)
		{
			const_iterator old = *this;
			if (curr_)
				curr_ = curr_->prev_;
			else
			{
				if (dList_)
				{
					curr_ = dList_->back_;
				}
			}
			return old;
		}

		bool operator==(const_iterator rhs)
		{
			return curr_ == rhs.curr_;
		}
		bool operator!=(const_iterator rhs)
		{
			return !(*this == rhs);
		}
		const T& operator*()const
		{
			return curr_->data_;
		}
	};
	class iterator :public const_iterator
	{
		friend class DList;
		iterator(Node* curr, DList* dList) :const_iterator(curr, dList)
		{
		}
	public:
		iterator() :const_iterator()
		{
		}
		iterator& operator++()
		{
			if (this->curr_)
				this->curr_ = this->curr_->next_;
			return *this;
		}
		iterator operator++(int)
		{
			iterator old = *this;
			if (this->curr_)
				this->curr_ = this->curr_->next_;
			return old;
		}
		iterator& operator--()
		{
			if (this->curr_)
				this->curr_ = this->curr_->prev_;
			else
			{
				if (this->dList_)
				{
					this->curr_ = this->dList_->back_;
				}
			}
			return *this;
		}
		iterator operator--(int)
		{
			iterator old = *this;
			if (this->curr_)
				this->curr_ = this->curr_->prev_;
			else
			{
				if (this->dList_)
				{
					this->curr_ = this->dList_->back_;
				}
			}
			return old;
		}
		T& operator*()
		{
			return this->curr_->data_;
		}
		const T& operator*()const
		{
			return this->curr_->data_;
		}

	};

	const_iterator cbegin() const
	{
		if (front_)
			return const_iterator(front_, this);
		return cend();
	}

	iterator begin()
	{
		if (front_)
			return iterator(front_, this);
		return end();
	}

	const_iterator cend() const
	{
		return const_iterator(nullptr, this);
	}
	iterator end()
	{
		return iterator(nullptr, this);
	}
};


template <typename T>
void DList<T>::push_front(const T& data){
	Node* nn = new Node(data, front_);
	if (front_)
		front_->prev_ = nn;
	else
		back_ = nn;
	front_ = nn;
}


template <typename T>
DList<T>::~DList(){
	Node* cur = nullptr;
	while (front_)
	{
		cur = front_->next_;
		delete front_;
		front_ = cur;
	}
}


template <typename T>
class Sentinel{
	struct Node{
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data=T{},Node* next=nullptr, Node* prev=nullptr){
			data_=data;
			next_=next;
			prev_=prev;
		}
	};
	Node* front_;
	Node* back_;
public:
	Sentinel(){
		front_=new Node();
		back_=new Node();
		front_->next_=back_;
		back_->prev_=front_;
	}
	void push_front(const T& data);
	~Sentinel();

	class const_iterator
	{
		friend class Sentinel;
	protected:
		Node* curr_;
		const Sentinel* dList_;
		const_iterator(Node* n, const Sentinel* dList)
		{
			curr_ = n;
			dList_ = dList;
		}
	public:
		const_iterator()
		{
			curr_ = nullptr;
			dList_ = nullptr;
		}
		const_iterator& operator++()
		{
			if (curr_)
				curr_ = curr_->next_;
			return *this;
		}
		const_iterator operator++(int)
		{
			const_iterator old = *this;
			if (curr_)
				curr_ = curr_->next_;
			return old;
		}
		const_iterator& operator--()
		{
			if (curr_)
				curr_ = curr_->prev_;
			else
			{
				if (dList_)
					curr_ = dList_->back_->prev_;
			}
			return *this;
		}
		const_iterator operator--(int)
		{
			const_iterator old = *this;
			if (curr_)
				curr_ = curr_->prev_;
			else
			{
				if (dList_)
					curr_ = dList_->back_->prev_;
			}
			return old;
		}
		bool operator==(const_iterator rhs)
		{
			return curr_ == rhs.curr_;
		}
		bool operator!=(const_iterator rhs)
		{
			return !(*this == rhs);
		}
		const T& operator*()const
		{
			return curr_->data_;
		}
	};
	class iterator :public const_iterator
	{
		friend class Sentinel;
		iterator(Node* curr, Sentinel* dList) :const_iterator(curr, dList)
		{
		}
	public:
		iterator() :const_iterator()
		{
		};
		iterator& operator++()
		{
			if (this->curr_)
				this->curr_ = this->curr_->next_;
			return *this;
		}
		iterator operator++(int)
		{
			iterator old = *this;
			if (this->curr_)
				this->curr_ = this->curr_->next_;
			return old;
		}
		iterator& operator--()
		{
			if (this->curr_)
				this->curr_ = this->curr_->prev_;
			else
			{
				if (this->dList_)
				{
					this->curr_ = this->dList_->back_->prev_;
				}
			}
			return *this;
		}
		iterator operator--(int)
		{
			iterator old = *this;
			if (this->curr_)
				this->curr_ = this->curr_->prev_;
			else
			{
				if (this->dList_)
				{
					this->curr_ = this->dList_->back_->prev_;
				}
			}
			return old;
		}
		T& operator*()
		{
			return this->curr_->data_;
		}
		const T& operator*()const
		{
			return this->curr_->data_;
		}
	};
	const_iterator cbegin() const
	{
		if (front_->next_)
			return const_iterator(front_->next_, this);
		return cend();
	}
	iterator begin()
	{
		if (front_->next_)
			return iterator(front_->next_, this);
		return end();
	}
	const_iterator cend() const
	{
		return const_iterator(back_, this);
	}
	iterator end()
	{
		return iterator(back_, this);
	}
};


template <typename T>
void Sentinel<T>::push_front(const T& data){
	Node* nn = new Node(data, front_->next_, front_);
	front_->next_->prev_ = nn;
	front_->next_ = nn;
}


template <typename T>
Sentinel<T>::~Sentinel(){
	Node* cur = nullptr;
	while (front_)
	{
		cur = front_->next_;
		delete front_;
		front_ = cur;
	}
}
