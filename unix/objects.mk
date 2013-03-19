
obj_core = App.o Core.o ObjectDL.o WSIChar.o Directory+WSI.o Task+WSI.o Time+WSI.o UnitTest.o Object.o
obj_wtl = Algorithm+WSI.o String+WSI.o  Regex+WSI.o Variant+WSI.o
obj_cross = NetAddress.o SocketServer.o SocketStream.o SocketClient.o SoapObject.o
obj_security = WsiSecurity.o AES+WSI.o BaseN+WSI.o DES+WSI.o MDN+WSI.o RSA+WSI.o UUID+WSI.o
obj_store = DBMS.o DBMSqlAbstract.o WSIBdb.o WSIMySql.o WSISqlite.o WSISqlServer.o WSILogger.o WSIConfiguration.o
obj_parser = CSSParser.o XmlParser.o SOAPParser.o PropertyTree.o CmdArguments.o
obj_baison = BSEServer.o
obj_contrib = LIBXERCESC+WSI.o ACE+WSI.o
objs = $(obj_core) $(obj_wtl)  $(obj_cross) $(obj_security) $(obj_store) $(obj_baison) $(obj_parser) $(obj_contrib)
