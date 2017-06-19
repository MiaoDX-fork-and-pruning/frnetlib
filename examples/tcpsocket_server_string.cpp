#include <frnetlib/TcpSocket.h>
#include <frnetlib/TcpListener.h>
#include <iostream>

using namespace std;

int main(){
    //fr::HttpSocket<fr::TcpSocket> client; //fr::TcpSocket for HTTP. fr::SSLSocket for HTTPS.

	fr::TcpSocket client;
	

    fr::TcpListener listener;             //Use an fr::SSLListener if HTTPS.

	string port = "8081";

    //Bind to a port
    if(listener.listen(port) != fr::Socket::Success)
    {
		cout << "LISTENER:Failed to bind to port, going to shutdown" << endl;
		listener.shutdown();
		return -1;
    }

	cout << "LISTENER:Listener is listening on port " << port << " ..." << endl;

	while (true)
	{
		cout << "LISTENER:Waiting for a new connection ..." << endl;
		//Accept a new connection

		fr::Socket::Status status;


		if (listener.accept(client) != fr::Socket::Success)
		{
			cout << "LISTENER:Failed to accept client, shutdown" << endl;
			break;
		}

		while (true) // infinite loop for the communication
		{
			try
			{							
				size_t received_size;

				//char recv_str_buffer[RECV_CHUNK_SIZE];
				char* recv_str_buffer = new char[RECV_CHUNK_SIZE];
				
				status = client.receive_raw(recv_str_buffer, RECV_CHUNK_SIZE, received_size);

				if (status != fr::Socket::Success ) {
					cout << "LISTENER:Failed to receive request, we got status: " << status << endl;
					break;
				}

				string recv_str(recv_str_buffer);
				recv_str.resize(received_size);				

				cout << "LISTENER:We got from client:" << recv_str << ", size is: "<< received_size << endl;

				status = client.send_raw(recv_str.c_str(), recv_str.length());
				if (status != fr::Socket::Success) {
					cout << "LISTENER:Seems got something wrong when sending, we got status: " << status << endl;
					break;
				}

				cout << "LISTENER:Send OK" << endl;

			}
			catch (const std::exception& e)
			{
				cout << "ERROR: " << e.what() << endl;
				break;
			}
		} // inner while

		cout << "LISTENER:Seems that the client stop the connection, just destroy current connection and wait for another" << endl;
		//Close connection
		client.close_socket();

	}// out while

	cout << "Should not got there !!" << endl;
	listener.shutdown();
	return 0;
}

