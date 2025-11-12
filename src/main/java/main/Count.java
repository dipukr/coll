package main;

import static java.nio.charset.StandardCharsets.ISO_8859_1;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveTask;
import java.util.function.Predicate;

public class Count extends RecursiveTask<Long> {
	private File file;
	private Predicate<String> filter;

	public Count(File file, Predicate<String> filter) {
		this.file = file;
		this.filter = filter;
	}

	@Override
	public Long compute() {
		if (file.isFile() && filter.test(file.getName())) {
			try {
				return Files.lines(file.toPath(), ISO_8859_1).count();
			} catch (IOException e) {
				return 0L;
			}
		} else if (file.isDirectory()) {
			List<Count> subTasks = new ArrayList<>();
			for (File elem: file.listFiles()) {
				Count task = new Count(elem, filter);
				task.fork();
				subTasks.add(task);
			}
			long total = 0;
			for (Count task: subTasks)
				total += task.join();
			return total;
		} else return 0L;
	}

	public static void main(String[] args) {
		File root = new File(".");
		Predicate<String> filter = null;
		if (args.length == 0) filter = arg -> true;
		else filter = arg -> arg.endsWith(args[0]);
		ForkJoinPool pool = new ForkJoinPool();
		Count task = new Count(root, filter);
		long lines = pool.invoke(task);
		System.out.printf("Total lines: %d%n", lines);
		pool.close();
	}
}
