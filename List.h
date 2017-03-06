#ifndef _LIST_H
#define _LIST_H

template<class T>
class Array {
public:

	typedef T* iterator;

	Array(int size) {
	}

	Arrays(const List<T>& list) {
		for (Iterator i = list.begin(); i; ++i)
			add(*i);
	}

	~List() {
		Node* n = head;
		while (n) {
			Node* node = n;
			n = n->next;
			delete node;
		}
	}

	void add(const T& obj) {
		head = new Node(obj);
		++size;
	}

	void remove(const T& obj) {
		if (!head)
			return;
		if (head->obj == obj) {
			Node* oldHead = head;
			head = head->next;
			delete oldHead;
			return;
		}
		for (Node* n = head; n; n = n->next) {
			if (n->next->obj == obj) {
				Node* oldNode = n->next;
				n->next = n->next->next;
				delete oldNode;
				return;
			}
		}
	}

	void removeFirst() {
		if (head) {
			Node* oldHead = head;
			head = head->next;
			delete oldHead;
		}
	}

	T getFirst() const {
		return head->obj;
	} 

	T popFirst() {
		T first = getFirst();
		removeFirst();
		return first;
	}

	Iterator begin() {
		return Iterator(head);
	}

	int getSize() const {
		return size;
	}

private:
	Node* head;
	int size;

	struct Node {
		T     obj;
		Node* next;
		Node(T obj) : obj(obj), next(head) {
		}
	};
};

template<class T>
class List {
public:

	class Iterator {
	private:
		Node* node;

		Iterator(Node* node) {
			node = head;
		}
	public:

		operator bool() {
			return (node != NULL);
		}

		const T& operator*() const {
			return node->obj;
		}

		T& operator*() {
			return node->obj;
		}

		const T& operator->() const {
			return node->obj;
		}

		T& operator->() {
			return node->obj;
		}

		Iterator& operator++() {
			node = node->next;
			return *this;
		}
	};

	List() : head(NULL), size(0) {
	}

	List(const List<T>& list) {
		for (Iterator i = list.begin(); i; ++i)
			add(*i);
	}

	~List() {
		Node* n = head;
		while (n) {
			Node* node = n;
			n = n->next;
			delete node;
		}
	}

	void add(const T& obj) {
		head = new Node(obj);
		++size;
	}

	void remove(const T& obj) {
		if (!head)
			return;
		if (head->obj == obj) {
			Node* oldHead = head;
			head = head->next;
			delete oldHead;
			return;
		}
		for (Node* n = head; n; n = n->next) {
			if (n->next->obj == obj) {
				Node* oldNode = n->next;
				n->next = n->next->next;
				delete oldNode;
				return;
			}
		}
	}

	void removeFirst() {
		if (head) {
			Node* oldHead = head;
			head = head->next;
			delete oldHead;
		}
	}

	T getFirst() const {
		return head->obj;
	} 

	T popFirst() {
		T first = getFirst();
		removeFirst();
		return first;
	}

	Iterator begin() {
		return Iterator(head);
	}

	int getSize() const {
		return size;
	}

private:
	Node* head;
	int size;

	struct Node {
		T     obj;
		Node* next;
		Node(T obj) : obj(obj), next(head) {
		}
	};
};

#endif