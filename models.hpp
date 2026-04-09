#ifndef MODELS_H
#define MODELS_H

#include <QString>
#include <QVector>
#include <QTextStream>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

// Структура брони
struct Armor {
    int helmet;
    int chestplate;
    int boots;

    Armor(int h = 0, int c = 0, int b = 0) : helmet(h), chestplate(c), boots(b) {}

    QString toString() const {
        return QString("<%1/%2/%3>").arg(helmet).arg(chestplate).arg(boots);
    }

    QJsonObject toJson() const {
        QJsonObject obj;
        obj["helmet"] = helmet;
        obj["chestplate"] = chestplate;
        obj["boots"] = boots;
        return obj;
    }

    static Armor fromJson(const QJsonObject& obj) {
        return Armor(obj["helmet"].toInt(),
                     obj["chestplate"].toInt(),
                     obj["boots"].toInt());
    }
};

// Базовый класс Person
class Person {
public:
    Person(int code = 0, const QString& name = "", int health = 0, const Armor& armor = Armor());
    virtual ~Person() = default;

    int getCode() const { return m_code; }
    QString getName() const { return m_name; }
    int getHealth() const { return m_health; }
    Armor getArmor() const { return m_armor; }

    void setCode(int code) { m_code = code; }
    void setName(const QString& name) { m_name = name; }
    void setHealth(int health) { m_health = health; }
    void setArmor(const Armor& armor) { m_armor = armor; }

    virtual QString getType() const = 0;
    virtual QString getExtraInfo() const = 0;
    virtual void print(QTextStream& out) const = 0;
    virtual QJsonObject toJson() const = 0;
    virtual Person* clone() const = 0;

    // Виртуальная функция Craft
    virtual QString craft() const = 0;

protected:
    int m_code;
    QString m_name;
    int m_health;
    Armor m_armor;
};

// Наследник 1: MagP (Маг)
class MagP : public Person {
public:
    MagP(int code = 0, const QString& name = "", const QString& element = "",
         int mana = 0, int health = 0, const Armor& armor = Armor());

    QString getElement() const { return m_element; }
    int getMana() const { return m_mana; }

    void setElement(const QString& element) { m_element = element; }
    void setMana(int mana) { m_mana = mana; }

    QString getType() const override { return "Маг"; }
    QString getExtraInfo() const override { return QString("Стихия: %1 | Мана: %2").arg(m_element).arg(m_mana); }
    void print(QTextStream& out) const override;
    QJsonObject toJson() const override;
    Person* clone() const override;
    QString craft() const override;

private:
    QString m_element;
    int m_mana;
};

// Наследник 2: VragP (Враг)
class VragP : public Person {
public:
    VragP(int code = 0, const QString& name = "", const QString& rarity = "",
          int damage = 0, int health = 0, const Armor& armor = Armor());

    QString getRarity() const { return m_rarity; }
    int getDamage() const { return m_damage; }

    void setRarity(const QString& rarity) { m_rarity = rarity; }
    void setDamage(int damage) { m_damage = damage; }

    QString getType() const override { return "Враг"; }
    QString getExtraInfo() const override { return QString("Редкость: %1 | Урон: %2").arg(m_rarity).arg(m_damage); }
    void print(QTextStream& out) const override;
    QJsonObject toJson() const override;
    Person* clone() const override;
    QString craft() const override;

private:
    QString m_rarity;
    int m_damage;
};

#endif // MODELS_H