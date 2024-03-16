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
    TcpServer::TcpServer(string ip_address, int port)
        : m_ip_address(ip_address), m_port(port), m_socket(),
          m_new_socket(), m_incomingMessage(), m_socketAddress(),
          m_socketAdress_len(sizeof(m_socketAddress),
          m_serverMessage(buildResponse());
        {
            startServer();
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
        return 0;
    }

    void TcpServer :: closeServer(){
        close(m_socket);
        close(m_new_socket);
        exit(0);
    }
} // namespace http
