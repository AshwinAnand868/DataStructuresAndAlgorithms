/**************************************************/
/*                                                */
/*  Lab 7 Starter file                            */
/*                                                */
/*  Name:  Ashwin Anand                           */
/*  Student number:  152042206                    */
/*                                                */
/**************************************************/

#include <iostream>
#include <iomanip>

/*forward declaration*/
template <class T>
class Queue;

template <class T>
class BST
{
	struct Node
	{
		T data_;
		Node* left_;
		Node* right_;
		Node(const T& data, Node* lt = nullptr, Node* rt = nullptr)
		{
			data_ = data;
			left_ = lt;
			right_ = rt;
		}
	};
	Node* root_;

	void printPreOrder(Node* subroot)const
	{
		if (subroot)
		{
			std::cout << subroot->data_ << " ";
			printPreOrder(subroot->left_);
			printPreOrder(subroot->right_);
		}
	}
	void printInOrder(Node* subroot)const
	{
		if (subroot)
		{
			printInOrder(subroot->left_);
			std::cout << subroot->data_ << " ";
			printInOrder(subroot->right_);
		}
	}
	void destroy(Node* subroot)
	{
		if (subroot)
		{
			destroy(subroot->left_);
			destroy(subroot->right_);
			delete subroot;
		}
	}

	bool isSame(const Node* left, const Node* right) const;

	/*used by print() to print all nodes at same level*/
	void printLine(Node* data[], int numNodes, int width) const
	{
		int half = width / 2;
		int firsthalf = width % 2 ? half + 1 : half;

		if (numNodes > 1)
		{
			for (int i = 0; i < numNodes; i++)
			{
				if (i % 2 == 0)
				{
					if (data[i])
					{
						std::cout << std::right << std::setfill(' ') << std::setw(firsthalf) << "-";
						std::cout << std::left << std::setfill('-') << std::setw(half) << "-";
					}
					else
					{
						std::cout << std::right << std::setfill(' ') << std::setw(firsthalf) << " ";
						std::cout << std::left << std::setfill(' ') << std::setw(half) << " ";
					}
				}
				else
				{
					if (data[i])
					{
						std::cout << std::right << std::setfill('-') << std::setw(firsthalf) << "-";
						std::cout << std::left << std::setfill(' ') << std::setw(half) << "-";
					}
					else
					{
						std::cout << std::right << std::setfill(' ') << std::setw(firsthalf) << " ";
						std::cout << std::left << std::setfill(' ') << std::setw(half) << " ";
					}
				}
			}
			std::cout << std::endl;
		}
		for (int i = 0; i < numNodes; i++)
		{
			if (data[i])
			{
				if (i % 2 == 0)
				{
					std::cout << std::right << std::setw(firsthalf) << "|";
					std::cout << std::left << std::setfill(' ') << std::setw(half) << " ";
				}
				else
				{
					std::cout << std::right << std::setfill(' ') << std::setw(firsthalf) << " ";
					std::cout << std::left << std::setfill(' ') << std::setw(half) << "|";
				}
			}
			else
			{
				std::cout << std::left << std::setfill(' ') << std::setw(width) << " ";
			}
		}
		std::cout << std::endl;
		for (int i = 0; i < numNodes; i++)
		{
			if (data[i])
			{
				if (i % 2 == 0)
				{
					std::cout << std::right << std::setw(firsthalf) << data[i]->data_;
					std::cout << std::left << std::setfill(' ') << std::setw(half) << " ";
				}
				else
				{
					std::cout << std::right << std::setfill(' ') << std::setw(firsthalf) << " ";
					std::cout << std::left << std::setfill(' ') << std::setw(half) << data[i]->data_;
				}
			}
			else
			{
				std::cout << std::left << std::setfill(' ') << std::setw(width) << " ";
			}
		}
		std::cout << std::endl;
	}

	Node* detachSmallest(Node*& subtree)
	{
		Node* inorderSuccessor = subtree->right_;
		Node* inorderSuccessorParent = subtree;

		while (inorderSuccessor->left_)
		{
			inorderSuccessorParent = inorderSuccessor;
			inorderSuccessor = inorderSuccessor->left_;
		}

		if (inorderSuccessor->right_)
		{
			if (inorderSuccessorParent->left_ == inorderSuccessor)
			{
				inorderSuccessorParent->left_ = inorderSuccessor->right_;
			}
			else
			{
				inorderSuccessorParent->right_ = inorderSuccessor->right_;
			}
		}
		else
		{
			if (inorderSuccessorParent->left_ == inorderSuccessor)
			{
				inorderSuccessorParent->left_ = nullptr;
			}
			else
			{
				inorderSuccessorParent->right_ = nullptr;
			}
		}


		return inorderSuccessor;
	}

	void remove(const T& data, Node*& subtree)
	{
		if (subtree)
		{
			Node* subtreeParent = nullptr;
			Node* current = subtree;

			while (current != nullptr && current->data_ != data)
			{
				subtreeParent = current;

				if (data < current->data_)
				{
					// go left
					current = current->left_;
				}
				else
				{
					// go right
					current = current->right_;
				}
			}


			if (current)
			{
				if (!current->left_ && !current->right_)
				{
					if (subtreeParent)
					{
						if (subtreeParent->left_ == current)
							subtreeParent->left_ = nullptr;
						else
							subtreeParent->right_ = nullptr;
					}
					else
					{
						subtree = nullptr;
					}
					delete current;
					current = nullptr;
				}
				else if (current->left_ && current->right_)
				{
					Node* inorderSuccessor = detachSmallest(current);

					inorderSuccessor->left_ = current->left_;
					inorderSuccessor->right_ = current->right_;
					if (subtreeParent)
					{
						if (subtreeParent->left_ == current)
						{
							subtreeParent->left_ = inorderSuccessor;
						}
						else
						{
							subtreeParent->right_ = inorderSuccessor;
						}
					}
					else
					{
						subtree = inorderSuccessor;
					}

					delete current;
					current = nullptr;
				}
				else
				{
					Node* childNode = current->left_ ? current->left_ : current->right_;
					if (subtreeParent)
					{
						if (subtreeParent->left_ == current)
						{
							subtreeParent->left_ = childNode;
						}
						else
						{
							subtreeParent->right_ = childNode;
						}
					}
					else
					{
						subtree = childNode;
					}
					delete current;
					current = nullptr;
				}
			}
			else if (data < subtree->data_)
			{
				remove(data, subtree->left_);
			}
			else
			{
				remove(data, subtree->right_);
			}
		}
	}

	int depth(const T& data, const Node* subtree)
	{
		int dpth = -1;

		if (subtree)
		{

			if (subtree->data_ == data)
			{
				dpth += 1;
			}
			else if (data < subtree->data_)
			{
				dpth = depth(data, subtree->left_);
				dpth = dpth >= 0 ? dpth + 1 : -1;
			}
			else
			{
				dpth = depth(data, subtree->right_);
				dpth = dpth >= 0 ? dpth + 1 : -1;
			}
		}
		return dpth;
	}

public:
	BST()
	{
		root_ = nullptr;
	}

	/* Lab 7: Implement these 3 functions. */
	BST(const BST& rhs)
	{
		if (rhs.root_)
		{
			Queue<Node*> nodes;
			Node* curr = rhs.root_;

			nodes.enqueue(curr);
			while (!nodes.isEmpty())
			{

				curr = nodes.front();
				insert(curr->data_);
				if (curr->left_)
					nodes.enqueue(curr->left_);
				if (curr->right_)
					nodes.enqueue(curr->right_);

				nodes.dequeue();

			}
		}

	}

	void remove(const T& data)
	{
		remove(data, root_);
	}

	int depth(const T& data)
	{
		return depth(data, root_);
	}


	void printPreOrder() const
	{
		printPreOrder(root_);
		std::cout << std::endl;
	}
	void printInOrder() const
	{
		printInOrder(root_);
		std::cout << std::endl;
	}


	void insert(const T& data)
	{
		if (root_ == nullptr)
		{
			root_ = new Node(data);
		}
		else
		{

			Node* curr = root_;
			while (curr != nullptr)
			{
				if (data < curr->data_)
				{
					//go left
					if (curr->left_)
					{
						curr = curr->left_;
					}
					else
					{
						curr->left_ = new Node(data);
						curr = nullptr;
					}
				}
				else
				{
					//go right
					if (curr->right_)
					{
						curr = curr->right_;
					}
					else
					{
						curr->right_ = new Node(data);
						curr = nullptr;
					}
				}
			}

		}

	}

	bool operator==(const BST& rhs) const;
	void print() const
	{
		struct Output
		{
			Node* node_;
			int lvl_;
			int position_;
			Output(Node* n = nullptr, int l = 0, int p = 0)
			{
				node_ = n;
				lvl_ = l;
				position_ = p;
			}
			void set(Node* n = nullptr, int l = 0, int p = 0)
			{
				node_ = n;
				lvl_ = l;
				position_ = p;
			}
		};
		Queue<Output> theNodes;
		Node* line[16];
		if (root_)
		{
			for (int i = 0; i < 16; i++)
			{
				line[i] = nullptr;
			}
			theNodes.enqueue(Output(root_, 0, 0));
			int currline = 0;
			int width = 80;
			int numInLine = 1;
			while (theNodes.isEmpty() == false)
			{
				Output curr = theNodes.front();
				if (curr.node_->left_)
					theNodes.enqueue(Output(curr.node_->left_, curr.lvl_ + 1, curr.position_ * 2));
				if (curr.node_->right_)
					theNodes.enqueue(Output(curr.node_->right_, curr.lvl_ + 1, curr.position_ * 2 + 1));
				theNodes.dequeue();


				if (curr.lvl_ > currline)
				{
					printLine(line, numInLine, width);
					width = width / 2;
					numInLine = numInLine * 2;
					for (int i = 0; i < 16; i++)
					{
						line[i] = nullptr;
					}
					currline++;
				}
				line[curr.position_] = curr.node_;
			}
			printLine(line, numInLine, width);
			std::cout << std::endl;

		}
		else
		{
			std::cout << "tree is empty" << std::endl;
		}
	}
	~BST()
	{
		destroy(root_);
	}
};

template <class T>
class Queue
{
	T* theQueue_;
	int capacity_;
	int used_;
	int front_;
	int back_;
	void grow()
	{
		T* tmp = new T[capacity_ * 2];
		int j;
		for (int i = 0, j = front_; i < used_; i++, j = (j + 1) % capacity_)
		{
			tmp[i] = theQueue_[j];
		}
		delete[] theQueue_;
		theQueue_ = tmp;
		capacity_ = capacity_ * 2;
		front_ = 0;
		back_ = used_;
	}
public:
	Queue()
	{
		theQueue_ = new T[50];
		capacity_ = 50;
		used_ = 0;
		front_ = 0;
		back_ = 0;
	}
	void enqueue(const T& data)
	{
		if (used_ == capacity_)
		{
			grow();
		}
		theQueue_[back_] = data;
		back_ = (back_ + 1) % capacity_;
		used_++;
	}
	void dequeue()
	{
		if (!isEmpty())
		{
			used_--;
			front_ = (front_ + 1) % capacity_;
		}
	}
	T front() const
	{
		if (!isEmpty())
		{
			return theQueue_[front_];
		}
		return T{};

	}
	bool isEmpty() const
	{
		return used_ == 0;
	}
	~Queue()
	{
		delete[] theQueue_;
	}
};
