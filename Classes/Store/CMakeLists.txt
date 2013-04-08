
SOURCE (DBMS.cpp)
SOURCE (DBMSqlAbstract.cpp)
SOURCE (Bdb+NNT.cpp)
SOURCE (MySql+NNT.cpp)
SOURCE (Sqlite+NNT.cpp)
SOURCE (SqlServer+NNT.cpp)
SOURCE (Logger+NNT.cpp)
SOURCE (Configuration+NNT.cpp)

ADD_LIBRARY (NntStore STATIC ${CURRENT_SOURCES})
