package main;

import redis.clients.jedis.Jedis;

public class Main {
	public static void main(String[] args) throws Exception {
		try (Jedis jedis = new Jedis("localhost", 65)) {
			
		}
		var limiter = new TokenBucketRedis(null, 0, 0);
		
	}
}
