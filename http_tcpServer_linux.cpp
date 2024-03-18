#include <http_tcpServer_linux.h>

#include <iostream>
#include <sstream>
#include <unistd.h>
using namespace std;

namespace{

    const int BUFFER_SIZE = 30720;

    void log(const string &message){
        cout<<message<<endl;
    }
    void exitWithError(const string &errorMessage){
        log("Error: " + errorMessage);
        exit(1);
    }
}

namespace http
{
    TcpServer::TcpServer(std::string ip_address, int port) : m_ip_address(ip_address), m_port(port), m_socket(), m_new_socket(),
                                                             m_incomingMessage(),
                                                             m_socketAddress(), m_socketAddress_len(sizeof(m_socketAddress)),
                                                             m_serverMessage(buildResponse())
        {
            m_socketAddress.sin_family = AF_INET; //sets the address family to IPv4
            m_socketAddress.sin_port = htons(m_port); //converts the host byte order to network byte order
            m_socketAddress.sin_addr.s_addr = inet_addr(m_ip_address.c_str()); // converts the IP address in string format to binary format and then store it server address structure

            if(startServer() != 0){
                ostringstream ss;
                 ss<< "Failed to start a server with PORT: " << ntons(m_socketAddress.sin_port);
                 log(ss.str());
            }

        }

    TcpServer::~TcpServer(){
        closeServer();
    }

    int TcpServer :: startServer(){
        m_socket = socket(AF_INET, SOCK_STREAM, 0);
        if(m_socket < 0){
            exitWithError("Cannot create socket");
            return 1;
        }

        if (bind(m_socket, (sockaddr *)&m_socketAddress, m_socketAddress_len) < 0)
        {
            exitWithError("Cannot connect socket to address");
            return 1;
        }

        return 0;
    }

    void TcpServer :: closeServer(){
        close(m_socket);
        close(m_new_socket);
        exit(0);
    }

    void TcpServer :: startListen(){
        if(listen(m_socket, 20) < 0){
            exitWithError("Socket listen failed");
        }
    }

} // namespace http
