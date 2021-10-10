// SPDX-FileCopyrightText: 2021 Claudio Cambra <claudio.cambra@gmail.com>
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once
#include <Akonadi/Calendar/ETMCalendar>
#include <Akonadi/Calendar/IncidenceChanger>
#include <CalendarSupport/KCalPrefs>
#include <CalendarSupport/Utils>
#include <QSortFilterProxyModel>
#include <extratodomodel.h>
#include <incidencetreemodel.h>
#include <todomodel.h>

class TodoSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(Akonadi::IncidenceChanger *incidenceChanger WRITE setIncidenceChanger NOTIFY incidenceChangerChanged)
    Q_PROPERTY(Akonadi::ETMCalendar *calendar WRITE setCalendar NOTIFY calendarChanged)
    Q_PROPERTY(QVariantMap filter WRITE setFilter NOTIFY filterChanged)
    Q_PROPERTY(int showCompleted READ showCompleted WRITE setShowCompleted NOTIFY showCompletedChanged)

public:
    enum BaseTodoModelColumns {
        SummaryColumn = TodoModel::SummaryColumn,
        PriorityColumn = TodoModel::PriorityColumn,
        PercentColumn = TodoModel::PercentColumn,
        StartDateColumn = TodoModel::StartDateColumn,
        DueDateColumn = TodoModel::DueDateColumn,
        CategoriesColumn = TodoModel::CategoriesColumn,
        DescriptionColumn = TodoModel::DescriptionColumn,
        CalendarColumn = TodoModel::CalendarColumn,
    };
    Q_ENUM(BaseTodoModelColumns);

    enum ExtraTodoModelColumns { StartTimeColumn = TodoModel::ColumnCount, EndTimeColumn, PriorityIntColumn };
    Q_ENUM(ExtraTodoModelColumns);

    enum ShowComplete { ShowAll = 0, ShowCompleteOnly, ShowIncompleteOnly };
    Q_ENUM(ShowComplete);

    TodoSortFilterProxyModel(QObject *parent = nullptr);
    ~TodoSortFilterProxyModel() = default;

    bool filterAcceptsRow(int row, const QModelIndex &sourceParent) const override;
    bool filterAcceptsRowCheck(int row, const QModelIndex &sourceParent) const;
    bool hasAcceptedChildren(int row, const QModelIndex &sourceParent) const;

    void setCalendar(Akonadi::ETMCalendar *calendar);
    void setIncidenceChanger(Akonadi::IncidenceChanger *changer);
    void setColorCache(QHash<QString, QColor> colorCache);

    int showCompleted();
    void setShowCompleted(int showCompleted);
    QVariantMap filter();
    void setFilter(const QVariantMap &filter);

    Q_INVOKABLE void sortTodoModel(int sort, bool ascending);
    Q_INVOKABLE void filterTodoName(QString name, int showCompleted = ShowAll);

Q_SIGNALS:
    void incidenceChangerChanged();
    void calendarChanged();
    void filterChanged();
    void showCompletedChanged();

private:
    ExtraTodoModel *m_extraTodoModel = nullptr;
    int m_showCompleted = ShowComplete::ShowAll;
    int m_showCompletedStore; // For when searches happen
    QVariantMap m_filter;
};
