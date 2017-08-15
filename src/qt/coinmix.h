// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
//
#ifndef BITCOIN_QT_COINMIX_H
#define BITCOIN_QT_COINMIX_H

#include "amount.h"

#include <QWidget>


class ClientModel;
class TransactionFilterProxy;
class TxViewDelegate;
class WalletModel;

namespace Ui
{
class Coinmix;
}

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

/* coinmix ("home") page widget */
class Coinmix : public QWidget
{
    Q_OBJECT

public:
    explicit Coinmix(QWidget* parent = 0);
    ~Coinmix();

    void setClientModel(ClientModel* clientModel);
    void setWalletModel(WalletModel* walletModel);
    void showOutOfSyncWarning(bool fShow);
    void updateDarksendProgress();

public slots:
    void DarKsendStatus();
    void setBalance(const CAmount& balance, const CAmount& unconfirmedBalance, const CAmount& immatureBalance, const CAmount& anonymizedBalance, const CAmount& watchOnlyBalance, const CAmount& watchUnconfBalance, const CAmount& watchImmatureBalance);

signals:
    void transactionClicked(const QModelIndex& index);

private:
    QTimer* timer;
    Ui::Coinmix* ui;
    ClientModel* clientModel;
    WalletModel* walletModel;
    CAmount currentBalance;
    CAmount currentUnconfirmedBalance;
    CAmount currentImmatureBalance;
    CAmount currentAnonymizedBalance;
    CAmount currentWatchOnlyBalance;
    CAmount currentWatchUnconfBalance;
    CAmount currentWatchImmatureBalance;
    int nDisplayUnit;

    //TxViewDelegate2* txdelegate;
    TransactionFilterProxy* filter;

private slots:
    void toggleDarksend();
    void DarksendAuto();
    void DarksendReset();
    //void updateDisplayUnit();
    //void handleTransactionClicked(const QModelIndex& index);
    //void updateAlerts(const QString& warnings);
    //void updateWatchOnlyLabels(bool showWatchOnly);
};


#endif // BITCOIN_QT_COINMIX_H
