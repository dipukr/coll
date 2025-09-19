package main;

import java.security.MessageDigest;

public class CommonUtils {
	public static MessageDigest getSha256() {
		try {
			return MessageDigest.getInstance("SHA-256");
		} catch (Exception e) {
			return null;
		}
	}
}
