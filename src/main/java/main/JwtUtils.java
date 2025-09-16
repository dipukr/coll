package main;

import java.nio.charset.StandardCharsets;
import java.util.Arrays;
import java.util.Base64;
import java.util.LinkedHashMap;
import java.util.Map;
import javax.crypto.Mac;
import javax.crypto.spec.SecretKeySpec;

public class JwtUtils {

	private static final String JWT_SECRET = "ReplaceThisWithAReallySecretKey123!";
	private static final String HMAC_ALGO = "HmacSHA256";

	public static String generateToken(String subject) {
		long now = System.currentTimeMillis() / 1000L;
		Map<String, Object> header = new LinkedHashMap<>();
		header.put("alg", "HS256");
		header.put("typ", "JWT");

		Map<String, Object> payload = new LinkedHashMap<>();
		payload.put("sub", subject);
		payload.put("iat", now);
		payload.put("exp", now + 60);

		String headerB64 = base64UrlEncode(JSONUtils.encode(header).getBytes(StandardCharsets.UTF_8));
		String payloadB64 = base64UrlEncode(JSONUtils.encode(payload).getBytes(StandardCharsets.UTF_8));

		String signingInput = headerB64 + "." + payloadB64;
		byte[] sig = hmacSha256(JWT_SECRET.getBytes(StandardCharsets.UTF_8),
				signingInput.getBytes(StandardCharsets.UTF_8));
		String sigB64 = base64UrlEncode(sig);
		return signingInput + "." + sigB64;
	}

	public static boolean verifyToken(String token) {
		String[] parts = token.split("\\.");
		if (parts.length != 3) return false;
		
		String headerB64 = parts[0];
		String payloadB64 = parts[1];
		String signatureB64 = parts[2];

		String signingInput = headerB64 + "." + payloadB64;
		byte[] expectedSig = hmacSha256(JWT_SECRET.getBytes(StandardCharsets.UTF_8),
				signingInput.getBytes(StandardCharsets.UTF_8));
		byte[] providedSig = base64UrlDecode(signatureB64);

		if (!Arrays.equals(expectedSig, providedSig))
			return false;

		String payloadJson = new String(base64UrlDecode(payloadB64), StandardCharsets.UTF_8);
		Long exp = JSONUtils.extractLong(payloadJson, "exp");
		long now = System.currentTimeMillis() / 1000L;
		if (exp == null) return false;
		return now < exp;
	}
	
	public static String base64UrlEncode(byte[] data) {
		return Base64.getUrlEncoder().withoutPadding().encodeToString(data);
	}

	public static byte[] base64UrlDecode(String s) {
		return Base64.getUrlDecoder().decode(s);
	}

	public static byte[] hmacSha256(byte[] key, byte[] msg) {
		try {
			Mac mac = Mac.getInstance(HMAC_ALGO);
			mac.init(new SecretKeySpec(key, HMAC_ALGO));
			return mac.doFinal(msg);
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}
}
