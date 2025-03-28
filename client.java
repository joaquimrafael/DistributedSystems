/*Laboratorio de Computacao Distribuida
Joaquim Rafael Mariano Prieto Pereira - 10408805
Exercicio: Atv. Socket Calc */

import java.io.*;
import java.net.*;

public class Client {

	public static void main(String[] args) {
		String serverAddres = "127.0.0.1"; // loopback
		int port = 8080;
		
		try(Socket socket = new Socket(serverAddres, port);
			PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
	        BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
	        BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in))) {
			
				System.out.println("Type your operation following the pattern: n1 operator n2");
				String outputUser = stdIn.readLine();
				
				
				out.println(outputUser);
				
				String response = in.readLine();
				System.out.println("Server response: "+ response);
		}catch (UnknownHostException  e) {
			System.err.println("Unknown Host: "+ e.getMessage());
		}catch (IOException e) {
			System.err.println("IO error: "+ e.getMessage());
		}

	}
}