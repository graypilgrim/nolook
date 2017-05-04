#ifndef MAIL_H
#define MAIL_H

#include <QStandardItem>
#include <QString>

#include <string>
#include <vector>

class Mail : public QStandardItem
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

private:
    QString sender;
    QString recipient;
    QString topic;
    std::vector<QString> carbonCopy;
    std::vector<QString> blindCarbonCopy;
    QString content;

};

#endif // MAIL_H
