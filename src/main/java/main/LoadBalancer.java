package main;

import java.util.ArrayList;
import java.util.List;

public class LoadBalancer {

	public static final int ROUND_ROBIN = 1;
	public static final int WT_ROUND_ROBIN = 2;
	public static final int IP_HASH = 3;
	public static final int LEAST_CONN = 4;
	public static final int WT_LEAST_CONN = 5;
	public static final int LEAST_RESP_TIME = 6;
	public static final int RESOURCE = 7;
	
	private List<ServerData> servers = new ArrayList<>();
	private int algoKind;
	
	public LoadBalancer(int algoKind) {
		this.algoKind = algoKind;
	}
	
	public void addServer(ServerData serverData) {
		
	}
	
	public void removeServer(ServerData serverData) {
		
	}
	
	
}
