package main;

import java.util.Map;
import java.util.StringJoiner;
import java.util.Map.Entry;

public class JSONUtils {
	public static String encode(Map<String, Object> map) {
		var joiner = new StringJoiner(",", "{", "}");
		for (Entry<String, Object> elem: map.entrySet()) {
			String key = elem.getKey();
			Object val = elem.getValue();
			String valStr;
			if (val instanceof Number) valStr = val.toString();
			else valStr = '"' + escape(val.toString()) + '"';
			joiner.add("\"" + escape(key) + "\":" + valStr);
		}
		return joiner.toString();
	}

	public static Long extractLong(String json, String field) {
		String pattern = "\"" + field + "\":";
		int idx = json.indexOf(pattern);
		if (idx == -1) return null;
		idx += pattern.length();
		int end = idx;
		while (end < json.length() && (Character.isDigit(json.charAt(end)) || json.charAt(end) == '-'))
			end++;
		String num = json.substring(idx, end);
		try {
			return Long.parseLong(num);
		} catch (Exception e) {
			return null;
		}
	}
	
	public static String escape(String s) {
		return s.replace("\\", "\\\\").replace("\"", "\\\"");
	}
}
