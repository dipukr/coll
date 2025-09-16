package main;

import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

public class Router {
	
	private final Map<String, Handler> routes = new HashMap<>();

	public Router get(String path, Handler h) {
		routes.put("GET " + path, h);
		return this;
	}

	public Router post(String path, Handler h) {
		routes.put("POST " + path, h);
		return this;
	}

	public Optional<Handler> match(String method, String path) {
		return Optional.ofNullable(routes.get(method + " " + path));
	}
}
