#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QString>

enum class IncomingMailProtocol {
    POP3,
    IMAP4
};

class Configuration
{
public:
    Configuration();

    QString getAddress() const;
    void setAddress(const QString &value);

    QString getPassword() const;
    void setPassword(const QString &value);

    QString getInUsername() const;
    void setInUsername(const QString &value);

    QString getInPassword() const;
    void setInPassword(const QString &value);

    IncomingMailProtocol getInProtocol() const;
    void setInProtocol(const IncomingMailProtocol &value);

    QString getInServer() const;
    void setInServer(const QString &value);

    uint32_t getInPort() const;
    void setInPort(const uint32_t &value);

    QString getOutUsername() const;
    void setOutUsername(const QString &value);

    QString getOutPassword() const;
    void setOutPassword(const QString &value);

    QString getOutServer() const;
    void setOutServer(const QString &value);

    uint32_t getOutPort() const;
    void setOutPort(const uint32_t &value);

    void loadDefaultData();
    QString getProtocolName(IncomingMailProtocol protocol);

private:
    QString address;
    QString password;

    QString inUsername;
    QString inPassword;
    IncomingMailProtocol inProtocol;
    QString inServer;
    uint32_t inPort;

    QString outUsername;
    QString outPassword;
    QString outServer;
    uint32_t outPort;

};

#endif // CONFIGURATION_H
