#pragma once

#include <QJsonObject>
#include <QString>

struct Book
{
    QString id;
    QString title;
    QString author;
    QString publisher;
    bool borrowed = false;
    QString borrower;
    QString borrowedDate;

    QJsonObject toJson() const
    {
        return {
            {"id", id},
            {"title", title},
            {"author", author},
            {"publisher", publisher},
            {"borrowed", borrowed},
            {"borrower", borrower},
            {"borrowedDate", borrowedDate}
        };
    }

    static Book fromJson(const QJsonObject &object)
    {
        Book book;
        book.id = object.value("id").toString();
        book.title = object.value("title").toString();
        book.author = object.value("author").toString();
        book.publisher = object.value("publisher").toString();
        book.borrowed = object.value("borrowed").toBool(false);
        book.borrower = object.value("borrower").toString();
        book.borrowedDate = object.value("borrowedDate").toString();
        return book;
    }
};
