package main;

public class Error {
	public static void fatal(String messge) {
		System.out.println("ERROR: " + messge);
		System.exit(1);
	}
	
	public static void error(String messge) {
		System.out.println("ERROR: " + messge);
		System.exit(1);
	}
	
	public static void fatal(String format, Object ...args) {
		System.err.printf("ERROR: ");
		System.err.printf(format, args);
		System.err.printf("\n");
		System.exit(0);
	}
}
