// SPDX-FileCopyrightText: 2004 Marc Mutz <mutz@kde.org>,
// SPDX-FileCopyrightText: 2004 Ingo Kloecker <kloecker@kde.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QByteArray>
#include <map>

namespace MimeTreeParser
{

namespace Interface
{
class BodyPartFormatter;
}

struct ltstr {
    bool operator()(const char *s1, const char *s2) const
    {
        return qstricmp(s1, s2) < 0;
    }
};

typedef std::multimap<const char *, const Interface::BodyPartFormatter *, ltstr> SubtypeRegistry;
typedef std::map<const char *, MimeTreeParser::SubtypeRegistry, MimeTreeParser::ltstr> TypeRegistry;

class BodyPartFormatterBaseFactoryPrivate;

class BodyPartFormatterBaseFactory
{
public:
    BodyPartFormatterBaseFactory();
    virtual ~BodyPartFormatterBaseFactory();

    SubtypeRegistry::const_iterator createForIterator(const char *type, const char *subtype) const;
    const SubtypeRegistry &subtypeRegistry(const char *type) const;

protected:
    void insert(const char *type, const char *subtype, Interface::BodyPartFormatter *formatter);

private:
    static BodyPartFormatterBaseFactory *mSelf;

    BodyPartFormatterBaseFactoryPrivate *d;
    friend class BodyPartFormatterBaseFactoryPrivate;

private:
    // disabled
    const BodyPartFormatterBaseFactory &operator=(const BodyPartFormatterBaseFactory &);
    BodyPartFormatterBaseFactory(const BodyPartFormatterBaseFactory &);
};

}
