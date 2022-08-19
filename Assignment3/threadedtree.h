/********************************************************************/
/*                                                                  */
/*  A3: threaded BST			                                    */
/*                                                                  */
/*  Author1 Name: Ashwin Anand                                       */
/*      - class/function list/main author or main checker           */
/*  Author2 Name: James Hickman                                       */
/*      - class/function list/main author or main checker           */
/*                                                                  */
/********************************************************************/


#include <iostream>
using namespace std;

template <class T>
class ThreadedTree
{

	struct Node
	{
		Node* left_{};
		Node* right_{};
		T data_;
		bool isLeftThread{}, isRightThread{};
		Node(const T& data, Node* left, Node* right, bool lfThread, bool rtThread)
		{
			data_ = data;
			left_ = left;
			right_ = right;
			isLeftThread = lfThread;
			isRightThread = rtThread;
		}
	};

	Node* root_;
	int noOfNOdes;

	void print(const Node* rt, int lvl)const
	{
		//This function won't be tested, but you may find it useful to implement this so 
		//that you can see what the tree looks like.  lvl will allow you to use dashes to 
		//better show shape of tree.  Feel free to modify this to print in any way that will
		//help you debug.  Feel free to copy the pretty print function from lab 8 that will draw
		//the tree (though it won't draw threads)
	}


	void destroyTree(Node* subtree)
	{
		if (subtree)
		{
			if (subtree->left_ != nullptr && !subtree->isLeftThread)
			{
				destroyTree(subtree->left_);
			}
			if (subtree->right_ != nullptr && !subtree->isRightThread)
			{
				destroyTree(subtree->right_);
			}
			delete subtree;
		}

	}


public:
	class const_iterator
	{
		const ThreadedTree* threadedTree{};
		Node* curr_{};
		const_iterator(Node* curr, const ThreadedTree* threaded_tree)
		{
			curr_ = curr;
			threadedTree = threaded_tree;
		}
	protected:

	public:
		const_iterator()
		{

		}
		const_iterator operator++(int)
		{
			const_iterator old = *this;


			if (*this != threadedTree->cend())
			{
				if (curr_->right_)
				{
					if (curr_->isRightThread)
					{
						curr_ = curr_->right_;
					}
					else
					{
						curr_ = curr_->right_;
						while (curr_->left_ && !curr_->isLeftThread)
							curr_ = curr_->left_;
					}
				}

			}
			return old;
		}
		const_iterator operator--(int)
		{
			const_iterator old = *this;

			if (curr_)
			{
				if (curr_->left_)
				{
					if (curr_->isLeftThread)
					{
						curr_ = curr_->left_;
					}
					else
					{
						curr_ = curr_->left_;
						while (curr_->right_ && !curr_->isRightThread)
							curr_ = curr_->right_;
					}

				}
			}
			else if (curr_ == nullptr)
			{
				Node* curr = threadedTree->root_;
				while (curr->right_)
				{
					curr = curr->right_;
				}
				curr_ = curr;
			}
			return old;
		}
		const_iterator& operator++()
		{
			if (*this != threadedTree->cend())
			{
				if (curr_->right_)
				{
					if (curr_->isRightThread)
					{
						curr_ = curr_->right_;
					}
					else
					{
						curr_ = curr_->right_;
						while (curr_->left_ && !curr_->isLeftThread)
							curr_ = curr_->left_;
					}
				}

			}

			return *this;
		}
		const_iterator& operator--()
		{
			if (curr_)
			{
				if (curr_->left_)
				{
					if (curr_->isLeftThread)
					{
						curr_ = curr_->left_;
					}
					else
					{
						curr_ = curr_->left_;
						while (curr_->right_ && !curr_->isRightThread)
							curr_ = curr_->right_;
					}

				}
			}
			else if (curr_ == nullptr)
			{
				Node* curr = threadedTree->root_;
				while (curr->right_)
				{
					curr = curr->right_;
				}
				curr_ = curr;
			}
			return *this;
		}
		const T& operator*() const
		{
			return curr_->data_;
		}
		bool operator==(const const_iterator& rhs) const
		{
			return curr_ == rhs.curr_;
		}
		bool operator!=(const const_iterator& rhs) const
		{
			return !(*this == rhs);
		}
		friend class ThreadedTree;
	};
	class iterator :public const_iterator
	{
		iterator(Node* curr, ThreadedTree* threadedTree) :const_iterator(curr, threadedTree)
		{

		}
	public:
		iterator() :const_iterator()
		{
		}
		const T& operator*() const
		{
			return this->curr_->data_;
		}
		T& operator*()
		{
			return this->curr_->data_;
		}
		iterator operator++(int)
		{
			iterator old = *this;

			if (*this != this->threadedTree->cend())
			{
				if (this->curr_->right_)
				{
					if (this->curr_->isRightThread)
					{
						this->curr_ = this->curr_->right_;
					}
					else
					{
						this->curr_ = this->curr_->right_;
						while (this->curr_->left_ && !this->curr_->isLeftThread)
							this->curr_ = this->curr_->left_;
					}
				}

			}
			return old;
		}
		iterator operator--(int)
		{
			iterator old = *this;

			if (this->curr_)
			{
				if (this->curr_->left_)
				{
					if (this->curr_->isLeftThread)
					{
						this->curr_ = this->curr_->left_;
					}
					else
					{
						this->curr_ = this->curr_->left_;
						while (this->curr_->right_ && !this->curr_->isRightThread)
							this->curr_ = this->curr_->right_;
					}

				}

			}
			else if (this->curr_ == nullptr)
			{
				Node* curr = this->threadedTree->root_;
				while (curr->right_)
				{
					curr = curr->right_;
				}
				this->curr_ = curr;
			}
			return old;
		}
		iterator operator++()
		{
			if (*this != this->threadedTree->cend())
			{
				if (this->curr_->right_)
				{
					if (this->curr_->isRightThread)
					{
						this->curr_ = this->curr_->right_;
					}
					else
					{
						this->curr_ = this->curr_->right_;
						while (this->curr_->left_ && !this->curr_->isLeftThread)
							this->curr_ = this->curr_->left_;
					}
				}

			}
			return *this;
		}
		iterator operator--()
		{
			if (this->curr_)
			{
				if (this->curr_->left_)
				{
					if (this->curr_->isLeftThread)
					{
						this->curr_ = this->curr_->left_;
					}
					else
					{
						this->curr_ = this->curr_->left_;
						while (this->curr_->right_ && !this->curr_->isRightThread)
							this->curr_ = this->curr_->right_;
					}

				}

			}
			else if (this->curr_ == nullptr)
			{
				Node* curr = this->threadedTree->root_;
				while (curr->right_)
				{
					curr = curr->right_;
				}
				this->curr_ = curr;
			}
			return *this;
		}

		friend class ThreadedTree;
	};

	ThreadedTree()
	{
		root_ = nullptr;
		noOfNOdes = 0;
	}

	void insert(const T& data)
	{
		if (root_ == nullptr)
		{
			root_ = new Node(data, nullptr, nullptr, false, false);
			noOfNOdes++;
		}
		else
		{

			Node* curr = root_;

			while (curr != nullptr)
			{
				if (data < curr->data_)
				{
					if (curr->left_ && !curr->isLeftThread)
					{
						curr = curr->left_;
					}
					else
					{
						if (curr->data_ == *(cbegin()))
						{
							curr->left_ = new Node(data, nullptr, curr, false, true);
						}
						else
						{
							if (curr->isLeftThread)
							{
								curr->isLeftThread = false;
							}

							curr->left_ = new Node(data, curr->left_, curr, true, true);


						}
						noOfNOdes++;
						curr = nullptr;
					}


				}
				else
				{
					if (curr->right_ && !curr->isRightThread)
					{
						curr = curr->right_;
					}
					else
					{
						const_iterator itrToBiggestNode{};

						Node* localCurrent = root_;
						if (localCurrent)
						{

							while (localCurrent->right_)
							{
								itrToBiggestNode = const_iterator(localCurrent->right_, this);
								localCurrent = localCurrent->right_;
							}

							itrToBiggestNode = const_iterator(localCurrent, this);
						}

						if (curr->data_ == *itrToBiggestNode)
						{
							curr->right_ = new Node(data, curr, nullptr, true, false);
						}
						else
						{
							if (curr->isRightThread)
								curr->isRightThread = false;
							curr->right_ = new Node(data, curr, curr->right_, true, true);

						}
						noOfNOdes++;
						curr = nullptr;
					}
				}
			}

		}

	}

	iterator find(const T& key)
	{
		return findRecursive(key, root_);
	}
	const_iterator find(const T& key) const
	{
		const_iterator foundNode = findRecursive(key, root_);
		return foundNode;
	}
	iterator begin()
	{
		iterator leftMostItr{};
		Node* curr = root_;
		if (curr)
		{
			while (curr->left_)
			{
				leftMostItr = iterator(curr->left_, this);
				curr = curr->left_;
			}
			leftMostItr = iterator(curr, this);
		}
		else
		{
			leftMostItr = end();
		}

		return leftMostItr;
	}
	iterator end()
	{
		return iterator(nullptr, this);
	}
	const_iterator cbegin()const
	{
		const_iterator leftMostItr{};
		Node* curr = root_;
		if (curr)
		{
			while (curr->left_)
			{
				leftMostItr = const_iterator(curr->left_, this);
				curr = curr->left_;
			}
			leftMostItr = const_iterator(curr, this);
		}
		else
		{
			leftMostItr = cend();
		}

		return leftMostItr;
	}
	const_iterator cend() const
	{
		return const_iterator(nullptr, this);
	}
	void print() const
	{
		//this function won't be tested, but you may wish to implement this 
		//to help you debug.  You won't need to implement this for submission
	}
	int size() const
	{
		return noOfNOdes;
	}
	bool empty() const
	{
		return noOfNOdes == 0;
	}


	~ThreadedTree()
	{
		destroyTree(root_);
	}

private:
	iterator findRecursive(const T& key, Node* curr)
	{
		iterator foundNode = end();
		if (key == curr->data_)
		{
			foundNode = iterator(curr, this);
		}
		else if (key < curr->data_ && !curr->isLeftThread)
		{
			foundNode = findRecursive(key, curr->left_);
		}
		else if (!curr->isRightThread)
		{
			foundNode = findRecursive(key, curr->right_);
		}

		return foundNode;
	}

};
