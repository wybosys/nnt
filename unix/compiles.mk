
LDWITH += -lstdc++ -lACE -lssl -lcrypto -luuid -ldb -lboost_regex-mt -lmysqlclient -lsqlite3 -lsybdb -lxerces-c -llog4cpp -luuid
LDWITH =

CFLAGS += $(INC_DIR) -I$(SRC_DIR) -I$(SRC_DIR)/Core/ -Wno-deprecated
LDFLAGS += $(LIB_DIR) -shared -fPIC $(LDWITH)

CC = gcc
CXX = g++

CXX_COMPILE = $(CXX) $(CFLAGS) -fPIC -c
LINK = $(CXX) $(CFLAGS) $(LDFLAGS)

Core.o:
	$(CXX_COMPILE) $(SRC_DIR)/Core/Core.cpp

App.o:
	$(CXX_COMPILE) $(SRC_DIR)/Core/App.cpp

Object.o:
	$(CXX_COMPILE) $(SRC_DIR)/Core/Object.cpp

ObjectDL.o:
	$(CXX_COMPILE) $(SRC_DIR)/Core/ObjectDL.cpp

WSIChar.o:
	$(CXX_COMPILE) $(SRC_DIR)/Core/WSIChar.cpp

Directory+WSI.o:
	$(CXX_COMPILE) $(SRC_DIR)/Core/Directory+WSI.cpp

Task+WSI.o:
	$(CXX_COMPILE) $(SRC_DIR)/Core/Task+WSI.cpp

Time+WSI.o:
	$(CXX_COMPILE) $(SRC_DIR)/Core/Time+WSI.cpp

UnitTest.o:
	$(CXX_COMPILE) $(SRC_DIR)/Core/UnitTest.cpp

Algorithm+WSI.o:
	$(CXX_COMPILE) $(SRC_DIR)/WTL/Algorithm+WSI.cpp

String+WSI.o:
	$(CXX_COMPILE) $(SRC_DIR)/WTL/String+WSI.cpp

Regex+WSI.o:
	$(CXX_COMPILE) $(SRC_DIR)/WTL/Regex+WSI.cpp

Variant+WSI.o:
	$(CXX_COMPILE) $(SRC_DIR)/WTL/Variant+WSI.cpp

NetAddress.o:
	$(CXX_COMPILE) $(SRC_DIR)/Cross/NetAddress.cpp

SocketServer.o:
	$(CXX_COMPILE) $(SRC_DIR)/Cross/SocketServer.cpp

SocketClient.o:
	$(CXX_COMPILE) $(SRC_DIR)/Cross/SocketClient.cpp

SocketStream.o:
	$(CXX_COMPILE) $(SRC_DIR)/Cross/SocketStream.cpp

SoapObject.o:
	$(CXX_COMPILE) $(SRC_DIR)/Cross/SoapObject.cpp

WsiSecurity.o:
	$(CXX_COMPILE) $(SRC_DIR)/Security/WsiSecurity.cpp

AES+WSI.o:
	$(CXX_COMPILE) $(SRC_DIR)/Security/AES+WSI.cpp

DES+WSI.o:
	$(CXX_COMPILE) $(SRC_DIR)/Security/DES+WSI.cpp

BaseN+WSI.o:
	$(CXX_COMPILE) $(SRC_DIR)/Security/BaseN+WSI.cpp

MDN+WSI.o:
	$(CXX_COMPILE) $(SRC_DIR)/Security/MDN+WSI.cpp

RSA+WSI.o:
	$(CXX_COMPILE) $(SRC_DIR)/Security/RSA+WSI.cpp

UUID+WSI.o:
	$(CXX_COMPILE) $(SRC_DIR)/Security/UUID+WSI.cpp

DBMS.o:
	$(CXX_COMPILE) $(SRC_DIR)/Store/DBMS.cpp

DBMSqlAbstract.o:
	$(CXX_COMPILE) $(SRC_DIR)/Store/DBMSqlAbstract.cpp

WSIBdb.o:
	$(CXX_COMPILE) $(SRC_DIR)/Store/WSIBdb.cpp

WSISqlite.o:
	$(CXX_COMPILE) $(SRC_DIR)/Store/WSISqlite.cpp

WSIMySql.o:
	$(CXX_COMPILE) $(SRC_DIR)/Store/WSIMySql.cpp

WSILogger.o:
	$(CXX_COMPILE) $(SRC_DIR)/Store/WSILogger.cpp

WSISqlServer.o:
	$(CXX_COMPILE) $(SRC_DIR)/Store/WSISqlServer.cpp

WSIConfiguration.o:
	$(CXX_COMPILE) $(SRC_DIR)/Store/WSIConfiguration.cpp

BSEServer.o:
	$(CXX_COMPILE) $(SRC_DIR)/Baison/BSEServer.cpp

CSSParser.o:
	$(CXX_COMPILE) $(SRC_DIR)/Parser/CSSParser.cpp

XmlParser.o:
	$(CXX_COMPILE) $(SRC_DIR)/Parser/XmlParser.cpp

SOAPParser.o:
	$(CXX_COMPILE) $(SRC_DIR)/Parser/SOAPParser.cpp

CmdArguments.o:
	$(CXX_COMPILE) $(SRC_DIR)/Parser/CmdArguments.cpp

PropertyTree.o:
	$(CXX_COMPILE) $(SRC_DIR)/Parser/PropertyTree.cpp

LIBXERCESC+WSI.o:
	$(CXX_COMPILE) $(CONTRIB_DIR)/libxml/LIBXERCESC+WSI.cpp

ACE+WSI.o:
	$(CXX_COMPILE) $(CONTRIB_DIR)/ace/ACE+WSI.cpp

wsi:$(objs)
	$(LINK) *.o -o libwsi.so

clean:
	@rm *.o
