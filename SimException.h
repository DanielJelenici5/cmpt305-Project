#include <exception>
#include <string>

using namespace std;

class SimException : public exception {
    private:
        std::string m_message;
    public:
        SimException(const string& message) : m_message(message) {}

        const char* what() const noexcept override {
            return m_message.c_str();
        }
};