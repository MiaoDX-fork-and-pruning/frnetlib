#include <frnetlib/TcpSocket.h>
#include <frnetlib/TcpListener.h>
#include <iostream>

using namespace std;



int client_round(fr::TcpSocket& socket)
{
	
	string send_str = "Hello there, I am," + to_string((float)1.2) + ",years old";

	cout << "CLIENT:Going to send str: " << send_str << endl;
	

	if (socket.send_raw(send_str.c_str(), send_str.length()) != fr::Socket::Success)
	{
		//Failed to send packet
		cout << "CLIENT:Seems got something wrong when sending" << endl;
		return -1;
	}

	cout << "CLIENT:Going to receive ..." << endl;

	size_t received_size;
	char recv_str_buffer[RECV_CHUNK_SIZE];

	if (socket.receive_raw(recv_str_buffer, RECV_CHUNK_SIZE, received_size) != fr::Socket::Success)
	{
		cout << "CLIENT:seems got something wrong when receiving" << endl;
		return -2;
	}

	string recv_str(recv_str_buffer);
	recv_str.resize(received_size);

	

	cout << "CLIENT:We got from server:" << recv_str << ", size: " << received_size << endl;

	cout << "CLIENT:round finished" << endl;
	cout << endl << endl << endl << endl;
	return 0;
}


int main()
{
	fr::TcpSocket socket;

	string server_ip = "127.0.0.1";
	string server_port = "8081";

	if (socket.connect(server_ip, server_port) != fr::Socket::Success)
	{
		//Failed to connect
		cout << "CLIENT:it seem that the socket can be accessed or there is no such socket at all" << endl;
		socket.close_socket();
		return -1;
	}


	string op_str;
	int rtn = 0;

	while (true) {
		cout << "CLIENT:choose what you want to do, `c` for `continue`, `q` for `quit`:" << endl;
		cin >> op_str; // count for possible mutiple char input

		if (op_str.length() > 1) {
			cout << "CLIENT:Seems that you input more than one char, plese check your input" << endl;
			continue;
		}

		char op = op_str[0];
		switch (op) {
		case 'c':
			cout << "continue" << endl;
			rtn = client_round(socket);
			break;
		case 'q':
			break;
		}

		if (op == 'q')
			break;
		if (rtn != 0)
			break;
	}

	socket.close_socket();
	cout << "all done, bye" << endl;
}

