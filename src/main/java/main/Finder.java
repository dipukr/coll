package main;

import java.io.IOException;
import java.nio.file.FileVisitOption;
import java.nio.file.FileVisitResult;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.SimpleFileVisitor;
import java.nio.file.attribute.BasicFileAttributes;
import java.util.EnumSet;
import java.util.Set;
import java.util.TreeSet;

public class Finder extends SimpleFileVisitor<Path> {
	private Set<Path> filePaths = new TreeSet<>();
		
	@Override
	public FileVisitResult visitFile(Path file, BasicFileAttributes attrs) {
		filePaths.add(file);
		return FileVisitResult.CONTINUE;
	}

	@Override
	public FileVisitResult preVisitDirectory(Path dir, BasicFileAttributes attrs) {
		filePaths.add(dir);
		return FileVisitResult.CONTINUE;
	}

	@Override
	public FileVisitResult visitFileFailed(Path file, IOException exc) {
		filePaths.add(file);
		return FileVisitResult.CONTINUE;
	}
	
	public Set<Path> getFilePaths() {
		return filePaths;
	}
	
	public static void main(String[] args) throws Exception {
		Path root = Path.of("/home/dkumar/");
		Finder finder = new Finder();
		Files.walkFileTree(root, EnumSet.of(FileVisitOption.FOLLOW_LINKS),
				Integer.MAX_VALUE, finder);
		System.out.println(finder.getFilePaths().size());
	}
}
