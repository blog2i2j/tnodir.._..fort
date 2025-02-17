#include "protorange.h"

#include <common/fortconf.h>

#include <util/conf/confdata.h>
#include <util/net/netutil.h>
#include <util/stringutil.h>

ProtoRange::ProtoRange(QObject *parent) : ValueRange(parent) { }

bool ProtoRange::isEmpty() const
{
    return protoSize() == 0 && pairSize() == 0;
}

bool ProtoRange::checkSize() const
{
    return (protoSize() + pairSize()) < FORT_CONF_PROTO_MAX;
}

int ProtoRange::sizeToWrite() const
{
    return FORT_CONF_PROTO_LIST_SIZE(protoSize(), pairSize());
}

void ProtoRange::clear()
{
    ValueRange::clear();

    m_protoArray.clear();
    m_pairFromArray.clear();
    m_pairToArray.clear();
}

void ProtoRange::toList(QStringList &list) const
{
    for (int i = 0, n = protoSize(); i < n; ++i) {
        const proto_t proto = protoAt(i);

        list << NetUtil::protocolName(proto);
    }

    for (int i = 0, n = pairSize(); i < n; ++i) {
        const ProtoPair pair = pairAt(i);

        list << QString("%1-%2").arg(QString::number(pair.from), QString::number(pair.to));
    }
}

bool ProtoRange::fromList(const StringViewList &list, bool /*sort*/)
{
    clear();

    protorange_map_t protoRangeMap;
    int pairSize = 0;

    int lineNo = 0;
    for (const auto &line : list) {
        ++lineNo;

        const auto lineTrimmed = line.trimmed();
        if (lineTrimmed.isEmpty() || lineTrimmed.startsWith('#')) // commented line
            continue;

        if (parseProtoLine(line, protoRangeMap, pairSize) != ErrorOk) {
            appendErrorDetails(QString("line='%1'").arg(line));
            setErrorLineNo(lineNo);
            return false;
        }
    }

    fillRangeArrays<proto_t>({
            .rangeMap = protoRangeMap,
            .valuesArray = m_protoArray,
            .pairFromArray = m_pairFromArray,
            .pairToArray = m_pairToArray,
            .pairSize = pairSize,
    });

    return true;
}

ProtoRange::ParseError ProtoRange::parseProtoLine(
        const QStringView line, protorange_map_t &protoRangeMap, int &pairSize)
{
    static const QRegularExpression protoRe(R"(^([\d\w]+)\s*(-?)\s*(\S*))");

    const auto match = StringUtil::match(protoRe, line);
    if (!match.hasMatch()) {
        setErrorMessage(tr("Bad format"));
        return ErrorBadFormat;
    }

    const auto proto = match.captured(1);
    const auto sepStr = match.capturedView(2);
    const auto proto2 = match.captured(3);

    if (sepStr.isEmpty() != proto2.isEmpty()) {
        setErrorMessage(tr("Bad range"));
        setErrorDetails(QString("proto='%1' sep='%2' proto2='%3'").arg(proto, sepStr, proto2));
        return ErrorBadRangeFormat;
    }

    return parseProtoRange(proto, proto2, protoRangeMap, pairSize);
}

ProtoRange::ParseError ProtoRange::parseProtoRange(const QStringView proto,
        const QStringView proto2, protorange_map_t &protoRangeMap, int &pairSize)
{
    proto_t from = 0, to = 0;

    if (!(parseProtoNumber(proto, from) && parseProtoNumber(proto2, to)))
        return ErrorBadProto;

    if (to == 0) {
        to = from;
    }

    protoRangeMap.insert(from, to);

    if (from != to) {
        ++pairSize;
    }

    return ErrorOk;
}

bool ProtoRange::parseProtoNumber(const QStringView proto, proto_t &v)
{
    if (proto.isEmpty())
        return true;

    bool ok;

    if (proto.at(0).isDigit()) {
        v = proto.toUShort(&ok);
    } else {
        v = NetUtil::protocolNumber(proto, ok);
    }

    if (!ok) {
        setErrorMessage(tr("Bad Protocol"));
        setErrorDetails(QString("Protocol='%1'").arg(proto));
    }
    return ok;
}

void ProtoRange::write(ConfData &confData) const
{
    confData.writeProtoRange(*this);
}
