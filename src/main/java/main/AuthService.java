package main;

public class AuthService {

	private static final AuthService INSTANCE = new AuthService();
	
	private UserDAO userDAO = new UserDAO();

	public boolean register(String username, String password) {
		if (userDAO.find(username) != null) {
			System.out.println("User already exists.");
			return false;
		}
		User user = new User(username, password);
		userDAO.save(user);
		return true;
	}

	public String login(String username, String password) {
		User user = userDAO.find(username);
		if (user != null && user.getPassword().equals(password))
			return JwtUtils.generateToken(username);
		return null;
	}
	
	public boolean verify(String token) {
		return JwtUtils.verifyToken(token);
	}
	
	public static AuthService getInstance() {
		return INSTANCE;
	}
}
