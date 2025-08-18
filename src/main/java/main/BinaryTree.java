package main;

import java.util.ArrayList;
import java.util.Deque;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Stack;
import java.util.TreeMap;

public class BinaryTree {

	public class Node {
		public int data;
		public Node left;
		public Node right;
		public Node(int data) {
			this.data = data;
		}
	}
	
	public int size(Node node) {
		if (node == null) return 0;
		int leftSize = size(node.left);
		int rightSize = size(node.right);
		return leftSize + rightSize + 1;
	}
	
	public int height(Node node) {
		if (node == null) return 0;
		int leftHeight = height(node.left);
		int rightHeight = height(node.right);
		return Math.max(leftHeight, rightHeight) + 1;
	}
	
	public void visit(Node node) {
		Console.draw("%d\t", node.data);
	}
	
	public void preorder(Node root) {
		if (root != null) {
			visit(root);
			preorder(root.left);
			preorder(root.right);
		}
	}
	
	public void inorder(Node root) {
		if (root != null) {
			inorder(root.left);
			visit(root);
			inorder(root.right);
		}
	}
	
	public void postorder(Node root) {
		if (root != null) {
			postorder(root.left);
			postorder(root.right);
			visit(root);
		}
	}
	
	public void findByLevel(Node root, int level, List<Integer> data) {
		if (root == null) return;
		if (level == 1) data.add(root.data);
		else if (level > 1) {
			findByLevel(root.left, level - 1, data);
			findByLevel(root.right, level - 1, data);
		}
	}
	
	public void levelOrderTraversal(Node root, int level) {
		if (root == null) return;
		if (level == 1) visit(root);
		else if (level > 1) {
			levelOrderTraversal(root.left, level - 1);
			levelOrderTraversal(root.right, level - 1);
		}
	}
	
	public void levelOrderTraversal(Node root) {
		int height = height(root);
		for (int levelNo = 1; levelNo <= height; levelNo++) {
			Console.draw("Level %d: ", levelNo);
			levelOrderTraversal(root, levelNo);
			System.out.println();
		}
	}
	
	public void DFS(Node root) {
		if (root == null) return;
		DFS(root.left);
		DFS(root.right);
		Console.draw("%s\t", root.data);
	}
	
	public int treeSum(Node root) {
		if (root == null) return 0;
		int leftSum = treeSum(root.left);
		int rightSum = treeSum(root.right);
		return root.data + leftSum + rightSum;
	}
	
	@REM("BottomUP")
	public Node invert(Node node) {
		if (node != null) {
			Node leftTree = invert(node.left);
			Node rightTree = invert(node.right);
			node.left = rightTree;
			node.right = leftTree;
		}
		return node;
	}
	
	@REM("TopDown")
	public void invertTree(Node node) {
		if (node != null) {
			Node saved = node.left;
			node.left = node.right;
			node.right = saved;
			invertTree(node.left);
			invertTree(node.right);
		}
	}
	
	public List<Integer> leftView(Node root) {
		List<Integer> answer = new ArrayList<>();
		if (root == null) return answer;
		Queue<Node> queue = new LinkedList<>();
		queue.offer(root);
		while (!queue.isEmpty()) {
			int size = queue.size();
			for (int i = 0; i < size; i++) {
				Node node = queue.poll();
				if (node.left != null) queue.offer(node.left);
				if (node.right != null) queue.offer(node.right);
				if (i == 0) answer.add(node.data);
			}
		}
		return answer;
	}
	
	public List<Integer> rightView(Node root) {
		List<Integer> answer = new ArrayList<>();
		if (root == null) return answer;
		Queue<Node> queue = new LinkedList<>();
		queue.offer(root);
		while (!queue.isEmpty()) {
			int size = queue.size();
			for (int i = 0; i < size; i++) {
				Node node = queue.poll();
				if (node.left != null) queue.offer(node.left);
				if (node.right != null) queue.offer(node.right);
				if (i == size - 1) answer.add(node.data);
			}
		}
		return answer;
	}
	
	public void BFS(Node root) {
		var queue = new LinkedList<Node>();
		queue.offer(root);
		while (!queue.isEmpty()) {
			Node node = queue.poll();
			System.out.printf("%s\t", node.data);
			if (node.left != null)
				queue.offer(node.left);
			if (node.right != null)
				queue.offer(node.right);
		}
	}
	
	public void depthFirstSearch(Node root) {
		var stack = new Stack<Node>();
		stack.push(root);
		while (!stack.isEmpty()) {
			Node node = stack.pop();
			Console.draw("%s\t", node.data);
			if (node.left != null)
				stack.push(node.left);
			if (node.right != null)
				stack.push(node.right);
		}
	}

	public void levelWiseBFS(Node root) {
		var queue = new LinkedList<Node>();
		queue.offer(root);
		queue.offer(null);
		int level = 1;
		System.out.printf("Level %d: ", level);
		while (!queue.isEmpty()) {
			Node node = queue.poll();
			if (node != null) {
				System.out.printf("%d\t", node.data);
				if (node.left != null) queue.offer(node.left);
				if (node.right != null) queue.offer(node.right);
			} else if (!queue.isEmpty()) {
				level++;
				queue.offer(null);
				System.out.printf("\nLevel %d: ", level);
			}
		}
	}
	
	public Map<Integer, Integer> levelWiseSum(Node root) {
		var levelWiseSum = new TreeMap<Integer, Integer>();
		var queue = new LinkedList<Node>();
		queue.offer(root);
		queue.offer(null);
		int levelSum = 0;
		int levelNo = 1;
		while (!queue.isEmpty()) {
			Node node = queue.poll();
			if (node != null) {
				levelSum += node.data;
				if (node.left != null) queue.offer(node.left);
				if (node.right != null) queue.offer(node.right);
			} else if (!queue.isEmpty()) {
				levelWiseSum.put(levelNo, levelSum);
				levelSum = 0;
				levelNo++;
				queue.offer(null);
			}
		}
		levelWiseSum.put(levelNo, levelSum);
		return levelWiseSum;
	}
	
	public int leftLeavesSum(Node root) {
		return leftLeavesSum(root, false);
	}
	
	public int leftLeavesSum(Node root, boolean leftChild) {
		if (root == null) return 0;
		if (leftChild && root.left == null && root.right == null)
			return root.data;
		int leftSum = leftLeavesSum(root.left, true);
		int rightSum = leftLeavesSum(root.left, true);
		return leftSum + rightSum;
	}
	
	public boolean hasPathDFS(Node node, int val, LinkedList<Integer> path) {
		if (node == null) return false;
		path.addLast(node.data);
		if (node.data == val || hasPathDFS(node.left, val, path) || hasPathDFS(node.right, val, path))
			return true;
		path.removeLast();
		return false;
	}
	
	public boolean hasPath(Node root, int val, Deque<Integer> path) {
		if (root == null) return false;
		if (root.data == val) {
			path.addLast(root.data);
			return true;
		}
		if (hasPath(root.left, val, path)) {
			path.addLast(root.data);
			return true;
		}
		if (hasPath(root.right, val, path)) {
			path.addLast(root.data);
			return true;
		}
		return false;
	}
	
	public boolean findPath(Node root, int val, Deque<Integer> path) {
		if (root == null) return false;
		if (root.data == val || findPath(root.left, val, path) || findPath(root.right, val, path)) {
			path.addLast(root.data);
			return true;
		}
		return false;
	}
	
	public boolean getPath(Node root, int val, Deque<Integer> path) {
		if (root == null) return false;
		path.addLast(root.data);
		if (root.data == val || getPath(root.left, val, path) || getPath(root.right, val, path))
			return true;
		path.removeLast();
		return false;
	}
	
	public boolean contains(Node root, int key) {
		if (root == null) return false;
		if (root.data == key) return true;
		return contains(root.left, key) || contains(root.right, key);
	}
	
	public boolean binarySearchTree(Node node) {
		if (node == null) return true;
		boolean valid = true;
		if (node.left != null) valid = valid && node.left.data < node.data;
		if (node.right != null) valid = valid && node.right.data < node.data;
		return valid && binarySearchTree(node.left) && binarySearchTree(node.right);
	}
	
	public void test() {
		Node root = new Node(40);
		root.left = new Node(20);
		root.right = new Node(70);
		root.left.left = new Node(10);
		root.left.right = new Node(30);
		root.right.left = new Node(60);
		root.right.right = new Node(90);
		List<Integer> data = new ArrayList<>();
		levelOrderTraversal(root);
		findByLevel(root, 3, data);
		System.out.println(levelWiseSum(root));
	}

	public static void main(final String[] args) {
		var tree = new BinaryTree();
		tree.test();
	}
}
