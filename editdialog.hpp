#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include "models.h"

class EditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditDialog(Person* person = nullptr, QWidget *parent = nullptr);
    ~EditDialog();

    Person* getPerson() const;

private slots:
    void onTypeChanged(int index);
    void onSaveClicked();
    void onCancelClicked();

private:
    void setupUi();
    void loadFromPerson();
    void saveToPerson();

    Person* m_person;
    bool m_isNew;

    // Общие поля
    QLineEdit* m_codeEdit;
    QLineEdit* m_nameEdit;
    QSpinBox* m_healthSpin;
    QSpinBox* m_helmetSpin;
    QSpinBox* m_chestplateSpin;
    QSpinBox* m_bootsSpin;
    QComboBox* m_typeCombo;

    // Поля для мага
    QLineEdit* m_elementEdit;
    QSpinBox* m_manaSpin;

    // Поля для врага
    QLineEdit* m_rarityEdit;
    QSpinBox* m_damageSpin;

    QWidget* m_magWidget;
    QWidget* m_vragWidget;
};

#endif // EDITDIALOG_H