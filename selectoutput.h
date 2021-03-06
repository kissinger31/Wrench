// -*- mode: c++ -*-
#ifndef _SELECTOUTPUT_H_
#define _SELECTOUTPUT_H_
#include <QCoreApplication>
#include <QPixmap>

struct SelectedItem {
    QString selectedText;
    QString displayText;
    QPixmap icon;
    SelectedItem() {};
    bool operator==(const SelectedItem& si) {
        return displayText == si.displayText;
    }

    SelectedItem(const QString& name, const QString& display) : selectedText(name), displayText(display) {};

    SelectedItem(const QString& name, const QString& display, const QPixmap& iconArg) :
        selectedText(name), displayText(display), icon(iconArg)  {};

    SelectedItem(const SelectedItem& si) : selectedText(si.selectedText), displayText(si.displayText), icon(si.icon) {};

    SelectedItem& operator=(const SelectedItem& si) {
        selectedText = si.selectedText;
        displayText = si.displayText;
        icon = si.icon;
        return *this;
    };
};

#endif /* _SELECTOUTPUT_H_ */
