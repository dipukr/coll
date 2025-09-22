package main;

import redis.clients.jedis.Jedis;

public class Redis {
	public static void main(String[] args) throws Exception {
		Jedis jedis = new Jedis("localhost", 80);
		String key = "counter";
		int val = 100;
		jedis.set(key, String.valueOf(val));
	}
}
