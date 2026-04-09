#ifndef CARDDIALOG_H
#define CARDDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileInfo>
#include <QDir>
#include "models.h"

class CardDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CardDialog(Person* person, QWidget *parent = nullptr);
    ~CardDialog();

signals:
    void personRemoved();

private slots:
    void onPrintClicked();
    void onCancelClicked();
    void onSaveImageClicked();

private:
    void setupUi();
    void loadStaticImage();
    void loadRandomImage();
    void loadUniqueImage();
    void updateImage(int mode);
    void saveCardAsImage();

    Person* m_person;
    QLabel* m_nameLabel;
    QLabel* m_typeLabel;
    QLabel* m_attributeLabel;
    QLabel* m_healthLabel;
    QLabel* m_manaOrDamageLabel;
    QLabel* m_armorLabel;
    QLabel* m_imageLabel;
    QPushButton* m_printButton;
    QPushButton* m_cancelButton;
    QPushButton* m_saveImageButton;

    int m_imageMode; // 1 - статичная, 2 - рандомная, 3 - уникальная
    static QSet<QString> m_usedImages;
};

#endif // CARDDIALOG_H