#ifndef GESTIONSEQUENCE_H
#define GESTIONSEQUENCE_H

#include <QObject>

class GestionSequence : public QObject
{
    Q_OBJECT
public:
    explicit GestionSequence(QObject *parent = nullptr);

public slots:
    void init();

signals:

};

#endif // GESTIONSEQUENCE_H
