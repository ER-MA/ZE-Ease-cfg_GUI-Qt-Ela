#ifndef STRUCTS_H
#define STRUCTS_H

#include <QString>

namespace TableStructs {

    struct KeybindItem {
        QString KeyID;
        QString FunctionID;
    };

    struct KeybindModelItem {
        QString Key;
        QString Function;
        QString KeyID;
        QString FunctionID;
    };

    struct FunctionModelItem {
        QString Name;
        QString FunctionID;
        QString ParentID;
    };

}

namespace CSConfigStructs {

    struct KeyInfo {
        QString Appellation;
        QString Description;
        QString LabelSymbol;
        QString LabelText;
    };

    struct FunctionInfo {
        QString Name;
        QString Description;
        QString Detail;
    };

}

#endif // STRUCTS_H
