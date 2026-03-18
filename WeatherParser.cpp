#include <iostream>
#include <string>
#include <map>

class WeatherSentinel {
public:
    // This "Map" links the 3-letter NOAA code to a human-readable name and a priority level
    std::map<std::string, std::string> alertLevels = {
        {"TOR", "TORNADO WARNING - RED ALERT"},
        {"SVR", "SEVERE THUNDERSTORM - YELLOW ALERT"},
        {"FFW", "FLASH FLOOD - YELLOW ALERT"},
        {"RWT", "REQUIRED WEEKLY TEST - GREEN"}
    };

    void processSignal(std::string rawSignal) {
        // Real SAME signals have the event code starting at the 10th character
        // Example: ZCZC-WXR-TOR-022017
        std::string eventCode = rawSignal.substr(9, 3);

        if (alertLevels.count(eventCode)) {
            std::cout << "MESSAGE RECEIVED: " << alertLevels[eventCode] << std::endl;
        } else {
            std::cout << "UNKNOWN SIGNAL: " << eventCode << " - STANDING BY." << std::endl;
        }
    }
};

int main() {
    WeatherSentinel sentinel;

    // Simulating a Tornado Warning signal from the radio
    std::string mockRadioInput = "ZCZC-WXR-TOR-022017";
    
    std::cout << "--- Sentinel System Booted ---" << std::endl;
    sentinel.processSignal(mockRadioInput);

    return 0;
}
