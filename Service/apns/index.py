from mod_python import apache
import os
import _mysql
import base64
import socket
import ssl
import json

def index():
    return apache.OK

def echo(req, msg):
    return msg

def add(req, dt):
    db = _mysql.connect(host="127.0.0.1",user="root",passwd="root",db="apns.wsi")
    db.query("""select * from tokens where token='""" + dt + """'""")
    r = db.store_result()
    if (r.num_rows() != 0):
        db.close()
        return apache.OK
    db.query("""insert into tokens (`token`) values ('""" + dt + """')""")
    db.close()
    return apache.OK

def push(req, msg, token):
    cert = os.path.dirname(req.filename)
    cert = cert + "/cert/aps_dev.pem"
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    ssls = ssl.wrap_socket(s, certfile=cert)
    ssls.connect(("gateway.sandbox.push.apple.com", 2195))
    token = base64.b64decode(token)
    msg = json.dumps({"aps":{"alert":msg, "addition":"test"}})
    data = "\0\0 " + token + '\0' + chr(len(msg)) + msg
    ssls.write(data)
    ssls.close()
    return apache.OK

def pushall(req, msg):
    db = _mysql.connect(host="127.0.0.1",user="root",passwd="root",db="apns.wsi")
    db.query("""select token from tokens""")
    r = db.store_result()
    for i in range(r.num_rows()):
        d = r.fetch_row()
        push(req, msg, d[0][0])
    db.close()
    return apache.OK
