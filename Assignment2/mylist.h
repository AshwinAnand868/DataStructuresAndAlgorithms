#include<iostream>
#include<utility>

template <typename T>
class DList
{
	struct Node
	{
		T data_;
		Node* next_;
		Node* prev_; 
		Node(const T& data = T(), Node* next = nullptr, Node* prev = nullptr)
		{
			data_ = data;
			next_ = next;
			prev_ = prev;
		}
	};

	Node* front_;
	Node* back_;
	int listSize{};
public:

	class const_iterator
	{
		friend class DList;
	protected:
		const DList* myList_{};
		Node* curr_{};
		const_iterator(Node* curr, const DList* theList)
		{
			curr_ = curr;
			myList_ = theList;
		}
	public:
		const_iterator()
		{
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
				if (myList_)
				{
					curr_ = myList_->back_->prev_;
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
				if (myList_)
				{
					curr_ = myList_->back_->prev_;
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
				if (this->myList_)
				{
					this->curr_ = this->myList_->back_->prev_;
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
				if (this->myList_)
				{
					this->curr_ = this->myList_->back_->prev_;
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
	DList();
	~DList();
	DList(const DList& rhs);
	DList& operator=(const DList& rhs);
	DList(DList&& rhs)noexcept;
	DList& operator=(DList&& rhs)noexcept;
	iterator insert(iterator it, const T& data);
	iterator search(const T& data);
	const_iterator search(const T& data)const;
	iterator erase(iterator it);
	void sort(iterator first, iterator last);
	bool empty() const;
	int size() const;
	void push_front(const T& data);
	void push_back(const T& data);
	void pop_front();
	void pop_back();

	iterator begin()	//returns iterator to Node containing the first piece of data in the linked list
	{
		if (front_->next_)
			return iterator(front_->next_, this);
		return end();
	}
	iterator end()		// returns iterator to the Node after the node containing the last piece of data of the linked list
	{
		return iterator(back_, this);
	}
	const_iterator cbegin() const		//returns const_iterator to to Node containing the first piece of data in the linked list
	{
		if (front_->next_)
			return const_iterator(front_->next_, this);
		return cend();
	}
	const_iterator cend() const			//returns const_iterator to the Node after the node containing the last piece of data of the linked list
	{
		return const_iterator(back_, this);
	}
};

template <typename T>
DList<T>::DList()	//constructor, creates empty DList
{
	front_ = new Node();
	back_ = new Node();
	front_->next_ = back_;
	back_->prev_ = front_;
	listSize = 0;
}

template <typename T>
DList<T>::~DList()		//destructor
{
	Node* curr{};
	while (front_)
	{
		curr = front_->next_;
		delete front_;
		front_ = curr;
		listSize--;
	}
}
template <typename T>
DList<T>::DList(const DList& rhs)		//copy constructor
{
	front_ = new Node();
	back_ = new Node();
	front_->next_ = back_;
	back_->prev_ = front_;

	for (const_iterator constIt = rhs.cbegin(); constIt != rhs.cend(); constIt++)
	{
		push_back(*constIt);
	}
}

template <typename T>
DList<T>& DList<T>::operator=(const DList& rhs)		//assignment operator
{
	if (this != &rhs)
	{
		const_iterator constIt;
		this->~DList();
		front_ = new Node();
		back_ = new Node();
		front_->next_ = back_;
		back_->prev_ = front_;
		listSize = 0;
		for (constIt = rhs.cbegin(); constIt != rhs.cend(); constIt++)
		{
			push_back(*constIt);
		}
	}
	return *this;
}
template <typename T>
DList<T>::DList(DList&& rhs)noexcept		//move constructor
{
	front_ = rhs.front_;
	back_ = rhs.back_;
	listSize = rhs.listSize;
	rhs.front_ = nullptr;
	rhs.back_ = nullptr;
	rhs.listSize = 0;
}

template <typename T>
DList<T>& DList<T>::operator=(DList&& rhs)noexcept		//move operator
{
	if (this != &rhs)
	{
		this->~DList();
		front_ = rhs.front_;
		back_ = rhs.back_;
		listSize = rhs.listSize;

		rhs.front_ = nullptr;
		rhs.back_ = nullptr;
		rhs.listSize = 0;
	}
	return *this;
}

template <typename T>
void DList<T>::push_front(const T& data)		// create a node and link it to the rest of the list right after the front Sentinel Node
{
	Node* nn = new Node(data, front_->next_, front_);
	front_->next_->prev_ = nn;
	front_->next_ = nn;
}

template <typename T>
void DList<T>::push_back(const T& data)		   // create a node and link it to the rest of the list right before the back Sentinel Node
{
	Node* nn = new Node(data, back_, back_->prev_);
	back_->prev_->next_ = nn;
	back_->prev_ = nn;
	listSize++;
}


template <typename T>
void DList<T>::pop_front()					// remove the node right after the front Sentinel Node
{
	if (front_->next_ != back_)
	{
		Node* rm = front_->next_;
		front_->next_ = front_->next_->next_;
		front_->next_->prev_ = front_;
		delete rm;
	}
}

template <typename T>
void DList<T>::pop_back()					// remove the node right before the back Sentinel Node
{
	if (front_->next_ != back_)
	{
		Node* rm = back_->prev_;
		back_->prev_ = rm->prev_;
		back_->prev_->next_ = back_;
		delete rm;
	}
}


template <typename T>
typename DList<T>::iterator DList<T>::insert(iterator it, const T& data)	//adding a new node
{
	Node* nn = new Node(data, it.curr_, it.curr_->prev_);
	it.curr_->prev_->next_ = nn;
	it.curr_->prev_ = nn;
	it.curr_ = nn;
	listSize++;
	return it;
}

template <typename T>
typename DList<T>::iterator DList<T>::search(const T& data)			//returns iterator to the node containing data. If data is not found, returns end()
{
	bool found = false;
	iterator targetItr{};
	for (iterator itr = begin(); itr != end() && !found; itr++)
	{
		if (itr.curr_->data_ == data)
		{
			found = true;
			targetItr = itr;
		}
	}

	if (!found)
		targetItr = end();
	return targetItr;
}

template <typename T>
typename DList<T>::const_iterator DList<T>::search(const T& data)const	//returns iterator to the node containing data.If data is not found, returns end()
{
	bool found = false;
	const_iterator targetItr{};
	for (const_iterator itr = cbegin(); itr != cend() && !found; itr++)
	{
		if (itr.curr_->data_ == data)
		{
			found = true;
			targetItr = itr;
		}
	}

	if (!found)  // may b unnecessary
		targetItr = cend();
	return targetItr;
}
template <typename T>
typename DList<T>::iterator DList<T>::erase(iterator it)		//removes the node referred to by it, returns iterator to node that follows the node that was removed
{
	Node* rm = it.curr_;
	rm->prev_->next_ = rm->next_;
	rm->next_->prev_ = rm->prev_;
	it.curr_ = rm->next_;
	delete rm;
	listSize--;
	return it;
}

template <typename T>
void DList<T>::sort(iterator first, iterator last)				//This function sorts all nodes from first to last, including first but not including last
{
	bool unsorted = true, enteredWhileLoop;

	Node* nextOne = first.curr_;
	Node* nn = first.curr_->prev_;

	while (unsorted)
	{
		Node* currentNode = nextOne;
		enteredWhileLoop = false;
		while (currentNode != last.curr_)
		{

			Node* nextInner = currentNode->next_;
			while (currentNode->next_->next_ && currentNode->next_->data_ < currentNode->data_ && currentNode->next_ != last.curr_)
			{
				Node* temp1, * temp2, * temp3, * temp4;

				temp1 = currentNode->prev_;
				temp2 = currentNode;
				temp3 = currentNode->next_;
				temp4 = currentNode->next_->next_;


				temp1->next_ = temp3;
				temp2->prev_ = temp3;
				temp2->next_ = temp4;
				temp3->prev_ = temp1;
				temp3->next_ = temp2;
				temp4->prev_ = temp2;

				unsorted = true;
				enteredWhileLoop = true;
			}
			if (!enteredWhileLoop)
			{
				unsorted = false;
			}

			currentNode = nextInner;
		}

		if (first.curr_ == front_->next_)
		{
			nextOne = front_->next_;
		}
		else
		{
			nextOne = nn->next_;
		}

	}
}
template <typename T>
bool DList<T>::empty() const		//function returns true if the list is empty, false otherwise
{
	return listSize == 0;
}
template <typename T>
int DList<T>::size() const			//function returns number of pieces of data stored in the list
{
	return listSize;
}