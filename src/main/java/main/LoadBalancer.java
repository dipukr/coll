package main;

import java.util.ArrayList;
import java.util.List;

public class LoadBalancer {

	private List<ServerDetails> servers = new ArrayList<>();
	
	public LoadBalancer(List<ServerDetails> servers) {
		this.servers = servers;
	}
	
	
}
