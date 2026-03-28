#include <iostream>
#include <string>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main()
{
    // Initialize Winsock
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Create and connect socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(5001);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    std::cout << "Connecting..." << std::endl;
    connect(sock, (sockaddr*)&server, sizeof(server));
    std::cout << "Connected!" << std::endl;

    // Send speed loop
    float speed;
    while (true)
    {
        std::cout << "Enter speed (km/h): ";
        std::cin >> speed;

        std::string msg = std::to_string(speed) + "\n";
        send(sock, msg.c_str(), msg.length(), 0);

        std::cout << "Sent: " << speed << " km/h" << std::endl;
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}