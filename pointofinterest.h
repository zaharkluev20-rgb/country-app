#ifndef POINTOFINTEREST_H
#define POINTOFINTEREST_H

#include <QString>
#include <QJsonObject>

class PointOfInterest
{
public:
    PointOfInterest();
    PointOfInterest(const QString &name, const QString &description, int difficulty, double x, double y);

    // Геттеры
    QString getName() const;
    QString getDescription() const;
    int getDifficulty() const;
    double getX() const;
    double getY() const;

    // Сеттеры
    void setName(const QString &name);
    void setDescription(const QString &description);
    void setDifficulty(int difficulty);
    void setX(double x);
    void setY(double y);

    // Валидация
    bool isValid() const;

    // Сериализация
    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);

    // Из строки TXT (формат: название|описание|сложность|X|Y)
    static PointOfInterest fromTxtLine(const QString &line, bool &ok);

private:
    QString name;
    QString description;
    int difficulty;
    double x;
    double y;
};

#endif // POINTOFINTEREST_H