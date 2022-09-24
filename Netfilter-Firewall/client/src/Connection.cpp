/*
 * @Author: Rio
 * @Date: 2022-09-21 20:41:16
 * @LastEditTime: 2022-09-21 20:56:24
 * @FilePath: /firewall-in-linux-module/Netfilter-Firewall/client/src/Connection.cpp
 * @Description:
 */
#include "head.h"
#include <iostream>
#include <string>

Connection::Connection(char *data, int offset)
{
    src_ip = byteToInt(data, offset);
    dst_ip = byteToInt(data, offset + 4);
    src_port = byteToInt(data, offset + 8);
    dst_port = byteToInt(data, offset + 12);
    protocol = byteToInt(data, offset + 16);
    time = byteToInt(data, offset + 20);
}

void Connection::print()
{
    std::string ret;

    ret += "src_ip:" + ipToStr(src_ip) + "\t";
    ret += "dst_ip:" + ipToStr(dst_ip) + "\t";
    ret += "src_port:" + std::to_string(src_port) + "\t";
    ret += "dst_port:" + std::to_string(dst_port) + "\t";
    ret += "protocol:" + ptcToStr(protocol) + "\t";
    ret += "time:" + std::to_string(time) + "\n";

    std::cout << ret;
}
