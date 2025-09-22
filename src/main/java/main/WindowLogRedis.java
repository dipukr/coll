package main;

import redis.clients.jedis.Jedis;

public class WindowLogRedis {
	
	private Jedis redis;
	
	public WindowLogRedis(Jedis redis) {
		this.redis = redis;
	}
	
	public boolean isAllowed(String clientId) {
		return false;
	}
}
