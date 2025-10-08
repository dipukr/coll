package main;

import java.security.MessageDigest;
import java.util.List;

public class CommonUtils {
	public static MessageDigest getSha256() {
		try {
			return MessageDigest.getInstance("SHA-256");
		} catch (Exception e) {return null;}
	}
	
	public static long getLong(List<Object> results, int i, long defval) {
		return results.get(i) != null ? Long.parseLong((String) results.get(i)) : defval;
	}
	
	public static int getInt(List<Object> results, int i, int defval) {
		return results.get(i) != null ? Integer.parseInt((String) results.get(i)) : defval;
	}
}
