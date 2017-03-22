import requests
import re
import codecs  
import time
data = {}

login_url = 'http://p.nju.edu.cn/portal_io/login'  
logout_url = 'http://p.nju.edu.cn/portal_io/logout'
info_url = 'http://p.nju.edu.cn/portal_io/selfservice/userinfo/getlist'
time_url = 'http://p.nju.edu.cn//portal_io/selfservice/volume/getlist'
info_filename = 'info.txt'
user_filename = 'username.txt'
pass_filename = 'password.txt'
s = requests.session()


def init(filename): 
	fh = open(filename, 'w') 
	fh.close() 	
	
def save_chn(filename, contents): 
	fh = codecs.open(filename, 'a', 'utf-8') 
	fh.write(contents) 
	fh.close() 
	
def login(url):
	s.post(url, data)
	
def logout(url):
	s.post(url)

def getinfo(url):
	r = s.get(url)
	temp = r.text
	items = re.findall('reply_msg":"(.*?)",', temp)
	for item in items:
		to_save = item
		if to_save == "操作成功":
			save_chn(info_filename,'successful\n')
		else :
			save_chn(info_filename,'failed\n')
	items = re.findall('total":(.*?),', temp)
	for item in items:
		to_save = item
		save_chn(info_filename,to_save)
		save_chn(info_filename,'\n')
	items = re.findall('account_balance":(.*?),', temp)
	for item in items:
		to_save = item
		save_chn(info_filename,to_save)
		save_chn(info_filename,'\n')
	items = re.findall('username":"(.*?)",', temp)
	for item in items:
		to_save = item
		save_chn(info_filename,to_save)
		save_chn(info_filename,'\n')
	#get login time
	r = s.get(time_url)
	temp = r.text
	items = re.findall('total_time":(.*?),', temp)
	for item in items:
		to_save = item
		save_chn(info_filename,to_save)
		save_chn(info_filename,'\n')

def getdata():
	f = open(user_filename, "r")	
	line = f.readline() 
	line = line.strip()
	temp = line
	data['username']=temp
	f.close()
	f = open(pass_filename, "r")	
	line = f.readline() 
	line = line.strip()
	temp = line
	data['password']=temp
	f.close()
	#print(data['username']) 
	#print(data['password'])

init(info_filename)
getdata()
login(login_url)
time.sleep(2)
getinfo(info_url)