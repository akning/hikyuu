/*
 * DatabaseDriverFactory.cpp
 *
 *  Created on: 2012-8-14
 *      Author: fasiondog
 */

#include "base_info/mysql/MySQLBaseInfoDriver.h"
#include "base_info/sqlite/SQLiteBaseInfoDriver.h"
#include "block_info/qianlong/QLBlockInfoDriver.h"
#include "DataDriverFactory.h"
#include "KDataDriver.h"

namespace hku {

BaseInfoDriverPtr DataDriverFactory::
getBaseInfoDriver(const shared_ptr<IniParser>& ini) {
    string func_name(" [DataDriverFactory::getBaseInfoDriver]");
    BaseInfoDriverPtr result;
    if (!ini) {
        HKU_ERROR("Invalid parameter!" << func_name);
        return result;
    }

    if (!ini->hasSection("baseinfo")
            || !ini->hasOption("baseinfo", "type")) {
        HKU_ERROR("Can't read baseinfo configure!" << func_name);
        return result;
    }

    string dbtype = ini->get("baseinfo", "type");
    if (dbtype == "sqlite3") {
        result = make_shared<SQLiteBaseInfoDriver>(ini);

    } else if (dbtype == "mysql") {
        result = make_shared<MySQLBaseInfoDriver>(ini);
    }

    return result;
}


KDataDriverPtr DataDriverFactory::
getKDataDriver(const shared_ptr<IniParser>& ini) {
    string func_name(" [DataDriverFactory::getKDataDriver]");
    KDataDriverPtr  result;
    if (!ini) {
        HKU_ERROR("Null configure ini!" << func_name);
        return result;
    }

    result = make_shared<KDataDriver>(ini);
    return result;
}

BlockInfoDriverPtr DataDriverFactory::
getBlockDriver(const shared_ptr<IniParser>& ini) {
    string func_name(" [DataDriverFactory::getBlockDriver]");
    BlockInfoDriverPtr result;
    if (!ini) {
        HKU_ERROR("Null configure ini!" << func_name);
        return result;
    }

    if (!ini->hasOption("block", "type")) {
        return result;
    }

    string type = ini->get("block", "type");
    if (type == "qianlong") {
        result = make_shared<QLBlockInfoDriver>(ini);
    }
    return result;
}

} /* namespace hku */
