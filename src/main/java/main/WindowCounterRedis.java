package main;

import redis.clients.jedis.Jedis;
import redis.clients.jedis.Transaction;

public class WindowCounterRedis {
	
	private Jedis redis;
	private int winSize;
	private int limit;
	
	public WindowCounterRedis(Jedis redis, int limit, int winSize) {
		this.redis = redis;
		this.limit = limit;
		this.winSize = winSize;
	}
	
	public boolean isAllowed(String clientId) {
		boolean isAllowed = true;
		String key = "rate_limit:" + clientId;
		Transaction transaction = redis.multi();
		String counterStr = redis.get(key);
		int counter = counterStr != null ? Integer.parseInt(counterStr) : 0;
		transaction.exec();
		return isAllowed;
	}
}
