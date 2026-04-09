#include "models.h"

// ==================== Person ====================
Person::Person(int code, const QString& name, int health, const Armor& armor)
    : m_code(code), m_name(name), m_health(health), m_armor(armor)
{
}

// ==================== MagP ====================
MagP::MagP(int code, const QString& name, const QString& element,
           int mana, int health, const Armor& armor)
    : Person(code, name, health, armor), m_element(element), m_mana(mana)
{
}

void MagP::print(QTextStream& out) const
{
    out << m_code << ","
        << m_name << ","
        << m_element << ","
        << m_mana << ","
        << m_health << ","
        << m_armor.helmet << "/" << m_armor.chestplate << "/" << m_armor.boots << "\n";
}

QJsonObject MagP::toJson() const
{
    QJsonObject obj;
    obj["code"] = m_code;
    obj["type"] = "mag";
    obj["name"] = m_name;
    obj["element"] = m_element;
    obj["mana"] = m_mana;
    obj["health"] = m_health;
    obj["armor"] = m_armor.toJson();
    return obj;
}

Person* MagP::clone() const
{
    return new MagP(m_code, m_name, m_element, m_mana, m_health, m_armor);
}

QString MagP::craft() const
{
    return QString("Карточка мага:\n"
                   "⭐ Имя: %1\n"
                   "✨ Стихия: %2\n"
                   "❤️ Здоровье: %3\n"
                   "💙 Мана: %4\n"
                   "🛡️ Броня: %5")
            .arg(m_name, m_element, QString::number(m_health),
                 QString::number(m_mana), m_armor.toString());
}

// ==================== VragP ====================
VragP::VragP(int code, const QString& name, const QString& rarity,
             int damage, int health, const Armor& armor)
    : Person(code, name, health, armor), m_rarity(rarity), m_damage(damage)
{
}

void VragP::print(QTextStream& out) const
{
    out << m_code << ","
        << m_name << ","
        << m_rarity << ","
        << m_damage << ","
        << m_health << ","
        << m_armor.helmet << "/" << m_armor.chestplate << "/" << m_armor.boots << "\n";
}

QJsonObject VragP::toJson() const
{
    QJsonObject obj;
    obj["code"] = m_code;
    obj["type"] = "vrag";
    obj["name"] = m_name;
    obj["rarity"] = m_rarity;
    obj["damage"] = m_damage;
    obj["health"] = m_health;
    obj["armor"] = m_armor.toJson();
    return obj;
}

Person* VragP::clone() const
{
    return new VragP(m_code, m_name, m_rarity, m_damage, m_health, m_armor);
}

QString VragP::craft() const
{
    return QString("Карточка врага:\n"
                   "👹 Имя: %1\n"
                   "🏷️ Редкость: %2\n"
                   "❤️ Здоровье: %3\n"
                   "⚔️ Урон: %4\n"
                   "🛡️ Броня: %5")
            .arg(m_name, m_rarity, QString::number(m_health),
                 QString::number(m_damage), m_armor.toString());
}