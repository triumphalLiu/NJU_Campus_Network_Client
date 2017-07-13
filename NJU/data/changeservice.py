import requests
import re
import codecs  
import time

req_url = 'http://p.nju.edu.cn/portal_io/selfservice/userinfo/modifyservice'
change_filename = 'data/change.nju'
num_filename = 'data/service.nju'
data = {}
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
	f = open(num_filename, "r")	
	line = f.readline() 
	line = line.strip()
	temp = line
	data['service_id[]']=str.split(temp)
	print(data['service_id[]'])

init(change_filename)
getdata()
send()