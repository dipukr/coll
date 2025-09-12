package main;

public class List {

	public class Node {
		public int data;
		public Node next;
		public Node(int data) {
			this.data = data;
		}
	}
	
	public void draw(Node head) {
		if (head == null) {
			System.out.println("null");
			return;
		}
		System.out.printf("%d->", head.data);
		draw(head.next);
	}
	
	public void drawR(Node head) {
		if (head == null) {
			System.out.println("null");
			return;
		}
		drawR(head.next);
		System.out.printf("%d->", head.data);
	}
	
	public int size(Node head) {
		if (head == null) return 0;
		return 1 + size(head.next);
	}
	
	public boolean empty(Node head) {
		return size(head) == 0;
	}
	
	public void addAll(Node head, int ... data) {
		for (int elem: data)
			addTail(head, elem);
	}
	
	public Node addLast(Node head, int data) {
		if (head == null) return new Node(data);
		head.next = addLast(head.next, data);
		return head;
	}
	
	public Node deleteLast(Node head) {
		if (head.next == null) return null;
		head.next = deleteLast(head.next);
		return head;
	}
	
	public void addTail(Node head, int data) {
		if (head.next == null) {
			head.next = new Node(data);
			return;
		}
		addTail(head.next, data);
	}
	
	public void deleteTail(Node head) {
		if (head.next.next == null) {
			head.next = null;
			return;
		}
		deleteLast(head.next);
	}
	
	public void deleteNode(Node head, Node node) {
		Node curr = head;
		while (curr.next != null && curr.next != node)
			curr = curr.next;
		if (curr.next == node)
			curr.next = node.next;
	}
	
	public void deleteByValue(Node head, int val) {
		Node iter = head;
		while (iter.next != null && iter.next.data != val)
			iter = iter.next;
		if (iter.next != null)
			iter.next = iter.next.next;
	}
	
	public boolean searchElement(Node head, int key) {
		if (head == null) return false;
		if (head.data == key) return true;
		return searchElement(head.next, key);
	}
	
	public boolean circular(Node head, Node node) {
		if (node == head) return true;
		if (node == null) return false;
		return circular(head, node.next);
	}
	
	public Node reverse(Node head) {
		if (head == null || head.next == null) return head;
		Node partial = reverse(head.next);
		head.next.next = head;
		head.next = null;
		return partial;
	}
	
	public Node reverseK(Node head, int k) {
		Node prev = null, curr = head;
		while (curr != null && k-- != 0) {
			Node next = curr.next;
			curr.next = prev;
			prev = curr;
			curr = next;
		}
		head.next = curr;
		return prev;
	}
	
	public Node cloneList(Node head) {
		Node cloneHead = new Node(head.data);
		Node clone = cloneHead;
		Node curr = head.next;
		while (curr != null) {
			clone.next = new Node(curr.data);
			clone = clone.next;
			curr = curr.next;
		}
		return cloneHead;
	}
	
	public Node mergeSortedLists(Node first, Node second) {
		if (first == null) return second;
		if (second == null) return first;
		if (first.data < second.data) {
			first.next = mergeSortedLists(first.next, second);
			return first;
		} else {
			second.next = mergeSortedLists(first, second.next);
			return second;
		}
	}
	
	public void test() {
		Node first = new Node(10);
		Node second = new Node(15);
		addAll(first, 20,30,40,50);
		addAll(second, 25,35);
		draw(first);
		draw(second);
	}
	
	public static void main(final String[] args) {
		var list = new List();
		list.test();
	}
}











