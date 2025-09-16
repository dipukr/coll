package main;

import java.util.concurrent.TimeUnit;

public class TokenBucket {

	private int maxTokens;
	private int tokens;
	private int refillAmount;
	private int refillInterval;
	private int lastRefillTime;
	
	public TokenBucket(int maxTokens, int tokens, int refillAmount, int refillInterval) {
		this.maxTokens = maxTokens;
		this.tokens = tokens;
		this.refillAmount = refillAmount;
		this.refillInterval = refillInterval;
		this.lastRefillTime = currentTimeSeconds();
	}

	public boolean processRequest() {
		refillBucket();
		if (!empty()) {
			tokens -= 1;
			return true;
		}
		return false;
	}
	
	public void refillBucket() {
		int now = currentTimeSeconds();
		int timeElapsed = lastRefillTime - now;
		int refillCycle = timeElapsed / refillInterval;
		tokens = Math.min(maxTokens, tokens + refillCycle * refillAmount);
		lastRefillTime = now - (timeElapsed % refillInterval);
	}

	public boolean empty() {
		return tokens == 0;
	}
	
	public int currentTimeSeconds() {
		long now = System.currentTimeMillis();
		return (int) TimeUnit.SECONDS.convert(now, TimeUnit.MILLISECONDS);
	}


	public static void main(String[] args) throws Exception {
		TokenBucket limiter = new TokenBucket(5, 5, 2, 10);
		for (int i = 1; i <= 15; i++) {
			if (limiter.processRequest()) {
				System.out.printf("[%d] Processed.\n", i);
			} else System.out.printf("[%d] Rate limited.\n", i);
			Thread.sleep(1000);
		}
	}
}
