package main;

public class ServerData {

	public String host;
	public int port;
	public int cpuCount;
	
	public ServerData(String host, int port, int cpuCount) {
		this.host = host;
		this.port = port;
		this.cpuCount = cpuCount;
	}
	
	public static ServerData of(String host, int port) {
		return new ServerData(host, port, 0);
	}
	
	public static ServerData of(String host, int port, int cpuCount) {
		return new ServerData(host, port, cpuCount);
	}
}
