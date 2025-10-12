package main;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class ChatServer {

	private int port;
	
	public ChatServer(int port) {
		this.port = port;
	}
	
	public void start() {
		try (ServerSocket serverSocket = new ServerSocket(port)) {
			while (!serverSocket.isClosed()) {
				Socket clientSocket = serverSocket.accept();
				System.out.println("A new client has connected!");
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public void shutdown() {
		
	}
	
	public class ClientHandler implements Runnable {
		private Socket socket;
		private String clientName;
		
		public ClientHandler(Socket socket) {
			this.socket = socket;
		}

		@Override
		public void run() {
			try {
				InputStream inputStream = socket.getInputStream();
				OutputStream outputStream = socket.getOutputStream();
			} catch (IOException e) {
				e.printStackTrace();
			}
			
		}
	}
}
