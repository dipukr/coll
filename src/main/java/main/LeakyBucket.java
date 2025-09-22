package main;

public class LeakyBucket {
	
	private int capacity;
	private int leakRate;
	private int waterLevel;
	private int lastCheckedTime;
	
	public LeakyBucket(int capacity, int leakRate, int waterLevel) {
		this.capacity = capacity;
		this.leakRate = leakRate;
		this.waterLevel = waterLevel;
		this.lastCheckedTime = currentTimeSeconds();
	}

	public boolean processRequest() {
		leakWater();
		if (waterLevel < capacity) {
			waterLevel += 1;
			return true;
		}
		return false;
	}
	
	public void leakWater() {
		int now = currentTimeSeconds();
		int seconds = now - lastCheckedTime;
		int leakedWater = seconds * leakRate;
		waterLevel = Math.max(0, waterLevel - leakedWater);
		lastCheckedTime = now;
	}
	
	public int currentTimeSeconds() {
		long now = System.currentTimeMillis();
		return (int) (now / 1000);
	}
	
	public static void main(String[] args) throws Exception {
		var algo = new LeakyBucket(5, 1, 0);
		for (int i = 1; i <= 20; i++) {
			if (algo.processRequest())
				System.out.printf("%d: Processed.\n", i);
			else System.out.printf("%d: Rate limited.\n", i);
			if (i % 3 == 0) Thread.sleep(1000);
		}
	}
}
