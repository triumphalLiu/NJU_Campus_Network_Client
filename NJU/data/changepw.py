import requests
import re
import codecs  
import time
data = {}

req_url = 'http://p.nju.edu.cn/portal_io/selfservice/userinfo/modifypassword'
new_filename = 'data/pw.nju'
old_filename = 'data/old_pw.nju'
change_filename = 'data/change.nju'

s = requests.session()

def init(filename): 
	fh = open(filename, 'w') 
	fh.close() 	
	
def save_chn(filename, contents): 
	fh = codecs.open(filename, 'a', 'utf-8') 
	fh.write(contents) 
	fh.close() 
	
def send():
	r = s.post(req_url, data)
	temp = r.text
	items = re.findall('reply_msg":"(.*?)",', temp)
	for item in items:
		to_save = item
		if to_save == "操作成功":
			save_chn(change_filename,"successful")
			save_chn(change_filename,'\n')
		else:
			save_chn(change_filename,"failed")
			save_chn(change_filename,'\n')

def getdata():
	f = open(old_filename, "r")	
	line = f.readline() 
	line = line.strip()
	temp = line
	data['oldpassword']=temp
	f.close()
	f = open(new_filename, "r")		
	line = f.readline()
	line = line.strip()
	temp = line
	data['newpassword']=temp	
	data['confirmpassword']=temp
	f.close()

init(change_filename)
getdata()
send()