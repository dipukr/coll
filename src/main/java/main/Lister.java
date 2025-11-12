package main;

import java.nio.file.Files;
import java.nio.file.Path;
import java.util.TreeSet;
import java.util.stream.Stream;

public class Lister {
	public static void main(String[] args) throws Exception {
		Path root = Path.of(".");

		try (Stream<Path> stream = Files.walk(root)) {
			var files = new TreeSet<Path>();
			var dirs = new TreeSet<Path>();

			stream.forEach(path -> {
				if (Files.isDirectory(path))
					dirs.add(path.toAbsolutePath());
				else if (Files.isRegularFile(path))
					files.add(path.toAbsolutePath());
			});

			dirs.forEach(System.out::println);
			files.forEach(System.out::println);
			System.out.printf("Files: %d%n", files.size());
			System.out.printf("Folders: %d%n", dirs.size());
		}
	}
}
