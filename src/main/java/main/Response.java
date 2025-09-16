package main;

import java.io.IOException;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;
import java.time.ZonedDateTime;
import java.time.format.DateTimeFormatter;
import java.util.LinkedHashMap;
import java.util.Map;

public class Response {
	
	private final OutputStream out;
	private int status = 200;
	private String reason = "OK";
	private final Map<String, String> headers = new LinkedHashMap<>();
	private byte[] body = new byte[0];

	public Response(OutputStream out) {
		this.out = out;
	}

	public Response status(int code, String reason) {
		this.status = code;
		this.reason = reason;
		return this;
	}

	public Response header(String name, String value) {
		headers.put(name, value);
		return this;
	}

	public Response text(String text) {
		this.body = text.getBytes(StandardCharsets.UTF_8);
		header("Content-Type", "text/plain; charset=utf-8");
		return this;
	}

	public void send() throws IOException {
		header("Date", DateTimeFormatter.RFC_1123_DATE_TIME.format(ZonedDateTime.now()));
		header("Server", "MiniHttpServer/1.0 (virtual-threads)");
		header("Connection", "close"); // one-request-per-connection
		header("Content-Length", Integer.toString(body.length));
		var writer = new StringBuilder();
		writer.append("HTTP/1.1 ").append(status).append(' ').append(reason).append("\r\n");
		for (var elem: headers.entrySet())
			writer.append(elem.getKey()).append(": ").append(elem.getValue()).append("\r\n");
		writer.append("\r\n");
		out.write(writer.toString().getBytes(StandardCharsets.UTF_8));
		out.write(body);
		out.flush();
	}
}
