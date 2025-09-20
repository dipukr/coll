package main;

import redis.clients.jedis.Jedis;
import redis.clients.jedis.Transaction;

public class TokenBucketRedis {
	
	private Jedis redis;
	private int bucketCapacity;
	private double refillRate;
	
	public TokenBucketRedis(Jedis redis, int bucketCapacity, double refillRate) {
		this.redis = redis;
		this.bucketCapacity = bucketCapacity;
		this.refillRate = refillRate;
	}
	
	public boolean isAllowed(String clientId) {
		String keyCount = "rate_limit:" + clientId + ":count";
		String keyLastRefill = 	"rate_limit:" + clientId + "refillRate";
		Transaction transaction = redis.multi();
		transaction.get(keyLastRefill);
		transaction.get(keyCount);
		var results = transaction.exec();
		long currentTime = System.currentTimeMillis();
		long lastRefillTime = CommonUtils.getLong(results, 0, currentTime);
		int tokenCount = CommonUtils.getInt(results, 1, bucketCapacity);
		long elapsedTimeMs = currentTime - lastRefillTime;
		double elapsedTimeSecs = elapsedTimeMs / 1000.0;
		int tokensToAdd = (int) (elapsedTimeSecs * refillRate);
		tokenCount = Math.min(bucketCapacity, tokenCount + tokensToAdd);
		boolean isAllowed = tokenCount > 0;
		if (isAllowed) tokenCount -= 1;
		transaction = redis.multi();
		transaction.set(keyLastRefill, String.valueOf(currentTime));
		transaction.set(keyCount, String.valueOf(tokenCount));
		transaction.exec();
		return isAllowed;
	}
}
