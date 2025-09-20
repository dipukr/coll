package main;

public class TokenBucket {

	private int maxTokens;
	private int currTokens;
	private int refillAmount;
	private int refillInterval;
	private int lastRefillTime;
	
	public TokenBucket(int maxTokens, int currTokens, int refillAmount, int refillInterval) {
		this.maxTokens = maxTokens;
		this.currTokens = currTokens;
		this.refillAmount = refillAmount;
		this.refillInterval = refillInterval;
		this.lastRefillTime = currentTimeSeconds();
	}

	public boolean processRequest() {
		refillBucket();
		if (!empty()) {
			currTokens -= 1;
			return true;
		}
		return false;
	}
	
	public void refillBucket() {
		int now = currentTimeSeconds();
		int timeElapsed = lastRefillTime - now;
		int refillCycle = timeElapsed / refillInterval;
		currTokens = Math.min(maxTokens, currTokens + refillCycle * refillAmount);
		lastRefillTime = now - (timeElapsed % refillInterval);
	}

	public boolean empty() {
		return currTokens == 0;
	}
	
	public int currentTimeSeconds() {
		long now = System.currentTimeMillis();
		return (int) (now / 1000);
	}
}
