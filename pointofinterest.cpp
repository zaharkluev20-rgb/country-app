#include "pointofinterest.h"
#include <QRegularExpression>

PointOfInterest::PointOfInterest()
    : difficulty(0), x(0), y(0)
{
}

PointOfInterest::PointOfInterest(const QString &name, const QString &description, int difficulty, double x, double y)
    : name(name), description(description), difficulty(difficulty), x(x), y(y)
{
}

QString PointOfInterest::getName() const { return name; }
QString PointOfInterest::getDescription() const { return description; }
int PointOfInterest::getDifficulty() const { return difficulty; }
double PointOfInterest::getX() const { return x; }
double PointOfInterest::getY() const { return y; }

void PointOfInterest::setName(const QString &name) { this->name = name; }
void PointOfInterest::setDescription(const QString &description) { this->description = description; }
void PointOfInterest::setDifficulty(int difficulty) { this->difficulty = difficulty; }
void PointOfInterest::setX(double x) { this->x = x; }
void PointOfInterest::setY(double y) { this->y = y; }

bool PointOfInterest::isValid() const
{
    // Проверка: все поля заполнены и соответствуют формату
    if (name.trimmed().isEmpty()) return false;
    if (description.trimmed().isEmpty()) return false;
    if (difficulty < 1 || difficulty > 10) return false; // сложность от 1 до 10
    // Координаты могут быть любыми числами, главное что они заданы (проверяем через isNull не нужно, double всегда имеет значение)
    return true;
}

QJsonObject PointOfInterest::toJson() const
{
    QJsonObject json;
    json["name"] = name;
    json["description"] = description;
    json["difficulty"] = difficulty;
    json["x"] = x;
    json["y"] = y;
    return json;
}

void PointOfInterest::fromJson(const QJsonObject &json)
{
    name = json["name"].toString();
    description = json["description"].toString();
    difficulty = json["difficulty"].toInt();
    x = json["x"].toDouble();
    y = json["y"].toDouble();
}

PointOfInterest PointOfInterest::fromTxtLine(const QString &line, bool &ok)
{
    ok = false;
    QStringList parts = line.split('|');
    if (parts.size() != 5) return PointOfInterest();

    QString name = parts[0].trimmed();
    QString description = parts[1].trimmed();
    bool diffOk;
    int difficulty = parts[2].trimmed().toInt(&diffOk);
    bool xOk;
    double x = parts[3].trimmed().toDouble(&xOk);
    bool yOk;
    double y = parts[4].trimmed().toDouble(&yOk);

    if (name.isEmpty() || description.isEmpty() || !diffOk || !xOk || !yOk)
        return PointOfInterest();

    PointOfInterest poi(name, description, difficulty, x, y);
    if (poi.isValid())
        ok = true;
    
    return poi;
}