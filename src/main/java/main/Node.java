package main;

public class Node {
	
	public String host;
	public int port;
	public int cpuCount;
	
	public Node(String host, int port, int cpuCount) {
		this.host = host;
		this.port = port;
		this.cpuCount = cpuCount;
	}
	
	public static Node of(String host, int port, int cpuCount) {
		return new Node(host, port, cpuCount);
	}
}
