
# include "Core.h"
# include "NNTSqlServer.h"
# include "../Core/Boost+NNT.h"
# include <boost/regex.hpp>

# ifdef NNT_UNIX
#   define _FREETDS
# else
#   define _MSSQL
# endif

# ifdef _MSSQL
#  include "../Cross/NetAddress.h"
# endif

# ifdef _FREETDS
#   include <freetds/sqlfront.h>
#   include <freetds/sqldb.h>

#define SQLTEXT SYBTEXT
#define SQLCHAR SYBCHAR
#define SQLVARCHAR SYBVARCHAR
#define SQLINT1 SYBINT1
#define SQLINT2 SYBINT2
#define SQLINT4 SYBINT4
#define SQLINTN SYBINTN
#define SQLBIT SYBBIT
#define SQLFLT4 SYBREAL
#define SQLFLT8 SYBFLT8
#define SQLFLTN SYBFLTN
#define SQLDECIMAL SYBDECIMAL
#define SQLNUMERIC SYBNUMERIC
#define SQLDATETIME SYBDATETIME
#define SQLDATETIM4 SYBDATETIME4
#define SQLDATETIMN SYBDATETIMN
#define SQLMONEY SYBMONEY
#define SQLMONEY4 SYBMONEY4
#define SQLMONEYN SYBMONEYN
#define SQLIMAGE SYBIMAGE
#define SQLBINARY SYBBINARY
#define SQLVARBINARY SYBVARBINARY

#define dbrpcexec dbrpcsend

# endif

# ifdef _MSSQL

# include <comdef.h>
# include <atlstr.h>

# ifdef _WIN32
# define ADO_DLL SYSDEV ## \\Program Files (x86)\\Common Files\\System\\ado\\msado15.dll
# else
# define ADO_DLL SYSDEV ## \\Program Files\\Common Files\\System\\ado\\msado15.dll
# endif

# pragma message ("auto link with " NNTMACRO_TOSTR(ADO_DLL) " for ado access.")
# import NNTMACRO_TOSTR(ADO_DLL) no_namespace rename("EOF", "adoEOF")

# ifdef variant_t
#  undef variant_t
# endif

# endif

NNT_BEGIN_CXX 
NNT_BEGIN_NS(store)

NNTDECL_PRIVATE_BEGIN_CXX(SqlServer)

# ifdef _FREETDS

static int tds_error(DBPROCESS * dbproc, int severity, int dberr, int oserr, char *dberrstr, char *oserrstr)
{
# ifdef NNT_DEBUG
    if (dberr) {							
		fprintf(stderr, "%s: Msg %d, Level %d\n", 
				"NNT", dberr, severity);
		fprintf(stderr, "%s\n\n", dberrstr);
	}
    
	else {
		fprintf(stderr, "%s: DB-LIBRARY error:\n\t", "NNT");
		fprintf(stderr, "%s\n", dberrstr);
	}
# endif
	return INT_CANCEL;
}

static int tds_msg(DBPROCESS * dbproc, DBINT msgno, int msgstate, int severity, char *msgtext, char *srvname,
                   char *proc, int line)
{
# ifdef NNT_DEBUG
    enum {changed_database = 5701, changed_language = 5703 };	
	
	if (msgno == changed_database || msgno == changed_language) 
		return 0;
    
	if (msgno > 0) {
		fprintf(stderr, "Msg %ld, Level %d, State %d\n", 
				(long) msgno, severity, msgstate);
        
		if (strlen(srvname) > 0)
			fprintf(stderr, "Server '%s', ", srvname);
		if (line > 0)
			fprintf(stderr, "Line %d", line);
        
		fprintf(stderr, "\n\t");
	}
	fprintf(stderr, "%s\n", msgtext);
	
	if (severity > 10) {						
		fprintf(stderr, "%s: error: severity %d > 10, exiting\n", 
				"NNT", severity);
	}
# endif
	return 0;
}

# endif

void init()
{
# ifdef _FREETDS
    this->proc = NULL;
    
    dbinit();
    
    dberrhandle(tds_error);
    dbmsghandle(tds_msg);
# endif

# ifdef _MSSQL
	DWORD sta = ::CoInitialize(NULL);
	this->conn = NULL;
	if (!SUCCEEDED(sta))
		trace_msg("failed to initialize com envirnment");
# endif
}

void dealloc()
{
# ifdef _FREETDS
    if (proc)
        dbclose(proc);
# endif

# ifdef _MSSQL
	::CoUninitialize();
# endif
}

# ifdef _FREETDS

DBPROCESS* proc;

# endif

# ifdef _MSSQL

_ConnectionPtr conn;

# endif

NNTDECL_PRIVATE_END_CXX

core::string SqlServer::identity = "mssql";

IDBMS* SqlServer::dbmsInstance()
{
    return new SqlServer;
}

SqlServer::SqlServer()
{
    NNTDECL_PRIVATE_CONSTRUCT(SqlServer);
}

SqlServer::~SqlServer()
{
    NNTDECL_PRIVATE_DESTROY();
}

bool SqlServer::connect(connection_info const& info)
{    
# ifdef _FREETDS
    RETCODE sta;
    LOGINREC* login = dblogin();
    
    sta = DBSETLUSER(login, info.user.c_str());
    if (sta == FAIL)
        return false;
    
    sta = DBSETLPWD(login, info.passwd.c_str());
    if (sta == FAIL)
        return false;
    
    DBPROCESS* proc = dbopen(login, info.url.c_str());
    if (proc == NULL)
        return false;
    
    sta = dbuse(proc, info.database.c_str());
    if (sta == FAIL)
        return false;
    
    d_ptr->proc = proc;
    
# endif

# ifdef _MSSQL

	_ConnectionPtr conn;
	HRESULT sta = conn.CreateInstance(__uuidof(Connection));
	if (FAILED(sta)) 
	{
		MessageBox(NULL, _W("failed to instance a new connection."), NULL, MB_OK);
		return false;
	}

	core::stringstream ss;
	ss << "Driver={SQL Server};" <<
		"Server=" << info.url << ";" << 
		"Database=" << info.database << ";" <<
		"UID=" << info.user << ";" <<
		"PWD=" << info.passwd << ";";
	core::string str_conn = ss.str();

	try
	{
		sta = conn->Open(str_conn.c_str(), "", "", adModeUnknown);
	}
	catch (_com_error& NNTDEBUG_EXPRESS(er))
	{
		trace_msg((char const*)er.ErrorMessage());
		return false;
	}
	catch (...)
	{
		trace_msg("failed to open database.");
		return false;
	}

	this->close();
	d_ptr->conn = conn;
 
# endif
    
    return true;
}

void SqlServer::close()
{
# ifdef _FREETDS
    if (d_ptr->proc)
    {
        dbclose(d_ptr->proc);
        d_ptr->proc = NULL;
    }
# endif

# ifdef _MSSQL
	if (d_ptr->conn && d_ptr->conn->State == adStateOpen)
	{
		d_ptr->conn->Close();
	}
# endif
}

DBMSqlDatatable* SqlServer::exec(const core::string &sql)
{
    MSSqlDatatable* dt = NULL;
    
# ifdef _FREETDS
    
    RETCODE sta = dbcmd(d_ptr->proc, sql.c_str());
    if (sta == FAIL)
        return NULL;
    
    sta = dbsqlexec(d_ptr->proc);
    if (sta == FAIL)
        return NULL;
    
    sta = dbresults(d_ptr->proc);    
    if (sta == NO_MORE_RESULTS)
        return NULL;   
    
    while (0 == dbrows(d_ptr->proc) && \
           FAIL == dbresults(d_ptr->proc));                    
    
    dt = new MSSqlDatatable(d_ptr->proc);
    dt->update();
    
    MSSqlDatatable* prev_ = dt;
    while (SUCCEED == (sta = dbresults(d_ptr->proc)))
    {
        MSSqlDatatable* next_dt = new MSSqlDatatable(d_ptr->proc);
        next_dt->update();
        
        prev_->next = next_dt;
        next_dt->prev = prev_;
        prev_ = next_dt;
    }
    
# endif

# ifdef _MSSQL

	_RecordsetPtr rcdset;
	try
	{
		rcdset.CreateInstance(__uuidof(Recordset));
		rcdset->Open(sql.c_str(), _variant_t((IDispatch*)d_ptr->conn, true), adOpenStatic, adLockOptimistic, adCmdText);
	}
	catch (_com_error& err)
	{
		_bstr_t msg = err.ErrorMessage();
		trace_msg((char const*)msg);
		return NULL;
	}
	catch (...)
	{
		trace_msg("failed to execute sql.");
		return NULL;
	}

	if (rcdset->adoEOF)
		return NULL;

	dt = new MSSqlDatatable(rcdset);
	dt->update();

# endif
    
    return dt;
}

static int mssql_field_type(variant_t const& var)
{
# ifdef _FREETDS
    int ret = SQLINT4;
    switch (var.vt)
    {
        default: break;
        case variant_t::VT_SIGNEDCHAR: case variant_t::VT_UNSIGNEDCHAR:
            ret = SQLINT1; break;
        case variant_t::VT_SIGNEDSHORT: case variant_t::VT_UNSIGNEDSHORT:
            ret = SQLINT2; break;
        case variant_t::VT_SIGNEDINT: case variant_t::VT_UNSIGNEDINT:
        case variant_t::VT_SIGNEDLONG: case variant_t::VT_UNSIGNEDLONG:
            ret = SQLINT4; break;
        case variant_t::VT_FLOAT:
            ret = SQLFLT4; break;
        case variant_t::VT_DOUBLE:
            ret = SQLFLT8; break;
        case variant_t::VT_PCHAR:
            ret = SQLVARCHAR; break;
        case variant_t::VT_DATA:
            ret = SQLVARBINARY; break;
    }
    return ret;
# endif

# ifdef _MSSQL
	int ret = VT_I4;
	switch (var.vt)
	{
	default: break;
	case variant_t::VT_SIGNEDCHAR: case variant_t::VT_UNSIGNEDCHAR:
		ret = VT_I1; break;
	case variant_t::VT_SIGNEDSHORT: case variant_t::VT_UNSIGNEDSHORT:
		ret = VT_I2; break;
	case variant_t::VT_SIGNEDINT: case variant_t::VT_UNSIGNEDINT:
	case variant_t::VT_SIGNEDLONG: case variant_t::VT_UNSIGNEDLONG:
		ret = VT_I4; break;
	case variant_t::VT_FLOAT:
		ret = VT_R4; break;
	case variant_t::VT_DOUBLE:
		ret = VT_R8; break;
	case variant_t::VT_PCHAR:
		ret = VT_LPSTR; break;
	case variant_t::VT_DATA:
		ret = VT_ARRAY; break;
	}
	return ret;
# endif
}

static core::string mssql_field_decl(variant_t const& var)
{
# ifdef _FREETDS
    int type = mssql_field_type(var);
    core::string str;
    switch (type)
    {
        default: break;
        case SQLINT1: str = "char(1)"; break;
        case SQLINT2: str = "tinyint"; break;
        case SQLINT4: str = "int"; break;
        case SQLFLT4: str = "float"; break;
        case SQLFLT8: str = "real"; break;
        case SQLVARCHAR: str = "varchar(" + core::tostr(var.size()) + ")"; break;
        case SQLVARBINARY: str = "varbinary(" + core::tostr(var.size()) + ")"; break;
    }
    return str;
# endif

# ifdef _MSSQL
	int type = mssql_field_type(var);
	core::string str;
	switch (type)
	{
	default: break;
	case VT_I1: str = "char(1)"; break;
	case VT_I2: str = "tinyint"; break;
	case VT_I4: str = "int"; break;
	case VT_R4: str = "float"; break;
	case VT_R8: str = "real"; break;
	case VT_LPSTR: str = "varchar(" + core::tostr(var.size()) + ")"; break;
	case VT_ARRAY: str = "varbinary(" + core::tostr(var.size()) + ")"; break;
	}
	return str;
# endif
}

DBMSqlDatatable* SqlServer::exec(const core::string &sql, const params_type &params)
{
    if (params.size() == 0)
        return this->exec(sql);
    
    core::vector<core::string> str_decls; str_decls.resize(params.size());
    core::vector<core::string> str_sets; str_sets.resize(params.size());
    
    for (core::counter<params_type::const_iterator> each = params.begin();
         each != params.end();
         ++each)
    {
        core::string const& name = each->first;
		variant_t const& var = each->second;
        
        core::string sep;
		if (var.vt == variant_t::VT_PCHAR ||
            var.vt == variant_t::VT_DATA)
            sep = "'";
        
        str_decls[each.count] = "@" + name + " " + mssql_field_decl(var);
        str_sets[each.count] = "@" + name + "=" + sep + core::tostr(var) + sep;
    }
    
    core::string str_decl = core::combine<core::string>(str_decls, ",");
    core::string str_set = core::combine<core::string>(str_sets, ",");
    core::string str_sql = "DECLARE " + str_decl + ";";
    str_sql += "EXECUTE sp_executesql N'" + sql + "',";
    str_sql += "N'" + str_decl + "',";
    str_sql += str_set + ";";
    
    //str_sql = "DECLARE @id int; SET @id = 1;EXECUTE sp_executesql N'SELECT * FROM TEST WHERE ID = @id', N'@id int', @id;";
    //trace_msg(str_sql);
    
    return this->exec(str_sql);
}

MSSqlDatatable::MSSqlDatatable(void* proc)
: _proc(proc)
{
# ifdef _MSSQL
	_proc = new _RecordsetPtr((IUnknown*)proc);
# endif
}

MSSqlDatatable::~MSSqlDatatable()
{
# ifdef _MSSQL
	delete (_RecordsetPtr*)_proc;
# endif
}

void MSSqlDatatable::update()
{
    // clear.
    this->clear();
    
# ifdef _FREETDS
    
    DBPROCESS* proc = (DBPROCESS*)_proc;
    
    // update.
    uint const ncols = dbnumcols(proc); 
    
    struct COL 						
    { 
        char *name; 
        char *buffer; 
        int type, size, status; 
    } *columns, *pcol;
    
    if ((columns = (COL*)calloc(ncols, sizeof(struct COL))) == NULL) {
        return;
    }
    
    RETCODE sta = 0;
    
    rows_type& rows = this->_rows;
    cols_type& cols = this->_cols;
    cols.resize(ncols);        
    
    //Read metadata and bind.  
    for (pcol = columns; pcol - columns < ncols; pcol++) {
        int c = (int)(pcol - columns + 1);
        
        pcol->name = dbcolname(proc, c);		
        pcol->type = dbcoltype(proc, c);
        pcol->size = dbcollen(proc, c);
        
        // add cols.
        cols[c - 1] = new variant_t(pcol->name, core::copy);
        
        if (SYBCHAR != pcol->type) {			
            pcol->size = dbwillconvert(pcol->type, SYBCHAR);
        }        
        
        if ((pcol->buffer = (char*)calloc(1, pcol->size + 1)) == NULL){
            break;
        }
        
        sta = dbbind(proc,
                     c,
                     NTBSTRINGBIND,	
                     pcol->size + 1,
                     (byte*)pcol->buffer);
        if (sta == FAIL) {
            break;
        }
        sta = dbnullbind(proc, 
                         c,
                         &pcol->status);	
        if (sta == FAIL) {
            break;
        }
    }
    
    // Get rows.
    while ((sta = dbnextrow(proc)) != NO_MORE_ROWS){	
        switch (sta) {
			case REG_ROW:
            {
                DBMSqlDatatable::row_type *row = new DBMSqlDatatable::row_type;
                row->resize(ncols);
                
				for (pcol=columns; pcol - columns < ncols; ++pcol) 
                {
                    int c = (int)(pcol - columns + 1);
					char const* buffer = pcol->status == -1 ? "" : pcol->buffer;
                    (*row)[c - 1] = new variant_t(buffer, core::copy);
				}
                
                rows.push_back(row);
            } break;
        }                
    }
    
    /* free metadata and data buffers */
    for (pcol=columns; pcol - columns < ncols; pcol++) {
        free(pcol->buffer);
    }
    free(columns);
    
# endif

# ifdef _MSSQL
	_RecordsetPtr& rcdset = *((_RecordsetPtr*)_proc);

	usize const ncols = (usize const)rcdset->Fields->GetCount();

	rows_type& rows = this->_rows;
	cols_type& cols = this->_cols;
	cols.resize(ncols);	

	// read cols.
	for (uint idx = 0; idx < ncols; ++idx)
	{
# ifdef NNT_DEBUG
		try {
# endif

		_bstr_t name = rcdset->Fields->GetItem((long)idx)->GetName();
		cols[idx] = new variant_t((char const*)name, core::copy);

# ifdef NNT_DEBUG
		} catch (_com_error& err) 	{
			_bstr_t msg = err.ErrorMessage();
			trace_msg((char const*)msg);
		}
# endif
	}

	// read rows.
	while (!rcdset->adoEOF)
	{
		row_type* row = new row_type;
		row->resize(ncols);

		for (uindex idx = 0; idx < ncols; ++idx)
		{
# ifdef NNT_DEBUG
			try {
# endif

			_bstr_t val = rcdset->GetCollect((long)idx);
			(*row)[idx] = new variant_t((char const*)val, core::copy);

# ifdef NNT_DEBUG
			} catch (_com_error& err) 	{
				_bstr_t msg = err.ErrorMessage();
				trace_msg((char const*)msg);
			}
# endif
		}

		rows.push_back(row);

		rcdset->MoveNext();
	}

# endif

}

core::string SqlServer::urlize(connection_info const& info) const
{
    static ::boost::regex re_ip("(\\S+):(\\d+)");
    static ::boost::regex re_ipd("(\\S+),(\\d+)");
    static ::boost::regex re_in("(\\S+)(?:[/\\\\])(\\S+)");
    core::string const& url = info.url;
    core::string ret;
    ::boost::match_results<core::string::const_iterator> wh;
    if ((true == ::boost::regex_match(url.begin(), url.end(), wh, re_ip)) ||
        (true == ::boost::regex_match(url.begin(), url.end(), wh, re_ipd)))
    {
# ifdef _FREETDS
        ret = wh[1].str() + ":" + wh[2].str();
# else
        ret = wh[1].str() + "," + wh[2].str();
# endif
    }
    else if (true == ::boost::regex_match(url.begin(), url.end(), wh, re_in))
    {
        ret = wh[1].str() + "/" + wh[2].str();
    }
    else
    {
# ifdef _FREETDS
        ret = url + ":1433";
# else
        ret = url + ",1433";
# endif
    }
    return ret;
}

NNT_BEGIN_NS(test)

bool Mssql::prepare()
{
	_db = new store::SqlServer;
	return true;
}

void Mssql::collect()
{
	safe_delete(_db);
}

bool Mssql::run()
{
	store::connection_info info;
	info.url = "127.0.0.1";
	core::string str = _db->urlize(info);
# ifdef _FREETDS
	assert("127.0.0.1:1433" == str);
# else
	assert("127.0.0.1,1433" == str);
# endif
	step();

	info.url = "127.0.0.1:1433";
	str = _db->urlize(info);
# ifdef _FREETDS
	assert("127.0.0.1:1433" == str);
# else
	assert("127.0.0.1,1433" == str);
# endif
	step();

	info.url = "127.0.0.1,1433";
	str = _db->urlize(info);
# ifdef _FREETDS
	assert("127.0.0.1:1433" == str);
# else
	assert("127.0.0.1,1433" == str);
# endif
	step();

	info.url = "127.0.0.1/instance";
	str = _db->urlize(info);
	assert("127.0.0.1/instance" == str);
	step();

	return true;
}

NNT_END_NS

NNT_END_NS 
NNT_END_CXX

NNT_BEGIN_C

::nnt::store::test::Mssql* UTMssql()
{
	return new ::nnt::store::test::Mssql;
}

NNT_END_C
