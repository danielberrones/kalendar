// SPDX-FileCopyrightText: 2022 Carl Schwan <carl@carlschwan.eu>
// SPDX-License-Identifier: LGPL-3.0-or-later

import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import QtQuick.Layouts 1.15
import org.kde.kirigami 2.12 as Kirigami
import org.kde.kalendar.contact 1.0
import org.kde.kalendar 1.0
import './private'

Kirigami.ScrollablePage {
    objectName: "contactView"
    property int mode: KalendarApplication.Contact
    property var attendeeAkonadiIds
    title: i18n("Contacts")

    actions.main: Kirigami.Action {
        icon.name: 'contact-new-symbolic'
        text: i18n('Create')
        Kirigami.Action {
            text: i18n('New Contact')
            onTriggered: pageStack.pushDialogLayer(Qt.resolvedUrl("private/ContactEditorPage.qml"), {
                mode: ContactEditor.CreateMode,
            })
        }
        Kirigami.Action {
            text: i18n('New Contact Group')
            onTriggered: pageStack.pushDialogLayer(Qt.resolvedUrl("private/ContactGroupEditorPage.qml"), {
                mode: ContactGroupEditor.CreateMode,
            })
        }
    }

    ListView {
        id: contactsList
        reuseItems: true
        section.property: "display"
        section.criteria: ViewSection.FirstCharacter
        section.delegate: Kirigami.ListSectionHeader {
            text: section
        }
        clip: true
        model: ContactManager.filteredContacts
        delegate: ContactListItem {
            height: Kirigami.Settings.isMobile ? Kirigami.Units.gridUnit * 3 : Kirigami.Units.gridUnit * 2
            name: model && model.display
            avatarIcon: model && model.decoration

            onClicked: if (model.mimeType === 'application/x-vnd.kde.contactgroup') {
                applicationWindow().pageStack.push(Qt.resolvedUrl('./private/ContactGroupPage.qml'), {
                    itemId: model.itemId,
                })
            } else {
                applicationWindow().pageStack.push(Qt.resolvedUrl('./private/ContactPage.qml'), {
                    itemId: model.itemId,
                })
            }
        }
        Kirigami.PlaceholderMessage {
            anchors.centerIn: parent
            text: i18n("No contacts")
            visible: contactsList.count === 0
        }
    }
}
