#include "configuration.h"

Configuration::Configuration()
{
    loadDefaultData();
}

QString Configuration::getAddress() const
{
    return address;
}

void Configuration::setAddress(const QString &value)
{
    address = value;
}

QString Configuration::getPassword() const
{
    return password;
}

void Configuration::setPassword(const QString &value)
{
    password = value;
}

QString Configuration::getInUsername() const
{
    return inUsername;
}

void Configuration::setInUsername(const QString &value)
{
    inUsername = value;
}

QString Configuration::getInPassword() const
{
    return inPassword;
}

void Configuration::setInPassword(const QString &value)
{
    inPassword = value;
}

IncomingMailProtocol Configuration::getInProtocol() const
{
    return inProtocol;
}

void Configuration::setInProtocol(const IncomingMailProtocol &value)
{
    inProtocol = value;
}

QString Configuration::getInServer() const
{
    return inServer;
}

void Configuration::setInServer(const QString &value)
{
    inServer = value;
}

uint32_t Configuration::getInPort() const
{
    return inPort;
}

void Configuration::setInPort(const uint32_t &value)
{
    inPort = value;
}

QString Configuration::getOutUsername() const
{
    return outUsername;
}

void Configuration::setOutUsername(const QString &value)
{
    outUsername = value;
}

QString Configuration::getOutPassword() const
{
    return outPassword;
}

void Configuration::setOutPassword(const QString &value)
{
    outPassword = value;
}

QString Configuration::getOutServer() const
{
    return outServer;
}

void Configuration::setOutServer(const QString &value)
{
    outServer = value;
}

uint32_t Configuration::getOutPort() const
{
    return outPort;
}

void Configuration::setOutPort(const uint32_t &value)
{
    outPort = value;
}

void Configuration::loadDefaultData()
{
    address = "billgates@ejpyl.com";
    password = "r2d2";

    inUsername = "billgates";
    inPassword = "r2d2";
    inProtocol = IncomingMailProtocol::IMAP4;
    inServer = "mail.ejpyl.com";
    inPort = 993;

    outUsername = "billgates";
    outPassword = "r2d2";
    outServer = "mail.ejpyl.com";
    outPort = 587;
}

QString Configuration::getProtocolName(IncomingMailProtocol protocol)
{
    if (protocol == IncomingMailProtocol::POP3)
        return "POP3";
    else
        return "IMAP4";
}

