#ifndef MAIL_H
#define MAIL_H

#include <QString>
#include <QDateTime>

#include <string>
#include <vector>

class Mail
{
public:
    Mail();

    QString getSender();
    void setSender(const QString &sender);
    QString getRecipient();
    void setRecipient(const QString &recipient);
    QString getTopic();
    void setTopic(const QString &topic);
    std::vector<QString> getCarbonCopy();
    void setCarbonCopy(const std::vector<QString> &cc);
    std::vector<QString> getBlindCarbonCopy();
    void setBlindCarbonCopy(const std::vector<QString> &bcc);
    QString getContent();
    void setContent(const QString &content);
    QDateTime getSendTime();
    void setSendTime(const QDateTime &time);

private:
    QString sender;
    QString recipient;
    QString topic;
    std::vector<QString> carbonCopy;
    std::vector<QString> blindCarbonCopy;
    QString content;
    QDateTime sendTime;
};

#endif // MAIL_H
