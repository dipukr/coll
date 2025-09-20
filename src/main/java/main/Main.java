package main;

public class Main {
	public static void main(String[] args) throws Exception {
		HTTPServer server = new HTTPServer();
		server.register("GET", "/hello", request -> {
			String name = request.queryParams.getOrDefault("name", "world");
			String body = "Hello, " + name + "!";
			return Response.builder()
					.statusCode(200)
					.reasonPhrase("OK")
					.header("Content-Type", "text/plain; charset=utf-8")
					.body(body)
					.build();
		});
		server.start();
	}
}
