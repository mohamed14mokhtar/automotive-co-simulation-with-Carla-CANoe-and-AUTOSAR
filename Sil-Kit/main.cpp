#include <silkit/SilKit.hpp>
#include <silkit/config/IParticipantConfiguration.hpp>
#include <silkit/services/can/CanDatatypes.hpp>
#include <silkit/services/can/ICanController.hpp>
#include <silkit/services/orchestration/ILifecycleService.hpp>

#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#ifdef _WIN32
#include <windows.h>
#endif

using namespace SilKit;
using namespace SilKit::Services::Can;
using namespace SilKit::Services::Orchestration;

// Global variables
SOCKET gSock = INVALID_SOCKET;
ICanController* gCanController = nullptr;

// Warning config
const float SPEED_LIMIT = 30.0f;  // km/h

bool connectToCarla()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    gSock = socket(AF_INET, SOCK_STREAM, 0);
    if (gSock == INVALID_SOCKET)
    {
        std::cerr << "Socket creation failed!" << std::endl;
        return false;
    }

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(5001);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    std::cout << "Connecting to CARLA script on 127.0.0.1:5001..." << std::endl;

    if (connect(gSock, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
    {
        std::cerr << "Connection to CARLA failed!" << std::endl;
        closesocket(gSock);
        gSock = INVALID_SOCKET;
        return false;
    }

    std::cout << "Connected to CARLA script!" << std::endl;
    return true;
}

void sendSpeedToCarla(float speed)
{
    if (gSock != INVALID_SOCKET)
    {
        std::string msg = std::to_string(speed) + "\n";
        send(gSock, msg.c_str(), msg.length(), 0);
        std::cout << "Sent speed to CARLA: " << speed << " km/h" << std::endl;
    }
}

// ===== Send CAN Frame to CANoe =====
void sendCanFrame(uint32_t canId, const std::vector<uint8_t>& data)
{
    if (gCanController != nullptr)
    {
        CanFrame frame;
        frame.canId = canId;
        frame.dataField = SilKit::Util::Span<const uint8_t>(data.data(), data.size());
        frame.dlc = static_cast<uint16_t>(data.size());
        frame.flags = {};

        gCanController->SendFrame(frame);
    }
}

// ===== Send Warning to CANoe =====
// CAN ID: 0x3AC
// Byte 0: Warning (0 = OK, 1 = OVERSPEED)
// Byte 1: Current speed (raw)
// Byte 2: Speed limit (raw)
void sendWarningToCanoe(float speed)
{
    uint8_t warning = 0x00;

    if (speed > SPEED_LIMIT)
    {
        warning = 0x01;  // OVERSPEED
        std::cout << "⚠️  WARNING: Speed " << speed 
                  << " km/h exceeds limit " << SPEED_LIMIT << " km/h!" << std::endl;
    }
    else
    {
        warning = 0x00;  // OK
        std::cout << "✅ Speed OK: " << speed << " km/h" << std::endl;
    }

    std::vector<uint8_t> data = {
        warning,                                          // Byte 0: Warning flag
    };

    sendCanFrame(0x3AC, data);
}

void cleanup()
{
    if (gSock != INVALID_SOCKET)
    {
        closesocket(gSock);
    }
    WSACleanup();
}

int main()
{
    try
    {
        // Connect to CARLA first
        if (!connectToCarla())
        {
            std::cerr << "Failed to connect to CARLA. Exiting." << std::endl;
            return 1;
        }

        auto config = SilKit::Config::ParticipantConfigurationFromFile("ParticipantConfig.yaml");

        std::string participantName = "CppSpeedReader";
#ifdef _WIN32
        participantName += "_" + std::to_string(GetCurrentProcessId());
#endif

        auto participant =
            SilKit::CreateParticipant(config, participantName, "silkit://localhost:8500");

        auto* lifecycleService = participant->CreateLifecycleService({OperationMode::Autonomous});
        auto* canController = participant->CreateCanController("CanController1", "CAN1");

        // Store globally
        gCanController = canController;

        canController->AddFrameHandler(
            [](ICanController*, const CanFrameEvent& event)
            {
                if (event.frame.canId == 0x3AB && event.frame.dataField.size() >= 1)
                {
                    float speed = static_cast<float>(event.frame.dataField[0]);
                    std::cout << "Received Speed = " << speed << std::endl;
                    
                    // Check speed and send warning to CANoe
                    sendWarningToCanoe(speed);

                    speed = speed / 3.0f;

                    // Send speed to CARLA
                    sendSpeedToCarla(speed);

                    
                }
            });

        lifecycleService->SetCommunicationReadyHandler([&]() {
            canController->SetBaudRate(500000, 2000000, 2000000);
            canController->Start();
        });

        std::cout << "========================================" << std::endl;
        std::cout << "Speed Limit: " << SPEED_LIMIT << " km/h" << std::endl;
        std::cout << "Receive CAN: 0x3AB (Speed from CANoe)" << std::endl;
        std::cout << "Send CAN:    0x3AC (Warning to CANoe)" << std::endl;
        std::cout << "========================================" << std::endl;

        lifecycleService->StartLifecycle().get();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        cleanup();
        return 1;
    }

    cleanup();
    return 0;
}


// cmake .. -G "Visual Studio 18 2026" -A Win32
// cmake --build . --config Release