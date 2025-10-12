package main;

import java.security.MessageDigest;
import java.util.SortedMap;
import java.util.TreeMap;

public class ConsistentHash {
	
	private TreeMap<Long, String> ring = new TreeMap<>();
	private int replicaCount;
	private MessageDigest md;
	
	public ConsistentHash(int replicaCount) {
		this.replicaCount = replicaCount;
		this.md = Commons.getSha256();
	}
	
	public void addServer(String server) {
		for (int i = 0; i < replicaCount; i++) {
			long hash = hash(server + ":" + i);
			ring.put(hash, server);
		}
	}
	
	public void removeServer(String server) {
		for (int i = 0; i < replicaCount; i++) {
			long hash = hash(server + ":" + i);
			ring.remove(hash, server);
		}
	}
	
	public String getServer(String key) {
		if (ring.isEmpty()) return null;
		long hash = hash(key);
		if (!ring.containsKey(hash)) {
			SortedMap<Long, String> tailMap = ring.tailMap(hash);
			hash = tailMap.isEmpty() ? ring.firstKey() : tailMap.firstKey();
		}
		return ring.get(hash);
	}
	
	public long hash(String key) {
		md.reset();
		md.update(key.getBytes());
		byte[] digest = md.digest();
		long hash = ((long) (digest[0] & 0xFF) << 56) |
			((long) (digest[0] & 0xFF) << 48) |
			((long) (digest[0] & 0xFF) << 40) |
			((long) (digest[0] & 0xFF) << 32) |
			((long) (digest[0] & 0xFF) << 24) |
			((long) (digest[0] & 0xFF) << 16) |
			((long) (digest[0] & 0xFF) << 8) |
			((long) (digest[0] & 0xFF));
		return hash;
	}
}
