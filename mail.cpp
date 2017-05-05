#include "mail.h"

Mail::Mail()
{

}

QString Mail::getSender() {
    return sender;
}

void Mail::setSender(const QString &sender) {
    this->sender = sender;
}

QString Mail::getRecipient() {
    return recipient;
}

void Mail::setRecipient(const QString &recipient) {
    this->recipient = recipient;
}

QString Mail::getTopic() {
    return topic;
}

void Mail::setTopic(const QString &topic) {
    this->topic = topic;
}

std::vector<QString> Mail::getCarbonCopy() {
    return carbonCopy;
}

void Mail::setCarbonCopy(const std::vector<QString> &cc) {
    carbonCopy = cc;
}

std::vector<QString> Mail::getBlindCarbonCopy() {
    return blindCarbonCopy;
}

void Mail::setBlindCarbonCopy(const std::vector<QString> &bcc) {
    blindCarbonCopy = bcc;
}

QString Mail::getContent() {
    return content;
}

void Mail::setContent(const QString &content) {
    this->content = content;
}

QDateTime Mail::getSendTime() {
    return sendTime;
}

void Mail::setSendTime(const QDateTime &time) {
    sendTime = time;
}
