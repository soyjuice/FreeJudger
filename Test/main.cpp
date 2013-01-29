﻿
#define JUDGER_IMPORT

#include "../judgerlib/logger/Logger.h"
#include "../judgerlib/logger/Logger_log4cxx.h"

#include "../judgerlib/thread/Thread.h"
#include "../judgerlib/xml/Xml.h"

#include "../judgerlib/process/Process.h"

#include "../judgerlib/sql/Sql.h"

#include <vector>

using namespace std;

void ThreadFun()
{
    IMUST::ILogger *logger = new IMUST::Log4CxxLoggerImpl(GetOJString("log.cfg"), GetOJString("logger1"));

    // FIXED ME:logger中文乱码
    logger->logDebug(GetOJString("thread log"));
}

int main()
{
#if 0
    vector<IMUST::ILogger *> iloggers;
    vector<IMUST::ILogger *> loggers;

    iloggers.push_back(new IMUST::Log4CxxLoggerImpl(GetOJString("log.cfg"), GetOJString("logger1")));
    iloggers.push_back(new IMUST::Log4CxxLoggerImpl(GetOJString("log.cfg"), GetOJString("logger2")));
    iloggers.push_back(new IMUST::Log4CxxLoggerImpl(GetOJString("log.cfg"), GetOJString("logger3")));

    for (int i = 0; i < 3; ++i)
        IMUST::LoggerFactory::registerLogger(iloggers[i], i);

    for (int i = 0; i < 3; ++i)
        loggers.push_back(IMUST::LoggerFactory::getLogger(i));

    for (int i = 0; i < 3; ++i)
    {
        loggers[i]->logFatal(GetOJString("Msg4cxx"));
        loggers[i]->logError(GetOJString("Msg"));
        loggers[i]->logWarn(GetOJString("Msg"));
        loggers[i]->logInfo(GetOJString("Msg"));
        loggers[i]->logDebug(GetOJString("Msg"));
        loggers[i]->logTrace(GetOJString("Msg"));
    }
#endif

#if 0
    IMUST::Thread t(&ThreadFun);
    t.join();
#endif

#if 0

    IMUST::XmlPtr xmlRoot = IMUST::allocateRapidXml();
    if(!xmlRoot->load(GetOJString("config.xml")))
    {
        OJCout<<GetOJString("read config fail!")<<std::endl;
        return 0;
    }
   
    OJCout<<GetOJString("read config.xml")<<std::endl;

    //test read node
    IMUST::XmlPtr ptr = xmlRoot->read(GetOJString("AppConfig/MySql/Ip"));
    while(ptr)
    {
        OJCout<<ptr->tag()<<GetOJString(" = ")<<ptr->value()<<std::endl;
        ptr = ptr->getNextSibling();
    }
    
    //test read many
    IMUST::XmlPtrVector vector;
    if(xmlRoot->reads(GetOJString("AppConfig/JudgeCode/Pending"), vector))
    {
        for(IMUST::XmlPtrVector::iterator it=vector.begin(); it != vector.end(); ++it)
        {
            OJCout<<(*it)->tag()<<GetOJString(" = ")<<(*it)->value()<<std::endl;
        }
    }

    //test read data
    IMUST::OJInt32_t t = 0;
    IMUST::OJString tag = GetOJString("AppConfig/MySql/Port");
    if(xmlRoot->readInt32(tag, t))
    {
        OJCout<<tag<<GetOJString(" = ")<<t<<std::endl;
    }

    //test write
    xmlRoot = IMUST::allocateRapidXml();

    xmlRoot->writeInt32(GetOJString("config/size/x"), t+5);
    xmlRoot->writeFloat16(GetOJString("testTag/a"), 7.1f);
    xmlRoot->writeFloat32(GetOJString("testTag/b"), 8.777);

    //test save
    xmlRoot->save(GetOJString("testConfig.xml"));
#endif

#if 0
    IMUST::WindowsProcess wp;
    wp.create(GetOJString("calc.exe"));
#endif

#if 1

    IMUST::SqlDriverPtr mysql = IMUST::SqlFactory::createDriver(IMUST::SqlType::MySql);
    if(!mysql->loadService())
    {
        OJCout<<GetOJString("loadService faild!")<<mysql->getErrorString()<<std::endl;
        return 0;
    }

    if(!mysql->connect(GetOJString("127.0.0.1"), 3306, GetOJString("root"),
        GetOJString(""), GetOJString("jol")))
    {
        OJCout<<GetOJString("connect faild!")<<mysql->getErrorString()<<std::endl;
        return 0;
    }

    if(mysql->query(GetOJString("select solution_id, problem_id, user_id, time, memory from solution")))
    {
        IMUST::SqlResultPtr result = mysql->storeResult();
        if(result)
        {
            IMUST::OJUInt32_t cols = result->getNbCols();
            for(IMUST::OJUInt32_t i=0; i<cols; ++i)
            {
                OJCout<<result->getFieldName(i)<<GetOJString("\t");
            }
            OJCout<<endl;
            IMUST::SqlRowPtr row(NULL);
            while(row = result->fetchRow())
            {
                for(IMUST::OJUInt32_t i=0; i<cols; ++i)
                {
                    OJCout<<(*row)[i].getString()<<GetOJString("\t");
                }
                OJCout<<endl;
            }
        }
    }

    mysql->disconect();

    mysql->unloadService();

#endif
       
    system("pause");
    return 0;
}
