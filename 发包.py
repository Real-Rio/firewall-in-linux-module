'''
Author: Rio
Date: 2022-09-02 12:54:14
LastEditTime: 2022-09-02 12:58:42
FilePath: /firewall-in-linux-module/发包.py
Description: 
'''
import scapy
from scapy.all import *

# 1.创建一个IP包
ip = IP(dst="47.98.203.252")
# 2.创建一个TCP包
tcp = TCP(dport=3344)
# 3.创建一个数据包
data = "GET / HTTP/1.1\r"
# 4.发送数据包
send(ip/tcp/data)
