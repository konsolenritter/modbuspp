#ifndef MODBUSPP_MODBUS_H
#define MODBUSPP_MODBUS_H


#include <string>
#include <sys/socket.h>


#include "util.h"

namespace Modbus {
    static int counter_ = 0;
    namespace Function_Code {
        enum {
            READ_COILS = 0x01,
            READ_INPUT_BITS = 0x02,
            READ_REGS = 0x03,
            READ_INPUT_REGS = 0x04,
            WRITE_COIL = 0x05,
            WRITE_REG = 0x06,
            WRITE_COILS = 0x0F,
            WRITE_REGS = 0x10,
        };
    };

    namespace Error_Code {
        enum {
            EX_ILLEGAL_FUNCTION = 0x01, // Function Code not Supported
            EX_ILLEGAL_ADDRESS = 0x02, // Output Address not exists
            EX_ILLEGAL_VALUE = 0x03, // Output Value not in Range
            EX_SERVER_FAILURE = 0x04, // Slave Deive Fails to process request
            EX_ACKNOWLEDGE = 0x05, // Service Need Long Time to Execute
            EX_SERVER_BUSY = 0x06, // Server Was Unable to Accept MB Request PDU
            EX_GATEWAY_PROBLEMP = 0x0A, // Gateway Path not Available
            EX_GATEWYA_PROBLEMF = 0x0B, // Target Device Failed to Response
        };
    }



    class Modbus
    {
    public:
        Modbus():host_("192.0.0.1"), port_(502){};
        Modbus(std::string host): host_(host), port_(502){};
        Modbus(std::string host, uint16_t port):host_(host), port_(port){};
        ~Modbus();

        std::string getHost() {return host_;};
        uint16_t getPort() {return port_;};
        bool checkConnection() {return connected;};
        void resetMsgId() {msg_id_counter = 0;};
        int  getSlaveId() {return slave_id;};
        int getId() {return id;};


        void setHost(std::string host){host_ = host; connected = false;};
        void setPort(int port){port_ = port; connected = false;};
        void setSlaveId(int id){slave_id = id;};


        void connect();


    private:
        std::string host_;
        uint16_t port_;

        bool connected;
        int msg_id_counter;
        int slave_id;
        int id;
    };




    typedef std::shared_ptr<Modbus::Modbus> ModbusPtr;
    inline ModbusPtr getModbusPtr(std::string host, uint16_t port)
    {
        return std::make_shared<Modbus::Modbus>(host, port);
    };

    inline ModbusPtr getModbusPtr(std::string host)
    {
        return getModbusPtr(host, 502);
    };

    inline ModbusPtr getModbusPtr()
    {
        return getModbusPtr("192.0.0.1", 502);
    };
}






#endif //MODBUSPP_MODBUS_H
