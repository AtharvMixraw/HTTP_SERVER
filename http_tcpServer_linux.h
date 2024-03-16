#ifndef INCLUDED_HTTP_TCPSERVER_LINUX
#define INCLUDED_HTTP_TCPSERVER_LINUX

#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string>

using namespace std;

namespace http {
    class TcpServer{
        public :
            TcpServer(string ip_address, int port);
            ~TcpServer();
        private:
            string m_ip_address;
            int m_port;
            int m_socket;
            int m_new_socket;
            long m_incomingMessage;
            struct sockaddr_in m_socketAddress;
            unsigned int m_socketAdress_len;
            string m_serverMessage;

            int startServer();
            void closeServer();
            void acceptConnection(int &new_socket);
            string buildResponse();
            void sendResponse();

    };
}
#endif